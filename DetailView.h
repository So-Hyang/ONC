#pragma once
#include "afxwin.h"
#include "ONC.h"

class CDetailView : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailView)

public:
	CDetailView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CDetailView();
	LPCTSTR Caption;
	CString Contents;
	CStringArray TempDataVector = {};
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DETAIL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CStatic D_Title;
	CListBox D_Notice;


};

