// ProfileView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ONC.h"
#include "ProfileView.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// ProfileView 대화 상자입니다.

IMPLEMENT_DYNAMIC(ProfileView, CDialogEx)

ProfileView::ProfileView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PROFILE, pParent)
{

}

ProfileView::~ProfileView()
{

}

void ProfileView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//CString test2;
	//s_str = ("gdg");
	DDX_Control(pDX, IDC_EDIT1, m_str);
	DDX_Control(pDX, IDC_EDIT2, m_str2);
	DDX_Control(pDX, IDC_EDIT3, m_str3);
	DDX_Control(pDX, IDC_EDIT4, m_str4); //테스트 김시완
}


BEGIN_MESSAGE_MAP(ProfileView, CDialogEx)
	
	ON_EN_CHANGE(IDC_EDIT1, &ProfileView::OnEnChangeEdit1)

	ON_EN_CHANGE(IDC_EDIT2, &ProfileView::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &ProfileView::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &ProfileView::OnEnChangeEdit4)
END_MESSAGE_MAP()


// ProfileView 메시지 처리기입니다.


void ProfileView::Profile_view()
{





}




void ProfileView::PeopleAnalysis()
{


}







void ProfileView::OnEnChangeEdit1() //벌금란
{

}





void ProfileView::OnEnChangeEdit2() // 학생 번호
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProfileView::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void ProfileView::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


BOOL ProfileView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();

	for (vector<People_DB>::iterator i = mDataManager->people_v.begin(); i != mDataManager->people_v.end(); i++)
	{
		string a = (*i).Fine;
		string b = (*i).Name;
		string c = (*i).Phone_N;
		string d = (*i).Student_N;
		CString buf;
		buf = b.c_str();
		if (user_name.Compare(buf) == 0)
		{
			buf = a.c_str();
			m_str.SetWindowTextW(buf);
			buf = c.c_str();
			m_str2.SetWindowTextW(buf);
			buf = d.c_str();
			m_str3.SetWindowTextW(buf);
			buf = b.c_str();
			m_str4.SetWindowTextW(buf);
		}
	}
	DBConnect sDBConnect;
	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
