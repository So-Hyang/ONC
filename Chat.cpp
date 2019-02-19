
#include "stdafx.h"

#include "Chat.h"
#include "Resource.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBar

CString EmergencyMsg;

COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	
	// 탭 창을 만듭니다.
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("출력 탭 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	// 출력 창을 만듭니다.
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	const DWORD edit_dwStyle = ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL;

	m_wndInputEdit.Create(edit_dwStyle, CRect(0,0,100,100), this, 5426);
	m_wndInputBtn.Create(_T("보내기"), WS_CHILD | WS_VISIBLE | WS_BORDER , CRect(0, 0, 100, 100),this,5427);

	if (!m_wndOutputBuild.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_wndOutputDebug.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_wndOutputFind.Create(dwStyle, rectDummy, &m_wndTabs, 4))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// 탭에 목록 창을 연결합니다.
	bNameValid = strTabName.LoadString(IDS_BUILD_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputBuild, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_DEBUG_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputDebug, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_FIND_TAB);
	ASSERT(bNameValid);
	m_wndTabs.AddTab(&m_wndOutputFind, strTabName, (UINT)2);

	// 출력 탭을 더미 텍스트로 채웁니다.
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	EmergencyMsg = "확성기 메세지입니다";

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);
	
	// Tab 컨트롤은 전체 클라이언트 영역을 처리해야 합니다.

	HDWP hdwp = ::BeginDeferWindowPos(3);
	::DeferWindowPos(hdwp, m_wndTabs, HWND_TOP, -1, -1, cx, cy - 80, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	::DeferWindowPos(hdwp, m_wndInputEdit, HWND_TOP, rect.left, cy - 80, cx - 80, 80, SWP_NOZORDER | SWP_NOACTIVATE );
	::DeferWindowPos(hdwp, m_wndInputBtn, HWND_TOP, cx-80, cy - 80, 80, 80, SWP_NOZORDER);
	::EndDeferWindowPos(hdwp);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i ++)
	{
		CString strItem;
		wndListBox.GetText(i, strItem);

		cxExtentMax = max(cxExtentMax, (int)dc.GetTextExtent(strItem).cx);
	}

	wndListBox.SetHorizontalExtent(cxExtentMax);
	dc.SelectObject(pOldFont);
}

void COutputWnd::FillBuildWindow()
{
	m_wndOutputBuild.AddString(_T("여기에 빌드 출력이 표시됩니다."));
	m_wndOutputBuild.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
	m_wndOutputBuild.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

void COutputWnd::FillDebugWindow()
{
	m_wndOutputDebug.AddString(_T("여기에 디버그 출력이 표시됩니다."));
	m_wndOutputDebug.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_wndOutputDebug.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

void COutputWnd::FillFindWindow()
{
	m_wndOutputFind.AddString(_T("여기에 찾기 출력이 표시됩니다."));
	m_wndOutputFind.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_wndOutputFind.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

CString COutputWnd::TransferEmergencyMsg()
{
	EmergencyMsg = L"확성기 메세지 전달 성공";
	return  EmergencyMsg;
}

void COutputWnd::UpdateFonts()
{
	m_wndOutputBuild.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputDebug.SetFont(&afxGlobalData.fontRegular);
	m_wndOutputFind.SetFont(&afxGlobalData.fontRegular);
}


/////////////////////////////////////////////////////////////////////////////
// COutputList1

COutputList::COutputList()
{
}

COutputList::~COutputList()
{
}

BEGIN_MESSAGE_MAP(COutputList, CListBox)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TEXT_SAVE, OnTextSave)
	ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// COutputList 메시지 처리기

void COutputList::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_OUTPUT_POPUP);

	CMenu* pSumMenu = menu.GetSubMenu(0);

	if (AfxGetMainWnd()->IsKindOf(RUNTIME_CLASS(CMDIFrameWndEx)))
	{
		CMFCPopupMenu* pPopupMenu = new CMFCPopupMenu;

		if (!pPopupMenu->Create(this, point.x, point.y, (HMENU)pSumMenu->m_hMenu, FALSE, TRUE))
			return;

		((CMDIFrameWndEx*)AfxGetMainWnd())->OnShowPopupMenu(pPopupMenu);
		UpdateDialogControls(this, FALSE);
	}

	SetFocus();
}


void COutputList::OnTextSave()
{
}
