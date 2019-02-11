
// CalendarView.h : CCalendarView Ŭ������ �������̽�
//

#pragma once


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

	int CalculateDateInformation(CPoint matrixlocation);

	void ColorMatrix(CPoint matrixlocation);

	void CreateAddView(CString type, CString status, CString name, CString date);

	vector<CString> LoadListSchedule(CString type, CString status, CString name, CString date);

	void AddListSchedule(vector<CString> schedule, int date);

	void ChangeColorEmergencyNotice(string color);

	void EmergencyNotice();

	void DrawCalendar();//�޷� �׸��� �Լ� ���Ƿ� �߰���

	void GetCurrentYearMonth(); //���� �⵵, �� �ҷ����� �Լ�




// �۾��Դϴ�.
public:
	CButton *leftbtn, *rightbtn, *todaybtn, *readbtn;
	//CString btnlist[4] = { L"leftbtn", L"rightbtn", L"todaybtn", L"readbtn" }; /��ư ����ϰ� �����ϴ� �� �ٽ� �õ��ϱ�
	COLORREF newColor;
	bool temp_noticecolor_key = true; //��޸޼��� ����/�б�� �ӽ÷� ���� ����
	CString emergencymsg = L"2�ñ��� �ÿ�, ���� ������ ������ ȣ��"; //��޸޼��� ����
	//�޷� �׸���� ����
	int BackgroundAdd = IDB_BITMAP_CALENDAR_BK;
	CString day[7] = { L"��" ,L"��", L"ȭ", L"��", L"��", L"��", L"��" };
	CString date[35] = {};
	int cur_Month = 0;
	int cur_Year = 0;


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
   { return reinterpret_cast<CONCDoc*>(m_pDocument); }
#endif


