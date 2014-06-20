#ifndef SAFE_MAZE
#define SAFE_MAZE


#include "absmaze.h"
#include "imazeinterface.h"


static const unsigned int g_uiThrshldOfMaze = 4;

class SafeMaze : public AbsMaze
{
public:
	SafeMaze(IMazeInterface* pIMazeInterface);
	int InitMaze(const unsigned int& uiX, const unsigned int& uiY);
	int StartExplore();
	void Display();

protected:
//	void GenerateMaze();
//	void ChangeArch();
//	void PutMonsterIn();


private:
	IMazeInterface* m_pIMazeInterface;
	char** m_ppMazeArch;
};

#endif
