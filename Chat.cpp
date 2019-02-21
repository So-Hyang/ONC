
#include "stdafx.h"

#include "Chat.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ONC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//#define IsSHIFTPressed() (0x8000==(GetKeyState(VK_SHIFT)&0x8000))

/////////////////////////////////////////////////////////////////////////////
// COutputBar


COutputWnd::COutputWnd()
{
}

COutputWnd::~COutputWnd()
{
}

BEGIN_MESSAGE_MAP(COutputWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(5427,SendMsg)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_TEXT_SAVE, OnTextSave)
	ON_WM_WINDOWPOSCHANGING()
	ON_REGISTERED_MESSAGE(AFX_WM_CHANGE_ACTIVE_TAB, OnTabSetActive)
END_MESSAGE_MAP()

int COutputWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// �� â�� ����ϴ�.
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_FLAT, rectDummy, this, 1))
	{
		TRACE0("��� �� â�� ������ ���߽��ϴ�.\n");
		return -1;      // ������ ���߽��ϴ�.
	}
	m_wndTabs.EnableTabSwap(FALSE);
	// ��� â�� ����ϴ�.
	const DWORD dwStyle = LBS_NOINTEGRALHEIGHT | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL;
	const DWORD edit_dwStyle = ES_AUTOVSCROLL | ES_MULTILINE | WS_CHILD | WS_VISIBLE | WS_BORDER;
	
	m_wndInputEdit.Create(edit_dwStyle, CRect(0, 0, 100, 100), this, 5426);
	//m_wndInputBtn.Create(_T("������"), WS_CHILD | WS_VISIBLE | WS_BORDER, CRect(0, 0, 100, 100), this, 5427);

	//UpdateFonts();

	CString strTabName;

	for(int i=0; i<10;i++)
	{
		m_wndList[i].Create(dwStyle, rectDummy, &m_wndTabs, i+2);
		m_wndTabs.AddTab(&m_wndList[i], _T("abcd"), (UINT)i);
	}

	// ��� ���� ���� �ؽ�Ʈ�� ä��ϴ�.
	FillBuildWindow();
	FillDebugWindow();
	FillFindWindow();

	return 0;
}

void COutputWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(rect);

	// Tab ��Ʈ���� ��ü Ŭ���̾�Ʈ ������ ó���ؾ� �մϴ�.

	HDWP hdwp = ::BeginDeferWindowPos(3);
	::DeferWindowPos(hdwp, m_wndTabs, HWND_TOP, -1, -1, cx, cy - 80, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
	::DeferWindowPos(hdwp, m_wndInputEdit, HWND_TOP, rect.left, cy - 80, cx, 80, SWP_NOZORDER | SWP_NOACTIVATE);
	//::DeferWindowPos(hdwp, m_wndInputBtn, HWND_TOP, cx - 80, cy - 80, 80, 80, SWP_NOZORDER);
	::EndDeferWindowPos(hdwp);
}

void COutputWnd::AdjustHorzScroll(CListBox& wndListBox)
{
	CClientDC dc(this);
	CFont* pOldFont = dc.SelectObject(&afxGlobalData.fontRegular);

	int cxExtentMax = 0;

	for (int i = 0; i < wndListBox.GetCount(); i++)
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
	
	m_wndList[0].AddString(_T("���⿡ ���� ����� ǥ�õ˴ϴ�."));
	m_wndList[0].AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndList[0].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[1].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[1].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[1].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[1].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[2].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[2].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	m_wndList[2].AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	
}

void COutputWnd::FillDebugWindow()
{
	/*
	m_wndOutputDebug.AddString(_T("���⿡ ����� ����� ǥ�õ˴ϴ�."));
	m_wndOutputDebug.AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndOutputDebug.AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	*/
}

void COutputWnd::FillFindWindow()
{
	/*
	m_wndOutputFind.AddString(_T("���⿡ ã�� ����� ǥ�õ˴ϴ�."));
	m_wndOutputFind.AddString(_T("����� ��� �� �࿡ ǥ�õ�����"));
	m_wndOutputFind.AddString(_T("ǥ�� ����� ���ϴ� ��� ������ �� �ֽ��ϴ�."));
	*/
}


void COutputWnd::UpdateFonts()
{
	for (int i = 0; i<10; i++)
	{
		m_wndList[i].SetFont(&afxGlobalData.fontRegular);
	}
}

void COutputWnd::SendMsg()
{
	AfxMessageBox(_T("��ư Ŭ�� �ȴ�!!"));
}

void COutputWnd::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
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


void COutputWnd::OnTextSave()
{	
	COutputWnd a;
	CString csstrVoca, csFileNum, csDate;
	string sSaveMsg, sFileNum, sName= "�� Log", sDate;
	CTime cTime = CTime::GetCurrentTime(); // ���� �ý������κ��� ��¥ �� �ð��� ��� �´�.
	csDate.Format(_T("_%02d%02d_%02d%02d%02d.txt"), cTime.GetMonth(), cTime.GetDay(), cTime.GetHour(), cTime.GetMinute(), cTime.GetSecond());
	sDate = string(CT2CA(csDate.operator LPCWSTR()));

	char* name;

	char *dir = "C:\\Users\\USER\\Desktop\\";
	int sel = m_wndTabs.GetActiveTab();
	csFileNum.Format(_T("%d"), sel);
	sFileNum = string(CT2CA(csFileNum.operator LPCWSTR()));
	sName = sFileNum + sName + sDate;
	name = (char*)sName.c_str();

	for (int i = 0; i < m_wndList[sel].GetCount(); i++)
	{
		m_wndList[sel].GetText(i, csstrVoca);
		sSaveMsg = string(CT2CA(csstrVoca.operator LPCWSTR()));
		sSaveMsg = sSaveMsg + "\n";
		a.SaveText(dir, name, sSaveMsg);
	}
}


void COutputWnd::SaveText(char* filedirectory, char* filename, string data)
{
	ofstream ofile;
	char cTemp[256];

	strcpy(cTemp, AppendChar(filedirectory, filename));
	if (!ofile.is_open())
	{
		ofile.open(cTemp, ios_base::out | ios_base::app);
	}
	ofile << data;
	ofile.close();
}

char* COutputWnd::AppendChar(char* arg1, char* arg2)
{
	char *concat = (char *)malloc(strlen(arg1) + strlen(arg2) + 1);
	strcpy(concat, arg1);
	strcat(concat, arg2);

	return concat;
}


BOOL COutputWnd::PreTranslateMessage(MSG* pMsg)
{
	short Shift;
	Shift = GetKeyState(VK_SHIFT);
	// ����Ű
	//AfxMessageBox(_T("�Ϲ� ä��"));
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN) && (Shift>=0))
	{
		// ���⿡ ���ϴ� ������ �ڵ带 ����
		if (nType == 0)
		{
			AfxMessageBox(_T("�Ϲ� ä��"));
			return true;
		}
		else if (nType == Emergency_Alarm)
		{
			AfxMessageBox(_T("��� �˶�"));
			nType = 0;
			return true;
		}
	}
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN) && (Shift<0))
	{
		// ���⿡ ���ϴ� ������ �ڵ带 ����
		int nLen = m_wndInputEdit.GetWindowTextLength();
		m_wndInputEdit.SetSel(nLen, nLen);
		m_wndInputEdit.ReplaceSel(_T("\r\n"));
		
		return true;
	}
	return CDockablePane::PreTranslateMessage(pMsg);
}

LRESULT COutputWnd::OnTabSetActive(WPARAM wParam, LPARAM lParam)
{
	CString label;
	int sel = m_wndTabs.GetActiveTab();
	m_wndTabs.GetTabLabel(sel, label);
	label.Format(_T("%d"), sel);
	//AfxMessageBox(label);
	return 0;
}

void COutputWnd::ChatRoomLeave()
{
	int sel = m_wndTabs.GetActiveTab();
	m_wndList[sel].ResetContent();
}