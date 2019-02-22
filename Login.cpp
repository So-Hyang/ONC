// LoginDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ONC.h"
#include "Login.h"
#include "afxdialogex.h"
#pragma warning(disable:4996)




vector<PeopleInfo> dumi;

using namespace std;


// LoginDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN, pParent)
{
}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_IPCER, &CLogin::OnIPAuthenticationBtnClicked)
	ON_BN_CLICKED(IDC_PWBUTTON, &CLogin::OnLogOKBtnClicked)
END_MESSAGE_MAP()


// LoginDlg 메시지 처리기입니다.
string CLogin::GetIpAddress()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	string strIpAddress;
	wVersionRequested = MAKEWORD(2, 0);

	if (WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if (gethostname(name, sizeof(name)) == 0)
		{
			if ((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa(*(struct in_addr *)*hostinfo->h_addr_list);
		}
		WSACleanup();
	}
	return strIpAddress;
}

void CLogin::OnIPAuthenticationBtnClicked()
{
	//int count;
	string sUserIP;
	CString csUserIP;

	sUserIP = GetIpAddress();

	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	mDataManager->

	csUserIP = sUserIP.c_str();
	GetDlgItem(IDC_IPCER)->EnableWindow(FALSE);
	GetDlgItem(IDC_PWBUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_PWINPUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPCER)->SetWindowTextW(csUserIP);

	/*
	for(count=0;count<40;count++)
	{
	if (sUserIP.compare(dumi[count].IP)==0)
	{
	csUserIP = dumi[count].ID.c_str();

	GetDlgItem(IDC_IPCER)->EnableWindow(FALSE);
	GetDlgItem(IDC_PWBUTTON)->EnableWindow(TRUE);
	GetDlgItem(IDC_IPCER)->SetWindowTextW(csUserIP);

	PassWord = dumi[count].PW;
	}
	}	*/
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CLogin::OnLogOKBtnClicked()
{
	CString csInput;
	if (PassWord == "")
	{
		GetDlgItem(IDC_PWINPUT)->GetWindowTextW(PassWord);
		//SendPWMessage(UserID, PassWord);
		AfxMessageBox(_T("패스워드가 설정되었습니다."));
	}

	else
	{
		GetDlgItem(IDC_PWINPUT)->GetWindowTextW(csInput);
		if (PassWord.Compare(csInput) == 0)
		{
			CDialog::OnOK();
		}
		else
		{
			AfxMessageBox(_T("비밀번호를 확인하세요."));
		}
	}
}


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	CString sContent;
	// ESC 키
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		// 여기에 원하는 동작의 코드를 삽입
		return true;
	}

	// 엔터키
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// 여기에 원하는 동작의 코드를 삽입
		CEdit *pEdit = (CEdit*)GetDlgItem(IDC_PWINPUT);
		pEdit->GetWindowText(sContent);
		if (sContent != "")
		{
			OnLogOKBtnClicked();
		}
		return true;
	}
	return CDialog::PreTranslateMessage(pMsg);
}