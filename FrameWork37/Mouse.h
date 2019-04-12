#pragma once

#include "value.h"

class CMouse
{
public:
	static POINT GetPos(void)
	{
		POINT	pt;
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);
		return pt;
	}

public:
	CMouse(void);
	~CMouse(void);
};
