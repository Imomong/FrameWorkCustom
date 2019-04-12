#pragma once

#include "Include.h"

class CStateObj
{
protected:
	map<string, CBitMap*>		m_MapBmp;

public:
	virtual void Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release(void)PURE;

public:
	CStateObj(void);
	virtual ~CStateObj(void);
};
