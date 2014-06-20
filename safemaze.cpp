#include "safemaze.h"

SafeMaze::SafeMaze(IMazeInterface* pIMazeInterface) :
m_pIMazeInterface(pIMazeInterface),
m_ppMazeArch(0),
m_uiX(0),
m_uiY(0)
{

}

int SafeMaze::InitMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	if(uiX < MIN_X || uiY < MIN_Y)
	{
		std::cout << "size error" << std::endl;
		return -1;
	}

	m_uiX = uiX;
	m_uiY = uiY;
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

void SafeMaze::Display()
{
	m_pIMazeInterface->DisplayMaze(m_ppMazeArch, m_uiX, m_uiY);
}
/**
void SafeMaze::GenerateMaze()
{

}

void SafeMaze::ChangeArch()
{

}

void SafeMaze::PutMonsterIn()
{

}
**/
