#include "StdAfx.h"
#include "StageBack.h"
#include "Player.h"

CStageBack::CStageBack(void)
{
}

CStageBack::~CStageBack(void)
{
}

void CStageBack::Initialize( void )
{
	m_tInfo = INFO(0, 0, 800, 18165);

	m_ptOffSet.x = WINCX / 2;
	m_ptOffSet.y = WINCY / 2;

	iYCount = 18165 - WINCY;
	iStartTime = GetTickCount();
}

int CStageBack::Progress( void )
{
	DelayTik();

	return 0;
}

void CStageBack::Render( HDC hdc )
{
	BitBlt(hdc, 
		int(m_tInfo.fX), 
		int(m_tInfo.fY), 
		(int)m_tInfo.fCX, (int)m_tInfo.fCY, 
		(*m_pMapBmp)["BackGround"]->GetMemDC(),
		0, iYCount,SRCCOPY);
}

void CStageBack::Release( void )
{

}

void CStageBack::StageScroll( void )
{
	iYCount--;

	if (iYCount < 0) iYCount = 18165 - WINCY;
}

void CStageBack::DelayTik()
{
	if (GetTickCount() - iStartTime >= 1)//0.1초
	{
		iStartTime = GetTickCount(); // 초기화

		StageScroll();
	}
	else
	{
		iStartTime++;
	}
}
