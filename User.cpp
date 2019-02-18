
#include "stdafx.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "User.h"
#include "Resource.h"
#include "ONC.h"
#include "ONCDoc.h"
#include "Chat.h"


class CClassViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CClassViewMenuButton)

public:
	CClassViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);
		pImages->EndDrawImage(ds);
		/////�׽�Ʈ�� �ϴ� ���� �߰��غ��ϴ�.
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// ����/�Ҹ�
//////////////////////////////////////////////////////////////////////

CClassView::CClassView()
{
}

CClassView::~CClassView()
{
}

BEGIN_MESSAGE_MAP(CClassView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(IDR_BITMAP_LS, OnLoudSpeakerImageBtnClicked)
	ON_COMMAND(IDB_BITMAP_EXIT, OnExitImageBtnClicked)
	ON_COMMAND(ID_BITMAP_IN, OnInImageBtnClicked)
	ON_COMMAND(ID_BITMAP_OUT, OnOutImageBtnClicked)
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClassView �޽��� ó����

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �並 ����ϴ�.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("Ŭ���� �並 ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}

	// �̹����� �ε��մϴ�.
	DWORD toolbarstyle = WS_CHILD | WS_VISIBLE|CBRS_TOOLTIPS ;
	toolbarstyle |= (CBRS_ALIGN_BOTTOM & CBRS_ALIGN_ANY);

	m_wndToolBar.Create(this, toolbarstyle, IDR_TOOLBAR_USER);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR_USER, 0, 0, TRUE /* ��� */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// ��� ����� �θ� �������� �ƴ� �� ��Ʈ���� ���� ����õ˴ϴ�.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ���� Ʈ�� �� �����͸� ���� �ڵ�� ä��ϴ�.
	FillClassView();

	return 0;
}

void CClassView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}



void CClassView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*)&m_wndClassView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}

	if (point != CPoint(-1, -1))
	{
		// Ŭ���� �׸��� �����մϴ�.
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
		}
	}

	pWndTree->SetFocus();
	CMenu menu;
	menu.LoadMenu(IDR_POPUP_SORT);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}
}

void CClassView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndClassView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

BOOL CClassView::PreTranslateMessage(MSG* pMsg)
{
	return CDockablePane::PreTranslateMessage(pMsg);
}

void CClassView::OnLoudSpeakerImageBtnClicked()
{
	static char *ex1, *ex2;
	CString chatMSG = _T("������ ���� xxx");

	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CONCDoc *pDoc = (CONCDoc *)pFrame->GetActiveDocument();
	CChildFrame *pChild = (CChildFrame *)pFrame->GetActiveFrame();
	COutputWnd *pChatView = (COutputWnd *)pChild->GetActiveView();

	chatMSG = pChatView->TransferEmergencyMsg();
	SendEmergencyAlarmMessage(ex1, ex2);
	MessageBox((LPCTSTR) chatMSG);
}

void CClassView::OnExitImageBtnClicked()
{
	int MB_return = 0;
	MB_return = MessageBox(_T("���α׷��� �����Ͻðڽ��ϱ�?"), _T("ONC"), MB_OKCANCEL);
	
	if (MB_return == IDOK) {
		CreateExitView();
	}
	else {}
}

void CClassView::OnInImageBtnClicked()
{
}

void CClassView::OnOutImageBtnClicked()
{
}



void CClassView::OnPaint()
{
	CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.


}

void CClassView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndClassView.SetFocus();
}

LRESULT CClassView::OnChangeActiveTab(WPARAM, LPARAM)
{
	return LRESULT();
}

void CClassView::OnChangeVisualStyle()
{
	m_ClassViewImages.DeleteImageList();

	
}

void CClassView::SendEmergencyAlarmMessage(char * cMyID, char * cMsg)//����� �Լ��� �ӽ÷� ����
{
	
}

void CClassView::CreateExitView()
{
	AfxGetMainWnd()->PostMessageW(WM_CLOSE);
}


void CClassView::FillClassView()
{

	//for(int k=0; k < vecUserinfo.size(), k++)
	
		//string a; 
		//vecUserInfo.at().userID = a;
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("NSL"), 0, 0);
	/*m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("Leader"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("������"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("�����"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("�����"), 3, 3, hClass);

	m_wndClassView.Expand(hRoot, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("���Ի�"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("������"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("��ÿ�"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("����ȣ"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("������"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("��漱"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("�ڼ�ȭ"), 3, 3, hClass);

	hClass = m_wndClassView.InsertItem(_T("�ܱ���"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("������"), 4, 4, hClass);
	m_wndClassView.InsertItem(_T("����Ű"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("���"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("�ɺ�"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("����"), 3, 3, hClass);*/
}
