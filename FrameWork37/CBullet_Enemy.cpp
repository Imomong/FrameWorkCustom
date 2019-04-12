#include "stdafx.h"
#include "CBullet_Enemy.h"

void CBullet_Enemy::Initialize(void)
{
	m_fSpeed = 5.0f;
	m_bActive = false;

	m_iBulletSizeX = 24;
	m_iBulletSizeY = 24;

	m_tInfo = INFO(WINCX / 2, WINCY / 2, m_iBulletSizeX, m_iBulletSizeY);
}

int CBullet_Enemy::Progress(void)
{
	if (m_bActive) m_tInfo.fY += m_fSpeed;
	if (m_tInfo.fY > WINCY)
	{
		m_bActive = false;
		m_tInfo.fY = 0;
	}


	return 0;
}

void CBullet_Enemy::Render(HDC hdc)
{
	if (m_bActive)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2),
			int(m_tInfo.fY - m_tInfo.fCY / 2),
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,
			(*m_pMapBmp)["Bullet_Enemy"]->GetMemDC(),
			0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
}

void CBullet_Enemy::Release(void)
{
}

void CBullet_Enemy::SetActive(bool _flag)
{
	m_bActive = _flag;
}

bool CBullet_Enemy::GetActive()
{
	return m_bActive;
}

CBullet_Enemy::CBullet_Enemy()
{
}


CBullet_Enemy::~CBullet_Enemy()
{
}