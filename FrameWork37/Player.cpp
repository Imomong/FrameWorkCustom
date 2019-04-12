#include "StdAfx.h"
#include "Player.h"
#include "KeyMgr.h"
#include "Device.h"
#include "ObjFactory.h"
#include "ObjMgr.h"
#include "StateMgr.h"
#include "CBullet_Player.h"

#define PLAYER_SIZEX 32
#define PLAYER_SIZEY 32

CPlayer::CPlayer(void)
{
}

CPlayer::~CPlayer(void)
{
}

void CPlayer::Initialize( void )
{
	m_tInfo		= INFO(WINCX / 2, WINCY * 4 / 5, PLAYER_SIZEX, PLAYER_SIZEY);
	m_tFrame	= FRAME(0, 2, 0, 300);
	m_dwState	= STATE_STAND;

	m_fSpeed	= 5.f;
	m_dwKey		= 0;
	m_dwTime	= GetTickCount();
	m_tCount	= GetTickCount();

	m_strDrawID = "Player_DOWN";

	m_iHP = 3;
	m_bDead = false;

	m_tPlayerHit = false;

	m_bRestart = false;
}

int CPlayer::Progress( void )
{
	CObjMgr::GetInst()->SetPlayerPos(m_tInfo.fX, m_tInfo.fY);

	KeyCheck();

	if (m_iHP <= 0)
	{
		m_bDead = true;
	}

	if (!m_bDead)
	{
		//맞을시 잠깐무적
		if (m_tPlayerHit)
		{
			if (m_tPlayerHitTime + 1000 < GetTickCount())
			{
				m_tPlayerHit = false;

				m_tFrame = FRAME(0, 2, 0, 300);
			}
		}

		Frame();
		Direction();
		Motion();
	}

	return 0;
}

void CPlayer::Render( HDC hdc )
{
	if (!m_bDead)
	{
		//플레이어
		TransparentBlt(hdc,		// 그려질 위치
			int((m_tInfo.fX - m_tInfo.fCX / 2)),		// X좌표로부터
			int((m_tInfo.fY - m_tInfo.fCY / 2)),		// Y좌표로부터
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// 현재 스케일 값을
			(*m_pMapBmp)[m_strDrawID]->GetMemDC(),		// 그려낼 위치에
			int(m_tInfo.fCX * m_tFrame.iStart),		//	시작할 프레임
			int(m_tInfo.fCY * m_tFrame.iScene),		// 시작할 장면을
			(int)m_tInfo.fCX, (int)m_tInfo.fCY,		// 현재 스케일 값으로
			RGB(255, 255, 255));		// 현재 비트맵의 색을 제외한후 복사 한다.

		//UI
		TransparentBlt(hdc, 0, WINCY * 8 / 9, 74, 35, (*m_pMapBmp)["UI_1"]->GetMemDC(), 0, 0, 74, 35,
			RGB(0, 30, 255));

		if (m_iHP > 1)
		{
			for (int i = 0; i < m_iHP - 1; i++)
			{
				TransparentBlt(hdc, i * 37, WINCY * 8 / 9 + 35, 37, 47, (*m_pMapBmp)["UI_2"]->GetMemDC(), 0, 0, 37, 47,
					RGB(0, 30, 255));
			}
		}
	}
	else
	{
		TransparentBlt(hdc, 0, WINCY/2, 300, 100, (*m_pMapBmp)["UI_RESTART"]->GetMemDC(), 0, 0, 300, 100,
			RGB(255, 255, 255));
	}
}

void CPlayer::Release( void )
{
}

void CPlayer::KeyCheck( void )
{
	m_dwKey = CKeyMgr::GetInst()->GetKey();

	if (m_dwKey & KEY_UP)
	{
		if(m_tInfo.fY > PLAYER_SIZEY / 2) m_tInfo.fY -= m_fSpeed;
	}

	if(m_dwKey & KEY_DOWN)
	{
		if (m_tInfo.fY < WINCY - PLAYER_SIZEY / 2) m_tInfo.fY += m_fSpeed;
	}

	if(m_dwKey & KEY_LEFT)
	{
		if (m_tInfo.fX > PLAYER_SIZEX / 2) m_tInfo.fX -= m_fSpeed;
	}

	if(m_dwKey & KEY_RIGHT)
	{
		if (m_tInfo.fX < WINCX - PLAYER_SIZEX / 2) m_tInfo.fX += m_fSpeed;
	}

	if(m_dwKey & KEY_SPACE)
	{
		if (!m_bDead)
		{
			if (m_tCount + 100 < GetTickCount())
			{
				m_tCount = GetTickCount();
				CreateBullet();
				CDevice::GetInstance()->SoundPlay(1, 0);
			}
		}
		else
		{
			if (m_tCount + 1000 < GetTickCount())
			{
				m_tCount = GetTickCount();

				CDevice::GetInstance()->SoundStop(0);
				m_bRestart = true;
			}
			
		}
	}

	if (m_dwKey & KEY_ESCAPE && m_bDead)
	{
		if (m_tCount + 1000 < GetTickCount())
		{
			CDevice::GetInstance()->SoundStop(0);
			CStateMgr::GetInst()->SetState(IDS_MENU);
		}
	}
	
}

void CPlayer::Frame( void )
{
	if(m_dwTime + m_tFrame.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();
		++m_tFrame.iStart;

		if(m_tFrame.iStart >= m_tFrame.iLast)
		{
			if(m_strDrawID == "Player_DOWN") m_tFrame.iStart = 0;
			else m_tFrame.iStart = 1;
		}
	}
}

void CPlayer::Direction( void )
{
	if(KEY_LEFT & m_dwKey && KEY_UP & m_dwKey)
	{
		m_strDrawID = "Player_LEFT";
		return;
	}

	if(KEY_LEFT & m_dwKey && KEY_DOWN & m_dwKey)
	{
		m_strDrawID = "Player_LEFT";
		return;
	}

	if(KEY_RIGHT & m_dwKey && KEY_UP & m_dwKey)
	{
		m_strDrawID = "Player_RIGHT";
		return;
	}

	if(KEY_RIGHT & m_dwKey && KEY_DOWN & m_dwKey)
	{
		m_strDrawID = "Player_RIGHT";
		return;
	}

	if(KEY_LEFT & m_dwKey)
		m_strDrawID = "Player_LEFT";

	if(KEY_RIGHT & m_dwKey)
		m_strDrawID = "Player_RIGHT";

	if(KEY_UP & m_dwKey)
		m_strDrawID = "Player_UP";

	if(KEY_DOWN & m_dwKey)
		m_strDrawID = "Player_DOWN";

}

void CPlayer::Motion( void )
{
	if (!m_dwKey)
		m_strDrawID = "Player_DOWN";

	if (m_strDrawID == "Player_UP")
	{
		m_tInfo.fCY = 39;
	}
	else
	{
		m_tInfo.fCY = 32;
	}
}

void CPlayer::SetScene( int _ilast, int _iscene, DWORD _dwtime )
{
	if(m_tFrame.iScene != _iscene)
		m_tFrame.iStart = 0;

	m_tFrame.iLast = _ilast;
	m_tFrame.iScene = _iscene;
	m_tFrame.dwTime = _dwtime;
}

void CPlayer::CreateBullet()
{
	CObjMgr::GetInst()->SetActiveObj(OBJ_BULLET);
}

void CPlayer::SetHitInvi()
{
	m_tFrame = FRAME(0, 3, 0, 50);
	m_tPlayerHitTime = GetTickCount();
	m_tPlayerHit = true;
}
