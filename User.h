
#pragma once

#include "ViewTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

struct People {
	string Name;
	string IP;
	string Birthday;
	string Student_N;
	string Phone_N;
	string Fine;
	string Password;
};

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void SetTreeData(vector<People> peoples);

private:
	void MakeTreeview();

public:
	vector<People> vecPeople;


protected:
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	CString myString = _T("3");



	// 재정의입니다.
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void SendEmergencyAlarmMessage(char* cMyID, char* cMsg);
	void CreateExitView();
	void profileView();
	void Onselectedtest();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg LRESULT OnChangeActiveTab(WPARAM, LPARAM);
	afx_msg void OnLoudSpeakerImageBtnClicked();
	afx_msg void OnExitImageBtnClicked();
	afx_msg void OnInImageBtnClicked();
	afx_msg void OnOutImageBtnClicked();
	afx_msg void OnSortingSortbyaccess();

	DECLARE_MESSAGE_MAP()
	
};

