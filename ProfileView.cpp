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
	ON_BN_CLICKED(IDC_BUTTON1, &ProfileView::OnBnClickedButton1)
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



void ProfileView::OnBnClickedButton1() 
{
	People mPeople;

	mPeople.Birthday = "940203"; // 더미데이터 // USER NAME = 김시완 
	mPeople.Fine = "5000";
	mPeople.name = "kimsiwan";
	mPeople.Phone_N = "010-4741-5688";
	mPeople.Student_N = "20186081";
	People_v.push_back(mPeople); // 

	mPeople.Birthday = "5235235"; // 
	mPeople.Fine = "5003434340";
	mPeople.name = "lee";
	mPeople.Phone_N = "0155550-4741-5688";
	mPeople.Student_N = "2000000186081";
	People_v.push_back(mPeople);

	mPeople.Birthday = "234234"; // 
	mPeople.Fine = "5023423400";
	mPeople.name = "c";
	mPeople.Phone_N = "0111110-4741-5688";
	mPeople.Student_N = "201866666081";
	People_v.push_back(mPeople);

	mPeople.Birthday = "940203"; //
	mPeople.Fine = "5000";
	mPeople.name = "b";
	mPeople.Phone_N = "010-4741-5688정답";
	mPeople.Student_N = "20186081";
	People_v.push_back(mPeople);

	for (vector<People>::iterator i = People_v.begin(); i != People_v.end(); i++)
	{
		string a = (*i).Fine;
		string b = (*i).name;
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
	//for (int count = 0; count < People_v.size(); count++)
	//{
	//	string a = People_v[count].Fine;
	//	string b = People_v[count].name;
	//	string c = People_v[count].Phone_N;
	//	string d = People_v[count].Student_N;

	//	if (b.compare(str_user_name) == 0)
	//	{
	//		str_Fine = People_v[count].Fine;
	//		str_name = People_v[count].name;
	//		str_Phone_N = People_v[count].Phone_N;
	//		str_Student_N = People_v[count].Student_N;

	//		CString Fine(str_Fine.c_str()); // string to CString
	//		CString Phone_N(str_name.c_str());
	//		CString Student_N(str_Phone_N.c_str());
	//		CString name(str_Student_N.c_str());

	//		m_str.SetWindowTextW(Fine);
	//		m_str2.SetWindowTextW(Phone_N);
	//		m_str3.SetWindowTextW(Student_N);
	//		m_str4.SetWindowTextW(user_name);
	//	}
	//}

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
