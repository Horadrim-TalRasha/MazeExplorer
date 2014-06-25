#ifndef SAFE_MAZE
#define SAFE_MAZE


#include "absmaze.h"
#include "imazeinterface.h"
#include "explorer.h"

static const unsigned int g_uiThrshldOfMaze = 4;

class SafeMaze : public AbsMaze
{
public:
	SafeMaze(IMazeInterface* pIMazeInterface);
	virtual ~SafeMaze();
	int InitMaze(const unsigned int& uiX, const unsigned int& uiY);
	int StartExplore();
	void Display();
	int SetExplorer(const int& idx, Explorer* pExplr);
	int SetExplorer(const int& idx, Explorer* pExplr, const unsigned int& uiX, const unsigned int& uiY);
	
	//	测试代码
	bool TestMazeValIsBinary();				//	数组中的值只能为0和1
	bool TestMazeCornValIsZero();			//	迷宫四个角上的值都为0
	bool TestObjsPosAllZero();				//	探险者位置均为0
	bool TestMazeExplrNull();				//	探险者均不存在
//	bool TestMutex();						//	测试互斥锁
	bool TestExplrInPos();
	bool TestIsPosInMaze(const unsigned int& uiX, const unsigned int& uiY);
protected:
//	void GenerateMaze();
//	void ChangeArch();
//	void PutMonsterIn();


private:
	IMazeInterface* m_pIMazeInterface;

	char** m_ppMazeArch;
	long** m_ppObjsPos;
	unsigned int m_uiX;
	unsigned int m_uiY;
	const unsigned int m_uiSleepInterval;

	Explorer* m_szpExplorers[4];
	pthread_rwlock_t** m_ppObjsMutex;

private:
	static void* ExplrThrd(void* param);
	bool IsPosInMaze(const unsigned int& uiX, const unsigned int& uiY);
	int MoveExplorer(const unsigned int& uiX, const unsigned int& uiY, Explorer* pExplr);
};

#endif
