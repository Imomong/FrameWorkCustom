#include "stdafx.h"
#include "CBullet_Player.h"

void CBullet_Player::Initialize(void)
{
	m_fSpeed = 10.0f;
	m_bActive = false;

	m_iBulletSizeX = 48;
	m_iBulletSizeY = 48;

	m_tInfo = INFO(WINCX / 2, WINCY / 2, m_iBulletSizeX, m_iBulletSizeY);
}

int CBullet_Player::Progress(void)
{
	if (m_bActive) m_tInfo.fY -= m_fSpeed;
	if (m_tInfo.fY < 0)
	{
		m_bActive = false;
		m_tInfo.fY = WINCY;
	}


	return 0;
}

void CBullet_Player::Render(HDC hdc)
{
	if (m_bActive)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2),
			int(m_tInfo.fY - m_tInfo.fCY / 2),
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,
			(*m_pMapBmp)["Bullet_Player"]->GetMemDC(),
			0, 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			RGB(255, 255, 255));
	}
}

void CBullet_Player::Release(void)
{
}

void CBullet_Player::SetActive(bool _flag)
{
	m_bActive = _flag;
}

bool CBullet_Player::GetActive()
{
	return m_bActive;
}

CBullet_Player::CBullet_Player()
{
}

CBullet_Player::~CBullet_Player()
{
}
