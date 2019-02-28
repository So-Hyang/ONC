// AddView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ONC.h"
#include "AddView.h"
#include "afxdialogex.h"


// AddView 대화 상자입니다.

IMPLEMENT_DYNAMIC(AddView, CDialogEx)

AddView::AddView(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{
}

AddView::~AddView()
{
}

void AddView::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, PubPri); //공개 비공개 콤보 박스 표시하는거

	//콤보박스에 Pub/Pri 리스트 추가
	PubPri.AddString(TEXT("공개"));
	PubPri.AddString(TEXT("비공개"));

	//콤보박스 수정이 불가능하도록 설정
	CWnd *p_combo = GetDlgItem(IDC_COMBO1);
	HWND h_wnd = ::FindWindowEx(p_combo->m_hWnd, NULL, _T("Edit"), NULL);
	if (NULL != h_wnd)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	DDX_Control(pDX, IDC_Date, date); //날짜 표시하는 스태틱 박스 표시하는거
	date.SetWindowTextW(Caption);  //Caption이라는 변수로 스태틱 박스에 값 넣음
	DDX_Control(pDX, IDC_EDIT1, CalEdit); //메세지 입력받는 에딧 박스 표시하는거
	
}


BEGIN_MESSAGE_MAP(AddView, CDialogEx)
	ON_BN_CLICKED(IDC_ADD, &AddView::OnBnClickedAdd)
END_MESSAGE_MAP()


// AddView 메시지 처리기입니다.


void AddView::OnBnClickedAdd() //버튼 클릭 이벤트
{
	/*int nLength = CalEdit.GetWindowTextLengthW();
	CalEdit.SetSel(nLength, nLength);
	CalEdit.ReplaceSel(Caption);
	CalEdit.GetWindowTextW()*/
	int index = 0;
	index = PubPri.GetCurSel(); //콤보 박스에서 어떤 부분이 선택되었는가

	if (index == -1) //아무것도 선택되지 않았을때
	{
		AddView::OnCancel(); //취소 상태 반환
	}
	else  //아무거나 선택되었을 때
	{
		PubPri.GetLBText(index, a_status);//콤보 박스 중에 뭐가 선택 되었는지에 대한 값을 a_status 변수에 넣음

		int nLen = CalEdit.GetWindowTextLength();
		CalEdit.SetFocus();
		CalEdit.SetSel(nLen, nLen);

		CalEdit.GetWindowTextW(a_contents); //에딧 박스에 입력되어 있는 텍스트 값을 a_contents 변수에 넣음
		AddView::OnOK(); //OK 상태 반환
	}
	


	
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
