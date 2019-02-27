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

struct ALLNoticeInfo
{
	string Notice_CUserID;
	string Notice_cMsg;
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
/*	
	vector<NoticeInfo> dm_noticeinfo{
		{ 1, "", "ID", "NSL1", "2018-10-22", "", "", "", true },{ 1, "", "ID", "NSL2", "2019-02-26", "", "", "", true },{ 1, "", "ID", "NSL3", "2019-02-26", "", "", "", true },
		{ 1, "", "IDDDD", "NSL4_ID 다름", "2019-02-26", "", "", "", true },{ 2, "", "ID", "개인1", "2019-02-26", "", "", "", false },{1, "", "ID", "NSL5", "2019-02-26", "", "","", true},
		{ 2, "", "ID", "개인2", "2019-02-26", "", "", "", false },{ 1, "", "ID", "NSL6", "2019-03-01", "", "", "", true },{ 2, "", "ID", "개인3", "2019-04-20", "", "", "", false },
		{ 3, "", "ID", "Notice", "2019-05-01", "", "", "", true },{ 2, "", "IDDDD", "개인4_ID 다름", "2019-02-26", "", "", "", false }
	};
	vector<NoticeInfo> cur_NSL_notice{};
	vector<NoticeInfo> cur_Personal_notice{};
	*/
	string N_cur_Year;
	string N_cur_Month;
	string N_cur_Day;

	vector<ALLNoticeInfo>vecNoticeInfo;
	void AddNoticeInfo(ALLNoticeInfo Infos);
	void AddNoticeInfoDB();
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
	afx_msg void OnViewAddBtnCLicked();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);
	//vector<NoticeInfo> LoadListNotice(int type, string name, string date);
	//CString SelectedLatesofList(vector<NoticeInfo> schedule);

	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	void OnViewAllBtnCLicked();

	int m_nComboHeight;
};

