
#pragma once
#include <fstream>
#include <string>

#pragma warning(disable:4996)
using namespace std;
using std::ifstream;
using std::ofstream;


class COutputWnd : public CDockablePane
{
	// �����Դϴ�.
public:
	COutputWnd();
	void UpdateFonts();
	int nType=0;
	CString csTitleList[10];
	string sTitleList[10];
	int FindChatRoom(string TopicTitle);
	CListBox m_wndList[10];

	// Ư���Դϴ�.

protected:
	CEdit m_wndInputEdit;

protected:
	
	void AdjustHorzScroll(CListBox& wndListBox);
	
	// �����Դϴ�.
public:
	virtual ~COutputWnd();
	void RefreshTab();

private:
	void SaveText(char* filedirectory, char* filename, string data);
	char* AppendChar(char* arg1, char* arg2);
	CMFCTabCtrl	m_wndTabs;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint point);
	afx_msg void OnTextSave();
	LRESULT OnTabSetActive(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void ChatRoomLeave();

};