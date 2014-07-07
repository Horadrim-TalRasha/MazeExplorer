#include "safemaze.h"
#include "safemazeinterface.h"
#include "explorer.h"
#include "TextLog.h"

extern pthread_rwlock_t rwlock;
pthread_mutex_t deadlock = PTHREAD_MUTEX_INITIALIZER;
int main(int argc, char** argv)
{
	//	设置随机数种子
	srand(time(NULL));

	//	构造对象
	IMazeInterface* pSafeMazeInterface = new SafeMazeInterface();
	AbsMaze* pSafeMaze = new SafeMaze(pSafeMazeInterface);
	Explorer* pExplorer = new Explorer();
	//	初始化对象
#ifndef COMPETE_TEST
	if(pSafeMaze->InitMaze(32, 16))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		delete pExplorer;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		pExplorer = 0;
		return -1;
	}
#else
	if(pSafeMaze->InitEmptyMaze(32, 16))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		delete pExplorer;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		pExplorer = 0;
		return -1;
	}
#endif

#ifndef SKIP_TEST
/**
	if(((SafeMaze*)pSafeMaze)->TestIsPosInMaze(33, 24))
	{
		std::cout << "x:33, y:24 is not in maze, test failed" << std::endl;
		return 1;
	}

	if(!((SafeMaze*)pSafeMaze)->TestIsPosInMaze(2, 5))
	{
		std::cout << "x: 2, y: 5 is in maze, test faliled" << std::endl;
		return 1;
	}
**/

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

	if(!((SafeMaze*)pSafeMaze)->TestRWLock())
	{
		std::cout << "Test rwlock not passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test rwlock passed" << std::endl;
	}
#endif

#ifdef COMPETE_TEST
	Explorer* pExplr_1 = new Explorer();
	Explorer* pExplr_2 = new Explorer();
	Explorer* pExplr_3 = new Explorer();
	Explorer* pExplr_4 = new Explorer();

	if(((SafeMaze*)pSafeMaze)->SetExplorer(2, pExplr_1, 11, 10))
	{
		std::cout << "Set Explorer failed" << std::endl;
		return 1;
	}

	sleep(2);
	((SafeMaze*)pSafeMaze)->Display();
	if(((SafeMaze*)pSafeMaze)->SetExplorer(0, pExplr_3, 10, 11))
	{
		std::cout << "Set Explorer failed" << std::endl;
		return 1;
	}

	sleep(2);
	((SafeMaze*)pSafeMaze)->Display();
	if(((SafeMaze*)pSafeMaze)->SetExplorer(3, pExplr_2, 9, 10))
	{
		std::cout << "Set Explorer failed" << std::endl;
		return 1;
	}
	sleep(2);
	((SafeMaze*)pSafeMaze)->Display();
	if(((SafeMaze*)pSafeMaze)->SetExplorer(1, pExplr_4, 10, 9))
	{
		std::cout << "Set Explorer failed" << std::endl;
		return 1;
	}

	sleep(2);
	((SafeMaze*)pSafeMaze)->Display();
#else
	if(((SafeMaze*)pSafeMaze)->SetExplorer(3, pExplorer))
	{
		delete pSafeMaze;
		delete pSafeMazeInterface;
		delete pExplorer;
		pSafeMaze = 0;
		pSafeMazeInterface = 0;
		pExplorer = 0;
		return -1;	
	}

#endif

#ifndef SKIP_TEST

	if(!((SafeMaze*)pSafeMaze)->TestExplrInPos())
	{
		std::cout << "Test Explr In Pos not passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test Explr In Pos passed" << std::endl;
	}

#endif
	
	((SafeMaze*)pSafeMaze)->Display();

#ifdef COMPETE_TEST
	((SafeMaze*)pSafeMaze)->CompetePos();
	for(int i = 0; i < 10000000; i++);
		pthread_rwlock_unlock(&rwlock);

	sleep(5);
	
	((SafeMaze*)pSafeMaze)->Display();
	if(!((SafeMaze*)pSafeMaze)->TestExplrInPos())
	{
		std::cout << "Test Explr In Pos not passed" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "Test Explr In Pos passed" << std::endl;
	}
#else
	((SafeMaze*)pSafeMaze)->StartExplore();
#endif
//	((SafeMaze*)pSafeMaze)->StartNetServ();    // 此处起网络会出错
	pthread_mutex_lock(&deadlock);
	pthread_mutex_lock(&deadlock);
	return 0;
}
