#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>


#define PI 3.1415										// 3.1415


IMAGE scene;
int graphDriver = CGA;
int graphMode   = CGAC0;


typedef struct tagWindow
{
	int width;											// �����Ŀ��
	int height;											// �����ĸ߶�
}Window;


typedef struct tagBuilding
{
	int width;											// ������Ŀ��
	int height;											// ������ĸ߶�
	Window window;										// �����ṹ��
}Building;



void drawMoon();										// ��������
void drawScene();										// ���Ƴ�ʼ����
int	 drawBuilding(int pos);								// ���ƽ����posΪ��ǰ��������ʼλ��
void drawLightning(int pos);							// ��������,posΪ�������λ��
void drawChangeScene();									// ���Ʊ仯��ĳ���


/********************************************************************************************************/
//									������
/********************************************************************************************************/

int main(int argc, char** argv)
{	
	srand(time(NULL));									// �������������

	initgraph(&graphDriver, &graphMode, "");			// Ĭ�ϴ��ڳߴ�Ϊ640*480
	setorigin(0, 480);									// Ϊ������ƣ�������ԭ������Ϊ�������½�
	setaspectratio(1, -1);								// Ϊ������ƣ����½�����Ϊy�����ᣬ����Ϊx������



	setbkcolor(RGB(45,45,45));							// ���ñ�����ɫ RGB(45,45,45)
	cleardevice();

	drawScene();										// ���Ƴ�ʼ����

	int timeTrigger = 0;				// ���紥��ʱ��
	int timeLight   = 0;				// ������ֵ�ʱ��
	int posLight    = 0;				// ������ֵ�λ��

	while (true)										// ����ѭ��
	{
		do {
			timeTrigger = rand() % 500;
		} while (timeTrigger <= 150);

		timeLight = rand() % 3000 + timeTrigger;		// �������������ֵ�ʱ��
		posLight  = rand() % 590 + 50;					// �������������ֵ�λ��


		Sleep(timeLight);								// �ȴ���������ĳ���ʱ��

		drawLightning(posLight);						// ��������

		drawChangeScene();								// ���ƴ�����ʱ�ĳ���

	}



	closegraph();										// �ر�ͼ�ν���

	return 0;

}



/********************************************************************************************************/
//									�������ƺ���
//		Ĭ�ϴ��ڳ�Ϊ640���Ӷ���������0һֱ���Ƶ�640Ϊֹ
/********************************************************************************************************/

void drawScene()
{
	for (int pos = 0; pos <= 640;)						// posΪ��ǰ������λ�� ��0��640
	{

		pos = drawBuilding(pos);

	}

	drawMoon();											// ��������

	getimage(&scene, 0, 0, 640, 480);					// ���Ա��������Ƶĳ�������
}



/********************************************************************************************************/
//									��������ƺ���
//		ÿ�η��ص�ǰ���������½�λ��
/********************************************************************************************************/

int drawBuilding(int pos)
{
	Building house;
	house.height = rand() % 160 + 80;					// �������		��Χ��80~240
	house.width  = rand() % 80 + 20;					// �������		��Χ��20~100

	house.window.height = 8;							// ���� �߶� 8
	house.window.width  = 10;							// ���� ��� 10

	if (house.width <= 50)
	{
		pos += house.width;
		return pos;
	}

	int points[8] = {	pos, 0,							// �ɽ��������½ǿ�ʼ����ʱ�봢����������λ��
						pos + house.width, 0,
						pos + house.width, house.height,
						pos, house.height };							
	setfillcolor(RGB(30, 30, 60));						// ���ý��������ɫ	
	solidpolygon((POINT*)points, 4);					// ���ƽ�����



	// ���Ʒ����ϵĴ���
	int winDist  = rand() % 10 + 10;					// ��������֮��ľ���
	int winDistX = rand() % 10 + 18;					// ���������ʼ����
	int winDistY = rand() % 10 + 10;					// ����������ʼ����

	for (int posY = house.height  - winDistY; posY > house.height / 5;)				// ���ƴ���������
	{
		for (int posX = pos + winDistX; posX < pos + house.width - 19;)				// ����ÿ�л���������
		{
			int WinPoint[8] = { posX, posY,
								posX + house.window.width, posY,
								posX + house.window.width, posY - house.window.height,
								posX, posY - house.window.height };

			int ran = rand() % 4;
			if (ran == 1)
				setfillcolor(RGB(240, 240, 150));			// ���ô�������
			else
				setfillcolor(RGB(30, 44, 40));				// ���ô�������

			solidpolygon((POINT*)WinPoint, 4);				// ���ޱ߿����䴰(�ı���)

			posX += (house.window.width + winDist);			// �����Ͻǵ�xֵÿ�λ��궼���ӣ����㻭��һ������
		}
		posY -= (house.window.height + winDist);			// �����Ͻǵ�yֵÿ�λ��궼���ӣ����㻭��һ������
	}






	pos += house.width;
	return pos;
}


/********************************************************************************************************/
//									������ƺ���
/********************************************************************************************************/

void drawLightning(int pos)
{
	int num = rand() % 3;								// �������ͬʱ���ֵ��������
	int posX   = pos;										
	int posY   = 480;
	int posEnd = 0;										// ���ڼ�¼������յ�

	int dist   = 0;										// ÿС�����糤��
	int angleX = 0;										
	int angleY = 0;										// ����Ƕȷ���

	int nextX = 0;
	int nextY = 0;										// ÿС��������յ�


	for (int i = 0; i < num; i++)
	{

		posEnd = posY - (rand() % 120) - 120;			// �������������յ�	��ΧΪ240~360
		while (posY >= posEnd)							// ��������ÿ��С�߶�
		{
			dist   = rand() % 20;						
			angleX = rand() % 120 - 60;					// ���ҷ�ΧΪ : -60~60
			angleY = rand() % 120 - 60;					// ���ҷ�ΧΪ : -60~60
			nextX = posX + (int)(dist * sin(angleX * PI / 180));	
			nextY = posY - (int)(dist * cos(angleY * PI / 180));	

			setlinecolor(RGB(125, 250, 240));						// ����������ɫ
			setlinestyle(PS_ENDCAP_ROUND | PS_SOLID, 2);			// ����������ʽ(�߶ζϵ�Ϊƽ��ʵ�ߡ����Ϊ2)
			line(posX, posY, nextX,nextY);							// ��������

			posX = nextX;											// ���˵㸳ֵ����ʼ��(x��)
			posY = nextY;											// ���˵㸳ֵ����ʼ��(y��)
			Sleep((rand() % 100) > 66 ? 10 : 5);					// ����ͣ��ʱ��
		}
	}
}


/********************************************************************************************************/
//									�仯�������ƺ���
/********************************************************************************************************/

void drawChangeScene()
{

	int ran = rand() % 15 + 10;
	ran = rand() % 10 + (ran / 10);


	IMAGE image;											// ����һ��ͼ��������ڻ��Ƹ�����ͼ��
	getimage(&image, 0, 0, 640, 480);						// ��ȡͼ��Χ
	DWORD *pMem = GetImageBuffer(&image);					// ��ȡָ���Դ��ָ��
	int r, g, b;											// ����ֱ��ȡ���RGB��ɫֵ
	for (int i = 0; i < (640 * 480); i++)							
	{
		r = min((int)(GetRValue(pMem[i])*ran), 255);			
		b = min((int)(GetBValue(pMem[i])*ran), 255);
		g = min((int)(GetGValue(pMem[i])*ran), 255);
		pMem[i] = RGB(r, g, b);
	}

	putimage(0, 0, &image);									// ��������ʱ�ĳ���
	Sleep(200);												// ͣ��ʱ��
	cleardevice();								
	putimage(0, 0, &scene);									// ���������ȥ�󳡾�
}



void drawMoon()
{
	int posX = rand() % 600 + 20;							// ���� ���ַ�Χ 20~620
	int posY = rand() % 160 + 300;							// ���� �߶ȷ�Χ 300~460
	int dist = rand() % 45;			

	setfillcolor(RGB(240, 250, 170));
	solidcircle(posX,posY,20);
	setbkcolor(RGB(45, 45, 45));
	clearcircle(posX - dist, posY, 20);
}