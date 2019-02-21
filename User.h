
#pragma once

#include "ViewTree.h"
#include <iostream>
#include <string>
#include <vector>
#include "DataManager.h"
#include "DBCollector.h"


using namespace std;

class CClassToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CClassView : public CDockablePane
{
public:
	CClassView();
	virtual ~CClassView();

	void AdjustLayout();
	void OnChangeVisualStyle();
	void SetTreeData(vector<People_DB> peoples);

private:
	void MakeTreeview();

public:
	vector<People_DB> vecPeople;


protected:
	CClassToolBar m_wndToolBar;
	CViewTree m_wndClassView;
	CImageList m_ClassViewImages;
	CString myString = _T("3");



	// 재정의입니다.
public:
	//void SendEmergencyAlarmMessage(char* cMyID, char* cMsg);
	void CreateExitView();
	void profileView();
	void Onselectedtest();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

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

