#ifndef IMAZE_INTERFACE
#define IMAZE_INTERFACE

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include "TextLog.h"

class IMazeInterface
{
public:
	virtual int GenerateMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY) = 0;
	virtual int GenerateEmptyMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY) = 0;
	virtual int DisplayMaze(char** ppMazeArch, long** ppObjsPos, const unsigned int& uiX, const unsigned int& uiY) = 0;
	virtual	void ChangeArch() = 0;
	virtual void PutMonsterIn() = 0;
	inline void SetTextLog(TextLog* pTextLog) {	m_pTextLog = pTextLog; }

protected:
	TextLog* m_pTextLog;
};

#endif
