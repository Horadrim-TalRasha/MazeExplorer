#include "explorer.h"


Explorer::Explorer() :
m_iCurX(-1),
m_iCurY(-1)
{

}

Explorer::~Explorer()
{
	std::cout << "explorer destroyed" << std::endl;
}

int Explorer::Walk(unsigned int& uiDestX, unsigned int& uiDestY)
{
	EDirector eDirector = (EDirector)(random() % E_Directors);
	uiDestX = m_iCurX;
	uiDestY = m_iCurY;
	switch(eDirector)
	{
	case E_Up:
		uiDestY -= 1;
		break;
	case E_Down:
		uiDestY += 1;
		break;
	case E_Left:
		uiDestX -= 1;
		break;
	case E_Right:
		uiDestX += 1;
		break;
	default:
		return 1;
	}
	return 0;
}

int Explorer::Walk(unsigned int& uiDestX, unsigned int& uiDestY, const EDirector& eDirector)
{
	uiDestX = m_iCurX;
	uiDestY = m_iCurY;
	switch(eDirector)
	{
	case E_Up:
		uiDestY -= 1;
		break;
	case E_Down:
		uiDestY += 1;
		break;
	case E_Left:
		uiDestX -= 1;
		break;
	case E_Right:
		uiDestX += 1;
		break;
	default:
		return 1;
	}
	return 0;
}

int Explorer::ActivatePower(AbsPower* pPower)
{
	pPower->ActivateInMaze(0);
	return 0;
}
