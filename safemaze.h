#ifndef SAFE_MAZE
#define SAFE_MAZE


#include "absmaze.h"
#include "imazeinterface.h"


static const unsigned int g_uiThrshldOfMaze = 4;

class SafeMaze : public AbsMaze
{
public:
	SafeMaze(IMazeInterface* pIMazeInterface);
	virtual ~SafeMaze();
	int InitMaze(const unsigned int& uiX, const unsigned int& uiY);
	int StartExplore();
	void Display();
	
	//	测试代码
	bool TestMazeValIsBinary();				//	数组中的值只能为0和1
	bool TestMazeCornValIsZero();			//	迷宫四个角上的值都为0
protected:
//	void GenerateMaze();
//	void ChangeArch();
//	void PutMonsterIn();


private:
	IMazeInterface* m_pIMazeInterface;
	char** m_ppMazeArch;
	unsigned int m_uiX;
	unsigned int m_uiY;

	pthread_mutex_t m_mutex;
};

#endif
