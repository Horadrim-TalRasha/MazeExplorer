#include "safemazeinterface.h"


SafeMazeInterface::SafeMazeInterface() :
m_ucThrShldValueOfMazeArch(4),
m_ucMazeArchFactor(10)
{

}

int SafeMazeInterface::GenerateMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY)
{
	if(uiCurY >= uiY)
		return 0;

	char* pLandScale = (char*)malloc(uiX);
	long* pLandScaleOfExplr = (long*)malloc(sizeof(long) * uiX);
	pthread_rwlock_t* pRwLock = (pthread_rwlock_t*)malloc(sizeof(pthread_rwlock_t) * uiX);
	memset(pLandScaleOfExplr, 0, sizeof(long) * uiX);
	memset(pLandScale, 0, uiX);

	if(pLandScale == NULL || pLandScaleOfExplr == NULL || pRwLock == NULL)
	{
		return 1;
	}

	for(unsigned int i = 0; i < uiX; i++)
	{
		pLandScale[i] = ((random() % m_ucMazeArchFactor < 4) ? 1 : 0);
		pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
		pRwLock[i] = rwlock;
	}

	ppMazeArch[uiCurY] = pLandScale;
	ppExplrPos[uiCurY] = pLandScaleOfExplr;
	ppRwLock[uiCurY] = pRwLock;
	if(GenerateMaze(ppMazeArch, ppExplrPos, ppRwLock, uiX, uiY, uiCurY + 1))
	{
		delete pLandScale;
		pLandScale = 0;
		delete pLandScaleOfExplr;
		pLandScaleOfExplr = 0;
		return 1;
	}
	return 0;
}

int SafeMazeInterface::GenerateEmptyMaze(char** ppMazeArch, long** ppExplrPos, pthread_rwlock_t** ppRwLock, const unsigned int& uiX, const unsigned int& uiY, const unsigned int& uiCurY)
{
	if(uiCurY >= uiY)
		return 0;

	char* pLandScale = (char*)malloc(uiX);
	long* pLandScaleOfExplr = (long*)malloc(sizeof(long) * uiX);
	pthread_rwlock_t* pRwLock = (pthread_rwlock_t*)malloc(sizeof(pthread_rwlock_t) * uiX);
	memset(pLandScaleOfExplr, 0, sizeof(long) * uiX);
	memset(pLandScale, 0, uiX);

	if(pLandScale == NULL || pLandScaleOfExplr == NULL || pRwLock == NULL)
	{
		return 1;
	}

	for(unsigned int i = 0; i < uiX; i++)
	{
		pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;
		pRwLock[i] = rwlock;
	}

	ppMazeArch[uiCurY] = pLandScale;
	ppExplrPos[uiCurY] = pLandScaleOfExplr;
	ppRwLock[uiCurY] = pRwLock;
	if(GenerateEmptyMaze(ppMazeArch, ppExplrPos, ppRwLock, uiX, uiY, uiCurY + 1))
	{
		delete pLandScale;
		pLandScale = 0;
		delete pLandScaleOfExplr;
		pLandScaleOfExplr = 0;
		return 1;
	}
	return 0;
}

int SafeMazeInterface::DisplayMaze(char** ppMazeArch, long** ppObjsPos, const unsigned int& uiX, const unsigned int& uiY)
{
	for(unsigned int i = 0; i < uiX; i++)
	{
		for(unsigned int j = 0; j < uiY; j++)
		{
			if(ppObjsPos[j][i] != 0)
				std::cout << '*';
			else if(ppMazeArch[j][i])
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
