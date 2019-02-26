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

	DDX_Control(pDX, IDC_LIST_NOTICE, D_Notice);
	DDX_Control(pDX, IDC_Date, D_Title);
	D_Title.SetWindowTextW(Caption);
	for (int i = 0; i < TempDataVector.GetSize(); i++) 
	{
		Contents = TempDataVector[i];
		D_Notice.AddString(Contents);
	}




	/*
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_NOTICE, D_Notice);
	DDX_Control(pDX, IDC_Date, D_Title);
	D_Title.SetWindowTextW(Caption);

	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	CPropertiesWnd *pView = (CPropertiesWnd *)pChild->GetActiveView();


	for (int i = 0; i < (pView->cur_NSL_notice.size()); i++)
	{
	Contents = (pView->cur_NSL_notice[i].cMsg).c_str();
	D_Notice.AddString(Contents);
	}



	D_Notice.AddString(Contents);

	for (int i = 0; i < 30; i++)
	{
	if (Contents[i] != "")
	{
	notice.AddString(Contents[i]);
	}
	}
	*/
}
