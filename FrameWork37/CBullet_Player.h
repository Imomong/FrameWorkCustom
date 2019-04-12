#pragma once
#include "obj.h"

class CBullet_Player : public CObj
{
private:
	float		m_fSpeed;
	int			m_iBulletSizeX;
	int			m_iBulletSizeY;
	bool		m_bActive;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);

public:
	void SetActive(bool _flag);
	bool GetActive();
public:
	CBullet_Player();
	~CBullet_Player();
};

