#include "mazenet.h"


MazeNet::MazeNet() :
m_sLsnSocket(-1),
m_epSocket(-1),
m_usLsnPort(0),
m_uiConcurrentNum(1024),
m_uiMaxPacketSize(2048),
m_uiMinPacketSize(8)
{

}

MazeNet::~MazeNet()
{
	if(m_sLsnSocket != -1)
	{
		close(m_sLsnSocket);
		m_sLsnSocket = -1;
	}
	
	if(m_epSocket != -1)
	{
		close(m_epSocket);
		m_epSocket = -1;
	}
}

int MazeNet::InitNet(const unsigned short& usLsnPort, TextLog* pTextLog)
{
	if(m_uiMaxPacketSize <= 0 || m_uiMinPacketSize <=0)
	{
		pTextLog->Write("InitNet Max Packet Size(%d Bytes) Min Packet Size(%d Bytes) error!", m_uiMaxPacketSize, m_uiMinPacketSize);
		return -1;
	}

	m_usLsnPort = usLsnPort;
	m_sLsnSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sLsnSocket == -1)
	{
		pTextLog->Write("Init Socket Error! When InitNet");
		return -1;
	}

	unsigned int uiReuseAddr = 1;
	setsockopt(m_sLsnSocket, SOL_SOCKET, SO_REUSEADDR, (char*)uiReuseAddr, sizeof(uiReuseAddr));

	if(FileUtil::SetNoBlock(m_sLsnSocket))
	{
		pTextLog->Write("Set Socket to Nonblock Error! When InitNet");
		return -1;
	}

	sockaddr_in svrSockAddr;
	svrSockAddr.sin_family = AF_INET;
	svrSockAddr.sin_port = htons(m_usLsnPort);
	svrSockAddr.sin_addr.s_addr = INADDR_ANY;

	m_epSocket = epoll_create(m_uiConcurrentNum);
	if(m_epSocket == -1)
	{
		pTextLog->Write("epoll_create error! When InitNet");
		return -1;
	}

	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = m_sLsnSocket;
	if(epoll_ctl(m_epSocket, EPOLL_CTL_ADD, m_sLsnSocket, &ev) == -1)
	{
		pTextLog->Write("epoll_ctl_add error! when InitNet");
		return -1;
	}

	if(bind(m_sLsnSocket, (sockaddr*)&svrSockAddr, sizeof(svrSockAddr)) == -1)
	{
		pTextLog->Write("bind m_sLsnSocket error! when InitNet");
		return -1;
	}

	if(listen(m_sLsnSocket, 20) == -1)
	{
		pTextLog->Write("listen m_sLsnSocket error! when InitNet");
		return -1;
	}
	return 0;
}

int MazeNet::StartNetServ(TextLog* pTextLog)
{
	epoll_event evs[m_uiConcurrentNum];
	while(1)
	{
		sockaddr_in cliSockAddr;
		socklen_t iAddrLen = sizeof(sockaddr);

		int nfds = epoll_wait(m_epSocket, evs, m_uiConcurrentNum, -1);
		if(nfds < 1)
		{
			if(errno == EINTR)
			{
				pTextLog->Write("epoll_wait interrupted by signal.");
				continue;
			}
			pTextLog->Write("epoll_wait error: %s! when start net serv.", strerror(errno));
			return -1;
		}
		
		for(int i = 0; i < nfds; i++)
		{
			if(evs[i].data.fd == m_sLsnSocket)
			{
				int fd = accept(m_sLsnSocket, (sockaddr*)&cliSockAddr, &iAddrLen);
				if(fd == -1)
				{
					pTextLog->Write("accept error!");
					continue;
				}
				if(FileUtil::SetNoBlock(fd))
				{
					pTextLog->Write("set nonblock error, fd: %d, from: %s:%d", fd, inet_ntoa(cliSockAddr.sin_addr), ntohs(cliSockAddr.sin_port));
					close(fd);
					continue;
				}
				struct epoll_event ev;
				ev.data.fd = fd;
				ev.events = EPOLLIN | EPOLLET;
				if(epoll_ctl(m_epSocket, EPOLL_CTL_ADD, fd, &ev) == -1)
				{
					BreakConnect(fd);
					pTextLog->Write("epoll add socket error!");
					continue;
				}

				pTextLog->Write("add new connect, fd: %d, from: %s:%d", fd, inet_ntoa(cliSockAddr.sin_addr), ntohs(cliSockAddr.sin_port));
			}
			else if(evs[i].events & EPOLLIN)
			{
				struct sockaddr_in remoteSockAddr;
				unsigned int iRmtSockAddrLen = sizeof(sockaddr);
				getsockname(evs[i].data.fd, (sockaddr*)&remoteSockAddr, &iRmtSockAddrLen);
				char buff[m_uiMaxPacketSize];
				int ret = recv(evs[i].data.fd, buff, m_uiMaxPacketSize, MSG_NOSIGNAL);
				if(ret == 0 || ret > m_uiMaxPacketSize)
				{
					pTextLog->Write("client: %s:%d close socket or get exception size packet(%d bytes).", inet_ntoa(remoteSockAddr.sin_addr), ntohs(remoteSockAddr.sin_port), ret);
					BreakConnect(evs[i].data.fd);
					continue;
				}
				else if(ret > 0 && ret < m_uiMinPacketSize)
				{
					pTextLog->Write("clent: %s:%d send a packet size(%d bytes) smaller than uiMinPacketSize.", inet_ntoa(remoteSockAddr.sin_addr), ntohs(remoteSockAddr.sin_port), ret);
					BreakConnect(evs[i].data.fd);
					continue;
				}
				else if(ret == -1 && errno == EAGAIN)
				{
					continue;
				}
				else if(ret == -1)
				{
					pTextLog->Write("client: %s:%d recv error!", inet_ntoa(remoteSockAddr.sin_addr), ntohs(remoteSockAddr.sin_port));
					BreakConnect(evs[i].data.fd);
					continue;
				}
			}
		}
	}
}

void MazeNet::BreakConnect(const int& fd)
{
	struct epoll_event ev;
	epoll_ctl(m_epSocket, EPOLL_CTL_DEL, fd, &ev);
	close(fd);
}

