#include <unistd.h>
#include "safemaze.h"
#include "safemazeinterface.h"
#include "explorer.h"

int main(int argc, char** argv)
{
	//	设置随机数种子
	srand(time(NULL));

	//	构造对象
	IMazeInterface* pSafeMazeInterface = new SafeMazeInterface();
	AbsMaze* pSafeMaze = new SafeMaze(pSafeMazeInterface);

	//	初始化对象
	if(pSafeMaze->InitMaze(16, 32))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		return -1;
	}

	((SafeMaze*)pSafeMaze)->Display();
	((SafeMaze*)pSafeMaze)->TestMazeValIsBinary();
	if(!((SafeMaze*)pSafeMaze)->TestMazeCornValIsZero())
	{
		std::cout << "Maze corner value is not 0" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test maze corner value is zero passed" << std::endl;
	}

	return 0;
}
