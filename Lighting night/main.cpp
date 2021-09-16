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
	int width;											// 窗户的宽度
	int height;											// 窗户的高度
}Window;


typedef struct tagBuilding
{
	int width;											// 建筑物的宽度
	int height;											// 建筑物的高度
	Window window;										// 窗户结构体
}Building;



void drawMoon();										// 绘制月亮
void drawScene();										// 绘制初始场景
int	 drawBuilding(int pos);								// 绘制建筑物，pos为当前建筑物起始位置
void drawLightning(int pos);							// 绘制闪电,pos为闪电出现位置
void drawChangeScene();									// 绘制变化后的场景


/********************************************************************************************************/
//									主函数
/********************************************************************************************************/

int main(int argc, char** argv)
{	
	srand(time(NULL));									// 设置随机数种子

	initgraph(&graphDriver, &graphMode, "");			// 默认窗口尺寸为640*480
	setorigin(0, 480);									// 为方便绘制，将坐标原点重置为窗口左下角
	setaspectratio(1, -1);								// 为方便绘制，左下角向上为y正半轴，向右为x正半轴



	setbkcolor(RGB(45,45,45));							// 设置背景颜色 RGB(45,45,45)
	cleardevice();

	drawScene();										// 绘制初始场景

	int timeTrigger = 0;				// 闪电触发时间
	int timeLight   = 0;				// 闪电出现的时间
	int posLight    = 0;				// 闪电出现的位置

	while (true)										// 动画循环
	{
		do {
			timeTrigger = rand() % 500;
		} while (timeTrigger <= 150);

		timeLight = rand() % 3000 + timeTrigger;		// 随机掷出闪电出现的时间
		posLight  = rand() % 590 + 50;					// 随机掷出闪电出现的位置


		Sleep(timeLight);								// 等待随机掷出的出现时间

		drawLightning(posLight);						// 绘制闪电

		drawChangeScene();								// 绘制打闪电时的场景

	}



	closegraph();										// 关闭图形界面

	return 0;

}



/********************************************************************************************************/
//									场景绘制函数
//		默认窗口长为640，从而建筑物由0一直绘制到640为止
/********************************************************************************************************/

void drawScene()
{
	for (int pos = 0; pos <= 640;)						// pos为当前建筑物位置 由0到640
	{

		pos = drawBuilding(pos);

	}

	drawMoon();											// 绘制月亮

	getimage(&scene, 0, 0, 640, 480);					// 用以保存所绘制的场景对象。
}



/********************************************************************************************************/
//									建筑物绘制函数
//		每次返回当前建筑物右下角位置
/********************************************************************************************************/

int drawBuilding(int pos)
{
	Building house;
	house.height = rand() % 160 + 80;					// 建筑物高		范围：80~240
	house.width  = rand() % 80 + 20;					// 建筑物宽		范围：20~100

	house.window.height = 8;							// 窗户 高度 8
	house.window.width  = 10;							// 窗户 宽度 10

	if (house.width <= 50)
	{
		pos += house.width;
		return pos;
	}

	int points[8] = {	pos, 0,							// 由建筑物左下角开始，逆时针储存各个顶点的位置
						pos + house.width, 0,
						pos + house.width, house.height,
						pos, house.height };							
	setfillcolor(RGB(30, 30, 60));						// 设置建筑物填充色	
	solidpolygon((POINT*)points, 4);					// 绘制建筑物



	// 绘制房子上的窗户
	int winDist  = rand() % 10 + 10;					// 各个窗户之间的距离
	int winDistX = rand() % 10 + 18;					// 窗户左边起始距离
	int winDistY = rand() % 10 + 10;					// 窗户顶部起始距离

	for (int posY = house.height  - winDistY; posY > house.height / 5;)				// 控制窗户的行数
	{
		for (int posX = pos + winDistX; posX < pos + house.width - 19;)				// 控制每行画几个窗户
		{
			int WinPoint[8] = { posX, posY,
								posX + house.window.width, posY,
								posX + house.window.width, posY - house.window.height,
								posX, posY - house.window.height };

			int ran = rand() % 4;
			if (ran == 1)
				setfillcolor(RGB(240, 240, 150));			// 设置窗户亮着
			else
				setfillcolor(RGB(30, 44, 40));				// 设置窗户暗着

			solidpolygon((POINT*)WinPoint, 4);				// 画无边框的填充窗(四边形)

			posX += (house.window.width + winDist);			// 窗左上角的x值每次画完都增加，方便画下一个窗户
		}
		posY -= (house.window.height + winDist);			// 窗左上角的y值每次画完都增加，方便画下一个窗户
	}






	pos += house.width;
	return pos;
}


/********************************************************************************************************/
//									闪电绘制函数
/********************************************************************************************************/

void drawLightning(int pos)
{
	int num = rand() % 3;								// 随机掷出同时出现的闪电个数
	int posX   = pos;										
	int posY   = 480;
	int posEnd = 0;										// 用于记录闪电的终点

	int dist   = 0;										// 每小段闪电长度
	int angleX = 0;										
	int angleY = 0;										// 闪电角度分量

	int nextX = 0;
	int nextY = 0;										// 每小段闪电的终点


	for (int i = 0; i < num; i++)
	{

		posEnd = posY - (rand() % 120) - 120;			// 随机掷出闪电的终点	范围为240~360
		while (posY >= posEnd)							// 绘制闪电每个小线段
		{
			dist   = rand() % 20;						
			angleX = rand() % 120 - 60;					// 正弦范围为 : -60~60
			angleY = rand() % 120 - 60;					// 余弦范围为 : -60~60
			nextX = posX + (int)(dist * sin(angleX * PI / 180));	
			nextY = posY - (int)(dist * cos(angleY * PI / 180));	

			setlinecolor(RGB(125, 250, 240));						// 设置闪电颜色
			setlinestyle(PS_ENDCAP_ROUND | PS_SOLID, 2);			// 设置闪电样式(线段断点为平、实线、宽度为2)
			line(posX, posY, nextX,nextY);							// 绘制闪电

			posX = nextX;											// 将端点赋值给初始点(x轴)
			posY = nextY;											// 将端点赋值给初始点(y轴)
			Sleep((rand() % 100) > 66 ? 10 : 5);					// 设置停滞时间
		}
	}
}


/********************************************************************************************************/
//									变化场景绘制函数
/********************************************************************************************************/

void drawChangeScene()
{

	int ran = rand() % 15 + 10;
	ran = rand() % 10 + (ran / 10);


	IMAGE image;											// 定义一个图像对象，用于绘制高亮的图像
	getimage(&image, 0, 0, 640, 480);						// 获取图像范围
	DWORD *pMem = GetImageBuffer(&image);					// 获取指向显存的指针
	int r, g, b;											// 定义分别获取点的RGB颜色值
	for (int i = 0; i < (640 * 480); i++)							
	{
		r = min((int)(GetRValue(pMem[i])*ran), 255);			
		b = min((int)(GetBValue(pMem[i])*ran), 255);
		g = min((int)(GetGValue(pMem[i])*ran), 255);
		pMem[i] = RGB(r, g, b);
	}

	putimage(0, 0, &image);									// 绘制闪电时的场景
	Sleep(200);												// 停滞时间
	cleardevice();								
	putimage(0, 0, &scene);									// 绘制闪电过去后场景
}



void drawMoon()
{
	int posX = rand() % 600 + 20;							// 月亮 出现范围 20~620
	int posY = rand() % 160 + 300;							// 月亮 高度范围 300~460
	int dist = rand() % 45;			

	setfillcolor(RGB(240, 250, 170));
	solidcircle(posX,posY,20);
	setbkcolor(RGB(45, 45, 45));
	clearcircle(posX - dist, posY, 20);
}