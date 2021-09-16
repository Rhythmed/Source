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
	setlinecolor(BLACK);            //����������ɫ
	setlinestyle(PS_SOLID, 8);      //���8
	rectangle(20, 20, 620, 460);    //����߿�
	setlinestyle(PS_SOLID, 3);      //��Ȼ�ԭ
}

void myFrame::mainButton()
{
	rectangle(180, 100, 440, 160);    // BB84Э�� ������
	rectangle(180, 180, 440, 240);    // BB84Э�� ������
	rectangle(180, 260, 440, 320);    // B92Э��  ������
	rectangle(180, 340, 440, 400);    // B92Э��  ������

	LOGFONT ball_text;              //��������
	gettextstyle(&ball_text);
	_tcscpy_s(ball_text.lfFaceName, _T("����"));
	ball_text.lfHeight = 32;
	ball_text.lfQuality = ANTIALIASED_QUALITY;
	settextstyle(&ball_text);
	settextcolor(BLACK);            //���ֺ�ɫ

	outtextxy(200 - 6, 113, _T("BB84Э�� ������"));
	outtextxy(200 - 6, 193, _T("BB84Э�� ������"));
	outtextxy(200, 273, _T("B92Э�� ������"));
	outtextxy(200, 353, _T("B92Э�� ������"));


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
				if (m.y>100 && m.y < 160){						// ѡ��bb84 �޼���
					exit = true;
					isBB84 = true;
					isWiretap = false;
				}
				if (m.y>180 && m.y < 240){						// ѡ��bb84 �м���
					exit = true;
					isBB84 = true;
					isWiretap = true;
				}
				if (m.y>260 && m.y < 320){						// ѡ��b92 �޼���
					exit = true;
					isBB84 = false;
					isWiretap = false;
				}
				if (m.y>340 && m.y < 400){						// ѡ��b92 �м���
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
	bool exit = false;									// ����ѭ��
	MOUSEMSG m;											// �����Ϣ


	int button1 = 0;
	int button2 = 0;
	int button3 = 0;

	setcolor(YELLOW);
	rectangle(60, 300,160, 340);						// Alice �����ŵ�����
	outtextxy(70 - 8, 313, _T("�����ŵ�����"));

	setcolor(GREEN);
	rectangle(180, 300, 280, 340);
	outtextxy(190 - 8, 313, _T("�����ŵ�����"));		// Alice �ľ����ŵ�����

	rectangle(900, 300, 1070, 340);
	outtextxy(950 - 8, 313, _T("�����ŵ�����"));		// Bob �ľ����ŵ�����
	setcolor(WHITE);

	while (!exit)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.y > 300 && m.y < 340)
			{
				if (m.x > 62 && m.x < 158)						// ��� Alice�����ŵ�
				{
					if (isWiretap)									// ��������
					{
						if (button1 == 0)							// ������������ŵ�����
						{
							a.drawSend(true,true);
							b.bb84sendToAlice(a);
							e.bb84wiretap(a, b);
							a.drawQuantum(true,true);
							e.drawRecev(true);
							b.drawRecev(false);						// �����Alice���͵����ӱ� Eve�ػ����·��͸�Bob
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
						if (button1 == 0)							// ������������ŵ�����
						{
							a.drawSend(true,false);
							b.bb84sendToAlice(a);						// Alice �������Ӹ� Bob
							b.bb84recvFromAlice(a);						// Bob   ��������
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
					if (button1 > 0 && button3 == 0)			// �����ŵ��Ѿ����� �ҳ������Bob �����ŵ�����
					{
						b.drawSend(true);
						a.drawCheckout1(true,b);
						button3++;
					}
					if (button2 > 0 && button3 > 0)
					{
						b.drawSend1();
						if(b.bb84checkout(a))
							MessageBox(NULL, L"���������ڣ�ͨ�Ű�ȫ", L"����ɹ�", MB_SYSTEMMODAL | MB_OK);
						else
							MessageBox(NULL, L"���������ڣ�ͨ�Ų���ȫ", L"����ɹ�", MB_SYSTEMMODAL | MB_OK);
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
	bool exit = false;									// ����ѭ��
	MOUSEMSG m;											// �����Ϣ


	int button1 = 0;
	int button2 = 0;
	int button3 = 0;

	setcolor(YELLOW);
	rectangle(60, 300, 160, 340);						// Alice �����ŵ�����
	outtextxy(70 - 8, 313, _T("�����ŵ�����"));

	setcolor(GREEN);
	rectangle(180, 300, 280, 340);
	outtextxy(190 - 8, 313, _T("�����ŵ�����"));		// Alice �ľ����ŵ�����

	rectangle(900, 300, 1070, 340);
	outtextxy(950 - 8, 313, _T("�����ŵ�����"));		// Bob �ľ����ŵ�����
	setcolor(WHITE);

	while (!exit)
	{
		m = GetMouseMsg();

		if (m.uMsg == WM_LBUTTONDOWN)
		{
			if (m.y > 300 && m.y < 340)
			{
				if (m.x > 62 && m.x < 158)						// ��� Alice�����ŵ�
				{
					if (isWiretap)									// ��������
					{

						if (button1 == 0)
						{
							a.drawSend(false, true);
							b.b92sendToAlice(a);
							e.b92wiretap(a, b);
							a.drawQuantum(false, true);
							e.drawRecev(true);
							b.drawRecev(false);						// �����Alice���͵����ӱ� Eve�ػ����·��͸�Bob
							b.bb84recvFromAlice(a);
							b.drawResult();
							button1++;
						}
						else
							button1++;


					}
					else											// ����������
					{
						if (button1 == 0)							// ������������ŵ�����
						{
							a.drawSend(false, false);				// ����BB84Э�� �Ҳ���������
							b.b92sendToAlice(a);					// ���Ͳ�����
							b.b92recvFromAlice(a);					// ���շ���
							a.drawQuantum(false,false);				// ���͹���
							b.drawRecev(false);						// ����
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
					if (button1 > 0 && button3 == 0)			// �����ŵ��Ѿ����� �ҳ������Bob �����ŵ�����
					{
						b.drawSend(false);
						a.drawCheckout1(false,b);


						button3++;
					}
					if (button3 > 0)
					{
						b.drawSend1();
						if (b.bb84checkout(a))
							MessageBox(NULL, L"���������ڣ�ͨ�Ű�ȫ", L"����ɹ�", MB_SYSTEMMODAL | MB_OK);
						else
							MessageBox(NULL, L"���������ڣ�ͨ�Ų���ȫ", L"����ɹ�", MB_SYSTEMMODAL | MB_OK);
					}
				}

			}
		}
		if (m.uMsg == WM_RBUTTONDOWN)
			exit = true;
	}
}