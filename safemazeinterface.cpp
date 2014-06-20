#include "safemazeinterface.h"


SafeMazeInterface::SafeMazeInterface() :
m_ucThrShldValueOfMazeArch(4)
{

}

int SafeMazeInterface::GenerateMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY)
{
	for(unsigned int i = 0; i < uiX; i++)
	{
		for(unsigned int j = 0; j < uiY; j++)
		{
			ppMazeArch[i][j] = (random() % 10) < m_ucThrShldValueOfMazeArch ? (char)1 : (char)0;
		}
	}	
	return 0;
}

int SafeMazeInterface::DisplayMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY)
{
	for(unsigned int i = 0; i < uiX; i++)
	{
		for(unsigned int j = 0; j < uiY; j++)
		{
			if(ppMazeArch[i][j])
				std::cout << '*';
			else
				std::cout << ' ';
		}
		std::cout << std::endl;
	}	
	return 0;
}

void SafeMazeInterface::ChangeArch()
{

}

void SafeMazeInterface::PutMonsterIn()
{


}
