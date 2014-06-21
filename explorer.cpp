#include "explorer.h"


Explorer::Explorer()
{

}

int Explorer::Walk(const EDirector& eDirectory, const unsigned int& uiStep, const unsigned int& uiXEdge, const unsigned int& uiYEdge)
{

	return 0;
}

int Explorer::ActivatePower(AbsPower* pPower)
{
	pPower->ActivateInMaze(0);
	return 0;
}
