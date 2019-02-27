// LoginDlg.cpp : 구현 파일입니다.
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
		AfxMessageBox(_T("IP인증에 실패하였습니다."));
}


void CLogin::OnLogOKBtnClicked()
{
	
	CString csInput;
	if (PassWord == "NULL")
	{
		GetDlgItem(IDC_PWINPUT)->GetWindowTextW(PassWord);
		//SendPWMessage(UserID, PassWord); 서버로 비밀번호 전송해서 DB에 비밀번호 저장하는 함수 필요함
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
	/*																		OnAllTopicTitleMessage사용법 참고
	GetDlgItem(IDC_PWINPUT)->GetWindowTextW(PassWord);
	PassWord11 = string(CT2CA(PassWord.operator LPCWSTR()));
	GuiClientInterface::getInstance()->OnAllTopicTitleMessage(PassWord11);
	CDialog::OnOK();*/
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
			pMsg->wParam == VK_CANCEL)       //CTRL + PAUSE 방지
			return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}