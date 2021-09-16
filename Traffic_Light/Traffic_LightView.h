
// Traffic_LightView.h : CTraffic_LightView 类的接口
//

#pragma once


class CTraffic_LightView : public CView
{


protected: // 仅从序列化创建
	CTraffic_LightView();
	DECLARE_DYNCREATE(CTraffic_LightView)

// 特性
public:
	CTraffic_LightDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTraffic_LightView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // Traffic_LightView.cpp 中的调试版本
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







