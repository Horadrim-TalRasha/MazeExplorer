#ifndef EXPLORER_H
#define EXPLORER_H

#include "abspower.h"

enum EDirector
{
	E_Up = 0,
	E_Down,
	E_Left,
	E_Right,
	E_Directors
};

class Explorer
{
public:
	Explorer();
	int Walk(const EDirector& eDirector, const unsigned int& step, const unsigned int& uiXEdge, const unsigned int& uiYEdge);
	int ActivatePower(AbsPower* pPower);

private:
	int m_iCurX;
	int	m_iCurY;

	AbsPower* m_pPowers[E_Powers];
};

#endif
