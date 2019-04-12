#include "StdAfx.h"
#include "BackGround.h"

CBackGround::CBackGround(void)
{
}

CBackGround::~CBackGround(void)
{
}

void CBackGround::Initialize( void )
{
		
}

int CBackGround::Progress( void )
{
	return 0;
}

void CBackGround::Render( HDC hdc )
{
	BitBlt(hdc, 
		0,0,WINCX, WINCY, 
		(*m_pMapBmp)["BackGround"]->GetMemDC(), 
		0,0,SRCCOPY);
}

void CBackGround::Release( void )
{

}
