
// ONC.h : ONC ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.

#include <iostream>
#include <string>
#include <vector>

#include <ctime>
using namespace std;

// CONCApp:
// �� Ŭ������ ������ ���ؼ��� ONC.cpp�� �����Ͻʽÿ�.
//

class CONCApp : public CWinAppEx
{
public:
	CONCApp();


	// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// �����Դϴ�.
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;
	CMultiDocTemplate* pDocTemplate;
	CDocument* pDoc;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CONCApp theApp;
