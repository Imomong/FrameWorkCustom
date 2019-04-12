#pragma once
#include "stateobj.h"

class CObj;

class CMyMenu :
	public CStateObj
{
private:
	CObj*	m_pBackGround;
	list<CObj*>		m_ButtonList;

public:
	CObj* CreateButton(float _fx, float _fy, string _DrawId);

public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMyMenu(void);
	virtual ~CMyMenu(void);
};
