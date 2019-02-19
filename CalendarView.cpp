
// CalendarView.cpp : CCalendarView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "ONC.h"
#endif

#include "ONCDoc.h"
#include "CalendarView.h"
#include "AddView.h"
#include "Login.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static const POINT readbtnpos = { 516,465 };
static const POINT calbkpos = { 0,0 };

// CCalendarView

IMPLEMENT_DYNCREATE(CCalendarView, CView)

BEGIN_MESSAGE_MAP(CCalendarView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CCalendarView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
	ON_COMMAND_RANGE(101, 102, CCalendarView::OnLeftRightBtnClicked)
	ON_BN_CLICKED(103, &CCalendarView::OnCalendarTodayBtnClicked)
	ON_BN_CLICKED(104, &CCalendarView::OnCalendarReadBtnClicked)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CCalendarView ����/�Ҹ�

CCalendarView::CCalendarView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	CLogin a;
	//a.DoModal();
}

////��ư Ŭ�� �̺�Ʈ
void CCalendarView::OnLeftRightBtnClicked(UINT uiID)
{
	switch (uiID) {
	case 101://left ��ư
		cur_Month--;
		if (cur_Month == 0) {
			cur_Month = 12;
			cur_Year--;
		}
		break;
	case 102://right ��ư
		cur_Month++;
		if (cur_Month == 13) {
			cur_Month = 1;
			cur_Year++;
		}
		break;
	}
	Invalidate(TRUE);
	UpdateWindow();

}

void CCalendarView::OnCalendarReadBtnClicked()
{
	CClientDC DC(this);
	CBrush Noticebrush, *Oldbrush;
	//���� �޼��� ��Ʈ�� ���� ����
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap bmp; //���� �޼��� ��Ʈ��
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

void CCalendarView::OnCalendarTodayBtnClicked()
{
	GetCurrentYearMonth();
	Invalidate(TRUE);
	UpdateWindow();
}

CCalendarView::~CCalendarView()
{
}

BOOL CCalendarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CCalendarView �׸���

void CCalendarView::OnDraw(CDC* /*pDC*/)
{
	CONCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;



	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CCalendarView �μ�


void CCalendarView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CCalendarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCalendarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCalendarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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

void CCalendarView::OnLButtonDblClk(UINT nFlags, CPoint point)////���켱��
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	POINT n_matrix;
	CString n_date;

	n_matrix = CalculateCoordinatevalueLocation(point);
	ColorMatrix(n_matrix);
	n_date = CalculateDateInformation(n_matrix);


	AddView dlg;
	CString str11;
	//Static caption ����
	dlg.Caption = n_date;

	if (IDOK == dlg.DoModal()) {
		str11 = dlg.test;
	}
	//	dlg.CalEdit.GetWindowTextW(str);
	AfxMessageBox(str11);


	CView::OnLButtonDblClk(nFlags, point);
}


// CCalendarView ����

#ifdef _DEBUG
void CCalendarView::AssertValid() const
{
	CView::AssertValid();
}

void CCalendarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CONCDoc* CCalendarView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CONCDoc)));
	return (CONCDoc*)m_pDocument;
}
#endif //_DEBUG


// CCalendarView �޽��� ó����


void CCalendarView::OnInitialUpdate()
{
	CView::OnInitialUpdate();


	GetCurrentYearMonth();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	leftbtn = new CButton();
	rightbtn = new CButton();
	todaybtn = new CButton();
	readbtn = new CButton();

	leftbtn->Create(L"<-", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 416, 20, calbkpos.x + 450, 42), this, 101);
	rightbtn->Create(L"->", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 516, 20, calbkpos.x + 550, 42), this, 102);
	todaybtn->Create(L"����", BS_DEFPUSHBUTTON, CRect(calbkpos.x + 462, 20, calbkpos.x + 504, 42), this, 103);
	readbtn->Create(L"readbtn", BS_DEFPUSHBUTTON, CRect(readbtnpos.x, readbtnpos.y, readbtnpos.x + 70, readbtnpos.y + 25), this, 104);

	leftbtn->ShowWindow(SW_SHOW); //���� ��ġ�� �´��� Ȯ���ϱ�
	rightbtn->ShowWindow(SW_SHOW);
	todaybtn->ShowWindow(SW_SHOW);
	readbtn->ShowWindow(SW_SHOW);

	int cnt = 0;
	for (int i = 1; i < 8; i++)
	{
		for (int j = 1; j < 6; j++)
		{
			list_cal[cnt] = new CListBox();
			list_cal[cnt]->Create(LBS_STANDARD, CRect(((i - 1) * 90 + 2), (100 + ((j - 1) * 74)), (((i - 1) * 90) + 89), (((j - 1) * 74) + 154)), this, 200 + (j * 10) + i);
			list_cal[cnt]->ShowWindow(SW_SHOW);
			cnt++;
		}
	}

}


void CCalendarView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
					   // �׸��� �޽����� ���ؼ��� CView::OnPaint()��(��) ȣ������ ���ʽÿ�.

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


	CalcaulateCalendar();
	DrawCalendar();
	//DrawCalendar();
}

void CCalendarView::CreateLoginView()
{
}

void CCalendarView::CalcaulateCalendar()
{
	bool leapyear = false;
	int mdays[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	int this_month_date;//�̹� ���� ��¥ ����
	int total_year;
	int total;
	int blank_front;
	int num_date = 1;

	if (((cur_Year % 400) == 0) || (!(cur_Year % 100) && (cur_Year % 4))) //�⵵�� 400���� �����������/100���� ����������� �ʰ� 4�� �����������
		leapyear = true; // ����
	else                  //�ƴϸ�
		leapyear = false; //�����̾ƴϴ�.

	this_month_date = mdays[cur_Month - 1];
	if (leapyear && (cur_Month == 2))//�����̰� 2���̸�
		this_month_date++;//1���� �����ش�.

						  //�۳������ �� ��¥���� ���
	total_year = cur_Year - 1;
	total = 365 * total_year;
	//�� ��¥�� ������ �߻��Ѹ�ŭ ������
	total += ((total_year / 400) - (total_year / 100) + (total_year / 4));
	//���� ���������� ��¥�� ����
	for (int m = 0; m < cur_Month - 1; m++) {
		total += mdays[m];
	}
	//���ذ� �����̸�, 2���� �������� �ѳ�¥�� 1�� ������
	if (leapyear && (cur_Month > 2))
		total += 1;

	total += 1;//�Ϸ縦 ������//�̹� �� 1�ϵ� �����ϴ� ��
	blank_front = (total % 7);// ������� �� ��¥���� 7�� ���� �������� ������ �ε���//0:�Ͽ���, 1:������,,6:�����


	for (int i = 0; i < 35; i++) {
		if (blank_front > 0) { //����Ⱑ ������
			date[i] = "  "; //�������� ǥ��
			blank_front--;
		}
		else {//�������� ó���� �κ��� ���� ��
			if (this_month_date >  0) { //�̹� �޿� ���� ��¥�� ���� ���
				date[i].Format(_T("%d"), num_date); //��¥ ǥ��
				num_date++; //��¥ 1�� ����
				this_month_date--; //���� ��¥ ����
			}
			else {//�̹��޿� ���� ��¥�� ���� ���, �������� ����ó��
				date[i] = "  ";
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
	*/ //�ʿ���� �κ��ϵ�
	return CPoint();
}

CPoint CCalendarView::CalculateCoordinatevalueLocation(CPoint xylocation)
{
	CPoint location;
	for (int i = 0; i < 5; i++) {
		if (((i * 75) + 240 <= xylocation.y) && (((i + 1) * 75) + 240 > xylocation.y))
		{

			location.y = i;
		}
		for (int j = 0; j < 7; j++) {
			if (((j * 90) + 192 <= xylocation.x) && (((j + 1) * 90) + 192 > xylocation.x))
			{
				location.x = j;
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
	Y.Format(_T("%d"), cur_Year);
	M.Format(_T("%d"), cur_Month);
	D = date[matrixindex];
	clickeddate = Y + L"." + M + L"." + D;

	return clickeddate;
}

void CCalendarView::ColorMatrix(CPoint matrixlocation)
{
	CClientDC DC(this);
	CBrush MyBrush;
	CBrush *OldBrush;

	MyBrush.CreateHatchBrush(HS_DIAGCROSS, RGB(0, 0, 255));
	OldBrush = DC.SelectObject(&MyBrush);
	DC.SetBkMode(TRANSPARENT);
	DC.Rectangle(matrixlocation.x * 90, (matrixlocation.y * 74) + 78, (matrixlocation.x + 1) * 90, ((matrixlocation.y + 1) * 74) + 78);
	DC.SelectObject(OldBrush);
	MyBrush.DeleteObject();
}

void CCalendarView::CreateAddView(CString type, CString status, CString name, CString date)
{
}

vector<CString> CCalendarView::LoadListSchedule(CString type, CString status, CString name, CString date)
{
	//DM�� �ִ� ������ �������� �Լ�
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
	else if (color == "Red")
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
	int date_num = 0;
	CString temp_y, temp_m;

	// ��¥ ǥ���ϱ� ���� �� ��ȯ
	MemDC.CreateCompatibleDC(&DC);
	temp_y.Format(_T("%d"), cur_Year);
	temp_m.Format(_T("%d"), cur_Month);
	DC.TextOutW(calbkpos.x + 20, calbkpos.y + 20, temp_y + L"�� " + temp_m + L"��");
	for (int i = 0; i < 7; i++) {
		DC.TextOutW(calbkpos.x + 10 + (i * 89), calbkpos.y + 55, day[i]);
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
			DC.TextOutW(calbkpos.x + 10 + (j * 90), calbkpos.y + 80 + (i * 74), date[date_num]);

			date_num++;
		}
	}

	/*
	CDC MemDC;
	BITMAP bmpInfo;
	CBitmap bmp;
	CBitmap* pOldBmp = NULL;

	MemDC.CreateCompatibleDC(&DC);
	bmp.LoadBitmapW(BackgroundAdd);
	bmp.GetBitmap(&bmpInfo);
	pOldBmp = MemDC.SelectObject(&bmp);
	MemDC.SelectObject(&bmp);
	DC.BitBlt(calbkpos.x, calbkpos.y, bmpInfo.bmWidth, bmpInfo.bmHeight, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBmp);

	/

	*/

}

void CCalendarView::GetCurrentYearMonth()
{
	CTime cur_time = CTime::GetCurrentTime();
	cur_Year = cur_time.GetYear();
	cur_Month = cur_time.GetMonth();
}

