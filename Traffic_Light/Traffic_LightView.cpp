
// Traffic_LightView.cpp : CTraffic_LightView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "Traffic_Light.h"
#endif

#include "Traffic_LightDoc.h"
#include "Traffic_LightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int g_posX = 0;
Car car;
Light light;
BOOL GAME_STAR = TRUE;

void Init()
{
	car.speed = 20;								// �ٶ�
	car.color = rand()%4;								// ��ɫ
	car.road = rand()%2;//rand() % 2;					// ��· 0Ϊ���� 1 Ϊ����
	car.dire = rand()%2; //rand() % 3;					// ���� 0�ϻ��� 1 Ϊ�»���

	if (car.road == 0)
	{
		switch (car.dire)
		{
		case 0:									// ������
			car.x = 1500;
			car.y = 250;
			break;
		case 1:									// ������
			car.x = 0;
			car.y = 450;
			break;
		}
	}
	else
	{
		switch (car.dire)
		{
		case 0:									// ������
			car.x = 800;
			car.y = 700;
			break;
		case 1:									// ������
			car.x = 600;
			car.y = 0;
			break;
		}
	}

	if (GAME_STAR)
	{
		light.acce = 1;							//�̵�
		light.seconds = 200;
		GAME_STAR = FALSE;
	}
}



void check()
{
	if (car.road == 0)
	{
		if (car.dire == 0)
		{
			if (car.x < -100)
				Init();
		}
		if (car.dire == 1)
		{
			if (car.x > 1600)
				Init();
		}

	}
	if (car.road == 1)
	{
		if (car.dire == 0)
		{
			if (car.y < -100)
				Init();
		}
		if (car.dire == 1)
		{
			if (car.y >800)
				Init();
		}
	}
}





void loop()
{
	if (car.road == 0)
	{
		if (light.acce == 1)							// �̵�
		{
			if (car.dire == 0)
				car.x -= car.speed;
			else
				car.x += car.speed;
		}
		if (light.acce != 1)							// ��� �Ƶ�
		{
			switch (car.dire)
			{
			case 0:
				if (car.x > 950 && car.x <970)
					break;
				else
					car.x -= car.speed;
				break;
			case 1:
				if (car.x <450 && car.x>430)
					break;
				else
					car.x += car.speed;
				break;
			}
		}
	}
	if (car.road == 1)
	{
		if (light.acce == 1)							// �̵�
		{
			if (car.dire == 0)
				car.y -= car.speed;
			else
				car.y += car.speed;
		}
		if (light.acce != 1)							// ��� �Ƶ�
		{
			switch (car.dire)
			{
			case 0:
				if (car.y > 595 && car.y<615)
					break;
				else
					car.y -= car.speed;
				break;
			case 1:
				if (car.y<105 && car.y>85)
					break;
				else
					car.y += car.speed;
				break;
			}
		}
	}

	light.seconds--;
	if (light.seconds > 10)
		light.acce = 1;										// �̵�
	if (light.seconds <= 10 && light.seconds >= -10)
		light.acce = 2;									// �Ƶ�
	if (light.seconds < -10 && light.seconds >= -200)
		light.acce = 0;										// ���


	if (light.seconds < -200)
	{
		light.seconds = 200;
		light.acce = 1;
	}


	check();
}









// CTraffic_LightView

IMPLEMENT_DYNCREATE(CTraffic_LightView, CView)

BEGIN_MESSAGE_MAP(CTraffic_LightView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
		ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CTraffic_LightView ����/����

CTraffic_LightView::CTraffic_LightView()
{
	// TODO:  �ڴ˴���ӹ������
	srand(time(NULL));
	Init();


}
CTraffic_LightView::~CTraffic_LightView()
{
}

BOOL CTraffic_LightView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTraffic_LightView ����

void CTraffic_LightView::OnDraw(CDC* pDC)
{
	CTraffic_LightDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���





	CPen *penPrev;												// ����
	CPen penRoad(PS_SOLID, 18, RGB(128, 128, 128));
	CPen penYellow(PS_SOLID, 3, RGB(255, 255, 0));
	CPen penWhite(PS_SOLID, 1, RGB(255, 255, 255));

	CBrush *bushPrev;											// ��ˢ
	CBrush bushGrey;
	CBrush bushWhite;
	CBrush bushRed;
	CBrush bushPink;
	CBrush bushGreen;
	CBrush bushBlack;
	CBrush bushBlue;
	CBrush bushYellow;
	bushYellow.CreateSolidBrush(RGB(255, 255, 0));
	bushPink.CreateSolidBrush(RGB(230, 0, 0));
	bushGrey.CreateSolidBrush(RGB(70, 70, 70));
	bushWhite.CreateSolidBrush(RGB(255, 255, 255));
	bushRed.CreateSolidBrush(RGB(255, 0, 0));
	bushGreen.CreateSolidBrush(RGB(0, 255, 0));
	bushBlack.CreateSolidBrush(RGB(30, 30, 20));
	bushBlue.CreateSolidBrush(RGB(0, 0, 180));

	/*****************************************************************************************/
	bushPrev = pDC->SelectObject(&bushGrey);						// ���ư���·��
	CPoint point1(500, 0);
	CPoint point2(900, 700);
	CPoint point3(0, 150);
	CPoint point4(1500, 550);
	pDC->Rectangle(point1.x, point1.y, point2.x, point2.y);
	pDC->Rectangle(point3.x, point3.y, point4.x, point4.y);
	//pDC->SelectObject(bushPrev);
	//bushGrey.DeleteObject();										// ɾ����ˢ
	/*****************************************************************************************/

	/*****************************************************************************************/
	penPrev = pDC->SelectObject(&penRoad);						// ���Ƶ�·����
	pDC->MoveTo(500, 0);
	pDC->LineTo(500, 150);
	pDC->MoveTo(900, 0);
	pDC->LineTo(900, 150);

	pDC->MoveTo(500, 550);
	pDC->LineTo(500, 700);
	pDC->MoveTo(900, 550);
	pDC->LineTo(900, 700);

	pDC->MoveTo(0, 150);
	pDC->LineTo(500, 150);
	pDC->MoveTo(0, 550);
	pDC->LineTo(500, 550);

	pDC->MoveTo(900, 150);
	pDC->LineTo(1500, 150);
	pDC->MoveTo(900, 550);
	pDC->LineTo(1500, 550);

	pDC->SelectObject(penPrev);
	penRoad.DeleteObject();
	/*****************************************************************************************/

	/*****************************************************************************************/
	penPrev = pDC->SelectObject(&penYellow);						// ���ƻ�ʵ��
	pDC->MoveTo(700, 0);
	pDC->LineTo(700, 105);
	pDC->MoveTo(700, 595);
	pDC->LineTo(700, 700);

	pDC->MoveTo(0, 350);
	pDC->LineTo(450, 350);
	pDC->MoveTo(950, 350);
	pDC->LineTo(1500, 350);

	pDC->SelectObject(penPrev);
	penYellow.DeleteObject();
	/*****************************************************************************************/

	/*****************************************************************************************/
	pDC->SelectObject(&penWhite);						// ���ư�����
	pDC->SelectObject(&bushWhite);

	for (int n = 0; n <= 370; n += 10)
	{
		pDC->Rectangle(515 + n, 115, 520 + n, 155);
		pDC->Rectangle(515 + n, 545, 520 + n, 585);
		pDC->Rectangle(460, 160 + n, 505, 165 + n);
		pDC->Rectangle(895, 160 + n, 940, 165 + n);
	}


	pDC->Rectangle(510, 108, 890, 110);
	pDC->Rectangle(510, 590, 890, 592);
	pDC->Rectangle(454, 160, 456, 540);
	pDC->Rectangle(945, 160, 947, 540);


	pDC->SelectObject(penPrev);
	penWhite.DeleteObject();
	pDC->SelectObject(bushPrev);
	bushWhite.DeleteObject();
	/*****************************************************************************************/

	/*****************************************************************************************/

	CPen temPen(PS_SOLID, 3, RGB(10, 10, 10));
	pDC->SelectObject(temPen);
	pDC->SelectObject(bushGrey);
	pDC->Rectangle(681, 301, 719, 399);


	switch (light.acce){

	case 0:
		pDC->SelectObject(bushRed);									// ·�ں��̵�
		pDC->Ellipse(685, 305, 715, 335);
		pDC->SelectObject(bushPrev);
		bushRed.DeleteObject();
		pDC->Ellipse(685, 365, 715, 395);
		pDC->Ellipse(685, 335, 715, 365);
		break;
	case 1:
		pDC->SelectObject(bushGreen);
		pDC->Ellipse(685, 365, 715, 395);
		pDC->SelectObject(bushPrev);
		bushGreen.DeleteObject();
		pDC->Ellipse(685, 305, 715, 335);
		pDC->Ellipse(685, 335, 715, 365);
		break;
	case 2:
		pDC->SelectObject(bushYellow);
		pDC->Ellipse(685, 335, 715, 365);
		pDC->SelectObject(bushPrev);
		bushYellow.DeleteObject();
		pDC->Ellipse(685, 305, 715, 335);
		pDC->Ellipse(685, 365, 715, 395);
		break;
	}

	/*****************************************************************************************/





	/*****************************************************************************************/
	switch (car.color)
	{
	case 0:
		pDC->SelectObject(bushPink);
		break;
	case 1:
		pDC->SelectObject(bushWhite);
		break;
	case 2:
		pDC->SelectObject(bushBlack);
		break;
	case 3:
		pDC->SelectObject(bushBlue);
		break;
	}

	if (car.road == 0)
	{
		if (car.dire == 0)
			pDC->Rectangle(car.x, car.y, car.x + 50, car.y + 30);
		if (car.dire == 1)
			pDC->Rectangle(car.x-50, car.y, car.x, car.y + 30);
	}
	else{
		if (car.dire == 0)
			pDC->Rectangle(car.x, car.y, car.x + 30, car.y + 50);
		if (car.dire == 1)
			pDC->Rectangle(car.x-30, car.y-50, car.x, car.y);
	}

	pDC->SelectObject(bushPrev);
	switch (car.color)
	{
	case 0:
		bushPink.DeleteObject();
		break;
	case 1:
		bushWhite.DeleteObject();
		break;
	case 2:
		bushBlack.DeleteObject();
		break;
	case 3:
		bushBlue.DeleteObject();
		break;
	}

	/*****************************************************************************************/
}


int CTraffic_LightView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	static CBrush bru(RGB(50, 210, 30));
	SetClassLong(this->m_hWnd, GCL_HBRBACKGROUND, (LONG)(HBRUSH)bru);
	SetTimer(1, 60, NULL);						//	��ʱ��


}

void CTraffic_LightView::OnTimer(UINT_PTR nIDEvent)
{
	CClientDC dc(this);

	loop();
	
	OnDraw(&dc);

	InvalidateRect(NULL, TRUE);

	CView::OnTimer(nIDEvent);
}


void CTraffic_LightView::OnDestroy()
{
	CView::OnDestroy();
	KillTimer(1);
}




// CTraffic_LightView ��ӡ

BOOL CTraffic_LightView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTraffic_LightView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CTraffic_LightView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CTraffic_LightView ���

#ifdef _DEBUG
void CTraffic_LightView::AssertValid() const
{
	CView::AssertValid();
}

void CTraffic_LightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTraffic_LightDoc* CTraffic_LightView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTraffic_LightDoc)));
	return (CTraffic_LightDoc*)m_pDocument;
}



void CTraffic_LightView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTraffic_LightView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{

}



#endif //_DEBUG


// CTraffic_LightView ��Ϣ�������
