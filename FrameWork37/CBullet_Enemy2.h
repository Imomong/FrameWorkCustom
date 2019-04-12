#pragma once
#include "obj.h"

class CBullet_Enemy2 : public CObj
{
public:
	float		m_fCurve;
private:
	float		m_fSpeed;
	int			m_iBulletSizeX;
	int			m_iBulletSizeY;
	bool		m_bActive;

	float		m_tBulletTik;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
public:
	void SetActive(bool _flag);
	bool GetActive();
public:
	CBullet_Enemy2();
	~CBullet_Enemy2();
};

