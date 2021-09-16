#pragma once
#include <graphics.h>





class myGraph
{
public:
	 myGraph();
	~myGraph();


public:
	void drawKey(int x, int y, int n);
	void drawD(int x, int y);
	void drawR(int x, int y);
	void draw1(int x, int y,int n);
	void draw2(int x, int y,int n);
	void drawText(int x, int y, int n);
	void drawText(int x, int y, TCHAR* str);
	void drawText1(int x, int y, int n, int m);
	void drawB92(int x, int y, int n);
	void setFont(int size);
};

