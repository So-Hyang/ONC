// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ONC.h"
#include "Login.h"
#include "afxdialogex.h"
#pragma warning(disable:4996)




vector<PeopleInfo> dumi;

using namespace std;


// LoginDlg ��ȭ �����Դϴ�.

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


// LoginDlg �޽��� ó�����Դϴ�.
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
	int count;
	string sUserIP;
	CString csUserIP;
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	sUserIP = GetIpAddress();

	for(count=0;count<mDataManager->people_v.size();count++)
	{
		if (sUserIP.compare(mDataManager->people_v[count].IP) == 0)
		{
			csUserIP = mDataManager->people_v[count].name.c_str();

			GetDlgItem(IDC_IPCER)->EnableWindow(FALSE);
			GetDlgItem(IDC_PWBUTTON)->EnableWindow(TRUE);
			GetDlgItem(IDC_PWINPUT)->EnableWindow(TRUE);
			GetDlgItem(IDC_IPCER)->SetWindowTextW(csUserIP);

			PassWord = mDataManager->people_v[count].Password.c_str();



		}
	}	
}


void CLogin::OnLogOKBtnClicked()
{
	CString csInput;
	if (PassWord == "NULL")
	{
		GetDlgItem(IDC_PWINPUT)->GetWindowTextW(PassWord);
		//SendPWMessage(UserID, PassWord); ������ ��й�ȣ �����ؼ� DB�� ��й�ȣ �����ϴ� �Լ� �ʿ���
		AfxMessageBox(_T("�н����尡 �����Ǿ����ϴ�."));
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
			AfxMessageBox(_T("��й�ȣ�� Ȯ���ϼ���."));
		}
	}
}


BOOL CLogin::PreTranslateMessage(MSG* pMsg)
{
	CString sContent;
	// ESC Ű
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_ESCAPE))
	{
		// ���⿡ ���ϴ� ������ �ڵ带 ����
		return true;
	}

	// ����Ű
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN))
	{
		// ���⿡ ���ϴ� ������ �ڵ带 ����
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