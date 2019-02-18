
#pragma once

/////////////////////////////////////////////////////////////////////////////
// COutputList â

class COutputList : public CListBox
{
// �����Դϴ�.
public:
	COutputList();

// �����Դϴ�.
public:
	virtual ~COutputList();

protected:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnViewOutput();

	DECLARE_MESSAGE_MAP()
};

class COutputWnd : public CDockablePane
{
// �����Դϴ�.
public:
	COutputWnd();

	CString TransferEmergencyMsg();
	void UpdateFonts();

// Ư���Դϴ�.
protected:
	CMFCTabCtrl	m_wndTabs;

	COutputList m_FirstChat;
	COutputList m_SecondChat;
	COutputList m_ThirdChat;
	COutputList m_FourthChat;
	COutputList m_FifthChat;
	COutputList m_SixthChat;
	COutputList m_SeventhChat;
	COutputList m_EighthChat;
	COutputList m_NinthChat;
	COutputList m_TenthChat;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();

	void AdjustHorzScroll(CListBox& wndListBox);

// �����Դϴ�.
public:
	virtual ~COutputWnd();
	

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
};

