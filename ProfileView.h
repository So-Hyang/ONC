#pragma once
#include "afxwin.h"
#include "User.h"



// ProfileView 대화 상자입니다.

class ProfileView : public CDialogEx
{
	DECLARE_DYNAMIC(ProfileView)

public:
	ProfileView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ProfileView();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_profile };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
