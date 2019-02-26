#include "ONC.h"
#pragma once

struct NoticeInfo//DM 데이터 패킷
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
	// 생성입니다.
public:
	CPropertiesWnd();

	void AdjustLayout();
	void Get_CalendarNotice();
	vector<NoticeInfo> dm_noticeinfo{
		{ 1, "", "ID", "contents1", "2018-10-22", "", "", "", true },{ 1, "", "ID", "contents2", "2019-02-20", "", "", "", true },{ 1, "", "ID", "contents3", "2019-02-25", "", "", "", true },
		{ 1, "", "ID", "contents4", "2019-02-25", "", "", "", true },{ 2, "", "ID", "contents5", "2019-02-25", "", "", "", false },{1, "", "ID", "contents_sohyang", "2019-02-25", "", "","", true},
		{ 2, "", "ID", "contents6", "2019-02-25", "", "", "", false },{ 1, "", "ID", "contents7", "2019-03-01", "", "", "", true },{ 1, "", "ID", "contents8", "2019-04-20", "", "", "", true },
		{ 3, "", "ID", "contents7", "2019-05-01", "", "", "", true },{ 2, "", "ID", "contents7", "2019-02-25", "", "", "", true }
	};
	vector<NoticeInfo> cur_NSL_notice{};
	vector<NoticeInfo> cur_Personal_notice{};
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
	vector<NoticeInfo> LoadListNotice(int type, string name, string date);
	CString SelectedLatesofList(vector<NoticeInfo> schedule);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	void OnViewAllBtnCLicked();

	int m_nComboHeight;
};

