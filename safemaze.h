#ifndef SAFE_MAZE
#define SAFE_MAZE


#include "absmaze.h"
#include "imazeinterface.h"


class SafeMaze : public AbsMaze
{
public:
	SafeMaze(IMazeInterface* pIMazeInterface);
	int InitMaze(const unsigned int& uiX, const unsigned int& uiY);
	int StartExplore();

protected:
	void GenerateMaze();
	void ChangeArch();
	void PutMonsterIn();


private:
	IMazeInterface* m_pIMazeInterface;
	char** m_ppMazeArch;
};

#endif
