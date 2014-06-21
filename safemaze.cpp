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
	if(pthread_mutex_init(&m_mutex, NULL))
	{
		std::cout << "mutex init error." << std::endl;
		return -1;
	}

	if(uiX < MIN_X || uiY < MIN_Y)
	{
		std::cout << "size error" << std::endl;
		return -1;
	}

	m_uiX = uiX;
	m_uiY = uiY;
	m_ppMazeArch = (char**)malloc(uiY * sizeof(char*));
	m_ppObjsPos = (long**)malloc(uiY * sizeof(long*));
	if(m_ppMazeArch == NULL)
	{
		std::cout << "memory error" << std::endl;
		return -1;
	}

	if(m_pIMazeInterface->GenerateMaze(m_ppMazeArch, m_ppObjsPos, uiX, uiY, 0))
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
	m_pIMazeInterface->DisplayMaze(m_ppMazeArch, m_ppObjsPos, m_uiX, m_uiY);
}

int SafeMaze::SetExplorer(const int& idx, Explorer* pExplorer)
{
	if(idx < 0 || idx >= 4)
	{
		return 1;
	}
	else if(m_szpExplorers[idx] != 0)
	{
		return 2;
	}
	
	m_szpExplorers[idx] = pExplorer;
	switch(idx)
	{
	case 0:
		m_ppObjsPos[0][0] = (long)pExplorer;
		break;
	case 1:
		m_ppObjsPos[0][m_uiX - 1] = (long)pExplorer;
		break;
	case 2:
		m_ppObjsPos[m_uiY - 1][0] = (long)pExplorer;
		break;
	case 3:
		m_ppObjsPos[m_uiY - 1][m_uiX - 1] = (long)pExplorer;
		break;
	}
	return 0;
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

bool SafeMaze::TestObjsPosAllZero()
{
	for(unsigned int i = 0; i < m_uiX; i++)
	{
		for(unsigned int j = 0; j < m_uiY; j++)
		{
			if(m_ppObjsPos[j][i] != 0)
			{
				std::cout << "x: " << i << " y: " << j << " is not zero" << std::endl;
				return false;
			}
		}
	}
	return true;
} 

bool SafeMaze::TestMazeExplrNull()
{
	for(int i = 0; i < 4; i ++)
	{
		if(m_szpExplorers[i] != NULL)
		{
			std::cout << "i: " << i << "not null" << std::endl;
			return false;
		}
	}
	return true;
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
