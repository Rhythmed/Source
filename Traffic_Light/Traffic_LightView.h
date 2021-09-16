
// Traffic_LightView.h : CTraffic_LightView ��Ľӿ�
//

#pragma once


class CTraffic_LightView : public CView
{


protected: // �������л�����
	CTraffic_LightView();
	DECLARE_DYNCREATE(CTraffic_LightView)

// ����
public:
	CTraffic_LightDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTraffic_LightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Traffic_LightView.cpp �еĵ��԰汾
inline CTraffic_LightDoc* CTraffic_LightView::GetDocument() const
   { return reinterpret_cast<CTraffic_LightDoc*>(m_pDocument); }
#endif


typedef struct tagCAR{
	int road;
	int dire;
	int x;
	int y;
	int color;
	int speed;
}Car;

typedef struct tagLIGHT{
	int acce;
	int seconds;
}Light;







