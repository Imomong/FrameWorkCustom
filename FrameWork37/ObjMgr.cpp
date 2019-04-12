#include "StdAfx.h"
#include "ObjMgr.h"

#include "Obj.h"

CObjMgr*	CObjMgr::m_pInst = NULL;

/* 콘솔창띄우기
*/
#ifdef UNICODE
     #pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#else
     #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console") 
#endif



CObjMgr::CObjMgr(void)
{
}

CObjMgr::~CObjMgr(void)
{
}

void CObjMgr::AddRenderObj( CObj* pObj )
{
	m_MapObj.insert(make_pair(pObj->GetInfo().fY, pObj));
}

void CObjMgr::Render( HDC hdc )
{
	for(multimap<float, CObj*>::iterator iter = m_MapObj.begin(); iter != m_MapObj.end(); ++iter)
	{
		iter->second->Render(hdc);
	}
}

void CObjMgr::Clear( void )
{
	m_MapObj.clear();
}

CObj* CObjMgr::SetActiveObj(int _enum)
{
	switch (_enum)
	{
	case OBJ_BULLET:
		for (list<CObj*>::iterator iter = m_ListObj[OBJ_BULLET].begin(); iter != m_ListObj[OBJ_BULLET].end(); ++iter)
		{
			if (!((CBullet_Player*)(*iter))->GetActive())
			{
				(*iter)->SetPos(m_PlayerPos.fX, m_PlayerPos.fY);
				((CBullet_Player*)(*iter))->SetActive(true);
				break;
			}
		}
		break;
	case OBJ_BULLET_ENEMY:
		for (list<CObj*>::iterator iter = m_ListObj[OBJ_BULLET_ENEMY].begin(); iter != m_ListObj[OBJ_BULLET_ENEMY].end(); ++iter)
		{
			if (!((CBullet_Enemy*)(*iter))->GetActive())
			{
				(*iter)->SetPos(m_PlayerPos.fX, m_PlayerPos.fY);
				((CBullet_Enemy*)(*iter))->SetActive(true);
				return *iter;
			}
		}
		break;
	case OBJ_BULLET_ENEMY2:
		for (list<CObj*>::iterator iter = m_ListObj[OBJ_BULLET_ENEMY2].begin(); iter != m_ListObj[OBJ_BULLET_ENEMY2].end(); ++iter)
		{
			if (!((CBullet_Enemy2*)(*iter))->GetActive())
			{
				(*iter)->SetPos(m_PlayerPos.fX, m_PlayerPos.fY);
				((CBullet_Enemy2*)(*iter))->SetActive(true);
				return *iter;
			}
		}
		break;
	}

	return 0;
}

void CObjMgr::SetPlayerPos(float _x, float _y)
{
	m_PlayerPos.fX = _x;
	m_PlayerPos.fY = _y;
}
