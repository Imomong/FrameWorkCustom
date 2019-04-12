#include "StdAfx.h"
#include "Stage.h"
#include "ObjFactory.h"
#include "StageBack.h"
#include "Player.h"
#include "Device.h"
#include "Monster.h"
#include "ObjMgr.h"

#include "CBullet_Player.h"
#include "CBullet_Enemy2.h"
#include "CMonster_Boss.h"
#include "CEffect.h"

CStage::CStage(void)
: m_pBackGround(NULL)
{
}

CStage::~CStage(void)
{
}

void CStage::Initialize( void )
{
	//생성숫자 지정
	m_iMonster = 9;
	m_iBulletPlayer = 50;
	m_iBulletEnemy = 100;
	m_iBulletEnemy2 = 100;
	m_iEffect = 10;

	//변수 설정 초기화
	m_bBossEffect = false;
	m_iEffectCount = 0;
	m_fEffectTik = GetTickCount();

	m_fDamage = 5;

	m_bActiveMon = true;
	m_iMonCount = 0;
	m_iKillCount = 0;

	m_iGamePoint = 0;

	//버퍼-백그라운드
	m_MapBmp["BackBuffer"] = (new CBitMap)->LoadBmp(L"../Texture/BackBuffer.bmp");
	m_MapBmp["BackGround"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Back/Stage_1.bmp");

	//플레이어
	m_MapBmp["Player_UP"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player2/Player_up.bmp");
	m_MapBmp["Player_DOWN"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player2/Player.bmp");
	m_MapBmp["Player_LEFT"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player2/Player_left.bmp");
	m_MapBmp["Player_RIGHT"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Player2/Player_right.bmp");

	//몬스터
	m_MapBmp["Monster"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/Monster.bmp");
	m_MapBmp["Monster_Boss"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Monster/Boss.bmp");
	
	//총알
	m_MapBmp["Bullet_Player"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Bullet/Bullet_Eg_a.bmp");
	m_MapBmp["Bullet_Enemy"] = (new CBitMap)->LoadBmp(L"../Texture/Stage/Bullet/Bullet_Enemy.bmp");

	//이펙트
	m_MapBmp["Effect_Player"] = (new CBitMap)->LoadBmp(L"../Texture/Effect/Effect_Player.bmp");
	m_MapBmp["Effect_Bullet"] = (new CBitMap)->LoadBmp(L"../Texture/Effect/Effect_Bullet.bmp");

	//UI
	m_MapBmp["UI_1"] = (new CBitMap)->LoadBmp(L"../Texture/UI/Status1.bmp");
	m_MapBmp["UI_2"] = (new CBitMap)->LoadBmp(L"../Texture/UI/Status2.bmp");
	m_MapBmp["UI_RESTART"] = (new CBitMap)->LoadBmp(L"../Texture/UI/Restart.bmp");
	m_MapBmp["UI_SCORE"] = (new CBitMap)->LoadBmp(L"../Texture/UI/Score.bmp");

	// 사운드
	CDevice::GetInstance()->LoadWave(L"../sound/Stage1.wav");
	CDevice::GetInstance()->LoadWave(L"../sound/Monster1.wav");
	CDevice::GetInstance()->LoadWave(L"../sound/Missile.wav");

	//배경 생성
	m_pBackGround = CObjFactory<CStageBack>::CreateObj();

	//플레이어 생성
	CObj*	pPlayer = CObjFactory<CPlayer>::CreateObj();
	m_ObjList[OBJ_PLAYER].push_back(pPlayer);

	((CStageBack*)m_pBackGround)->SetPlayer(pPlayer);

	//몬스터 생성

	for(int i = 0; i < m_iMonster; ++i)		
	{
		CObj*	pMonster = CObjFactory<CMonster>::CreateObj(float(rand() % WINCX), 0);
		m_ArrayMon[i] = pMonster;
		m_ObjList[OBJ_MONSTER].push_back(pMonster);
	}

	//몬스터 생성(보스)

	CObj*	pMonster_Boss = CObjFactory<Monster_Boss>::CreateObj(WINCX/2, -200);
	m_ObjList[OBJ_MONSTER_BOSS].push_back(pMonster_Boss);
	((Monster_Boss*)pMonster_Boss)->m_bActive = false;
	m_ArrayMon[9] = pMonster_Boss;

	//총알 생성(미리)
	for (int i = 0; i < m_iBulletPlayer; ++i)
	{
		CObj*	pBulletPlayer = CObjFactory<CBullet_Player>::CreateObj();
		m_ObjList[OBJ_BULLET].push_back(pBulletPlayer);
	}

	for (int i = 0; i < m_iBulletEnemy; ++i)
	{
		CObj*	pBulletEnemy = CObjFactory<CBullet_Enemy>::CreateObj();
		m_ObjList[OBJ_BULLET_ENEMY].push_back(pBulletEnemy);
	}

	for (int i = 0; i < m_iBulletEnemy2; ++i)
	{
		CObj*	pBulletEnemy = CObjFactory<CBullet_Enemy2>::CreateObj();
		m_ObjList[OBJ_BULLET_ENEMY2].push_back(pBulletEnemy);
	}

	//이펙트(미리)
	for (int i = 0; i < m_iEffect; i++)
	{
		CObj*	pEffect = CObjFactory<CEffect>::CreateObj();
		pEffect->SetSize(128, 128);
		((CEffect*)(pEffect))->SetSprite("Effect_Player", 6);
		((CEffect*)(pEffect))->m_bActive = false;
		m_ObjList[OBJ_EFFECT].push_back(pEffect);
	}

	CObjMgr::GetInst()->SetListObj(m_ObjList);

	CObj::SetBmp(&m_MapBmp);
	CDevice::GetInstance()->SoundPlay(0, 1);
}

int CStage::Progress( void )
{
	m_pBackGround->Progress();

	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			(*iter)->Progress();

			CObjMgr::GetInst()->AddRenderObj(*iter);
		}
	} 

	Collision();

	if (m_fEffectTik < GetTickCount())
	{
		m_fEffectTik = GetTickCount();
		BossEffect();
	}

	Scenario();

	list<CObj*>::iterator player = m_ObjList[OBJ_PLAYER].begin();
	if (((CPlayer*)(*player))->m_bRestart) Restart();

	return 0;
}

void CStage::Render( HDC hdc )
{
	m_pBackGround->Render(m_MapBmp["BackBuffer"]->GetMemDC());

	CObjMgr::GetInst()->Render(m_MapBmp["BackBuffer"]->GetMemDC());
	PrintPoint(m_MapBmp["BackBuffer"]->GetMemDC());

	//벡버퍼
	BitBlt(hdc, 0,0,WINCX, WINCY, 
		m_MapBmp["BackBuffer"]->GetMemDC(), 
		0,0,SRCCOPY);

	CObjMgr::GetInst()->Clear();
}

void CStage::Release( void )
{
	CStateObj::Release();
	Safe_Delete(m_pBackGround);

	for(int i = 0; i < OBJ_END; ++i)
	{
		for(list<CObj*>::iterator iter = m_ObjList[i].begin(); iter != m_ObjList[i].end(); ++iter)
		{
			Safe_Delete(*iter);
		}
		m_ObjList[i].clear();
	}
}

void CStage::Collision()
{
	//몬스터 - 플레이어 총알 충돌
	for (list<CObj*>::iterator iter1 = m_ObjList[OBJ_MONSTER].begin(); iter1 != m_ObjList[OBJ_MONSTER].end(); ++iter1)
	{
		for (list<CObj*>::iterator iter2 = m_ObjList[OBJ_BULLET].begin(); iter2 != m_ObjList[OBJ_BULLET].end(); ++iter2)
		{
			if (RangeCalculate((*iter1)->GetInfo(), (*iter2)->GetInfo(), (*iter1)->GetInfo().fCX/2) &&
				((CBullet_Player*)(*iter2))->GetActive() && ((CMonster*)(*iter1))->m_bActive)
			{
				((CMonster*)(*iter1))->m_iHP -= m_fDamage;
				m_iGamePoint += 1; // 명중시 1점
				//죽었을시 이펙트 활성화
				if (((CMonster*)(*iter1))->m_iHP <= 0)
				{
					m_iKillCount++;
					CheckKill();
					m_iGamePoint += 5; // 사살시 5점

					for (list<CObj*>::iterator effect = m_ObjList[OBJ_EFFECT].begin(); effect != m_ObjList[OBJ_EFFECT].end(); ++effect)
					{
						if (!((CEffect*)(*effect))->m_bActive)
						{
							(*effect)->SetPos((*iter1)->GetInfo().fX, (*iter1)->GetInfo().fY);
							((CEffect*)(*effect))->m_bActive = true;
							CDevice::GetInstance()->SoundPlay(1, 0);

							break;
						}
						
					}
				}
				
				((CBullet_Player*)(*iter2))->SetActive(false);
			}
		}
	}

	//보스 - 플레이어 총알 충돌
	list<CObj*>::iterator boss = m_ObjList[OBJ_MONSTER_BOSS].begin();

	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET].begin(); iter != m_ObjList[OBJ_BULLET].end(); ++iter)
	{
		if (RangeCalculate((*boss)->GetInfo(), (*iter)->GetInfo(), (*boss)->GetInfo().fCX / 2) &&
			((CBullet_Player*)(*iter))->GetActive() && ((Monster_Boss*)(*boss))->m_bActive)
		{
			((Monster_Boss*)(*boss))->m_iHP -= m_fDamage;
			m_iGamePoint += 1; // 명중시 1점
			//죽었을때 이펙트 활성화
			if (((Monster_Boss*)(*boss))->m_iHP <= 0)
			{
				m_iKillCount++;
				m_iGamePoint += 1; // 사살시 100점

				((Monster_Boss*)(*boss))->m_bActive = false;
				m_bBossEffect = true;

				//게임종료
				list<CObj*>::iterator player = m_ObjList[OBJ_PLAYER].begin();
				((CPlayer*)(*player))->m_iHP = -5;
			}
			
			((CBullet_Player*)(*iter))->SetActive(false);
		}
	}

	//플레이어 - 몬스터 총알 충돌
	list<CObj*>::iterator player = m_ObjList[OBJ_PLAYER].begin();

	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET_ENEMY].begin(); iter != m_ObjList[OBJ_BULLET_ENEMY].end(); ++iter)
	{
		if (RangeCalculate((*player)->GetInfo(), (*iter)->GetInfo(), (*iter)->GetInfo().fCX / 2) &&
			((CBullet_Enemy*)(*iter))->GetActive() && !((CPlayer*)(*player))->m_tPlayerHit)
		{
			((CPlayer*)(*player))->m_iHP -= 1;
			((CPlayer*)(*player))->SetHitInvi();
			
			m_iGamePoint -= 10; // 피해시 -10 감소
			((CBullet_Enemy*)(*iter))->SetActive(false);
		}
	}

	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET_ENEMY2].begin(); iter != m_ObjList[OBJ_BULLET_ENEMY2].end(); ++iter)
	{
		if (RangeCalculate((*player)->GetInfo(), (*iter)->GetInfo(), (*iter)->GetInfo().fCX / 2) &&
			((CBullet_Enemy2*)(*iter))->GetActive() && !((CPlayer*)(*player))->m_tPlayerHit)
		{
			((CPlayer*)(*player))->m_iHP -= 1;
			((CPlayer*)(*player))->SetHitInvi();

			m_iGamePoint -= 10; // 피해시 -10 감소
			((CBullet_Enemy2*)(*iter))->SetActive(false);
		}
	}
}

bool CStage::RangeCalculate(INFO _x, INFO _y, float _range)
{
	if ((_x.fX < _y.fX + _range && _x.fX > _y.fX - _range)
		&& (_x.fY < _y.fY + _range && _x.fY > _y.fY - _range))
	{
		return true;
	}
	return false;
}

void CStage::BossEffect()
{
	if (m_bBossEffect)
	{

		list<CObj*>::iterator boss = m_ObjList[OBJ_MONSTER_BOSS].begin();

		if (m_iEffectCount > EffectLimit)
		{
			((CEffect*)(*boss))->m_bActive = false;
			return;
		}

		for (list<CObj*>::iterator effect = m_ObjList[OBJ_EFFECT].begin(); effect != m_ObjList[OBJ_EFFECT].end(); ++effect)
		{
			if (!((CEffect*)(*effect))->m_bActive)
			{
				(*effect)->SetPos(
					((*boss)->GetInfo().fX - (*boss)->GetInfo().fCX / 2) + rand() % WINCX,
					((*boss)->GetInfo().fY - (*boss)->GetInfo().fCY / 2) + rand() % 200 + 200);
				((CEffect*)(*effect))->m_bActive = true;
				m_iEffectCount++;
				CDevice::GetInstance()->SoundPlay(1, 0);
				break;
			}
		}
	}
}

void CStage::Scenario()
{
	//처음시작
	if (m_bActiveMon && m_iKillCount == 0)
	{
		m_bActiveMon = false;

		for (int i = 0; i < 3; i++)
		{
			((CMonster*)(m_ArrayMon[i]))->m_bActive = true;
			((CMonster*)(m_ArrayMon[i]))->m_tBulletTik = GetTickCount();//시간 초기화
			((CMonster*)(m_ArrayMon[i]))->m_bStart = true;
		}
		return;
	}

	//두번째 웨이브
	if (m_bActiveMon && m_iKillCount == 3)
	{
		m_bActiveMon = false;
		for (int i = 3; i < 6; i++)
		{
			((CMonster*)(m_ArrayMon[i]))->m_bActive = true;
			((CMonster*)(m_ArrayMon[i]))->m_tBulletTik = GetTickCount();//시간 초기화
			((CMonster*)(m_ArrayMon[i]))->m_bStart = true;
		}

		return;
	}

	//세번째 웨이브
	if (m_bActiveMon && m_iKillCount == 6)
	{
		m_bActiveMon = false;

		for (int i = 6; i < 9; i++)
		{
			((CMonster*)(m_ArrayMon[i]))->m_bActive = true;
			((CMonster*)(m_ArrayMon[i]))->m_tBulletTik = GetTickCount();//시간 초기화
			((CMonster*)(m_ArrayMon[i]))->m_bStart = true;
		}
		return;
	}

	//보스
	if (m_bActiveMon && m_iKillCount == 9)
	{
		m_bActiveMon = false;

		((Monster_Boss*)(m_ArrayMon[9]))->m_bActive = true;
		((Monster_Boss*)(m_ArrayMon[9]))->m_tBulletTik = GetTickCount();//시간 초기화
		((Monster_Boss*)(m_ArrayMon[9]))->m_bStart = true;
		return;
	}
}

//킬확인 후 리스폰 활성화
void CStage::CheckKill(void)
{
	if ((m_iKillCount == 3 || m_iKillCount == 6 || m_iKillCount == 9)
		&& !m_bActiveMon)
	{
		m_bActiveMon = true;
	}
}

void CStage::PrintPoint(HDC hdc)
{
	if (m_iGamePoint < 0) m_iGamePoint = 0;

	int iThousand = m_iGamePoint % 10000 / 1000;
	int iHundred = m_iGamePoint % 1000 / 100;
	int iTen = m_iGamePoint % 100 / 10;
	int iOne = m_iGamePoint % 10;

	//천 자리
	TransparentBlt(hdc,
		0,
		0,
		47, 47,
		m_MapBmp["UI_SCORE"]->GetMemDC(),
		0, 47 * iThousand, 47, 47,
		RGB(255, 40, 255));

	//백 자리
	TransparentBlt(hdc,
		47,
		0,
		47, 47,
		m_MapBmp["UI_SCORE"]->GetMemDC(),
		0, 47 * iHundred, 47, 47,
		RGB(255, 40, 255));

	//십 자리
	TransparentBlt(hdc,
		94,
		0,
		47, 47,
		m_MapBmp["UI_SCORE"]->GetMemDC(),
		0, 47 * iTen, 47, 47,
		RGB(255, 40, 255));

	//일 자리
	TransparentBlt(hdc,
		141,
		0,
		47, 47,
		m_MapBmp["UI_SCORE"]->GetMemDC(),
		0, 47 * iOne, 47, 47,
		RGB(255, 40, 255));
}

void CStage::Restart(void)
{
	//점수 초기화
	m_bActiveMon = true;
	m_iMonCount = 0;
	m_iKillCount = 0;

	m_iGamePoint = 0;

	//플레이어 초기화
	list<CObj*>::iterator player = m_ObjList[OBJ_PLAYER].begin();
	(*player)->Initialize();

	//몬스터 초기화
	for (int i = 0; i < MonsterLimit - 1; i++)
	{
		m_ArrayMon[i]->Initialize();
		m_ArrayMon[i]->SetPos(float(rand() % WINCX), 0);
	}

	//보스 몬스터 초기화
	list<CObj*>::iterator boss = m_ObjList[OBJ_MONSTER_BOSS].begin();
	(*boss)->Initialize();
	(*boss)->SetPos(WINCX / 2, -200);

	//총알 초기화
	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET].begin(); iter != m_ObjList[OBJ_BULLET].end(); ++iter)
	{
		(*iter)->Initialize();
	}

	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET_ENEMY].begin(); iter != m_ObjList[OBJ_BULLET_ENEMY].end(); ++iter)
	{
		(*iter)->Initialize();
	}

	for (list<CObj*>::iterator iter = m_ObjList[OBJ_BULLET_ENEMY2].begin(); iter != m_ObjList[OBJ_BULLET_ENEMY2].end(); ++iter)
	{
		(*iter)->Initialize();
	}

	//이펙트 초기화
	for (list<CObj*>::iterator iter = m_ObjList[OBJ_EFFECT].begin(); iter != m_ObjList[OBJ_EFFECT].end(); ++iter)
	{
		(*iter)->Initialize();
	}

	CDevice::GetInstance()->SoundPlay(0, 1);

	((CPlayer*)(*player))->m_bRestart = false;
}
