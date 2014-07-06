#ifndef MAZE_NET_H
#define MAZE_NET_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "TextLog.h"
#include "FileUtil.h"


class MazeNet
{
public:
	MazeNet();
	virtual ~MazeNet();
	int InitNet(const unsigned short& usLsnPort, TextLog* pTextLog);
	int StartNetServ(TextLog* pTextLog);

protected:
	int m_sLsnSocket;
	int m_epSocket;
	unsigned short m_usLsnPort;
	const unsigned int m_uiConcurrentNum;
	const int m_uiMaxPacketSize;
	const int m_uiMinPacketSize;

protected:
	void BreakConnect(const int& iSocket);
	virtual bool CheckPack(const int& iPacketLen, char* szpBuff, TextLog* pTextLog);
	virtual int ProcPack(TextLog* pTextLog, char* szpBuff);

private:
};

#endif
