
#include "stdafx.h"

#include "Chat.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ONC.h"
#include "Interface.h"
#include "ServerDataManager.h"

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
	//UpdateFonts();

	CString strTabName;

	for(int i=0; i<10;i++)
	{
		csTitleList[i] = sTitleList[i].c_str();
		m_wndList[i].Create(dwStyle, rectDummy, &m_wndTabs, i+2);
		m_wndTabs.AddTab(&m_wndList[i], csTitleList[i], (UINT)i);
	}
	
	// ��� ���� ���� �ؽ�Ʈ�� ä��ϴ�.

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

int COutputWnd::FindChatRoom(string TopicTitle)
{
	int i = 0;
	for (i; i<10; i++)
	{
		if (sTitleList[i].compare(TopicTitle) == 0)
			return i;
	}
	/*
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
	*/
}


void COutputWnd::UpdateFonts()
{
	for (int i = 0; i<10; i++)
	{
		m_wndList[i].SetFont(&afxGlobalData.fontRegular);
	}
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


void COutputWnd::OnTextSave()			//����Ʈ �ڽ� �����ϴ� �Լ�
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


void COutputWnd::SaveText(char* filedirectory, char* filename, string data)		//�����ϴ� ����� ���� �Լ�
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

char* COutputWnd::AppendChar(char* arg1, char* arg2)			//������ ������� ��ġ�� �Լ�
{
	char *concat = (char *)malloc(strlen(arg1) + strlen(arg2) + 1);
	strcpy(concat, arg1);
	strcat(concat, arg2);

	return concat;
}


BOOL COutputWnd::PreTranslateMessage(MSG* pMsg)				//���� ��������쿡 �����ϴ� �Լ�
{
	short Shift;
	Shift = GetKeyState(VK_SHIFT);
	CString csMSG;
	string sMSG;
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	GetDlgItem(5426)->GetWindowTextW(csMSG);
	sMSG = string(CT2CA(csMSG.operator LPCWSTR()));

	// ����Ű
	if ((pMsg->message == WM_KEYDOWN) && (pMsg->wParam == VK_RETURN) && (Shift>=0))
	{
		if (nType == 0)
		{
			int sel = m_wndTabs.GetActiveTab();
			AfxMessageBox(_T("�Ϲ� ä��"));
			GuiClientInterface::getInstance()->SendChatMessage(ChattingPacket, sTitleList[sel], mDataManager->myinfo.Name, sMSG);
			return true;
		}
		else if (nType == EmergencyPacket)
		{
			AfxMessageBox(_T("��� �˶�"));
			GuiClientInterface::getInstance()->SendEmergencyAramMessage(EmergencyPacket, mDataManager->myinfo.Name, sMSG);
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

LRESULT COutputWnd::OnTabSetActive(WPARAM wParam, LPARAM lParam)		//���� Ŭ�������� �����ϴ� �Լ�
{
	CString csLabel;
	string sLabel;
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	int sel = m_wndTabs.GetActiveTab();
	m_wndTabs.GetTabLabel(sel, csLabel);
	sLabel = string(CT2CA(csLabel.operator LPCWSTR()));
	GuiClientInterface::getInstance()->SendTopicParticipantMessage(TopicParticipantPacket, mDataManager->myinfo.Name, sLabel);
	
	//Label.Format(_T("%d"), sel);
	//AfxMessageBox(label);
	return 0;
}

void COutputWnd::ChatRoomLeave()			//ä�ù� ������ ������ ��� ����Ʈ �ڽ� ����
{
	int sel = m_wndTabs.GetActiveTab();
	m_wndList[sel].ResetContent();
}

void COutputWnd::RefreshTab()
{
	for (int i = 0; i<10; i++)
	{
		csTitleList[i] = sTitleList[i].c_str();
		m_wndTabs.SetTabLabel(i, csTitleList[i]);
	}
}