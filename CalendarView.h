
// CalendarView.h : CCalendarView 클래스의 인터페이스
//

#pragma once
#include "DataManager.h"
#include "Interface.h"




class CCalendarView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCalendarView();
	DECLARE_DYNCREATE(CCalendarView)

	// 특성입니다.
public:
	CONCDoc* GetDocument() const;

	void OnLeftRightBtnClicked(UINT uiID);

	void OnCalendarReadBtnClicked();

	void OnCalendarTodayBtnClicked();

	void CreateLoginView();

	void CalcaulateCalendar();

	CPoint CalculateCursorPosition();

	CPoint CalculateCoordinatevalueLocation(CPoint xylocation);

	CString CalculateDateInformation(CPoint matrixlocation);

	void ColorMatrix(CPoint matrixlocation);

	void CreateAddView(CString type, CString status, CString name, CString date);

	vector<CalenderNotice> LoadListSchedule(string pubsub_status, CString name, string date);


	void AddListSchedule(CalenderNotice newschedule);

	void ChangeColorEmergencyNotice(string color);

	void EmergencyNotice();

	void DrawCalendar();//달력 그리는 함수 임의로 추가함

	void GetCurrentYearMonth(); //현재 년도, 월 불러오는 함수



	void DrawCalendarList(vector<CalenderNotice> n_calendar);

	void Get_CalendarNotice_Calendar();








								// 작업입니다.
public:
	CButton *leftbtn, *rightbtn, *todaybtn, *readbtn, *privatetab, *publictab;
	//CString btnlist[4] = { L"leftbtn", L"rightbtn", L"todaybtn", L"readbtn" }; /버튼 명료하게 선언하는 거 다시 시도하기
	CListBox *list_cal[35];

	COLORREF newColor;
	bool temp_noticecolor_key = true; //긴급메세지 수신/읽기용 임시로 놔둔 방편
	CString emergencymsg = L"긴급 메세지 입니다"; //긴급메세지 변수
	int BackgroundAdd = IDB_BITMAP_CALENDAR_BK;
	CString day[7] = { L"일" ,L"월", L"화", L"수", L"목", L"금", L"토" };
	CString t_date[35] = {};
	int C_cur_Month = 0;
	int C_cur_Year = 0;

	CString C_status, C_name;
	string s_date = "",s_name = "";
	string C_type = "Public";
	vector<CalenderNotice> dm_calendarinfo;


	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CCalendarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);//종우선배
	afx_msg  void OnCalendatTabBtnClicked(UINT uiID);
	afx_msg void OnCalendarListClicked(UINT uuid);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // CalendarView.cpp의 디버그 버전
inline CONCDoc* CCalendarView::GetDocument() const
{
	return reinterpret_cast<CONCDoc*>(m_pDocument);
}
#endif


