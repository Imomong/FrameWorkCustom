#include "StdAfx.h"
#include "StateObj.h"

CStateObj::CStateObj(void)
{
}

CStateObj::~CStateObj(void)
{
}

void CStateObj::Release( void )
{
	for(map<string, CBitMap*>::iterator iter = m_MapBmp.begin(); iter != m_MapBmp.end(); ++iter)
	{
		Safe_Delete(iter->second);
	}
	m_MapBmp.clear();
}


