
///////////////////////////////////////////////////////////////////
/* 작성자 : 박성화*/////////////////////////////////////////////////
/* 작업 날짜 : 2019년 2월 21일*/////////////////////////////////////   
/* 수정 내용 : ToolBar 버튼 활성화*/





#include "stdafx.h"

#include "Notice.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ONC.h"
#include "DetailView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif



CPropertiesWnd::CPropertiesWnd()

{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_NSL, OnViewNSLBtnCLicked)
	ON_COMMAND(ID_PERSONAL, OnViewPERSONALBtnCLicked)
	ON_COMMAND(ID_VIEW_ALL, OnViewAllBtnCLicked)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar message handlers

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd() == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() - (m_nComboHeight + cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();
	// Create combo:
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	CRect rectCombo;
	//m_wndObjectCombo.GetClientRect(&rectCombo);
	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("Failed to create Properties Grid \n");
		return -1;      // fail to create
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* Is locked */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// All commands will be routed via this control , not via the parent frame:
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	//m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}


void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	//m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();


	///////////////////////////////////////////////////////////////////////////////////////////////
	//propertygridprorperty 
	CMFCPropertyGridProperty* pAll = new CMFCPropertyGridProperty(_T("전체공지사항 List"));
	pAll->AddSubItem(new CMFCPropertyGridProperty(_T("전체 공지사항"), _T("시완 2시까지 교수님 호출")));
	m_wndPropList.AddProperty(pAll);

	CMFCPropertyGridProperty* pPersonal = new CMFCPropertyGridProperty(_T("개인 공지사항 List"));
	pPersonal->AddSubItem(new CMFCPropertyGridProperty(_T("개인공지사항"), /*(_variant_t)true,*/ _T("오늘 저녁 7시 약속")));
	m_wndPropList.AddProperty(pPersonal);

	CMFCPropertyGridProperty* pNSL = new CMFCPropertyGridProperty(_T("NSL List"));
	pNSL->AddSubItem(new CMFCPropertyGridProperty(_T(" NSL"), _T("논문 제출 7시까지 ")));
	m_wndPropList.AddProperty(pNSL);
}
///////////////////////////////////////////
///////// 달력/공지 정보 가져오기
///////////////02-25//////////////////////
void CPropertiesWnd::Get_CalendarNotice()
{
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();

	for (vector<CalenderNotice>::iterator i = mDataManager->calendernotice_v.begin(); i != mDataManager->calendernotice_v.end(); i++)
	{
		string a = (*i).Date;
		string b = (*i).Who;
		string c = (*i).Contents_Type;
		string d = (*i).Public_Type;
		string e = (*i).Main_Contents;
		CString buf;
		buf = b.c_str();
			
		
	}

}


void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

vector<NoticeInfo> CPropertiesWnd::LoadListNotice(int type, CString status, CString name, string date)
{
	return vector<NoticeInfo>();
}

CString CPropertiesWnd::SelectedLatesofList(vector<NoticeInfo> schedule)
{
	return CString();
}


void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);
	m_wndPropList.SetFont(&m_fntPropList);
	//m_wndObjectCombo.SetFont(&m_fntPropList);
}


void CPropertiesWnd::OnViewAllBtnCLicked()
{
	CDetailView dlg;
	CString caption, list;
	caption = "전체 공지사항 리스트";
	dlg.Caption = caption;
	dlg.DoModal();
}


void CPropertiesWnd::OnViewNSLBtnCLicked()
{
	CDetailView dlg;
	CString caption, list;
	caption = "NSL 공지사항 리스트";
	dlg.Caption = caption;
	dlg.DoModal();

	//NSL  자세히 버튼 클릭 이벤트
	//NSL  자세히 버튼 클릭 이벤트
	//공지사항 벡터 가져와서 그중에 type ==1, status == true인 거 골라내기
	//일정을 최신순으로 정렬할 예정
	//새로운 벡터에 30번까지만 데이터
	

	//일정을 최신순으로 정렬할 예정
	//새로운 벡터에 30번까지만 데이터

}

void CPropertiesWnd::OnViewPERSONALBtnCLicked()
{
	CDetailView dlg;
	CString caption, list;
	caption = "개인 공지사항 리스트";
	dlg.Caption = caption;
	dlg.DoModal();
}