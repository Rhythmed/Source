#include "stdafx.h"





int main(int argc, char** argv){
	srand(time(NULL));
	bool isBB84    = false;								// 选择 bb84协议 或 b92协议
	bool isWiretap = false;								// 选择 监听情况

	/*******************************************************************************/
	myFrame mainFrame = myFrame();						// 主界面对象
	initgraph(640, 480);

	mainFrame.mainInterface();							// 主界面绘制
	mainFrame.mainButton();								// 界面按钮绘制
	mainFrame.buttonRespond(isBB84, isWiretap);			// 按钮响应

	closegraph();
	/*********************************************************************************/

	initgraph(1200,742);									// 初始化graphics

	TCHAR len[5];											// 用于存放用户输入的序列长度
	InputBox(len, 5, _T("请输入比特序列长度："), _T("BB84协议"), _T("16"), 0, 0, 1);
	int n = _wtoi(len);										// TCHAR 转为 int


	if (isBB84)												// bb84协议
	{
		if (isWiretap)										// 有监听
		{
			Alice a = Alice(n, true);
			Bob   b = Bob(n, false);
			Bob   e = Bob(n, true);
			a.draw(true);
			b.draw(false);
			e.draw(true);
			mainFrame.BB84Loop(a, b, e, true);
		}
		else
		{
			Alice  a = Alice(n, true);
			Bob    b = Bob(n, false);
			a.draw(true);
			b.draw(false);
			mainFrame.BB84Loop(a, b, b, false);
		}
	}
	if (!isBB84)													// B92协议
	{
		if (isWiretap)
		{
			Alice a = Alice(n,false);
			Bob b = Bob(n,false);
			Bob e = Bob(n,true);
			a.draw(false);
			b.draw(false);
			e.draw(true);
			mainFrame.B92Loop(a, b, e, true);
		}
		else
		{
			Alice a = Alice(n,false);
			Bob   b = Bob(n,false);
			a.draw(false);
			b.draw(false);
			mainFrame.B92Loop(a, b, b, false);
		}
	}


	closegraph();													// 关闭graphics

	return 0;
}