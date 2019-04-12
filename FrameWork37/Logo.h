#pragma once
#include "stateobj.h"

class CLogo :
	public CStateObj
{
private:
	HWND		m_hVideo;

public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CLogo(void);
	virtual ~CLogo(void);
};
