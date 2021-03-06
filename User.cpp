
#include "stdafx.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "User.h"
#include "Resource.h"
#include "ONC.h"
#include "ONCDoc.h"
#include "Chat.h"

#include "ProfileView.h"
#include "cstringt.h"
#include "atlstr.h"
#include "afxcmn.h"
#include "DataPacket.h"
#include "Interface.h"
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
		/////테스트로 일단 문자 추가해봅니다.
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
	ON_COMMAND(ID_SORTING_SORTALPHABETIC, &CClassView::OnSortingSortbyaccess)
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
	DWORD toolbarstyle = WS_CHILD | WS_VISIBLE | CBRS_TOOLTIPS;
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

	
	//DBConnect mDBConnect;
	DBCollector mDBCollector;
	
	
	//mDBCollector.DB_mysql_disconnect();
	mDBCollector.Set_Information();// 최초 DB에서 데이터를 가져오는 함수가 여기서 실행된다
	mDBCollector.DB_mysql_disconnect();
	mDBCollector.Set_Contents();
	mDBCollector.DB_mysql_disconnect();
	//mDBCollector.Set_Contents();                                // 프로필 트리뷰 및 로그인까지 영향을 미침(people_v 에 접근하는 
	                                // 모든 경로에 영향을 미칠것 같음. -DB파트

	//mDBCollector.Set_Contents(); // 당장은 사용 안하나 추후 소향이가 DB접근으로 사용할 예정으로 만듬.

	
	
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	
	
	
	SetTreeData(mDataManager->people_v);
	
	
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
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	pFrame->m_wndOutput.nType = EmergencyPacket;
}

void CClassView::OnExitImageBtnClicked()
{
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	int MB_return = 0;
	MB_return = MessageBox(_T("프로그램을 종료하시겠습니까?"), _T("ONC"), MB_OKCANCEL);
	
	if (MB_return == IDOK) {
		GuiClientInterface::getInstance()->DisConnecttion(pFrame->Mysocket);
		CreateExitView();
	}
	//else {}
}

void CClassView::OnInImageBtnClicked()
{
	GuiClientInterface *mGuiClientInterface;
	mGuiClientInterface = GuiClientInterface::getInstance();
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	mGuiClientInterface->SendTopicEnterMessage(TopicEnterPacket, mDataManager->myinfo.Name, pFrame->m_wndOutput.ActiveTab());
	GuiClientInterface::getInstance()->SendTopicParticipantMessage(TopicParticipantPacket, mDataManager->myinfo.Name, pFrame->m_wndOutput.ActiveTab());
}

void CClassView::OnOutImageBtnClicked()
{
	CONCApp *pApp = (CONCApp *)AfxGetApp();
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	GuiClientInterface *mGuiClientInterface;
	mGuiClientInterface = GuiClientInterface::getInstance();
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();

	pFrame->m_wndOutput.ChatRoomLeave();
	mGuiClientInterface->SendTopicLeaveMessage(TopicLeavePacket, mDataManager->myinfo.Name, pFrame->m_wndOutput.ActiveTab());
	GuiClientInterface::getInstance()->SendTopicParticipantMessage(TopicParticipantPacket, mDataManager->myinfo.Name, pFrame->m_wndOutput.ActiveTab());
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
/*
void CClassView::SendEmergencyAlarmMessage(char * cMyID, char * cMsg)//통신팀 함수임 임시로 뒀음
{

}
*/
void CClassView::CreateExitView()
{
	AfxGetMainWnd()->PostMessageW(WM_CLOSE);
}

void CClassView::profileView()
{
	//CTreeCtrl &TreeCtrl = GetTreeCtrl();
	//HTREEITEM htr



}

void CClassView::Onselectedtest()
{


}



void CClassView::OnSortingSortbyaccess() //마우스 우클릭하여서 프로필 눌렀을때
{

	CEdit m_str;
	CString str;

	HTREEITEM hItem = m_wndClassView.GetSelectedItem();
	str = m_wndClassView.GetItemText(hItem);

	ProfileView m;
	m.user_name = str;

	m.DoModal();


}

void CClassView::SetTreeData(vector<People_DB> Participants)
{
	this->vecPeople = Participants;
	MakeTreeview();
}

void CClassView::SetTreeData(string Participants)
{
	//vector<People_DB> peoples;
	//this->vecPeople = peoples;
	this->vecPeople.clear();
	
	char* cPtr = (char*)Participants.c_str();
	int i = 0;

	char *ptr = strtok(cPtr, ";");

	while (ptr != NULL)
	{
		this->vecPeople.resize(i+1);
		string str(ptr);
		this->vecPeople[i].Name = str;
		ptr = strtok(NULL, ";");
		i++;
	}
	
	MakeTreeview();
}

void CClassView::MakeTreeview()
{
	CString buf;
	int n=0;
	m_wndClassView.DeleteAllItems();
	HTREEITEM hRoot = m_wndClassView.InsertItem(_T("NSL"), 0, 0);
	for (vector<People_DB>::iterator i = vecPeople.begin(); i != vecPeople.end(); i++)
	{		
		buf = (*i).Name.c_str();
		m_wndClassView.InsertItem(buf, 0, 0, hRoot);
	}
}