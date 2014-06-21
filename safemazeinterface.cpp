#include "safemazeinterface.h"


SafeMazeInterface::SafeMazeInterface() :
m_ucThrShldValueOfMazeArch(4),
m_ucMazeArchFactor(10)
{

}

int SafeMazeInterface::GenerateMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY)
{
	if(uiCurY >= uiY)
		return 0;

	char* pLandScale = (char*)malloc(uiX);
	if(pLandScale == NULL)
	{
		return 1;
	}

	for(unsigned int i = 0; i < uiX; i++)
	{
		pLandScale[i] = ((random() % m_ucMazeArchFactor < 4) ? 1 : 0);
	}

	ppMazeArch[uiCurY] = pLandScale;
	if(GenerateMaze(ppMazeArch, uiX, uiY, uiCurY + 1))
	{
		delete pLandScale;
		pLandScale = 0;
		return 1;
	}
	return 0;
}

int SafeMazeInterface::DisplayMaze(char** ppMazeArch, const unsigned int& uiX, const unsigned int& uiY)
{
	for(unsigned int i = 0; i < uiX; i++)
	{
		for(unsigned int j = 0; j < uiY; j++)
		{
			if(ppMazeArch[j][i])
				std::cout << (char)182;
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
