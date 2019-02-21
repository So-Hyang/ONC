
#pragma once
#include <fstream>
#include <string>

#pragma warning(disable:4996)
using namespace std;
using std::ifstream;
using std::ofstream;


class COutputWnd : public CDockablePane
{
	// 생성입니다.
public:
	COutputWnd();

	CString TransferEmergencyMsg();
	void UpdateFonts();

	CListBox m_wndOutputBuild;
	CListBox m_wndOutputDebug;
	CListBox m_wndOutputFind;
	CListBox m_wndTap[10];
	CMFCTabCtrl	m_wndTabs;

	// 특성입니다.
protected:
	CEdit m_wndInputEdit;
	CButton m_wndInputBtn;

protected:
	void FillBuildWindow();
	void FillDebugWindow();
	void FillFindWindow();
	void AdjustHorzScroll(CListBox& wndListBox);
	
	// 구현입니다.
public:
	virtual ~COutputWnd();
private:
	void SaveText(char* filedirectory, char* filename, string data);
	char* AppendChar(char* arg1, char* arg2);

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnTextSave();
	void SendMsg();
	BOOL PreTranslateMessage(MSG* pMsg);
	DECLARE_MESSAGE_MAP()
};