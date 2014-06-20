#ifndef IMAZE_INTERFACE
#define IMAZE_INTERFACE

#include <iostream>
#include <string.h>

class IMazeInterface
{
public:
	virtual int GenerateMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY) = 0;
	virtual int DisplayMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY) = 0;
	virtual	void ChangeArch() = 0;
	virtual void PutMonsterIn() = 0;
};

#endif