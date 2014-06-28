#include "mazenet.h"


MazeNet::MazeNet() :
m_sLsnSocket(-1),
m_epSocket(-1),
m_usLsnPort(0),
m_uIConcurrentNum(1024)
{

}

MazeNet::~MazeNet()
{


}

int MazeNet::InitNet(const unsigned short& usLsnPort, TextLog* pTextLog)
{
	m_usLsnPort = usLsnPort;
	m_sLsnSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(m_sLsnSocket == -1)
	{
		pTextLog("MazeExploer Init Socket Error");
		return -1;
	}

	unsigned int uiReuseAddr = 1;
	setsockopt(m_sLsnSocket, SOL_SOCKET, SO_REUSEADDR, (char*)uiReuseAddr, sizeof(uiReuseAddr));



	return 0;
}
