#include "stdafx.h"
#include "CEffect.h"


void CEffect::Initialize(void)
{
	m_dwTime = GetTickCount();

	m_bActive = false;
	m_tFrame = FRAME(0, 2, 0, 50);
}

int CEffect::Progress(void)
{
	if (m_bActive)
	{
		Frame();
	}
	
	return 0;
}

void CEffect::Render(HDC hdc)
{
	if (m_bActive)
	{
		TransparentBlt(hdc,
			int(m_tInfo.fX - m_tInfo.fCX / 2),
			int(m_tInfo.fY - m_tInfo.fCY / 2),
			int(m_tInfo.fCX), (int)m_tInfo.fCY,
			(*m_pMapBmp)[m_strDrawID]->GetMemDC(),
			int(m_tInfo.fCX * m_tFrame.iStart), 0, (int)m_tInfo.fCX, (int)m_tInfo.fCY,
			RGB(50, 150, 200));
	}
}

void CEffect::Release(void)
{
}

void CEffect::SetSprite(string _strDrawID, int _iMaxFrame)
{
	m_strDrawID = _strDrawID;
	m_tFrame.iLast = _iMaxFrame;
}

void CEffect::Frame(void)
{
	if (m_dwTime + m_tFrame.dwTime < GetTickCount())
	{
		m_dwTime = GetTickCount();
		++m_tFrame.iStart;

		if (m_tFrame.iStart >= m_tFrame.iLast)
		{
			m_bActive = false;
			m_tFrame.iStart = 0;
		}
	}
}

CEffect::CEffect()
{
}


CEffect::~CEffect()
{
}
