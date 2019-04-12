#include "StdAfx.h"
#include "MainGame.h"

#include "StateMgr.h"
#include "KeyMgr.h"
#include "Device.h"

CMainGame::CMainGame(void)
{
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Initialize( void )
{
	srand(unsigned(time(NULL)));

	m_hdc = GetDC(g_hWnd);

	CDevice::GetInstance()->Init();
	CStateMgr::GetInst()->SetState(IDS_MENU);
}

void CMainGame::Progress( void )
{
	CKeyMgr::GetInst()->CheckKey();
	CStateMgr::GetInst()->Progress();
}

void CMainGame::Render( void )
{
	CStateMgr::GetInst()->Render(m_hdc);
}

void CMainGame::Release( void )
{
	ReleaseDC(g_hWnd, m_hdc);
	CStateMgr::GetInst()->DestroyInst();
	CKeyMgr::GetInst()->DestroyInst();
}