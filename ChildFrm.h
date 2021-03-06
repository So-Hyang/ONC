
// ChildFrm.h : CChildFrame 클래스의 인터페이스
//

#pragma once

class CChildFrame : public CMDIChildWndEx
{
	DECLARE_DYNCREATE(CChildFrame)
public:
	CChildFrame();

// 특성입니다.
protected:
	CSplitterWndEx m_wndSplitter;
public:

// 작업입니다.
public:

// 재정의입니다.
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	/*CView * GetFtViewPane();
	CView * GetFtViewPane1();
	CView * GetFtViewPane2();
	CView * GetFtViewPane3();*/
#endif

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};
