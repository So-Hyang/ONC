
// CalendarView.h : CCalendarView Ŭ������ �������̽�
//

#pragma once

enum ListBoxID
{
	ListBox11 = 211, ListBox12 = 212, ListBox13 = 213

};

struct CalendarInfo//DM ������ ��Ŷ
{
	unsigned int nType;
	string TopicTitle;
	string cUserID;
	string cMsg;
	string cDate;
	string cPassWord;
	string cSenderID;
	string Participants;
	bool PubPrivate;
};

class CCalendarView : public CView
{
protected: // serialization������ ��������ϴ�.
	CCalendarView();
	DECLARE_DYNCREATE(CCalendarView)

	// Ư���Դϴ�.
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

	vector<CalendarInfo> LoadListSchedule(int type, CString status, CString name, string date);

	void AddListSchedule(CalendarInfo newschedule);

	void ChangeColorEmergencyNotice(string color);

	void EmergencyNotice();

	void DrawCalendar();//�޷� �׸��� �Լ� ���Ƿ� �߰���

	void GetCurrentYearMonth(); //���� �⵵, �� �ҷ����� �Լ�

	void OnCalendatTabBtnClicked(UINT uiID);

	void DrawCalendarList(vector<CalendarInfo> n_calendar);





								// �۾��Դϴ�.
public:
	CButton *leftbtn, *rightbtn, *todaybtn, *readbtn, *privatetab, *publictab;
	//CString btnlist[4] = { L"leftbtn", L"rightbtn", L"todaybtn", L"readbtn" }; /��ư ����ϰ� �����ϴ� �� �ٽ� �õ��ϱ�
	CListBox *list_cal[35];
	CListBox *list_cal_11, *list_cal_12, *list_cal_13, *list_cal_14, *list_cal_15, *list_cal_16, *list_cal_17;
	CListBox *list_cal_21, *list_cal_22, *list_cal_23, *list_cal_24, *list_cal_25, *list_cal_26, *list_cal_27;
	CListBox *list_cal_31, *list_cal_32, *list_cal_33, *list_cal_34, *list_cal_35, *list_cal_36, *list_cal_37;
	CListBox *list_cal_41, *list_cal_42, *list_cal_43, *list_cal_44, *list_cal_45, *list_cal_46, *list_cal_47;
	CListBox *list_cal_51, *list_cal_52, *list_cal_53, *list_cal_54, *list_cal_55, *list_cal_56, *list_cal_57;

	COLORREF newColor;
	bool temp_noticecolor_key = true; //��޸޼��� ����/�б�� �ӽ÷� ���� ����
	CString emergencymsg = L"2�ñ��� �ÿ�, ���� ������ ������ ȣ��"; //��޸޼��� ����
	int BackgroundAdd = IDB_BITMAP_CALENDAR_BK;
	CString day[7] = { L"��" ,L"��", L"ȭ", L"��", L"��", L"��", L"��" };
	CString t_date[35] = {};
	int cur_Month = 0;
	int cur_Year = 0;
	CString status, name;
	string s_date;
	int type = 1;
	vector<CalendarInfo> dm_calendarinfo{
		{ 1, "", "ID", "contents1", "2018-10-22", "", "", "", true },{ 1, "", "ID", "contents2", "2019-02-20", "", "", "", true },{ 1, "", "ID", "contents3", "2019-02-20", "", "", "", true },
		{ 1, "", "ID", "contents4", "2019-02-28", "", "", "", true },{ 2, "", "ID", "contents5", "2019-02-20", "", "", "", false },{ 2, "", "ID", "contents6", "2019-02-20", "", "", "", false },
		{ 1, "", "ID", "contents7", "2019-03-01", "", "", "", true },{ 1, "", "ID", "contents8", "2019-04-20", "", "", "", true }

	};


	// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// �����Դϴ�.
public:
	virtual ~CCalendarView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);//���켱��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // CalendarView.cpp�� ����� ����
inline CONCDoc* CCalendarView::GetDocument() const
{
	return reinterpret_cast<CONCDoc*>(m_pDocument);
}
#endif


