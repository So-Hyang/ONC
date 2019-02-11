// AddView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ONC.h"
#include "AddView.h"
#include "afxdialogex.h"


// AddView 대화 상자입니다.

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

	//콤보박스 리스트 추가
	PubPri.AddString(TEXT("공개"));
	PubPri.AddString(TEXT("비공개"));

	//콤보박스 수정 불가
	CWnd *p_combo = GetDlgItem(IDC_COMBO1);
	HWND h_wnd = ::FindWindowEx(p_combo->m_hWnd, NULL, _T("Edit"), NULL);
	if (NULL != h_wnd)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	DDX_Control(pDX, IDC_Date, date);
	date.SetWindowTextW(Caption);
	DDX_Control(pDX, IDC_EDIT1, CalEdit);
}


BEGIN_MESSAGE_MAP(AddView, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &AddView::OnBnClickedAdd)
END_MESSAGE_MAP()


// AddView 메시지 처리기입니다.


void AddView::OnBnClickedAdd()
{
	/*int nLength = CalEdit.GetWindowTextLengthW();
	CalEdit.SetSel(nLength, nLength);
	CalEdit.ReplaceSel(Caption);
	CalEdit.GetWindowTextW()*/

	CString str = L"";
	PubPri.GetLBText(PubPri.GetCurSel(), str);

	int nLen = CalEdit.GetWindowTextLength();
	CalEdit.SetFocus();
	CalEdit.SetSel(nLen, nLen);
	CalEdit.ReplaceSel(str);

	CalEdit.SetWindowText(str);
	test = str;


	AddView::OnOK();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
