#pragma once
#include "obj.h"

class Monster_Boss : public CObj
{
public:
	int		m_iHP;
	bool	m_bActive;
	bool	m_bStart; //시작시 동작구현
	float	m_tBulletTik;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
private:
	void Shooting();
public:
	Monster_Boss();
	~Monster_Boss();
};

