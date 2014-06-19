#ifndef SAFE_MAZE
#define SAFE_MAZE


#include "absmaze.h"
#include "imazeinterface.h"

class SafeMaze : public IMazeInterface
{
public:
	SafeMaze(IMazeInterface* pIMazeInterface);

protected:
	void GenerateMaze();
	void ChangeArch();
	void PutMonsterIn();


private:
	IMazeInterface* m_pIMazeInterface;
};

#endif
