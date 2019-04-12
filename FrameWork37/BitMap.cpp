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
	m_hdc = GetDC(g_hWnd); // ȭ���
	m_MemDC = CreateCompatibleDC(m_hdc); // �̹��� ������ �����ϱ� ���ѵ�

	m_bitMap = (HBITMAP)LoadImage(NULL, pFileName, IMAGE_BITMAP, 
		0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if(!m_bitMap)
	{
		MessageBox(g_hWnd, pFileName,L"File Load False", NULL);
	}

	// SelectObject�Լ��� ����� : m_MemDC�� m_bitmap�� ������ ���� �ִ� ���� �����Ѵ�.
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
