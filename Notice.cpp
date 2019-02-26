
///////////////////////////////////////////////////////////////////
/* �ۼ��� : �ڼ�ȭ*/////////////////////////////////////////////////
/* �۾� ��¥ : 2019�� 2�� 21��*/////////////////////////////////////   
/* ���� ���� : ToolBar ��ư Ȱ��ȭ*/





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
	CMFCPropertyGridProperty* pAll = new CMFCPropertyGridProperty(_T("��ü�������� List"));
	pAll->AddSubItem(new CMFCPropertyGridProperty(_T("��ü ��������"), _T("�ÿ� 2�ñ��� ������ ȣ��")));
	m_wndPropList.AddProperty(pAll);

	CMFCPropertyGridProperty* pPersonal = new CMFCPropertyGridProperty(_T("���� �������� List"));
	pPersonal->AddSubItem(new CMFCPropertyGridProperty(_T("���ΰ�������"), /*(_variant_t)true,*/ _T("���� ���� 7�� ���")));
	m_wndPropList.AddProperty(pPersonal);

	CMFCPropertyGridProperty* pNSL = new CMFCPropertyGridProperty(_T("NSL List"));
	pNSL->AddSubItem(new CMFCPropertyGridProperty(_T(" NSL"), _T("�� ���� 7�ñ��� ")));
	m_wndPropList.AddProperty(pNSL);
}
///////////////////////////////////////////
///////// �޷�/���� ���� ��������
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
	caption = "��ü �������� ����Ʈ";
	dlg.Caption = caption;
	dlg.DoModal();
}


void CPropertiesWnd::OnViewNSLBtnCLicked()
{
	CDetailView dlg;
	CString caption, list;
	caption = "NSL �������� ����Ʈ";
	dlg.Caption = caption;
	dlg.DoModal();

	//NSL  �ڼ��� ��ư Ŭ�� �̺�Ʈ
	//NSL  �ڼ��� ��ư Ŭ�� �̺�Ʈ
	//�������� ���� �����ͼ� ���߿� type ==1, status == true�� �� ��󳻱�
	//������ �ֽż����� ������ ����
	//���ο� ���Ϳ� 30�������� ������
	

	//������ �ֽż����� ������ ����
	//���ο� ���Ϳ� 30�������� ������

}

void CPropertiesWnd::OnViewPERSONALBtnCLicked()
{
	CDetailView dlg;
	CString caption, list;
	caption = "���� �������� ����Ʈ";
	dlg.Caption = caption;
	dlg.DoModal();
}