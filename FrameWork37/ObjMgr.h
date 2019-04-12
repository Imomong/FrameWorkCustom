#pragma once

#include "Include.h"
#include "CBullet_Player.h"
#include "CBullet_Enemy.h"
#include "CBullet_Enemy2.h"

class CObj;

class CObjMgr
{
private:
	INFO						m_PlayerPos;

	multimap<float, CObj*>		m_MapObj;
	list<CObj*>*				m_ListObj;

public:
	void AddRenderObj(CObj* pObj);
	void Render(HDC hdc);
	void Clear(void);
private:
	static CObjMgr*	m_pInst;

public:
	static CObjMgr* GetInst(void)
	{
		if(m_pInst == NULL)
			m_pInst = new CObjMgr;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		::Safe_Delete(m_pInst);
	}

public:
	void SetListObj(list<CObj*>* _list)
	{
		m_ListObj = _list;
	}

	CObj* SetActiveObj(int _enum);
	void SetPlayerPos(float _x, float _y);
private:
	CObjMgr(void);

public:
	~CObjMgr(void);
};
