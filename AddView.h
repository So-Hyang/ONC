#pragma once
#include "afxwin.h"


// AddView ��ȭ �����Դϴ�.

class AddView : public CDialogEx
{
	DECLARE_DYNAMIC(AddView)

public:
	AddView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AddView();
	LPCTSTR Caption;

	// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_AddCal };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CComboBox PubPri;
	CStatic date;
	afx_msg void OnBnClickedAdd();
	CEdit CalEdit;
	CString a_contents;
	CString a_status = L"";
};
