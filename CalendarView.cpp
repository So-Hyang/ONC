
// CalendarView.cpp : CCalendarView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ONC.h"
#endif

#include "ONCDoc.h"
#include "CalendarView.h"
#include "AddView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const POINT readbtnpos = { 10,450 };
static const POINT calbkpos = { 0,0 };

// CCalendarView

IMPLEMENT_DYNCREATE(CCalendarView, CView)

BEGIN_MESSAGE_MAP(CCalendarView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCalendarView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_BN_CLICKED(101, &CCalendarView::OnLeftRightBtnClicked)
	ON_BN_CLICKED(102, &CCalendarView::OnLeftRightBtnClicked)
	ON_BN_CLICKED(103, &CCalendarView::OnCalendarTodayBtnClicked)
	ON_BN_CLICKED(104, &CCalendarView::OnCalendarReadBtnClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCalendarView 생성/소멸

CCalendarView::CCalendarView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	//dkskdksdkadfasfas

}

////버튼 클릭 이벤트
void CCalendarView::OnLeftRightBtnClicked()
{
	MessageBox(L"OnLeftRightBtnClicked");

}

void CCalendarView::OnCalendarReadBtnClicked()
{
	//CCalendarView::OnCalendarReadBtnClicked();
	CClientDC DC(this);
	CBrush Noticebrush, *Oldbrush;
	//워닝 메세지 비트맵 띄우는 과정
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap bmp; //워닝 메세지 비트맵
	CBitmap* pOldBmp = NULL;

	if (temp_noticecolor_key) {
		ChangeColorEmergencyNotice("Red");
	}
	else {
		ChangeColorEmergencyNotice("White");
	}
	temp_noticecolor_key = !temp_noticecolor_key;


	Noticebrush.CreateSolidBrush(newColor);
	Oldbrush = DC.SelectObject(&Noticebrush);
	DC.Rectangle(readbtnpos.x+45, readbtnpos.y, readbtnpos.x + 760, readbtnpos.y + 50); 
	DC.SetTextColor(RGB(255, 255, 255));
	DC.SetBkColor(newColor);
	DC.TextOut(readbtnpos.x + 70, readbtnpos.y + 19, emergencymsg);

	////
	MemDC.CreateCompatibleDC(&DC);
	bmp.LoadBitmapW(IDB_BITMAP_WARNING);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	MemDC.SelectObject(&bmp);
	DC.BitBlt(readbtnpos.x, readbtnpos.y+5, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBmp);
	///////

	DC.SelectObject(Oldbrush);
	Noticebrush.DeleteObject();

}

void CCalendarView::OnCalendarTodayBtnClicked()
{
	MessageBox(L"OnCalendarTodayBtnClicked");
	CalcaulateCalendar();
	DrawCalendar();
}

CCalendarView::~CCalendarView()
{
}

BOOL CCalendarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CCalendarView 그리기

void CCalendarView::OnDraw(CDC* /*pDC*/)
{
	CONCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CCalendarView 인쇄


void CCalendarView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCalendarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCalendarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCalendarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CCalendarView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCalendarView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CCalendarView::OnLButtonDblClk(UINT nFlags, CPoint point)////종우선배
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	AddView dlg;
	CString str11;
	//Static caption 설정
	dlg.Caption = _T("강아지");
	dlg.DoModal();

	if (IDOK == dlg.DoModal()) {
		str11 = dlg.test;//
	}
	//	dlg.CalEdit.GetWindowTextW(str);
	//AfxMessageBox(str);

	//CView::OnLButtonDblClk(nFlags, point);
}


// CCalendarView 진단

#ifdef _DEBUG
void CCalendarView::AssertValid() const
{
	CView::AssertValid();
}

void CCalendarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CONCDoc* CCalendarView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CONCDoc)));
	return (CONCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCalendarView 메시지 처리기


void CCalendarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	leftbtn = new CButton();
	rightbtn = new CButton();
	todaybtn = new CButton();
	readbtn = new CButton();

	leftbtn->Create(L"leftbtn", BS_DEFPUSHBUTTON, CRect(650, 20, 700, 50), this, 101);
	rightbtn->Create(L"rightbtn", BS_DEFPUSHBUTTON, CRect(650, 70, 700, 100), this, 102);
	todaybtn->Create(L"todaybtn", BS_DEFPUSHBUTTON, CRect(650, 140, 700, 170), this, 103);
	readbtn->Create(L"readbtn", BS_DEFPUSHBUTTON, CRect(readbtnpos.x+670, readbtnpos.y+15, readbtnpos.x + 740, readbtnpos.y + 40), this, 104);

	leftbtn->ShowWindow(SW_SHOW); //여기 위치가 맞는지 확인하기
	rightbtn->ShowWindow(SW_SHOW);
	todaybtn->ShowWindow(SW_SHOW);
	readbtn->ShowWindow(SW_SHOW);
}


void CCalendarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.
	//DrawCalendar();
}

void CCalendarView::CreateLoginView()
{
}

void CCalendarView::CalcaulateCalendar()
{
	bool leapyear = false;
	int mdays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int this_month_date;//이번 달의 날짜 갯수
	int total_year;
	int total;
	int blank_front;
	int num_date = 1;

	if (((cur_Year % 400) == 0) || (!(cur_Year % 100) && (cur_Year % 4))) //년도가 400으로 나누어떨어지면/100으로 나누어떨어지지 않고 4로 나누어떨어지면
		leapyear = true; // 윤년
	else                  //아니면
		leapyear = false; //윤년이아니다.

	this_month_date = mdays[cur_Month - 1];
	if (leapyear && (cur_Month == 2))//윤달이고 2월이면
		this_month_date++;//1일을 더해준다.

						  //작년까지의 총 날짜수를 계산
	total_year = cur_Year - 1;
	total = 365 * total_year;
	//총 날짜에 윤년이 발생한만큼 더해줌
	total += ((total_year / 400) - (total_year / 100) + (total_year / 4));
	//올해 전월까지의 날짜수 더함
	for (int m = 0; m < cur_Month - 1; m++) {
		total += mdays[m];
	}
	//올해가 윤년이며, 2월을 지났으면 총날짜에 1을 더해줌
	if (leapyear && (cur_Month > 2))
		total += 1;

	total += 1;//하루를 더해줌//이번 달 1일도 포함하는 것
	blank_front = (total % 7);// 현재까지 총 날짜수를 7로 나눈 나머지가 요일의 인덱스//0:일요일, 1:월요일,,6:토요일


	for (int i = 0; i < 35; i++) {
		if (blank_front > 0) { //공백기가 있을때
			date[i] = "  "; //공백으로 표시
			blank_front--;
		}
		else {//공백으로 처리할 부분이 없을 때
			if (this_month_date >  0) { //이번 달에 남은 날짜가 있을 경우
				date[i].Format(_T("%d"), num_date); //날짜 표시
				num_date++; //날짜 1일 증가
				this_month_date--; //남은 날짜 감소
			}
			else {//이번달에 남은 날짜가 없을 경우, 나머지는 공백처리
				date[i] = "  ";
			}
		}
	}

}

CPoint CCalendarView::CalculateCursorPosition()
{
	return CPoint();
}

CPoint CCalendarView::CalculateCoordinatevalueLocation(CPoint xylocation)
{
	return CPoint();
}

int CCalendarView::CalculateDateInformation(CPoint matrixlocation)
{
	return 0;
}

void CCalendarView::ColorMatrix(CPoint matrixlocation)
{
}

void CCalendarView::CreateAddView(CString type, CString status, CString name, CString date)
{
}

vector<CString> CCalendarView::LoadListSchedule(CString type, CString status, CString name, CString date)
{
	return vector<CString>();
}

void CCalendarView::AddListSchedule(vector<CString> schedule, int date)
{
}

void CCalendarView::ChangeColorEmergencyNotice(string color)
{
	if (color == "")
	{
	}
	else if (color == "Red") //문제: newcolor를 인식을 못함, 이함수의 의미존재 모르겠음
	{
		newColor = RGB(255, 0, 0);
	}
	else if (color == "White")
	{
		newColor = RGB(255, 255, 255);
	}
}

void CCalendarView::EmergencyNotice()
{
}

void CCalendarView::DrawCalendar()
{
	CClientDC DC(this);
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;
	int date_num = 0;
	CString temp_y, temp_m;

	MemDC.CreateCompatibleDC(&DC);
	bmp.LoadBitmapW(BackgroundAdd);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	MemDC.SelectObject(&bmp);
	DC.BitBlt(calbkpos.x, calbkpos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBmp);

	//날짜 표시하기 위해 형 변환
	temp_y.Format(_T("%d"), cur_Year); 
	temp_m.Format(_T("%d"), cur_Month); 
	DC.TextOutW(calbkpos.x + 20, calbkpos.y + 20, temp_y + L"년 " + temp_m + L"월");
	for (int i = 0; i < 7; i++) {
		DC.TextOutW(calbkpos.x + 10 + (i * 89), calbkpos.y + 55, day[i]);
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			DC.TextOutW(calbkpos.x + 10 + (j * 90), calbkpos.y + 80 + (i * 74), date[date_num]);
			date_num++;
		}
	}
}

