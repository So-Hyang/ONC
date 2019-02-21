#pragma once
#include "afxwin.h"


// AddView 대화 상자입니다.

class AddView : public CDialogEx
{
	DECLARE_DYNAMIC(AddView)

public:
	AddView(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AddView();
	LPCTSTR Caption;

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddCal };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox PubPri;
	CStatic date;
	afx_msg void OnBnClickedAdd();
	CEdit CalEdit;
	CString a_contents;
	CString a_status = L"";
};
