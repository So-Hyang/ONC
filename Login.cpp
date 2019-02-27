// LoginDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ONC.h"
#include "Login.h"
#include "afxdialogex.h"
#include "Connect.h"
#include "SendRecv.h"
#include "DataPacket.h"
#include "PacketManager.h"
#include "ServerDataManager.h"
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

void CLogin::OnIPAuthenticationBtnClicked()
{
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	string str;
	CString cstr;
	if (mDataManager->FindMyInfo() == TRUE)
	{
		str = mDataManager->myinfo.Name;
		cstr = str.c_str();
		GetDlgItem(IDC_IPCER)->EnableWindow(FALSE);
		GetDlgItem(IDC_PWBUTTON)->EnableWindow(TRUE);
		GetDlgItem(IDC_PWINPUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_IPCER)->SetWindowTextW(cstr);

		PassWord = mDataManager->myinfo.Password.c_str();
	}
	else
		AfxMessageBox(_T("IP������ �����Ͽ����ϴ�."));
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
	/*																		OnAllTopicTitleMessage���� ����
	GetDlgItem(IDC_PWINPUT)->GetWindowTextW(PassWord);
	PassWord11 = string(CT2CA(PassWord.operator LPCWSTR()));
	GuiClientInterface::getInstance()->OnAllTopicTitleMessage(PassWord11);
	CDialog::OnOK();*/
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

	if (pMsg->message == WM_SYSKEYDOWN)
	{
		if (pMsg->wParam == VK_F4)
			return TRUE;
	}

	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE ||
			pMsg->wParam == VK_RETURN ||
			pMsg->wParam == VK_SPACE ||
			pMsg->wParam == VK_CANCEL)       //CTRL + PAUSE ����
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}