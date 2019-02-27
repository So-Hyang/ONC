// ProfileView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ONC.h"
#include "ProfileView.h"
#include "afxdialogex.h"
#include "MainFrm.h"

// ProfileView ��ȭ �����Դϴ�.

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
	DDX_Control(pDX, IDC_EDIT4, m_str4); //�׽�Ʈ ��ÿ�
}


BEGIN_MESSAGE_MAP(ProfileView, CDialogEx)
	
	ON_EN_CHANGE(IDC_EDIT1, &ProfileView::OnEnChangeEdit1)

	ON_EN_CHANGE(IDC_EDIT2, &ProfileView::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &ProfileView::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &ProfileView::OnEnChangeEdit4)
END_MESSAGE_MAP()


// ProfileView �޽��� ó�����Դϴ�.


void ProfileView::Profile_view()
{





}




void ProfileView::PeopleAnalysis()
{


}







void ProfileView::OnEnChangeEdit1() //���ݶ�
{

}





void ProfileView::OnEnChangeEdit2() // �л� ��ȣ
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProfileView::OnEnChangeEdit3()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ProfileView::OnEnChangeEdit4()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


BOOL ProfileView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
