#ifndef IMAZE_INTERFACE
#define IMAZE_INTERFACE

#include <iostream>
#include <string.h>

class IMazeInterface
{
public:
	
protected:
	virtual void GenterateMaze() = 0;
	virtual	void ChangeArch() = 0;
	virtual void PutMonsterIn() = 0;
};

#endif
