#include "safemaze.h"
#include "safemazeinterface.h"
#include "explorer.h"
#include "TextLog.h"

pthread_mutex_t deadlock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv)
{
	srand(time(NULL));

	IMazeInterface* pSafeMazeInterface = new SafeMazeInterface();
	AbsMaze* pSafeMaze = new SafeMaze(pSafeMazeInterface);
	if(pSafeMaze->InitMaze(32, 16))
	{
		delete pSafeMaze;
		pSafeMaze = 0;
		delete pSafeMazeInterface;
		pSafeMazeInterface = 0;
	}

	((SafeMaze*)pSafeMaze)->StartNetServ();
	pthread_mutex_lock(&deadlock);
	pthread_mutex_lock(&deadlock);
	return 0;
}
