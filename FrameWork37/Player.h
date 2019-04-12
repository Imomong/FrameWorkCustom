#pragma once
#include "obj.h"

class CPlayer :public CObj
{
public:
	int			m_iHP;
	bool		m_bDead;
	bool		m_tPlayerHit;
	bool		m_bRestart;
private:
	string		m_strDrawID;
	float		m_fSpeed;
	DWORD		m_dwKey;
	DWORD		m_dwTime;
	DWORD		m_dwState;

	FRAME		m_tFrame;
	DWORD		m_tCount;
	
	DWORD		m_tPlayerHitTime;
public:
	float GetSpeed(void) const {return m_fSpeed;}

private:
	void KeyCheck(void);
	void Frame(void);
	void Direction(void);
	void Motion(void);
	void SetScene(int _ilast, int _iscene, DWORD _dwtime);
	void CreateBullet();
public:
	void SetHitInvi();
public:
	virtual void Initialize( void );
	virtual int Progress( void );
	virtual void Render( HDC hdc );
	virtual void Release( void );

public:
	CPlayer(void);
	virtual ~CPlayer(void);
};
