#include "myFrame.h"
#include "Alice.h"
#include "Bob.h"
#include <graphics.h>


myFrame::myFrame()
{
}

myFrame::~myFrame()
{
}

void myFrame::mainInterface()
{
	
	setbkcolor(WHITE);
	cleardevice();
	setlinecolor(BLACK);            //设置线条黑色
	setlinestyle(PS_SOLID, 8);      //宽度8
	rectangle(20, 20, 620, 460);    //画大边框
	setlinestyle(PS_SOLID, 3);      //宽度还原
}

void myFrame::mainButton()
{
	rectangle(180, 100, 440, 160);    // BB84协议 无窃听
	rectangle(180, 180, 440, 240);    // BB84协议 有窃听
	rectangle(180, 260, 440, 320);    // B92协议  无窃听
	rectangle(180, 340, 440, 400);    // B92协议  有窃听

	LOGFONT ball_text;              //设置字体
	gettextstyle(&ball_text);
	_tcscpy_s(ball_text.lfFaceName, _T("黑体"));
	ball_text.lfHeight = 32;
	ball_text.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&ball_text);
	settextcolor(BLACK);            //文字黑色

	outtextxy(200 - 6, 113, _T("BB84协议 无窃听"));
	outtextxy(200 - 6, 193, _T("BB84协议 有窃听"));
	outtextxy(200, 273, _T("B92协议 无窃听"));
	outtextxy(200, 353, _T("B92协议 有窃听"));


	return;
}

void myFrame::buttonRespond(bool& isBB84,bool& isWiretap)
{
	bool exit = false;
	MOUSEMSG m;

	while (!exit)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN){

			if (m.x > 190 && m.x < 430){
				if (m.y>100 && m.y < 160){						// 选择bb84 无监听
					exit = true;
					isBB84 = true;
					isWiretap = false;
				}
				if (m.y>180 && m.y < 240){						// 选择bb84 有监听
					exit = true;
					isBB84 = true;
					isWiretap = true;
				}
				if (m.y>260 && m.y < 320){						// 选择b92 无监听
					exit = true;
					isBB84 = false;
					isWiretap = false;
				}
				if (m.y>340 && m.y < 400){						// 选择b92 有监听
					exit = true;
					isBB84 = false;
					isWiretap = true;
				}
			}

		}
	}
}

void myFrame::BB84Loop(Alice& a,Bob& b,Bob& e,bool isWiretap)
{
	bool exit = false;									// 结束循环
	MOUSEMSG m;											// 鼠标消息


	int button1 = 0;
	int button2 = 0;
	int button3 = 0;

	setcolor(YELLOW);
	rectangle(60, 300,160, 340);						// Alice 量子信道发送
	outtextxy(70 - 8, 313, _T("量子信道发送"));

	setcolor(GREEN);
	rectangle(180, 300, 280, 340);
	outtextxy(190 - 8, 313, _T("经典信道发送"));		// Alice 的经典信道发送

	rectangle(900, 300, 1070, 340);
	outtextxy(950 - 8, 313, _T("经典信道发送"));		// Bob 的经典信道发送
	setcolor(WHITE);

	while (!exit)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.y > 300 && m.y < 340)
			{
				if (m.x > 62 && m.x < 158)						// 点击 Alice量子信道
				{
					if (isWiretap)									// 存在窃听
					{
						if (button1 == 0)							// 初次左击量子信道发送
						{
							a.drawSend(true,true);
							b.bb84sendToAlice(a);
							e.bb84wiretap(a, b);
							a.drawQuantum(true,true);
							e.drawRecev(true);
							b.drawRecev(false);						// 完成了Alice发送的量子被 Eve截获并重新发送给Bob
							b.bb84recvFromAlice(a);
							button1++;
						}
						else
						{
							button1++;
						}
					}
					else
					{
						if (button1 == 0)							// 初次左击量子信道发送
						{
							a.drawSend(true,false);
							b.bb84sendToAlice(a);						// Alice 发送量子给 Bob
							b.bb84recvFromAlice(a);						// Bob   接收量子
							a.drawQuantum(true,false);
							b.drawRecev(false);
							button1++;
						}
						else
						{
							button1++;
						}
					}
				}
				if (m.x > 182 && m.x < 278)
				{
					if (button1 > 0 && button3 > 0)
					{
						a.drawSend1();
						b.drawResult();
						button2++;
					}
				}
				if (m.x > 902 && m.x < 1068)
				{
					if (button1 > 0 && button3 == 0)			// 量子信道已经发送 且初次左击Bob 经典信道发送
					{
						b.drawSend(true);
						a.drawCheckout1(true,b);
						button3++;
					}
					if (button2 > 0 && button3 > 0)
					{
						b.drawSend1();
						if(b.bb84checkout(a))
							MessageBox(NULL, L"无窃听存在，通信安全", L"检验成功", MB_SYSTEMMODAL | MB_OK);
						else
							MessageBox(NULL, L"有窃听存在，通信不安全", L"检验成功", MB_SYSTEMMODAL | MB_OK);
					}
				}
			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)
			exit = true;
	}
}

void myFrame::B92Loop(Alice& a, Bob& b, Bob& e, bool isWiretap)
{
	bool exit = false;									// 结束循环
	MOUSEMSG m;											// 鼠标消息


	int button1 = 0;
	int button2 = 0;
	int button3 = 0;

	setcolor(YELLOW);
	rectangle(60, 300, 160, 340);						// Alice 量子信道发送
	outtextxy(70 - 8, 313, _T("量子信道发送"));

	setcolor(GREEN);
	rectangle(180, 300, 280, 340);
	outtextxy(190 - 8, 313, _T("经典信道发送"));		// Alice 的经典信道发送

	rectangle(900, 300, 1070, 340);
	outtextxy(950 - 8, 313, _T("经典信道发送"));		// Bob 的经典信道发送
	setcolor(WHITE);

	while (!exit)
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.y > 300 && m.y < 340)
			{
				if (m.x > 62 && m.x < 158)						// 点击 Alice量子信道
				{
					if (isWiretap)									// 存在窃听
					{

						if (button1 == 0)
						{
							a.drawSend(false, true);
							b.b92sendToAlice(a);
							e.b92wiretap(a, b);
							a.drawQuantum(false, true);
							e.drawRecev(true);
							b.drawRecev(false);						// 完成了Alice发送的量子被 Eve截获并重新发送给Bob
							b.bb84recvFromAlice(a);
							b.drawResult();
							button1++;
						}
						else
							button1++;


					}
					else											// 不存在窃听
					{
						if (button1 == 0)							// 初次左击量子信道发送
						{
							a.drawSend(false, false);				// 不是BB84协议 且不存在窃听
							b.b92sendToAlice(a);					// 发送测量基
							b.b92recvFromAlice(a);					// 接收反馈
							a.drawQuantum(false,false);				// 发送光子
							b.drawRecev(false);						// 接收
							b.drawResult();
							b.b92checkout(a);
							button1++;
						}
						else
						{
							button1++;
						}
					}
				}


				//if (m.x > 182 && m.x < 278)
				//{
				//	if (button1 > 0 && button3 > 0)
				//	{
				//		button2++;
				//	}
				//}


				if (m.x > 902 && m.x < 1068)
				{
					if (button1 > 0 && button3 == 0)			// 量子信道已经发送 且初次左击Bob 经典信道发送
					{
						b.drawSend(false);
						a.drawCheckout1(false,b);


						button3++;
					}
					if (button3 > 0)
					{
						b.drawSend1();
						if (b.bb84checkout(a))
							MessageBox(NULL, L"无窃听存在，通信安全", L"检验成功", MB_SYSTEMMODAL | MB_OK);
						else
							MessageBox(NULL, L"有窃听存在，通信不安全", L"检验成功", MB_SYSTEMMODAL | MB_OK);
					}
				}

			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)
			exit = true;
	}
}