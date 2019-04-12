#pragma once
#include "Obj.h"

class CEffect : public CObj
{
public:
	bool	m_bActive;
private:
	string	m_strDrawID;
private:
	float	m_fTik;
	FRAME	m_tFrame;
	DWORD	m_dwTime;;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
private:
	void Frame(void);
public:
	void SetSprite(string _strDrawID,int _iMaxFrame);
public:
	CEffect();
	~CEffect();
};

