#ifndef EXPLORER_H
#define EXPLORER_H

#include "abspower.h"
#include <math.h>

enum EDirector
{
	E_Up = 0x0001,
	E_Down = 0x0002,
	E_Left = 0x0004,
	E_Right = 0x0008,
	E_Directors
};

class Explorer
{
public:
	Explorer();
	virtual ~Explorer();
	int Walk(unsigned int& uiDestX, unsigned int& uiDestY);
	int Walk(unsigned int& uiDestX, unsigned int& uiDesyY, const EDirector& eDirector);
	int ActivatePower(AbsPower* pPower);
	inline void SetCurX(const int& iCurX) {	m_iCurX = iCurX;	}
	inline void SetCurY(const int& iCurY) {	m_iCurY = iCurY;	}
	inline int CurX() {	return m_iCurX;	}
	inline int CurY() {	return m_iCurY;	}

private:
	int m_iCurX;
	int	m_iCurY;

	AbsPower* m_pPowers[E_Powers];
};

#endif
