#include "stdafx.h"
#include "DetailView.h"
#include "ONC.h"
#include "afxdialogex.h"
#include "Notice.h"
#include "DataManager.h"

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
	CPropertiesWnd NoticeView;
	CString NewNoticecontents;
	int i;

	DDX_Control(pDX, IDC_LIST_NOTICE, D_Notice);
	DDX_Control(pDX, IDC_Date, D_Title);
	D_Title.SetWindowTextW(Caption);

	for (int i = 0; i < TempDataVector.GetSize(); i++)
	{
		Contents = TempDataVector[i];
		D_Notice.AddString(Contents);
	}

}
