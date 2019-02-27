#include "ONC.h"
#include "DataManager.h"
#pragma once


class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
	// 생성입니다.
public:
	CPropertiesWnd();

	void AdjustLayout();
	void Get_CalendarNotice();

	vector<CalenderNotice> dm_noticeinfo{};
	vector<CalenderNotice> cur_NSL_notice{};
	vector<CalenderNotice> cur_Personal_notice{};

	string N_cur_Year;
	string N_cur_Month;
	string N_cur_Day;

	// 특성입니다.
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}

protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;
	CMFCPropertyGridCtrl m_wndPropList;

	// 구현입니다.
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnViewNSLBtnCLicked();
	afx_msg void OnViewPERSONALBtnCLicked();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	vector<CalenderNotice> LoadListNotice(int type, string name, string date);
	CString SelectedLatesofList(vector<CalenderNotice> schedule);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	void OnViewAllBtnCLicked();

	int m_nComboHeight;
};

