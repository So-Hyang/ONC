#include "stdafx.h"
#include "DetailView.h"
#include "ONC.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CDetailView, CDialogEx)


BEGIN_MESSAGE_MAP(CDetailView, CDialogEx)
END_MESSAGE_MAP()

CDetailView::CDetailView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_DETAIL, pParent)
{
}

CDetailView::~CDetailView()
{
}

void CDetailView::DoDataExchange(CDataExchange * pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_NOTICE, notice);
	DDX_Control(pDX, IDC_Date, date);

	notice.AddString(TEXT("첫번째 세부일정"));
	notice.AddString(TEXT("두번째 세부일정"));
	date.SetWindowTextW(L"변경예정");
}
