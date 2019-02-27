#include "stdafx.h"
#include "DetailView.h"
#include "ONC.h"
#include "afxdialogex.h"
#include "Notice.h"

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

	DDX_Control(pDX, IDC_LIST_NOTICE, D_Notice);
	DDX_Control(pDX, IDC_Date, D_Title);
	D_Title.SetWindowTextW(Caption);


	for (int i = 0; i < TempDataVector.GetSize(); i++)
	{
		Contents = TempDataVector[i];
		D_Notice.AddString(Contents);
	}


	for (int i = 0; i < NoticeView.vecNoticeInfo.size(); i++)
	{
		string Noticecontents = (NoticeView.vecNoticeInfo[i].Notice_CUserID)+ (NoticeView.vecNoticeInfo[i].Notice_cMsg);
		CString NewNoticecontents(Noticecontents.c_str());
		D_Notice.InsertString(i + 1, NewNoticecontents);
	}

}
