#include "myGraph.h"


myGraph::myGraph()
{
}


myGraph::~myGraph()
{
}


void myGraph::draw1(int x, int y, int n)
{
	if (n == 0)
		line(x - 9, y, x + 9, y);
	else
		line(x, y - 9, x, y + 9);
}

void myGraph::draw2(int x, int y, int n)
{
	if (n ==0 )
		line(x - 7, y - 7, x + 7, y + 7);
	else
		line(x - 7, y + 7, x + 7, y - 7);
}


void myGraph::drawD(int x, int y)
{
	line(x - 9, y, x + 9, y);
	line(x, y - 9, x, y + 9);

}

void myGraph::drawR(int x, int y)
{
	line(x - 7, y - 7, x + 7, y + 7);
	line(x - 7, y + 7, x + 7, y - 7);


}

void myGraph::drawText(int x, int y, int n)
{
	if (n == 0)
		outtextxy(x - 7, y - 40, L"0");
	else
		outtextxy(x - 7, y - 40, L"1");



}

void myGraph::setFont(int size)
{
	LOGFONT f;
	gettextstyle(&f);						// 获取当前字体设置
	f.lfHeight = size;						// 设置字体高度
	_tcscpy_s(f.lfFaceName, _T("黑体"));	// 设置字体为“黑体”
	f.lfQuality = ANTIALIASED_QUALITY;		// 设置输出效果为抗锯齿  
	settextstyle(&f);						// 设置字体样式

}

void myGraph::drawText(int x, int y, TCHAR* str)
{
	outtextxy(x - 7, y - 40, str);
}

void myGraph::drawText1(int x, int y, int n, int m)
{
	if (m == 0)
	{
		drawD(x, y);
		draw1(x, y + 30, n);
	}
	else
	{
		drawR(x, y);
		draw2(x, y + 30, n);
	}


}

void myGraph::drawKey(int x, int y, int n)
{
	setcolor(RED);

	rectangle(x-10, 40, x+10, 150);
	drawText(x+5, 200, n);

	setcolor(WHITE);
}


void myGraph::drawB92(int x,int y,int n)
{
	if (n == 0)
		line(x - 9, y, x + 9, y);
	if (n == 1)
		line(x - 7, y + 7, x + 7, y - 7);
}