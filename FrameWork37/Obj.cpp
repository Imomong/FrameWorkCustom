#include "StdAfx.h"
#include "Obj.h"

map<string, CBitMap*>*	CObj::m_pMapBmp = NULL;

POINT	CObj::m_ptScroll = {0};

CObj::CObj(void)
{
}

CObj::~CObj(void)
{
}

void CObj::SetPos( float _fx, float _fy )
{
	m_tInfo.fX = _fx;
	m_tInfo.fY = _fy;
}

void CObj::SetSize(float _fcx, float _fcy)
{
	m_tInfo.fCX = _fcx;
	m_tInfo.fCY = _fcy;
}

RECT CObj::GetRect( void )
{
	RECT	rt = 
	{
		int(m_tInfo.fX - m_tInfo.fCX / 2.f),
		int(m_tInfo.fY - m_tInfo.fCY / 2.f),
		int(m_tInfo.fX + m_tInfo.fCX / 2.f),
		int(m_tInfo.fY + m_tInfo.fCY / 2.f)
	};

	return rt;
}
