#pragma once
#include "afxwin.h"
#include "User.h"



// ProfileView ��ȭ �����Դϴ�.

class ProfileView : public CDialogEx
{
	DECLARE_DYNAMIC(ProfileView)

public:
	ProfileView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ProfileView();

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_profile };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	void Profile_view();

	CEdit m_str, m_str2, m_str3, m_str4;
	CString user_name;
	CString NSL_name[32];

	//vector<People> People_v;
	void PeopleAnalysis();
	afx_msg void OnEnChangeEdit4();
	virtual BOOL OnInitDialog();
};
