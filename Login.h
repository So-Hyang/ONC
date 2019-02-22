#pragma once
#include <string>
#include "afxwin.h"
#include "DataManager.h"

using namespace std;

// LoginDlg ��ȭ �����Դϴ�.

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
	CLogin(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CLogin();


private:
	PeopleInfo PeopleInfo;
	afx_msg void OnIPAuthenticationBtnClicked();
	afx_msg void OnLogOKBtnClicked();
	string GetIpAddress();
	CString PassWord;
	CString UserID;


	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);

};

