#include "StdAfx.h"
#include "Monster.h"
#include "Objmgr.h"

#define MONSTER_SIZEX 27
#define MONSTER_SIZEY 39

CMonster::CMonster(void)
{
}

CMonster::~CMonster(void)
{
}

void CMonster::Initialize( void )
{
	m_tInfo = INFO(0, 0, MONSTER_SIZEX, MONSTER_SIZEY);
	m_fSpeed = 2.0f;

	m_bLeft = true;
	m_bMov = true;

	m_tBulletTik = GetTickCount();

	m_iHP = 10;
	m_bActive = false;
	m_bStart = false;
}

int CMonster::Progress( void )
{
	//���۽� ����
	if (m_bStart)
	{
		if (m_tBulletTik + 1000 < GetTickCount())
		{
			printf("asd");
			m_tBulletTik = GetTickCount();
			m_bStart = false;
		}
		else
		{
			m_tInfo.fY += m_fSpeed;
		}
	}
	else
	{
		if (m_bActive)
		{
			if (m_iHP <= 0) m_bActive = false;
			if (m_tCount + 300 < GetTickCount())
			{
				m_bMov = true;
				m_tCount = GetTickCount();
			}

			if (m_bMov) SelectDir();
			else Moving();

			Shooting();
		}
	}
	return 0;
}

void CMonster::Render( HDC hdc )
{
	if (m_bActive)
	{
		TransparentBlt(hdc,		// �׷��� ��ġ
			int((m_tInfo.fX - m_tInfo.fCX / 2)),		// X��ǥ�κ���
			int((m_tInfo.fY - m_tInfo.fCY / 2)),		// Y��ǥ�κ���
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// ���� ������ ����
			(*m_pMapBmp)["Monster"]->GetMemDC(),		// �׷��� ��ġ��
			int(m_tInfo.fCX * 1),		//	������ ������
			int(m_tInfo.fCY * 0),		// ������ �����
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// ���� ������ ������
			RGB(0, 128, 128));		// ���� ��Ʈ���� ���� �������� ���� �Ѵ�.
	}
}

void CMonster::Release( void )
{
}

void CMonster::SelectDir()
{
	int temp = (int)(rand() % 10);

	if (temp >= 5)
	{
		m_bLeft = true;
	}
	else
	{
		m_bLeft = false;
	}

	if (m_tInfo.fX <= MONSTER_SIZEX / 2)
	{
		m_bLeft = false;
	}

	if (m_tInfo.fX >= WINCX - MONSTER_SIZEX / 2)
	{
		m_bLeft = true;
	}

	m_bMov = false;
}

void CMonster::Moving()
{
	if (m_bLeft)
	{
		if (m_tInfo.fX > MONSTER_SIZEX / 2)
		{
			m_tInfo.fX -= m_fSpeed;
		}
	}
	else
	{
		if (m_tInfo.fX < WINCX - MONSTER_SIZEX / 2)
		{
			m_tInfo.fX += m_fSpeed;
		}
	}
}

void CMonster::Shooting()
{
	if (m_tBulletTik + 500 < GetTickCount())
	{
		// �Ѿ˱���
		CObj* bullet = CObjMgr::GetInst()->SetActiveObj(OBJ_BULLET_ENEMY);
		bullet->SetPos(m_tInfo.fX, m_tInfo.fY);

		m_tBulletTik = GetTickCount();
	}
}
