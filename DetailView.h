#pragma once
#include "afxwin.h"

class CDetailView : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailView)

public:
	CDetailView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDetailView();
	LPCTSTR Caption;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic date;
	CListBox notice;
};

