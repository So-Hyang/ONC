
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

	if (!m_FirstChat.Create(dwStyle, rectDummy, &m_wndTabs, 2) ||
		!m_SecondChat.Create(dwStyle, rectDummy, &m_wndTabs, 3) ||
		!m_ThirdChat.Create(dwStyle, rectDummy, &m_wndTabs, 4) ||
		!m_FourthChat.Create(dwStyle, rectDummy, &m_wndTabs, 5) ||
		!m_FifthChat.Create(dwStyle, rectDummy, &m_wndTabs, 6) ||
		!m_SixthChat.Create(dwStyle, rectDummy, &m_wndTabs, 7) ||
		!m_SeventhChat.Create(dwStyle, rectDummy, &m_wndTabs, 8) ||
		!m_EighthChat.Create(dwStyle, rectDummy, &m_wndTabs, 9) ||
		!m_NinthChat.Create(dwStyle, rectDummy, &m_wndTabs, 10) ||
		!m_TenthChat.Create(dwStyle, rectDummy, &m_wndTabs, 11))
	{
		TRACE0("출력 창을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}

	UpdateFonts();

	CString strTabName;
	BOOL bNameValid;

	// 탭에 목록 창을 연결합니다.
	strTabName = L"chat1";
	m_wndTabs.AddTab(&m_FirstChat, strTabName, (UINT)0);

	strTabName = L"chat2";
	m_wndTabs.AddTab(&m_SecondChat, strTabName, (UINT)1);

	strTabName = L"chat3";
	m_wndTabs.AddTab(&m_ThirdChat, strTabName, (UINT)2);

	strTabName = L"chat4";
	m_wndTabs.AddTab(&m_FourthChat, strTabName, (UINT)3);

	strTabName = L"chat5";
	m_wndTabs.AddTab(&m_FifthChat, strTabName, (UINT)4);

	strTabName = L"chat6";
	m_wndTabs.AddTab(&m_SixthChat, strTabName, (UINT)5);

	strTabName = L"chat7";
	m_wndTabs.AddTab(&m_SeventhChat, strTabName, (UINT)6);

	strTabName = L"chat8";
	m_wndTabs.AddTab(&m_EighthChat, strTabName, (UINT)7);

	strTabName = L"chat9";
	m_wndTabs.AddTab(&m_NinthChat, strTabName, (UINT)8);

	strTabName = L"chat10";
	m_wndTabs.AddTab(&m_TenthChat, strTabName, (UINT)9);


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

	// Tab 컨트롤은 전체 클라이언트 영역을 처리해야 합니다.
	m_wndTabs.SetWindowPos (NULL, -1, -1, cx, cy, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
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
	m_FirstChat.AddString(_T("여기에 빌드 출력이 표시됩니다."));
	m_FirstChat.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_FirstChat.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

void COutputWnd::FillDebugWindow()
{
	m_SecondChat.AddString(_T("여기에 디버그 출력이 표시됩니다."));
	m_SecondChat.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_SecondChat.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

void COutputWnd::FillFindWindow()
{
	m_TenthChat.AddString(_T("여기에 찾기 출력이 표시됩니다."));
	m_TenthChat.AddString(_T("출력이 목록 뷰 행에 표시되지만"));
	m_TenthChat.AddString(_T("표시 방법을 원하는 대로 변경할 수 있습니다."));
}

CString COutputWnd::TransferEmergencyMsg()
{
	EmergencyMsg = L"확성기 메세지 전달 성공";
	return  EmergencyMsg;
}

void COutputWnd::UpdateFonts()
{
	m_FirstChat.SetFont(&afxGlobalData.fontRegular);
	m_SecondChat.SetFont(&afxGlobalData.fontRegular);
	m_ThirdChat.SetFont(&afxGlobalData.fontRegular);
	m_FourthChat.SetFont(&afxGlobalData.fontRegular);
	m_FifthChat.SetFont(&afxGlobalData.fontRegular);
	m_SixthChat.SetFont(&afxGlobalData.fontRegular);
	m_SeventhChat.SetFont(&afxGlobalData.fontRegular);
	m_EighthChat.SetFont(&afxGlobalData.fontRegular);
	m_NinthChat.SetFont(&afxGlobalData.fontRegular);
	m_TenthChat.SetFont(&afxGlobalData.fontRegular);
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
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_VIEW_OUTPUTWND, OnViewOutput)
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

void COutputList::OnEditCopy()
{
	MessageBox(_T("출력 복사"));
}

void COutputList::OnEditClear()
{
	MessageBox(_T("출력 지우기"));
}

void COutputList::OnViewOutput()
{
	CDockablePane* pParentBar = DYNAMIC_DOWNCAST(CDockablePane, GetOwner());
	CMDIFrameWndEx* pMainFrame = DYNAMIC_DOWNCAST(CMDIFrameWndEx, GetTopLevelFrame());

	if (pMainFrame != NULL && pParentBar != NULL)
	{
		pMainFrame->SetFocus();
		pMainFrame->ShowPane(pParentBar, FALSE, FALSE, FALSE);
		pMainFrame->RecalcLayout();

	}
}
