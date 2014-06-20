#include "safemaze.h"

SafeMaze::SafeMaze(IMazeInterface* pIMazeInterface) :
m_pIMazeInterface(pIMazeInterface),
m_ppMazeArch(0)
{

}

int SafeMaze::InitMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	if(uiX < MIN_X || uiY < MIN_Y)
	{
		std::cout << "size error" << std::endl;
		return -1;
	}

	m_ppMazeArch = (char**)malloc(uiX * uiY);
	if(m_ppMazeArch == NULL)
	{
		std::cout << "memory error" << std::endl;
		return -1;
	}

	return m_pIMazeInterface->GenerateMaze(m_ppMazeArch, uiX, uiY);
}

int SafeMaze::StartExplore()
{

	return 0;
}

void SafeMaze::GenerateMaze()
{

}

void SafeMaze::ChangeArch()
{

}

void SafeMaze::PutMonsterIn()
{

}
