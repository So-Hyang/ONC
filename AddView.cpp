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
	DDX_Control(pDX, IDC_COMBO1, PubPri);

	//�޺��ڽ� ����Ʈ �߰�
	PubPri.AddString(TEXT("����"));
	PubPri.AddString(TEXT("�����"));

	//�޺��ڽ� ���� �Ұ�
	CWnd *p_combo = GetDlgItem(IDC_COMBO1);
	HWND h_wnd = ::FindWindowEx(p_combo->m_hWnd, NULL, _T("Edit"), NULL);
	if (NULL != h_wnd)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	DDX_Control(pDX, IDC_Date, date);
	date.SetWindowTextW(Caption);
	DDX_Control(pDX, IDC_EDIT1, CalEdit);
	PubPri.GetWindowTextW(a_status);
}


BEGIN_MESSAGE_MAP(AddView, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &AddView::OnBnClickedAdd)
END_MESSAGE_MAP()


// AddView �޽��� ó�����Դϴ�.


void AddView::OnBnClickedAdd()
{
	/*int nLength = CalEdit.GetWindowTextLengthW();
	CalEdit.SetSel(nLength, nLength);
	CalEdit.ReplaceSel(Caption);
	CalEdit.GetWindowTextW()*/
	int index = 0;
	index = PubPri.GetCurSel();
	if (index == -1)
	{
		AddView::OnCancel();
	}
	else 
	{
		PubPri.GetLBText(PubPri.GetCurSel(), a_status);

		int nLen = CalEdit.GetWindowTextLength();
		CalEdit.SetFocus();
		CalEdit.SetSel(nLen, nLen);

		CalEdit.GetWindowTextW(a_contents);
		AddView::OnOK();
	}
	


	
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
