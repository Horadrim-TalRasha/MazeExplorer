#ifndef ABS_MAZE
#define ABS_MAZE

#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MIN_X 15
#define MIN_Y 15

class AbsMaze
{
public:
	virtual int InitMaze(const unsigned int& uiX, const unsigned int& uiY) = 0;
	virtual int StartExplore() = 0;



};

#endif
