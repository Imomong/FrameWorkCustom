#include "StdAfx.h"
#include "BitMap.h"

CBitMap::CBitMap(void)
{
}

CBitMap::~CBitMap(void)
{
	Release();
}

CBitMap* CBitMap::LoadBmp( PTCHAR pFileName )
{
	m_hdc = GetDC(g_hWnd); // 화면디씨
	m_MemDC = CreateCompatibleDC(m_hdc); // 이미지 한장을 보관하기 위한디씨

	m_bitMap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(!m_bitMap)
	{
		MessageBox(g_hWnd, pFileName,L"File Load False", NULL);
	}

	// SelectObject함수의 결과값 : m_MemDC가 m_bitmap을 가지기 전에 있던 값을 리턴한다.
	m_oldbitMap = (HBITMAP)SelectObject(m_MemDC, m_bitMap);
	
	ReleaseDC(g_hWnd,m_hdc);
	return this;
}

void CBitMap::Release( void )
{
	SelectObject(m_MemDC, m_oldbitMap);
	DeleteObject(m_bitMap);
	DeleteObject(m_oldbitMap);
	DeleteDC(m_MemDC);
}
