#ifndef SAFE_MAZE_INTERFACE_H
#define SAFE_MAZE_INTERFACE_H

#include "imazeinterface.h"

class SafeMazeInterface : public IMazeInterface
{
public:
	SafeMazeInterface();
	int GenerateMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY);
	int DisplayMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY);
	void ChangeArch();
	void PutMonsterIn();


};


#endif
