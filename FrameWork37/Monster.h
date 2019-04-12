#pragma once
#include "obj.h"

class CMonster :
	public CObj
{
public:
	int		m_iHP;
	bool	m_bActive;
	bool	m_bStart; //시작시 동작구현
	float   m_tBulletTik;
private:
	float	m_fSpeed;
	float	m_tCount;
	bool	m_bMov;
	bool	m_bLeft;

public:
	virtual void Initialize( void );
	virtual int Progress( void );
	virtual void Render( HDC hdc );
	virtual void Release( void );

public:
	void SelectDir();
	void Moving();
	void Shooting();
public:
	CMonster(void);
	virtual ~CMonster(void);
};
