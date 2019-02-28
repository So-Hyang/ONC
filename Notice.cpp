
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
#include "AddView.h"
#include "ChildFrm.h"

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
	ON_COMMAND(ID_VIEW_ADD, OnViewAddBtnCLicked)
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
	AddNoticeInfoDB();
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

	Get_CalendarNotice_Notice();
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
	CTime cur_time = CTime::GetCurrentTime();

	string N_cur_Year = to_string(cur_time.GetYear());
	string N_cur_Month = to_string(cur_time.GetMonth());
	string N_cur_Day = to_string(cur_time.GetDay());


	LPCTSTR propertycontents;
	LPCTSTR bbb;
	CString temp_propertycontents;
	
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	n_userID = "sohyang";
	//n_userID = mDataManager->myinfo.Name;

	if (cur_time.GetMonth() < 10)
		N_cur_Month = "0" + N_cur_Month;
	if (cur_time.GetDay() < 10)
		N_cur_Month = "0" + N_cur_Day;
	n_cur_date = N_cur_Year + "-" + N_cur_Month + "-" + N_cur_Day;


	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	//m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	string b = vecNoticeInfo.back().Notice_cMsg + vecNoticeInfo.back().Notice_CUserID;
	CString bb(b.c_str());
	bbb = (LPCTSTR)bb;
	CMFCPropertyGridProperty* pAll = new CMFCPropertyGridProperty(_T("전체공지사항 List"));

	pAll->AddSubItem(new CMFCPropertyGridProperty(_T("전체 공지사항"), bbb));
	m_wndPropList.AddProperty(pAll);

	//NSL 일정
	cur_NSL_notice = LoadListNotice(1, n_userID, n_cur_date);
	if (cur_NSL_notice.size() != 0)
		temp_propertycontents = ((cur_NSL_notice[0].Main_Contents).c_str());
	else
		temp_propertycontents = L"";
	propertycontents = (LPCTSTR)temp_propertycontents;
	pNSL = new CMFCPropertyGridProperty(_T("NSL 일정 List"));
	pNSL->AddSubItem(new CMFCPropertyGridProperty(_T("NSL 일정 List"), propertycontents));
	m_wndPropList.AddProperty(pNSL);

	//개인 일정
	cur_Personal_notice = LoadListNotice(2, n_userID, n_cur_date);
	if (cur_Personal_notice.size() != 0)
		temp_propertycontents = ((cur_Personal_notice[0].Main_Contents).c_str());
	else
		temp_propertycontents = L"";
	propertycontents = (LPCTSTR)temp_propertycontents;
	pPersonal = new CMFCPropertyGridProperty(_T("개인 일정 List"));
	pPersonal->AddSubItem(new CMFCPropertyGridProperty(_T("개인 일정 List"), propertycontents));
	m_wndPropList.AddProperty(pPersonal);
	
	
}

///////////////////////////////////////////
///////// 달력/공지 정보 가져오기
///////////////02-25//////////////////////
void CPropertiesWnd::Get_CalendarNotice_Notice()
{
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();
	
	CalenderNotice dm_vector_data;
	for (vector<CalenderNotice>::iterator i = mDataManager->calendernotice_v.begin(); i != mDataManager->calendernotice_v.end(); i++)
	{
		
		dm_vector_data.Who = (*i).Who;
		dm_vector_data.Date = (*i).Date;
		dm_vector_data.Contents_Type = (*i).Contents_Type;
		dm_vector_data.Main_Contents = (*i).Main_Contents;
		dm_vector_data.Public_Type = (*i).Public_Type;
		dm_noticeinfo.push_back(dm_vector_data);
	}

}

void CPropertiesWnd::AddNoticeInfo(ALLNoticeInfo Infos)
{
	vecNoticeInfo.push_back(Infos);
}

void CPropertiesWnd::AddNoticeInfoDB()
{
	ALLNoticeInfo NoticeInfos;
	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();

	for (int i = 0; i < mDataManager->calendernotice_v.size(); i++)
	{
		if (mDataManager->calendernotice_v[i].Contents_Type == "Notice")
		{
			NoticeInfos.Notice_cMsg = mDataManager->calendernotice_v[i].Main_Contents;
			NoticeInfos.Notice_CUserID = mDataManager->calendernotice_v[i].Who;
			vecNoticeInfo.push_back(NoticeInfos);
		}
	}
}

void CPropertiesWnd::AddListNotice(CalenderNotice newschedule) 
{
	LPCTSTR propertycontents_P, propertycontents_N;
	//일정 추가하기
	dm_noticeinfo.push_back(newschedule);
	cur_NSL_notice = LoadListNotice(1, n_userID, n_cur_date);
	cur_Personal_notice = LoadListNotice(2, n_userID, n_cur_date);

	propertycontents_P = (LPCTSTR) ((cur_Personal_notice[0].Main_Contents).c_str());
	pPersonal->AddSubItem(new CMFCPropertyGridProperty(_T("개인 일정 List"), propertycontents_P));
	m_wndPropList.AddProperty(pPersonal);

	propertycontents_N = (LPCTSTR)((cur_NSL_notice[0].Main_Contents).c_str());
	pNSL->AddSubItem(new CMFCPropertyGridProperty(_T("NSL 일정 List"), propertycontents_N));
	m_wndPropList.AddProperty(pNSL);
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

vector<CalenderNotice> CPropertiesWnd::LoadListNotice(int type, string name, string date)
{
	vector<CalenderNotice> result_Notice{};//선별해서 나타내진 결과 벡터
	switch (type)
	{
	case 1: //NSL //날짜일치 + type == true일치
		for (int i = 0; i < dm_noticeinfo.size(); i++)
		{
			if ((date == dm_noticeinfo[i].Date) && ("Public" == dm_noticeinfo[i].Public_Type) && ("Calendar" == dm_noticeinfo[i].Contents_Type))
			{
				result_Notice.push_back(dm_noticeinfo[i]);
			}
		}
		break;
	case 2://개인 //날짜일치+ID일치
		for (int i = 0; i < dm_noticeinfo.size(); i++)
		{
			if ((name == dm_noticeinfo[i].Who) && (date == dm_noticeinfo[i].Date) && ("Calendar" == dm_noticeinfo[i].Contents_Type))
			{
				if((dm_noticeinfo[i].Public_Type == "Public") || (dm_noticeinfo[i].Public_Type == "Private"))
				result_Notice.push_back(dm_noticeinfo[i]);
			}
		}
		break;
	case 3://공지사항
		break;
	default:
		break;
	}
	return result_Notice;
}


CString CPropertiesWnd::SelectedLatesofList(vector<CalenderNotice> schedule)
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

	for (int i = 0; i < vecNoticeInfo.size(); i++)
	{
		string Noticecontents = "[" + vecNoticeInfo[i].Notice_CUserID + "] : " + (vecNoticeInfo[i].Notice_cMsg);
		CString NewNoticecontents(Noticecontents.c_str());
		dlg.TempDataVector.Add(NewNoticecontents);
		//Dialog_detail.TempDataVector.Add(Dialog_detail_Contents);
	}

	dlg.DoModal();

}

void CPropertiesWnd::OnViewAddBtnCLicked()
{
	AddView AD;
	AD.DoModal();
	CString listbox_contents;
}



void CPropertiesWnd::OnViewNSLBtnCLicked()
{
	CDetailView Dialog_detail;
	CString Dialog_detail_Contents;
	Dialog_detail.Caption = _T("NSL 일정");

	for (int i = 0; i < cur_NSL_notice.size(); i++)
	{
		Dialog_detail_Contents = ((cur_NSL_notice[i].Main_Contents).c_str());
		Dialog_detail.TempDataVector.Add(Dialog_detail_Contents);
	}
	
	Dialog_detail.DoModal();
}

void CPropertiesWnd::OnViewPERSONALBtnCLicked()
{
	CDetailView Dialog_detail;
	CString Dialog_detail_Contents;
	Dialog_detail.Caption = _T("개인 일정");
	for (int i = 0; i < cur_Personal_notice.size(); i++)
	{
				Dialog_detail_Contents = ((cur_Personal_notice[i].Main_Contents).c_str());
				Dialog_detail.TempDataVector.Add(Dialog_detail_Contents);
	}

	Dialog_detail.DoModal();
}