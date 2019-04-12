#pragma once

#include "Include.h"

class CObj
{
protected:
	INFO	m_tInfo;
	static POINT	m_ptScroll;

	static map<string, CBitMap*>*	m_pMapBmp;
	
public:
	INFO GetInfo(void) const {return m_tInfo;}
	RECT GetRect(void);

public:
	void SetPos(float _fx, float _fy);
	void SetSize(float _fcx, float _fcy);
	static void SetBmp(map<string, CBitMap*>*	_pMapBmp) {m_pMapBmp = _pMapBmp;}

public:
	virtual void Initialize(void)PURE;
	virtual int Progress(void)PURE;
	virtual void Render(HDC hdc)PURE;
	virtual void Release(void)PURE;

public:
	CObj(void);
	virtual ~CObj(void);
};
