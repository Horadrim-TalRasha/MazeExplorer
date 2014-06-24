#ifndef ABS_POWER_H
#define ABS_POWER_H


#include <iostream>
#include <stdlib.h>

enum EPowerType
{
	E_Break_Wall = 0,
	E_Teleport,
	E_Attack_Mon,
	E_Powers
};

class AbsPower
{
public:
	virtual void ActivateInMaze(char** ppMazeArch) = 0;
};

#endif
