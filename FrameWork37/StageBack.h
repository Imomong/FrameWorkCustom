#pragma once
#include "obj.h"

class CStageBack :
	public CObj
{
private:
	CObj*	m_pPlayer;
	POINT	m_ptOffSet;
	SCROLL	m_Scroll;

	int iYCount;
	int iStartTime;

public:
	void SetPlayer(CObj* pPlayer) {m_pPlayer = pPlayer;}
	void StageScroll( void );
	void DelayTik();
public:
	virtual void Initialize( void );
	virtual int Progress( void );
	virtual void Render( HDC hdc );
	virtual void Release( void );

public:
	CStageBack(void);
	virtual ~CStageBack(void);
};
