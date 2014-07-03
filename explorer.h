#ifndef EXPLORER_H
#define EXPLORER_H

#include "abspower.h"
#include <math.h>
#include <vector>

enum EDirector
{
	E_Up = 0x0001,
	E_Down = 0x0002,
	E_Left = 0x0004,
	E_Right = 0x0008,
	E_Directors
};

struct Position
{
	unsigned int m_uiX;
	unsigned int m_uiY;
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
	void AddPath(const unsigned int& uiX, const unsigned int& uiY);
	bool IsPosInPath(const unsigned int& uiX, const unsigned int& uiY);
	int PosCount();
	int LastPath(unsigned int& uiX, unsigned int& uiY);
	void TurnBack();

private:
	int m_iCurX;
	int	m_iCurY;

	AbsPower* m_pPowers[E_Powers];
	std::vector<Position> m_Path;

private:
	int IsPosInSameDirection(const unsigned int& uiX1, const unsigned int& uiX2, const unsigned int& uiY1, const unsigned int& uiY2);
	int BackToSourceOfDirection(unsigned int& uiX, unsigned int& uiY);
};

#endif
