#include "ONC.h"
#pragma once

struct NoticeInfo//DM ������ ��Ŷ
{
	unsigned int nType;
	string TopicTitle;
	string cUserID;
	string cMsg;
	string cDate;
	string cPassWord;
	string cSenderID;
	string Participants;
	bool PubPrivate;
};

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
	// �����Դϴ�.
public:
	CPropertiesWnd();

	void AdjustLayout();
	void Get_CalendarNotice();
	vector<NoticeInfo> dm_noticeinfo{
		{ 1, "", "ID", "contents1", "2018-10-22", "", "", "", true },{ 1, "", "ID", "contents2", "2019-02-20", "", "", "", true },{ 1, "", "ID", "contents3", "2019-02-20", "", "", "", true },
		{ 1, "", "ID", "contents4", "2019-02-28", "", "", "", true },{ 2, "", "ID", "contents5", "2019-02-20", "", "", "", false },{ 2, "", "ID", "contents6", "2019-02-20", "", "", "", false },
		{ 1, "", "ID", "contents7", "2019-03-01", "", "", "", true },{ 1, "", "ID", "contents8", "2019-04-20", "", "", "", true },{ 3, "", "ID", "contents7", "2019-03-01", "", "", "", true }
	};
	vector<NoticeInfo> cur_NSL_notice{};

	// Ư���Դϴ�.
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

	// �����Դϴ�.
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
	vector<NoticeInfo> LoadListNotice(int type, CString status, CString name, string date);
	CString SelectedLatesofList(vector<NoticeInfo> schedule);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	void OnViewAllBtnCLicked();

	int m_nComboHeight;
};

