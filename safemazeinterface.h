#ifndef SAFE_MAZE_INTERFACE_H
#define SAFE_MAZE_INTERFACE_H

#include "imazeinterface.h"
#include "TextLog.h"


class SafeMazeInterface : public IMazeInterface
{
public:
	SafeMazeInterface();
	int GenerateMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY);
	int GenerateEmptyMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY);
	int DisplayMaze(char** ppMazeArch, long** ppObjsPos, const unsigned int& uiX, const unsigned int& uiY);
	void ChangeArch();
	void PutMonsterIn();

private:
	const unsigned char m_ucThrShldValueOfMazeArch;
	const unsigned char m_ucMazeArchFactor;
};


#endif
