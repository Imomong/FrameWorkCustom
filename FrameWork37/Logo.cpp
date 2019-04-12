#include "StdAfx.h"
#include "Logo.h"

#include "Include.h"

#include <vfw.h>
#pragma comment (lib, "vfw32.lib")
#include "StateMgr.h"

CLogo::CLogo(void)
{
}

CLogo::~CLogo(void)
{
	Release();
}

void CLogo::Initialize( void )
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD, 
		L"../Video/Logo.wmv");

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);
}

int CLogo::Progress( void )
{
	if(GetAsyncKeyState(VK_RETURN) ||
		GetAsyncKeyState(VK_ESCAPE))
	{
		CStateMgr::GetInst()->SetState(IDS_MENU);
		return 0;
	}

	return 0;
}

void CLogo::Render( HDC hdc )
{

}

void CLogo::Release( void )
{
	MCIWndClose(m_hVideo);
}
