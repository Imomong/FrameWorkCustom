#include "stdafx.h"
#include "CMonster_Boss.h"
#include "ObjMgr.h"
#include "CBullet_Enemy2.h"

#define MONSTER_SIZEX 354
#define MONSTER_SIZEY 372

void Monster_Boss::Initialize(void)
{
	m_bActive = false;
	m_bStart = false;

	m_tBulletTik = GetTickCount();

	m_tInfo = INFO(0, 0, MONSTER_SIZEX, MONSTER_SIZEY);
	m_iHP = 200;
}

int Monster_Boss::Progress(void)
{
	if (m_bStart)
	{
		if (m_tBulletTik + 3000 < GetTickCount())
		{
			m_tBulletTik = GetTickCount();
			m_bStart = false;
		}
		else
		{
			m_tInfo.fY += 1.0f;
		}
	}
	else
	{
		if (m_bActive) Shooting();
	}
	
	return 0;
}

void Monster_Boss::Render(HDC hdc)
{
	if (m_bActive)
	{
		TransparentBlt(hdc,		// 그려질 위치
			int((m_tInfo.fX - m_tInfo.fCX / 2)),		// X좌표로부터
			int((m_tInfo.fY - m_tInfo.fCY / 2)),		// Y좌표로부터
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// 현재 스케일 값을
			(*m_pMapBmp)["Monster_Boss"]->GetMemDC(),		// 그려낼 위치에
			0,		//	시작할 프레임
			0,		// 시작할 장면을
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// 현재 스케일 값으로
			RGB(0, 128, 128));		// 현재 비트맵의 색을 제외한후 복사 한다.
	}
}

void Monster_Boss::Release(void)
{
}

void Monster_Boss::Shooting()
{
	if (m_tBulletTik + 300 < GetTickCount())
	{
		// 총알 산탄도
		int iTemp = rand() % 10;
		int iSpread = 0;

		if (iTemp >= 7)
		{
			iSpread = -10;
		}
		else if (iTemp >= 4)
		{
			iSpread = 10;
		}
		else
		{
			iSpread = 0;
		}

		// 총알구현
		for (int i = 0; i < 5; i++)
		{
			CObj* bullet = CObjMgr::GetInst()->SetActiveObj(OBJ_BULLET_ENEMY2);
			bullet->SetPos(m_tInfo.fX + iSpread, m_tInfo.fY + m_tInfo.fCY / 2);
			((CBullet_Enemy2*)bullet)->m_fCurve = 2 - 1.0f * i;
		}

		m_tBulletTik = GetTickCount();
	}
}

Monster_Boss::Monster_Boss()
{
}


Monster_Boss::~Monster_Boss()
{
}
