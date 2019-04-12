#pragma once

#include "Include.h"

class CKeyMgr
{
private:
	DWORD		m_dwKey;

public:
	DWORD GetKey(void) const {return m_dwKey;}

public:
	void CheckKey(void);

private:
	static CKeyMgr*	m_pInst;

public:
	static CKeyMgr* GetInst(void)
	{
		if(m_pInst == NULL)
			m_pInst = new CKeyMgr;

		return m_pInst;
	}

	void DestroyInst(void)
	{
		::Safe_Delete(m_pInst);
	}

private:
	CKeyMgr(void);

public:
	~CKeyMgr(void);
};
