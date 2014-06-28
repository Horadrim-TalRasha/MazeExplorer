#ifndef MAZE_NET_H
#define MAZE_NET_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include "TextLog.h"
#include "FileUtil.h"


class MazeNet
{
public:
	MazeNet();
	virtual ~MazeNet();
	int InitNet(const unsigned short& usLsnPort, TextLog* pTextLog);

protected:
	int m_sLsnSocket;
	int m_epSocket;
	const unsigned int m_uiConcurrentNum;
	unsigned short m_usLsnPort;
};

#endif
