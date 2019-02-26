
// CalendarView.h : CCalendarView Ŭ������ �������̽�
//

#pragma once



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



	void DrawCalendarList(vector<CalendarInfo> n_calendar);







								// �۾��Դϴ�.
public:
	CButton *leftbtn, *rightbtn, *todaybtn, *readbtn, *privatetab, *publictab;
	//CString btnlist[4] = { L"leftbtn", L"rightbtn", L"todaybtn", L"readbtn" }; /��ư ����ϰ� �����ϴ� �� �ٽ� �õ��ϱ�
	CListBox *list_cal[35];

	COLORREF newColor;
	bool temp_noticecolor_key = true; //��޸޼��� ����/�б�� �ӽ÷� ���� ����
	CString emergencymsg = L"2�ñ��� �ÿ�, ���� ������ ������ ȣ��"; //��޸޼��� ����
	int BackgroundAdd = IDB_BITMAP_CALENDAR_BK;
	CString day[7] = { L"��" ,L"��", L"ȭ", L"��", L"��", L"��", L"��" };
	CString t_date[35] = {};
	int C_cur_Month = 0;
	int C_cur_Year = 0;

	//int cur_Month = 0;
	//int cur_Year = 0;

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
	afx_msg  void OnCalendatTabBtnClicked(UINT uiID);
	afx_msg void OnCalendarListClicked(UINT uuid);
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


