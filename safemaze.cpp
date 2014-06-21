#include "safemaze.h"

SafeMaze::SafeMaze(IMazeInterface* pIMazeInterface) :
m_pIMazeInterface(pIMazeInterface),
m_ppMazeArch(0),
m_uiX(0),
m_uiY(0)
{

}

SafeMaze::~SafeMaze()
{
	delete m_ppMazeArch;
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
	m_ppMazeArch = (char**)malloc(uiY * sizeof(char*));
	if(m_ppMazeArch == NULL)
	{
		std::cout << "memory error" << std::endl;
		return -1;
	}

	if(m_pIMazeInterface->GenerateMaze(m_ppMazeArch, uiX, uiY, 0))
	{
		std::cout << "memory error in generate maze" << std::endl;
		return -1;
	}

	m_ppMazeArch[0][0] = 0;
	m_ppMazeArch[m_uiY - 1][0] = 0;
	m_ppMazeArch[0][m_uiX - 1] = 0;
	m_ppMazeArch[m_uiY - 1][m_uiX - 1] = 0;
	return 0;
}

int SafeMaze::StartExplore()
{

	return 0;
}

void SafeMaze::Display()
{
	m_pIMazeInterface->DisplayMaze(m_ppMazeArch, m_uiX, m_uiY);
}

bool SafeMaze::TestMazeValIsBinary()
{
	for(unsigned int i = 0; i < m_uiX; i++)
	{
		for(unsigned int j = 0; j < m_uiY; j++)
		{
			if(m_ppMazeArch[j][i] != 1 && m_ppMazeArch[j][i] != 0)
			{
				std::cout << "Do not pass binary test" << std::endl;
				return false;
			}
		}
	}

	std::cout << "Binary test passed" << std::endl;
	return true;
}

bool SafeMaze::TestMazeCornValIsZero()
{
	return m_ppMazeArch[0][0] == 0 && 
		   m_ppMazeArch[m_uiY - 1][0] == 0 &&
		   m_ppMazeArch[0][m_uiX - 1] == 0 &&
		   m_ppMazeArch[m_uiY - 1][m_uiX - 1] == 0;
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
