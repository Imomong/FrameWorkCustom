#pragma once

#include "Include.h"

class CStateObj;

class CStateMgr
{
private:
	CStateObj*		m_pState;

public:
	void SetState(STATEID _estate);
	void Progress(void);
	void Render(HDC hdc);
	void Release(void);


private:
	static CStateMgr*	m_pInst;

public:
	static CStateMgr* GetInst(void)
	{
		if(m_pInst == NULL)
			m_pInst = new CStateMgr;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		::Safe_Delete(m_pInst);
	}

private:
	CStateMgr(void);

public:
	
	~CStateMgr(void);
};
