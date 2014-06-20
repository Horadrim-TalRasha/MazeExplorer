#include "safemaze.h"
#include "safemazeinterface.h"


int main(int argc, char** argv)
{
	char** pp = (char**)malloc(sizeof(char*) * 2);

	for(int i = 0; i < 16; i++)
	{
		char* p = 
	}

	//	设置随机数种子
	srand(time(NULL));

	//	构造对象
	IMazeInterface* pSafeMazeInterface = new SafeMazeInterface();
	AbsMaze* pSafeMaze = new SafeMaze(pSafeMazeInterface);

	//	初始化对象
	if(pSafeMaze->InitMaze(16, 16))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		return -1;
	}

	return 0;
}
