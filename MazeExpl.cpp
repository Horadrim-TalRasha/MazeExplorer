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
	Explorer* pExplorer = new Explorer();

	//	初始化对象
	if(pSafeMaze->InitMaze(16, 32))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		return -1;
	}

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
	if(!((SafeMaze*)pSafeMaze)->TestObjsPosAllZero())
	{
		std::cout << "Maze Objs Pos is not all zero" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test Objs Pos is all zero passed" << std::endl;
	}

	if(!((SafeMaze*)pSafeMaze)->TestMazeExplrNull())
	{
		std::cout << "Test Explr is not all null passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test Explr is all null passed" << std::endl;
	}

	if(!((SafeMaze*)pSafeMaze)->TestMutex())
	{
		std::cout << "Test mutex not passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test mutex passed" << std::endl;
	}

	if(((SafeMaze*)pSafeMaze)->SetExplorer(3, pExplorer))
	{
		std::cout << "Set Explorer failed" << std::endl;
		return 1;
	}

	if(!((SafeMaze*)pSafeMaze)->TestExplrInPos())
	{
		std::cout << "Test Explr In Pos not passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test Explr In Pos passed" << std::endl;
	}

	((SafeMaze*)pSafeMaze)->StartExplore();
	while(1)
	{
		sleep(3);
		((SafeMaze*)pSafeMaze)->Display();
	}
	return 0;
}
