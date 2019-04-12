#pragma once

#include "value.h"

class CBitMap
{
public:
	HDC			m_hdc, m_MemDC;
	HBITMAP		m_bitMap, m_oldbitMap;	

public:
	HDC GetMemDC(void) {return m_MemDC;}

public:
	CBitMap* LoadBmp(PTCHAR pFileName);
	void Release(void);

public:
	CBitMap(void);
	~CBitMap(void);
};
