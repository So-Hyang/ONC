// AddView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "ONC.h"
#include "AddView.h"
#include "afxdialogex.h"


// AddView ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(AddView, CDialogEx)

AddView::AddView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{
}

AddView::~AddView()
{
}

void AddView::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, PubPri); //���� ����� �޺� �ڽ� ǥ���ϴ°�

	//�޺��ڽ��� Pub/Pri ����Ʈ �߰�
	PubPri.AddString(TEXT("����"));
	PubPri.AddString(TEXT("�����"));

	//�޺��ڽ� ������ �Ұ����ϵ��� ����
	CWnd *p_combo = GetDlgItem(IDC_COMBO1);
	HWND h_wnd = ::FindWindowEx(p_combo->m_hWnd, NULL, _T("Edit"), NULL);
	if (NULL != h_wnd)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	DDX_Control(pDX, IDC_Date, date); //��¥ ǥ���ϴ� ����ƽ �ڽ� ǥ���ϴ°�
	date.SetWindowTextW(Caption);  //Caption�̶�� ������ ����ƽ �ڽ��� �� ����
	DDX_Control(pDX, IDC_EDIT1, CalEdit); //�޼��� �Է¹޴� ���� �ڽ� ǥ���ϴ°�
	
}


BEGIN_MESSAGE_MAP(AddView, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &AddView::OnBnClickedAdd)
END_MESSAGE_MAP()


// AddView �޽��� ó�����Դϴ�.


void AddView::OnBnClickedAdd() //��ư Ŭ�� �̺�Ʈ
{
	/*int nLength = CalEdit.GetWindowTextLengthW();
	CalEdit.SetSel(nLength, nLength);
	CalEdit.ReplaceSel(Caption);
	CalEdit.GetWindowTextW()*/
	int index = 0;
	index = PubPri.GetCurSel(); //�޺� �ڽ����� � �κ��� ���õǾ��°�

	if (index == -1) //�ƹ��͵� ���õ��� �ʾ�����
	{
		AddView::OnCancel(); //��� ���� ��ȯ
	}
	else  //�ƹ��ų� ���õǾ��� ��
	{
		PubPri.GetLBText(index, a_status);//�޺� �ڽ� �߿� ���� ���� �Ǿ������� ���� ���� a_status ������ ����

		int nLen = CalEdit.GetWindowTextLength();
		CalEdit.SetFocus();
		CalEdit.SetSel(nLen, nLen);

		CalEdit.GetWindowTextW(a_contents); //���� �ڽ��� �ԷµǾ� �ִ� �ؽ�Ʈ ���� a_contents ������ ����
		AddView::OnOK(); //OK ���� ��ȯ
	}
	


	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
