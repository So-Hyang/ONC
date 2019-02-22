#pragma once
#include <string>
#include "afxwin.h"
#include "DataManager.h"

using namespace std;

// LoginDlg 대화 상자입니다.

struct PeopleInfo
{
	string IP;
	string PW;
	string ID;
};

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CLogin();


private:
	PeopleInfo PeopleInfo;
	afx_msg void OnIPAuthenticationBtnClicked();
	afx_msg void OnLogOKBtnClicked();
	string GetIpAddress();
	CString PassWord;
	CString UserID;


	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

