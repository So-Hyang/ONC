
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
	}
};

IMPLEMENT_SERIAL(CClassViewMenuButton, CMFCToolBarMenuButton, 1)

//////////////////////////////////////////////////////////////////////
// 생성/소멸
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
// CClassView 메시지 처리기

int CClassView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 뷰를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndClassView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("클래스 뷰를 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 이미지를 로드합니다.
	DWORD toolbarstyle = WS_CHILD | WS_VISIBLE|CBRS_TOOLTIPS ;
	toolbarstyle |= (CBRS_ALIGN_BOTTOM & CBRS_ALIGN_ANY);

	m_wndToolBar.Create(this, toolbarstyle, IDR_TOOLBAR_USER);
	m_wndToolBar.LoadToolBar(IDR_TOOLBAR_USER, 0, 0, TRUE /* 잠금 */);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// 정적 트리 뷰 데이터를 더미 코드로 채웁니다.
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
		// 클릭한 항목을 선택합니다.
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
	CString chatMSG = _T("데이터 전달 xxx");

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
	MB_return = MessageBox(_T("프로그램을 종료하시겠습니까?"), _T("ONC"), MB_OKCANCEL);
	
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.


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

void CClassView::SendEmergencyAlarmMessage(char * cMyID, char * cMsg)//통신팀 함수임 임시로 뒀음
{
	
}

void CClassView::CreateExitView()
{
	AfxGetMainWnd()->PostMessageW(WM_CLOSE);
}


void CClassView::FillClassView()
{
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("NSL"), 0, 0);
	m_wndClassView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hClass = m_wndClassView.InsertItem(_T("Leader"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("차중혁"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("김승한"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("김다혜"), 3, 3, hClass);

	m_wndClassView.Expand(hRoot, TVE_EXPAND);

	hClass = m_wndClassView.InsertItem(_T("신입생"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("정소향"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("김시완"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("유상호"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("이종우"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("김경선"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("박성화"), 3, 3, hClass);

	hClass = m_wndClassView.InsertItem(_T("외국인"), 1, 1, hRoot);
	m_wndClassView.InsertItem(_T("산제이"), 4, 4, hClass);
	m_wndClassView.InsertItem(_T("리즈키"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("사디"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("케빈"), 3, 3, hClass);
	m_wndClassView.InsertItem(_T("피코"), 3, 3, hClass);
}
