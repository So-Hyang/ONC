
// CalendarView.h : CCalendarView 클래스의 인터페이스
//

#pragma once

enum ListBoxID
{
	ListBox11 = 211, ListBox12 = 212, ListBox13 = 213

};

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

	vector<CString> LoadListSchedule(CString type, CString status, CString name, CString date);

	void AddListSchedule(vector<CString> schedule, int date);

	void ChangeColorEmergencyNotice(string color);

	void EmergencyNotice();

	void DrawCalendar();//달력 그리는 함수 임의로 추가함

	void GetCurrentYearMonth(); //현재 년도, 월 불러오는 함수




								// 작업입니다.
public:
	CButton *leftbtn, *rightbtn, *todaybtn, *readbtn;
	//CString btnlist[4] = { L"leftbtn", L"rightbtn", L"todaybtn", L"readbtn" }; /버튼 명료하게 선언하는 거 다시 시도하기
	CListBox *list_cal[35];
	CListBox *list_cal_11, *list_cal_12, *list_cal_13, *list_cal_14, *list_cal_15, *list_cal_16, *list_cal_17;
	CListBox *list_cal_21, *list_cal_22, *list_cal_23, *list_cal_24, *list_cal_25, *list_cal_26, *list_cal_27;
	CListBox *list_cal_31, *list_cal_32, *list_cal_33, *list_cal_34, *list_cal_35, *list_cal_36, *list_cal_37;
	CListBox *list_cal_41, *list_cal_42, *list_cal_43, *list_cal_44, *list_cal_45, *list_cal_46, *list_cal_47;
	CListBox *list_cal_51, *list_cal_52, *list_cal_53, *list_cal_54, *list_cal_55, *list_cal_56, *list_cal_57;

	COLORREF newColor;
	bool temp_noticecolor_key = true; //긴급메세지 수신/읽기용 임시로 놔둔 방편
	CString emergencymsg = L"2시까지 시완, 종우 교수님 방으로 호출"; //긴급메세지 변수
													  //달력 그리기용 변수
	int BackgroundAdd = IDB_BITMAP_CALENDAR_BK;
	CString day[7] = { L"일" ,L"월", L"화", L"수", L"목", L"금", L"토" };
	CString date[35] = {};
	int cur_Month = 0;
	int cur_Year = 0;


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


