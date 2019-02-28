
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
#include "Login.h"
#include "DetailView.h"
#include "Connect.h"
#include "SendRecv.h"
#include "DataPacket.h"
#include "PacketManager.h"
#include "ServerDataManager.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const POINT readbtnpos = { 516,465 };
static const POINT calbkpos = { 0,0 };

// CCalendarView
Connect Main_Start;
SendRecv Recieve;
//PacketManager ReadyPacket;
SOCKET SeverSock;
IMPLEMENT_DYNCREATE(CCalendarView, CView)

BEGIN_MESSAGE_MAP(CCalendarView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCalendarView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND_RANGE(101, 102, CCalendarView::OnLeftRightBtnClicked)
	ON_BN_CLICKED(103, &CCalendarView::OnCalendarTodayBtnClicked)
	ON_BN_CLICKED(104, &CCalendarView::OnCalendarReadBtnClicked)
	ON_COMMAND_RANGE(105, 106, &CCalendarView::OnCalendatTabBtnClicked)
	ON_CONTROL_RANGE(LBN_DBLCLK, 20011, 20057, OnCalendarListClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()
// CCalendarView 생성/소멸

CCalendarView::CCalendarView()
{
	//SeverSock = Main_Start.ConnectWithServer();
	//CDataPacket::getInstance()->SenderMessage.nType = 5;
	//CDataPacket::getInstance()->SenderMessage.cMsg = "성공";
	
	//CLogin a;
	//a.DoModal();
	
	/*SeverSock = Main_Start.ConnectWithServer();
	CDataPacket::getInstance()->SenderMessage.nType = 5;
	CDataPacket::getInstance()->SenderMessage.cMsg = "성공";
	
	//Recieve.Send(CDataPacket::getInstance()->SenderMessage, SeverSock);
	//SeverSock = Main_Start.ConnectWithServer();
	//CDataPacket::getInstance()->Temp_struct.nType_Temp = 7;
	
	//aa.Temp_cMsg = "000klkkkk";
	//CDataPacket::getInstance()->RecverMessage.nType = 5;
    //scanf("성공", CDataPacket::getInstance()->RecverMessage.temp);
	//CDataPacket::getInstance()->RecverMessage.cMsg = "성공";
	//send(SeverSock,(char*)&CDataPacket::getInstance()->Temp_struct, sizeof(CDataPacket::getInstance()->Temp_struct),0);
	//Recieve.Send(CDataPacket::getInstance()->RecverMessage.temp, SeverSock);
	*/

	DataManager *mDataManager;
	mDataManager = DataManager::GetInstance();

	s_name = mDataManager->myinfo.Name;
	C_name = (mDataManager->myinfo.Name).c_str();
}

////버튼 클릭 이벤트
void CCalendarView::OnLeftRightBtnClicked(UINT uiID)
{
	switch (uiID) {
	case 101://left 버튼
		C_cur_Month--;
		if (C_cur_Month == 0) {
			C_cur_Month = 12;
			C_cur_Year--;
		}
		break;
	case 102://right 버튼
		C_cur_Month++;
		if (C_cur_Month == 13) {
			C_cur_Month = 1;
			C_cur_Year++;
		}
		break;
	}
	CalcaulateCalendar();
	s_date = to_string((C_cur_Year * 10000) + (C_cur_Month * 100));
	DrawCalendarList(LoadListSchedule(C_type,C_name, s_date));

	Invalidate(TRUE);
	UpdateWindow();

}

void CCalendarView::OnCalendarReadBtnClicked()
{
		/*
	if (temp_noticecolor_key) {
		ChangeColorEmergencyNotice("Red");
	}
	else {
		ChangeColorEmergencyNotice("White");
	}
	temp_noticecolor_key = !temp_noticecolor_key;
	*/
	ChangeColorEmergencyNotice("White");
}

void CCalendarView::OnCalendarTodayBtnClicked()
{
	GetCurrentYearMonth();
	CalcaulateCalendar();
	s_date = to_string((C_cur_Year * 10000) + (C_cur_Month * 100));
	DrawCalendarList(LoadListSchedule(C_type,C_name, s_date));
	Invalidate(TRUE);
	UpdateWindow();
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
	//GuiClientInterface *nGUIInterface;
	POINT n_matrix;
	CString n_date;
	AddView Adddlg;
	string n_contents;
	string s_date;
	CString n_status;
	CalenderNotice n_calinfo_vector;
	DataPacket n_calinfo_datapaket;

	n_matrix = CalculateCoordinatevalueLocation(point);
	ColorMatrix(n_matrix);
	n_date = CalculateDateInformation(n_matrix);

	if (n_date == "NULL") 
	{
	}
	else 
	{
		Adddlg.Caption = n_date;

		if (IDOK == Adddlg.DoModal()) {
			//n_calinfo.cUserID = "";//본인 ID
			n_contents = string(CT2CA(Adddlg.a_contents.operator LPCWSTR()));
			s_date = string(CT2CA(n_date.operator LPCWSTR()));

			//DB용 벡터값 추가하기
			n_calinfo_vector.Main_Contents = n_contents;
			n_calinfo_vector.Who = s_name; 
			n_calinfo_vector.Date = s_date;
			n_calinfo_vector.Contents_Type = "Calendar";

			n_status = Adddlg.a_status;

			if (n_status == "공개") 
			{
				n_calinfo_vector.Public_Type = "Public";
				GuiClientInterface::getInstance()->SendCalendarPublicMessage(1, s_name, n_contents, s_date, true);
			}
			else if (n_status == "비공개") 
			{
				n_calinfo_vector.Public_Type = "Private";
				GuiClientInterface::getInstance()->SendCalendarPrivateMessage(2, s_name, n_contents, s_date, false);
			}

			//내가 가진 DM 벡터에 추가된 벡터 추가하기
			AddListSchedule(n_calinfo_vector);
		}
		Invalidate(TRUE);
		UpdateWindow();
	}
	CView::OnLButtonDblClk(nFlags, point);
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


	

	GetCurrentYearMonth();
	

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	leftbtn = new CButton();
	rightbtn = new CButton();
	todaybtn = new CButton();
	readbtn = new CButton();
	privatetab = new CButton();
	publictab = new CButton();

	leftbtn->Create(L"<-", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 416, 20, calbkpos.x + 450, 42), this, 101);
	rightbtn->Create(L"->", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 516, 20, calbkpos.x + 550, 42), this, 102);
	todaybtn->Create(L"오늘", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 462, 20, calbkpos.x + 504, 42), this, 103);
	readbtn->Create(L"readbtn", BS_DEFPUSHBUTTON, CRect(readbtnpos.x, readbtnpos.y, readbtnpos.x + 70, readbtnpos.y + 25), this, 104);
	privatetab->Create(L"NSL", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 316, 20, calbkpos.x + 360, 42), this, 105);
	publictab->Create(C_name, BS_DEFPUSHBUTTON, CRect(calbkpos.x + 365, 20, calbkpos.x + 410, 42), this, 106);

	leftbtn->ShowWindow(SW_SHOW); //여기 위치가 맞는지 확인하기
	rightbtn->ShowWindow(SW_SHOW);
	todaybtn->ShowWindow(SW_SHOW);
	readbtn->ShowWindow(SW_SHOW);
	privatetab->ShowWindow(SW_SHOW);
	publictab->ShowWindow(SW_SHOW);

	int cnt = 0;
	
		for (int j = 1; j < 6; j++)
		{
			for (int i = 1; i < 8; i++)
			{
			list_cal[cnt] = new CListBox();
			list_cal[cnt]->Create(LBS_STANDARD, CRect(((i - 1) * 90 + 2), (100 + ((j - 1) * 74)), (((i - 1) * 90) + 89), (((j - 1) * 74) + 154)), this, 20000 + (j * 10) + i);
			list_cal[cnt]->ShowWindow(SW_SHOW);

			cnt++;
		}
	}
		Get_CalendarNotice_Calendar();
		CalcaulateCalendar();
		s_date = to_string((C_cur_Year * 10000) + (C_cur_Month * 100));
		DrawCalendarList(LoadListSchedule(C_type, C_name, s_date));

}


void CCalendarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CView::OnPaint()을(를) 호출하지 마십시오.

	CPen Background(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&Background);
	dc.MoveTo(0, 50);
	dc.LineTo(630, 50);
	dc.MoveTo(0, 75);
	dc.LineTo(630, 75);
	dc.MoveTo(0, 447);
	dc.LineTo(630, 447);

	for (int x = 0; x < 8; x++) {
		dc.MoveTo(0 + (90 * x), 50);
		dc.LineTo(0 + (90 * x), 77 + (74 * 5));
	}
	
	DrawCalendar();
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

	if (((C_cur_Year % 400) == 0) || (!(C_cur_Year % 100) && (C_cur_Year % 4))) //년도가 400으로 나누어떨어지면/100으로 나누어떨어지지 않고 4로 나누어떨어지면
		leapyear = true; // 윤년
	else                  //아니면
		leapyear = false; //윤년이아니다.

	this_month_date = mdays[C_cur_Month - 1];
	if (leapyear && (C_cur_Month == 2))//윤달이고 2월이면
		this_month_date++;//1일을 더해준다.

						  //작년까지의 총 날짜수를 계산
	total_year = C_cur_Year - 1;
	total = 365 * total_year;
	//총 날짜에 윤년이 발생한만큼 더해줌
	total += ((total_year / 400) - (total_year / 100) + (total_year / 4));
	//올해 전월까지의 날짜수 더함
	for (int m = 0; m < C_cur_Month - 1; m++) {
		total += mdays[m];
	}
	//올해가 윤년이며, 2월을 지났으면 총날짜에 1을 더해줌
	if (leapyear && (C_cur_Month > 2))
		total += 1;

	total += 1;//하루를 더해줌//이번 달 1일도 포함하는 것
	blank_front = (total % 7);// 현재까지 총 날짜수를 7로 나눈 나머지가 요일의 인덱스//0:일요일, 1:월요일,,6:토요일


	for (int i = 0; i < 35; i++) {
		if (blank_front > 0) { //공백기가 있을때
			t_date[i] = "  "; //공백으로 표시
			blank_front--;
		}
		else {//공백으로 처리할 부분이 없을 때
			if (this_month_date >  0) { //이번 달에 남은 날짜가 있을 경우
				t_date[i].Format(_T("%d"), num_date); //날짜 표시
				if (num_date < 10) 
				{
					t_date[i] = L"0" + t_date[i];
				}
				num_date++; //날짜 1일 증가
				this_month_date--; //남은 날짜 감소
			}
			else {//이번달에 남은 날짜가 없을 경우, 나머지는 공백처리
				t_date[i] = "  ";
			}
		}
	}

}

CPoint CCalendarView::CalculateCursorPosition()
{
	/*
	CPoint mouse;
	GetCursorPos(&mouse);
	return mouse;
	*/ //필요없는 부분일듯
	return CPoint();
}

CPoint CCalendarView::CalculateCoordinatevalueLocation(CPoint xylocation)
{
	CPoint location;
	if ((446 < xylocation.y) || (630< xylocation.x)) 
	{
		location.x = -1;
		location.y = -1;
		return location;
	}
	else 
	{
		for (int i = 0; i < 5; i++) {
			if (((i * 74) + 76 <= xylocation.y) && (((i + 1) * 74) + 76> xylocation.y))
			{

				location.y = i;
			}
			for (int j = 0; j < 7; j++) {
				if (((j * 90) + 2 <= xylocation.x) && (((j + 1) * 90) + 2 > xylocation.x))
				{
					location.x = j;
				}
			}
		}
	}
	
	return location;
}

CString CCalendarView::CalculateDateInformation(CPoint matrixlocation)
{
	int matrixindex;
	CString Y, M, D;
	CString clickeddate;
	if ((matrixlocation.x == -1) && (matrixlocation.y == -1))
	{
		clickeddate = "NULL";
	}
	else 
	{
		for (int i = 0; i < 5; i++) {
			if (matrixlocation.y == i)
			{
				for (int j = 0; j < 7; j++) {
					if (matrixlocation.x == j)
					{
						matrixindex = (i * 7) + (j);
					}
				}
			}
		}

		Y.Format(_T("%d"), C_cur_Year);
		if (C_cur_Month < 10)
		{
			M.Format(_T("%d"), C_cur_Month);
			M = L"0" + M;
		}
		else 
		{
			M.Format(_T("%d"), C_cur_Month);
		}

		D = t_date[matrixindex];
		clickeddate = Y + L"-" + M + L"-" + D;
	}
	if (D == "  ") 
	{
		clickeddate = "NULL";
	}
	

	return clickeddate;
}

void CCalendarView::ColorMatrix(CPoint matrixlocation)
{
	CClientDC DC(this);
	CBrush MyBrush;
	CBrush *OldBrush;

	if ((matrixlocation.x == -1) &&(matrixlocation.y == -1))
	{
	}
	else 
	{
		MyBrush.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 255));
		OldBrush = DC.SelectObject(&MyBrush);
		DC.SetBkMode(TRANSPARENT);
		DC.Rectangle(matrixlocation.x * 90, (matrixlocation.y * 74) + 78, (matrixlocation.x + 1) * 90, ((matrixlocation.y + 1) * 74) + 78);
		DC.SelectObject(OldBrush);
		MyBrush.DeleteObject();
	}
}

void CCalendarView::CreateAddView(CString type, CString status, CString name, CString date)
{
}

vector<CalenderNotice> CCalendarView::LoadListSchedule(string pubsub_status, CString name, string date)
{
	//DM에서 가져온 벡터
	int pubsub_type = 0;
	vector<CalenderNotice> n_calendarinfo; //반환할 벡터
										 //DM에서 데이터 가져왔다고 가정

	if (pubsub_status == "Public") 
	{
		pubsub_type = 1;
	}
	else if (pubsub_status == "Private") 
	{
		pubsub_type = 2;
	}
	switch (pubsub_type)
	{
	case 1: //NSL 일정일때
		for (int i = 0; i < dm_calendarinfo.size(); i++)
		{
			if (dm_calendarinfo[i].Public_Type == "Public") //NSL 일정
			{
				string temp = dm_calendarinfo[i].Date;
				if (temp.substr(0, 4) == (date.substr(0, 4))) //년, 월이 같으면 n_calendar에 값 추가하기
				{
					if (temp.substr(5, 2) == (date.substr(4, 2)))
					{
						n_calendarinfo.push_back(dm_calendarinfo[i]);
					}
				}
			}
		}
		break;
	case 2://개인 일정일때
		for (int i = 0; i < dm_calendarinfo.size(); i++)
		{
			if ((dm_calendarinfo[i].Who).c_str() == C_name) //개인 일정 //본인 ID인 것만 표시하도록 수정하기
			{
				string temp = dm_calendarinfo[i].Date;
				if (temp.substr(0, 4) == (date.substr(0, 4))) //년, 월이 같으면 n_calendar에 값 추가하기
				{
					if (temp.substr(5, 2) == (date.substr(4, 2)))
					{
						n_calendarinfo.push_back(dm_calendarinfo[i]);
					}
				}
			}

		}
		break;
	default:
		break;
	}
	
	return n_calendarinfo;
}

void CCalendarView::AddListSchedule(CalenderNotice newschedule)
{
	//일정 추가하기
	dm_calendarinfo.push_back(newschedule);
	//일정 리스트박스 다시 그리기
	DrawCalendarList(LoadListSchedule(C_type, C_name, s_date));
}

void CCalendarView::ChangeColorEmergencyNotice(string color)
{
	
	CClientDC DC(this);
	CBrush Noticebrush, *Oldbrush;
	//워닝 메세지 비트맵 띄우는 과정
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap bmp; //워닝 메세지 비트맵
	CBitmap* pOldBmp = NULL;

	if (color == "")
	{
	}
	else if (color == "Red")
	{
		newColor = RGB(255, 0, 0);
	}
	else if (color == "White")
	{
		newColor = RGB(255, 255, 255);
	}

	Noticebrush.CreateSolidBrush(newColor);
	Oldbrush = DC.SelectObject(&Noticebrush);
	DC.Rectangle(58, readbtnpos.y - 15, readbtnpos.x + 110, readbtnpos.y + 35);
	DC.SetTextColor(RGB(255, 255, 255));
	DC.SetBkColor(newColor);
	DC.TextOut(80, readbtnpos.y + 4, emergencymsg);

	////
	MemDC.CreateCompatibleDC(&DC);
	bmp.LoadBitmapW(IDB_BITMAP_WARNING);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	MemDC.SelectObject(&bmp);
	DC.BitBlt(10, readbtnpos.y - 10, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBmp);


	DC.SelectObject(Oldbrush);
	Noticebrush.DeleteObject();
}

void CCalendarView::EmergencyNotice()
{
}

void CCalendarView::DrawCalendar()
{
	CClientDC DC(this);
	CDC MemDC;
	int date_num = 0;
	CString temp_y, temp_m;
	

	// 날짜 표시하기 위해 형 변환
	MemDC.CreateCompatibleDC(&DC);
	temp_y.Format(_T("%d"), C_cur_Year);
	temp_m.Format(_T("%d"), C_cur_Month);
	DC.TextOutW(calbkpos.x + 20, calbkpos.y + 20, temp_y + L"년 " + temp_m + L"월");
	for (int i = 0; i < 7; i++) {
		DC.TextOutW(calbkpos.x + 10 + (i * 89), calbkpos.y + 55, day[i]);
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			DC.TextOutW(calbkpos.x + 10 + (j * 90), calbkpos.y + 80 + (i * 74), t_date[date_num]);

			date_num++;
		}
	}
}

void CCalendarView::GetCurrentYearMonth()
{
	CTime cur_time = CTime::GetCurrentTime();
	C_cur_Year = cur_time.GetYear();
	C_cur_Month = cur_time.GetMonth();
}

void CCalendarView::OnCalendatTabBtnClicked(UINT uiID)
{

	vector<CalenderNotice> calendar;
	s_date = to_string((C_cur_Year * 10000) + (C_cur_Month * 100));
	
	switch (uiID) {
	case 105://NSL
		C_type = "Public";
		calendar = LoadListSchedule(C_type,C_name, s_date);//DM에서 코드 가져오는 함수
		DrawCalendarList(calendar);
		break;
	case 106://개인
		C_type = "Private";
		calendar = LoadListSchedule(C_type, C_name, s_date);//DM에서 코드 가져오는 함수
		DrawCalendarList(calendar);
		break;
	}
}

void CCalendarView::OnCalendarListClicked(UINT uuid)
{
	int listbox_index = -1;
	int listbox_index_f, listbox_index_s;
	CString clickeddate, Y, M, D;
	CDetailView Dialog_detail;
	int listbox_cnt;
	CString listbox_contents;

	uuid = uuid - 20000;
	listbox_index_f = uuid / 10;
	listbox_index_s = uuid % 10;
	listbox_index = (((listbox_index_f - 1) * 7) + listbox_index_s - 1);

	Y.Format(_T("%d"), C_cur_Year);
	M.Format(_T("%d"), C_cur_Month);
	D = t_date[listbox_index];
	clickeddate = Y + L"." + M + L"." + D;
	Dialog_detail.Caption = clickeddate;

	listbox_cnt = list_cal[listbox_index]->GetCurSel();
	list_cal[listbox_index]->GetText(listbox_cnt, listbox_contents);
	Dialog_detail.TempDataVector.Add(listbox_contents);

	Dialog_detail.DoModal();

	list_cal[listbox_index]->SetCurSel(-1);
}

void CCalendarView::DrawCalendarList(vector<CalenderNotice>n_calendar)
{
	int cnt_r = 0, i = 0;
	string s_temp;
	CString c_temp;

	for (int i = 0; i < 35; i++)
	{
		list_cal[i]->ResetContent();
	}

	while (i < n_calendar.size()) {
		s_temp = n_calendar[i].Date;
		c_temp = (s_temp.substr(8, 2)).c_str();
		if (c_temp == t_date[cnt_r]) //일이 같으면 
		{
			s_temp = n_calendar[i].Main_Contents;
			c_temp = s_temp.c_str();
			list_cal[cnt_r]->AddString(c_temp);
			i++;
			cnt_r = 0;
		}
		else
		{
			if (cnt_r < 34)
				cnt_r++;
			else
				break;
		}
	}

	Invalidate(TRUE);
	UpdateWindow();
}


///////////////////////////////////////////
///////// 달력/공지 정보 가져오기
///////////////02-25//////////////////////
void CCalendarView::Get_CalendarNotice_Calendar()
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
		if((*i).Contents_Type == "Calendar")
		dm_calendarinfo.push_back(dm_vector_data);
	}

}

