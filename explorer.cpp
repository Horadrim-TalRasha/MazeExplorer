#include "explorer.h"


Explorer::Explorer() :
m_iCurX(-1),
m_iCurY(-1)
{

}

int Explorer::Walk(unsigned int& uiDestX, unsigned int& uiDestY)
{
	
	return 0;
}

int Explorer::ActivatePower(AbsPower* pPower)
{
	pPower->ActivateInMaze(0);
	return 0;
}
