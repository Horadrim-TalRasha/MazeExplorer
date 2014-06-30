#include "safemaze.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;


SafeMaze::SafeMaze(IMazeInterface* pIMazeInterface) :
m_pIMazeInterface(pIMazeInterface),
m_ppMazeArch(0),
m_uiX(0),
m_uiY(0),
m_uiSleepInterval(3)
{
	strcpy(m_cLogConfig.szpLogPath, "./logs");
	strcpy(m_cLogConfig.szpLogName, "maze_explorer_log");
	m_cLogConfig.u64LimitSize = 204800000;
	m_cLogConfig.uiExpiredDays = 5;
}

SafeMaze::~SafeMaze()
{
	m_cTextLog.Write("safemaze destroyed");
	for(unsigned int i = 0; i < m_uiY; i++)
	{
		char* pMazeArch = m_ppMazeArch[i];
		pthread_rwlock_t* pObjsMutex = m_ppObjsMutex[i];
		long* pObjsPos= m_ppObjsPos[i];
		if(pMazeArch != 0)
		{
			free(pMazeArch);
			pMazeArch = 0;
		}

		if(pObjsMutex != 0)
		{
			free(pObjsMutex);
			pObjsMutex = 0;
		}

		if(pObjsPos != 0)
		{
			free(pObjsPos);
			pObjsPos = 0;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		Explorer* pExplorer = m_szpExplorers[i];
		if(pExplorer != NULL)
		{
			delete pExplorer;
			pExplorer = 0;
		}
	}
	delete m_ppMazeArch;
	m_ppMazeArch = 0;
	delete m_ppObjsMutex;
	m_ppObjsMutex = 0;
}

int SafeMaze::InitMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	if(uiX < MIN_X || uiY < MIN_Y)
	{
		std::cout << "size error" << std::endl;
		return -1;
	}

	if(m_cTextLog.Init(&m_cLogConfig))
	{
		std::cout << "Log Init Error" << std::endl;
		return -1;
	}

	m_uiX = uiX;
	m_uiY = uiY;
	m_pIMazeInterface->SetTextLog(&m_cTextLog);
	m_cTextLog.Write("MazeExplorer Start...");

	m_ppMazeArch = (char**)malloc(uiY * sizeof(char*));
	m_ppObjsPos = (long**)malloc(uiY * sizeof(long*));
	m_ppObjsMutex = (pthread_rwlock_t**)malloc(uiY * sizeof(pthread_rwlock_t*));	
	
	if(m_ppMazeArch == NULL || m_ppObjsPos == NULL || m_ppObjsMutex == NULL)
	{
		m_cTextLog.Write("Allocate Memory For Maze Error");
		return -1;
	}

	if(m_MazeNet.InitNet(4660, &m_cTextLog))
	{
		return -1;
	}

	if(m_pIMazeInterface->GenerateMaze(m_ppMazeArch, m_ppObjsPos, m_ppObjsMutex, uiX, uiY, 0))
	{
		std::cout << "memory error in generate maze" << std::endl;
		return -1;
	}

	m_cTextLog.Write("Allocate Memory For Maze Success.");
	m_ppMazeArch[0][0] = 0;
	m_ppMazeArch[m_uiY - 1][0] = 0;
	m_ppMazeArch[0][m_uiX - 1] = 0;
	m_ppMazeArch[m_uiY - 1][m_uiX - 1] = 0;
	return 0;
}

int SafeMaze::InitEmptyMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	if(uiX < MIN_X || uiY < MIN_Y)
	{
		std::cout << "size error" << std::endl;
		return -1;
	}

	if(m_cTextLog.Init(&m_cLogConfig))
	{
		std::cout << "Log Init Error" << std::endl;
		return -1;
	}

	m_uiX = uiX;
	m_uiY = uiY;
	m_pIMazeInterface->SetTextLog(&m_cTextLog);
	m_cTextLog.Write("MazeExplorer Start...");

	m_ppMazeArch = (char**)malloc(uiY * sizeof(char*));
	m_ppObjsPos = (long**)malloc(uiY * sizeof(long*));
	m_ppObjsMutex = (pthread_rwlock_t**)malloc(uiY * sizeof(pthread_rwlock_t*));	
	
	if(m_ppMazeArch == NULL || m_ppObjsPos == NULL || m_ppObjsMutex == NULL)
	{
		m_cTextLog.Write("Allocate Memory For Maze Error");
		return -1;
	}

	if(m_MazeNet.InitNet(4660, &m_cTextLog))
	{
		return -1;
	}

	if(m_pIMazeInterface->GenerateEmptyMaze(m_ppMazeArch, m_ppObjsPos, m_ppObjsMutex, uiX, uiY, 0))
	{
		return -1;
	}

	m_cTextLog.Write("Allocate Memory For Maze Success.");
	return 0;
}

int SafeMaze::StartExplore()
{
	long szpThrdParam[8];
	for(int i = 0; i < 4; i ++)
	{
		if(m_szpExplorers[i] != NULL)
		{
			pthread_t tr;
			szpThrdParam[i * 2] = (long)this;
			szpThrdParam[i * 2 + 1] = i;
			m_cTextLog.Write("SafeMaze(Out Thrd) ptr: %p", (long)this);
			m_cTextLog.Write("ExploreNo(Out Thrd): %d", szpThrdParam[i * 2 + 1]);
			pthread_create(&tr,NULL, ExplrThrd, &szpThrdParam[i * 2]);
		}
	}

	return 0;
}

int SafeMaze::CompetePos()
{
	pthread_rwlock_wrlock(&rwlock);
	long szpThrdParam[8];
	for(int i = 0; i < 4; i++)
	{
		szpThrdParam[i * 2] = (long)this;
		szpThrdParam[i * 2 + 1] = i;
		pthread_t thrd;
		pthread_create(&thrd, NULL, ExplrCompeteThrd, &szpThrdParam[i * 2]);
	}
	
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
		m_cTextLog.Write("Explorer No: %d is not in [0, 4)", idx);
		return 1;
	}
	else if(m_szpExplorers[idx] != 0)
	{
		m_cTextLog.Write("Explorer No: %d has already been set.", idx);
		return 2;
	}
	
	m_szpExplorers[idx] = pExplorer;
	switch(idx)
	{
	case 0:
		pthread_rwlock_wrlock(&m_ppObjsMutex[0][0]);
		m_ppObjsPos[0][0] = (long)pExplorer;
		pthread_rwlock_unlock(&m_ppObjsMutex[0][0]);
		pExplorer->SetCurX(0);
		pExplorer->SetCurY(0);
		m_cTextLog.Write("Set Explorer No.%d at x: %d, y: %d", idx, pExplorer->CurX(), pExplorer->CurY());
		break;
	case 1:
		pthread_rwlock_wrlock(&m_ppObjsMutex[0][m_uiX - 1]);
		m_ppObjsPos[0][m_uiX - 1] = (long)pExplorer;
		pthread_rwlock_unlock(&m_ppObjsMutex[0][m_uiX - 1]);
		pExplorer->SetCurX((int)(m_uiX - 1));
		pExplorer->SetCurY(0);
		m_cTextLog.Write("Set Explorer No.%d at x: %d, y: %d", idx, pExplorer->CurX(), pExplorer->CurY());
		break;
	case 2:
		pthread_rwlock_wrlock(&m_ppObjsMutex[m_uiY - 1][0]);
		m_ppObjsPos[m_uiY - 1][0] = (long)pExplorer;
		pthread_rwlock_unlock(&m_ppObjsMutex[m_uiY - 1][0]);
		pExplorer->SetCurX(0);
		pExplorer->SetCurY((int)(m_uiY - 1));
		m_cTextLog.Write("Set Explorer No.%d at x: %d, y: %d", idx, pExplorer->CurX(), pExplorer->CurY());
		break;
	case 3:
		pthread_rwlock_wrlock(&m_ppObjsMutex[m_uiY - 1][m_uiX - 1]);
		m_ppObjsPos[m_uiY - 1][m_uiX - 1] = (long)pExplorer;
		pthread_rwlock_unlock(&m_ppObjsMutex[m_uiY - 1][m_uiX - 1]);
		pExplorer->SetCurX((int)(m_uiX - 1));
		pExplorer->SetCurY((int)(m_uiY - 1));
		m_cTextLog.Write("Set Explorer No.%d at x: %d, y: %d Success.", idx, pExplorer->CurX(), pExplorer->CurY());
		break;
	}
	return 0;
}

int SafeMaze::SetExplorer(const int& idx, Explorer* pExplr, const unsigned int& uiX, const unsigned int& uiY)
{
	if(idx < 0 || idx >= 4)
	{
		m_cTextLog.Write("Set Explorer No: %d at x: %d, y: %d is not in [0, 4)", idx, uiX, uiY);
		return 1;
	}
	else if(m_szpExplorers[idx] != 0)
	{
		m_cTextLog.Write("Set Explorer No: %d at x: %d, y: %d has already been set", idx, uiX, uiY);
		return 2;
	}

	if(IsPosInMaze(uiX, uiY))
	{
		m_szpExplorers[idx] = pExplr;
		pExplr->SetCurX(uiX);
		pExplr->SetCurY(uiY);
		pthread_rwlock_wrlock(&m_ppObjsMutex[uiY][uiX]);
		m_ppObjsPos[uiY][uiX] = (long)pExplr;
		pthread_rwlock_unlock(&m_ppObjsMutex[uiY][uiX]);
		m_cTextLog.Write("Set Explorer No: %d at x: %d, y: %d Success.", idx, uiX, uiY);
		return 0;
	}
	return 3;
}

int SafeMaze::StartNetServ()
{
	pthread_t thrd;
	pthread_create(&thrd, NULL, StartNetSvrThrd, this);
	return 0;
}

void* SafeMaze::ExplrThrd(void* param)
{
	srand(time(NULL));
	long* lpArgv = (long*)param;
	SafeMaze* pMaze = (SafeMaze*)(lpArgv[0]);
	int iExplrNo = (int)*(long*)((char*)param + 8);

	pMaze->m_cTextLog.Write("ExplrNo: %d start explore maze.", iExplrNo);
	pMaze->m_cTextLog.Write("addr lpArgv[0]: %p", &lpArgv[0]);
	pMaze->m_cTextLog.Write("addr lpArgv[1]: %p", &lpArgv[1]);
	pMaze->m_cTextLog.Write("SafeMaze(In Thrd) ptr: %p", pMaze);
	pMaze->m_cTextLog.Write("uiSleepInterval: %d", pMaze->m_uiSleepInterval);
	while(1)
	{
		sleep(pMaze->m_uiSleepInterval);
		unsigned int uiDestX = 0;
		unsigned int uiDestY = 0;
		const unsigned int iPrevX = pMaze->m_szpExplorers[iExplrNo]->CurX();
		const unsigned int iPrevY = pMaze->m_szpExplorers[iExplrNo]->CurY();
		if(pMaze->m_szpExplorers[iExplrNo]->Walk(uiDestX, uiDestY))
		{
			continue;
		}

		switch(pMaze->MoveExplorer(uiDestX, uiDestY, pMaze->m_szpExplorers[iExplrNo]))
		{
		case 0:
			pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Success.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
			std::cout << "CUR POSITION" << std::endl;
			pMaze->Display();
			break;
		case 1:
			pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos can't be access.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
			break;
		case 2:
			pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos occupied when explore want to read pos status.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
			break;
		case 3:
			pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos occupied when explore want to move to is.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
			break;
		}
	}

	return NULL;
}

void* SafeMaze::ExplrCompeteThrd(void* param)
{
	long* lpArgv = (long*)param;
	SafeMaze* pMaze = (SafeMaze*)(lpArgv[0]);
	long iExplrNo = lpArgv[1];
	
	unsigned int uiDestX = 0;
	unsigned int uiDestY = 0;
	const unsigned int iPrevX = pMaze->m_szpExplorers[iExplrNo]->CurX();
	const unsigned int iPrevY = pMaze->m_szpExplorers[iExplrNo]->CurY();
	pMaze->m_szpExplorers[iExplrNo]->Walk(uiDestX, uiDestY, (EDirector)iExplrNo);

	pthread_mutex_lock(&lock);
	pMaze->m_cTextLog.Write("ExplrNo: %d Ready For Compete.", iExplrNo);
	pthread_mutex_unlock(&lock);

	pthread_rwlock_rdlock(&rwlock);
	switch(pMaze->MoveExplorer(uiDestX, uiDestY, pMaze->m_szpExplorers[iExplrNo]))
	{
	case 0:
		pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Success.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
		break;
	case 1:
		pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos can't be access.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
		break;
	case 2:
		pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos occupied when explore want to read pos status.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
		break;
	case 3:
		pMaze->m_cTextLog.Write("Explorer at x: %d, y: %d ==> x: %d, y: %d On Direction: %d Failed. Maze Pos occupied when explore want to move to is.", iPrevX, iPrevY, uiDestX, uiDestY, iExplrNo);
		break;
	}
//	pthread_rwlock_unlock(&rwlock);
	return NULL;
}

void* SafeMaze::StartNetSvrThrd(void* vdparam)
{
	SafeMaze* pMaze = (SafeMaze*)vdparam;
	pMaze->m_MazeNet.StartNetServ(&pMaze->m_cTextLog);
	return NULL;
}

int SafeMaze::MoveExplorer(const unsigned int& uiX, const unsigned int& uiY, Explorer* pExplr)
{
	if(IsPosInMaze(uiX, uiY))
	{
		pthread_rwlock_rdlock(&m_ppObjsMutex[uiY][uiX]);
		if(m_ppObjsPos[uiY][uiX])
		{
			pthread_rwlock_unlock(&m_ppObjsMutex[uiY][uiX]);
			return 2;
		}
		pthread_rwlock_unlock(&m_ppObjsMutex[uiY][uiX]);

		pthread_rwlock_wrlock(&m_ppObjsMutex[uiY][uiX]);
		pthread_rwlock_wrlock(&m_ppObjsMutex[pExplr->CurY()][pExplr->CurX()]);
		if(m_ppObjsPos[uiY][uiX] != 0)
		{
			pthread_rwlock_unlock(&m_ppObjsMutex[uiY][uiX]);
			pthread_rwlock_unlock(&m_ppObjsMutex[pExplr->CurY()][pExplr->CurX()]);
			return 3;
		}

		int iPrevX = pExplr->CurX();
		int iPrevY = pExplr->CurY();
		m_ppObjsPos[uiY][uiX] = (long)pExplr;
		m_ppObjsPos[iPrevY][iPrevX] = 0;
		pExplr->SetCurX(uiX);
		pExplr->SetCurY(uiY);
		pthread_rwlock_unlock(&m_ppObjsMutex[uiY][uiX]);
		pthread_rwlock_unlock(&m_ppObjsMutex[iPrevY][iPrevX]);
		return 0;
	}
	return 1;
}

bool SafeMaze::IsPosInMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	return ((uiX >= 0 && uiX <= m_uiX - 1) && (uiY >= 0 && uiY <= m_uiY - 1) && m_ppMazeArch[uiY][uiX] == 0);
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


bool SafeMaze::TestRWLock()
{
	for(unsigned int i = 0; i < m_uiY; i++)
	{
		for(unsigned int j = 0; j < m_uiX; j++)
			pthread_rwlock_rdlock(&m_ppObjsMutex[i][j]);
	}

	for(unsigned int i = 0; i < m_uiY; i++)
	{
		for(unsigned int j = 0; j < m_uiX; j++)
		{
			bool ret = (pthread_rwlock_tryrdlock(&m_ppObjsMutex[i][j]) == 0 && pthread_rwlock_trywrlock(&m_ppObjsMutex[i][j]) != 0);
			if(ret)
			{
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				continue;
			}
			else
			{
				std::cout << "rwlock, x: " << j << " y: " << i << " has exception." << std::endl;
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				return false;
			}
		}
	}

	for(unsigned int i = 0; i < m_uiY; i++)
	{
		for(unsigned int j = 0; j < m_uiX; j++)
		{
			pthread_rwlock_wrlock(&m_ppObjsMutex[i][j]);
		}
	}

	for(unsigned int i = 0; i < m_uiY; i++)
	{
		for(unsigned int j = 0; j < m_uiX; j++)
		{
			bool ret = (pthread_rwlock_tryrdlock(&m_ppObjsMutex[i][j]) != 0 && pthread_rwlock_trywrlock(&m_ppObjsMutex[i][j]));
			if(ret)
			{
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				continue;
			}
			else
			{
				std::cout << "rwlock, x: " << j << " y: " << i << " has exception." << std::endl;
				pthread_rwlock_unlock(&m_ppObjsMutex[i][j]);
				return false;
			}
		}
	}
	return true;
}


bool SafeMaze::TestExplrInPos()
{
	bool ret = true;
	for(int i = 0; i < 4; i++)
	{
		if(m_szpExplorers[i])
		{
			ret = ((long)m_szpExplorers[i] == m_ppObjsPos[m_szpExplorers[i]->CurY()][m_szpExplorers[i]->CurX()]);
		}
		if(!ret)
			break;
	}
	return ret;
}

bool SafeMaze::TestIsPosInMaze(const unsigned int& uiX, const unsigned int& uiY)
{
	return IsPosInMaze(uiX, uiY);
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
