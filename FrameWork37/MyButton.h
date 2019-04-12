#pragma once
#include "obj.h"

class CMyButton :
	public CObj
{
private:
	string		m_strDrawID;
	int			m_iScene;

public:
	string GetDrawID(void) {return m_strDrawID;}

public:
	void SetDrawID(string _drawId) {m_strDrawID = _drawId;}

public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	CMyButton(void);
	virtual ~CMyButton(void);
};
