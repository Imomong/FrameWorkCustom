#pragma once
#include "stateobj.h"

class CObj;

class CStage :
	public CStateObj
{
private:
	CObj*			m_pBackGround;
	list<CObj*>		m_ObjList[OBJ_END];

	int				m_iMonster;
	int				m_iBulletPlayer;
	int				m_iBulletEnemy;
	int				m_iBulletEnemy2;
	int				m_iEffect;

	bool			m_bBossEffect;
	int				m_iEffectCount;
	float			m_fEffectTik;

	float			m_fDamage; //플레이어 데미지

	CObj*			m_ArrayMon[MonsterLimit];
	bool			m_bActiveMon;
	int				m_iMonCount;
	int				m_iKillCount;

	int				m_iGamePoint;
public:
	virtual void Initialize(void);
	virtual int Progress(void);
	virtual void Render(HDC hdc);
	virtual void Release(void);
private:
	void Collision(void);
	bool RangeCalculate(INFO _x, INFO _y, float _range);
	void BossEffect(void);
	void Scenario(void);
	void CheckKill(void);
	void PrintPoint(HDC hdc);
	void Restart(void);
public:
	CStage(void);
	virtual ~CStage(void);
};
