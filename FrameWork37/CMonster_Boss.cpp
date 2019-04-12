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
		TransparentBlt(hdc,		// �׷��� ��ġ
			int((m_tInfo.fX - m_tInfo.fCX / 2)),		// X��ǥ�κ���
			int((m_tInfo.fY - m_tInfo.fCY / 2)),		// Y��ǥ�κ���
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// ���� ������ ����
			(*m_pMapBmp)["Monster_Boss"]->GetMemDC(),		// �׷��� ��ġ��
			0,		//	������ ������
			0,		// ������ �����
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// ���� ������ ������
			RGB(0, 128, 128));		// ���� ��Ʈ���� ���� �������� ���� �Ѵ�.
	}
}

void Monster_Boss::Release(void)
{
}

void Monster_Boss::Shooting()
{
	if (m_tBulletTik + 300 < GetTickCount())
	{
		// �Ѿ� ��ź��
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

		// �Ѿ˱���
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
