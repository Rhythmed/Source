#include "Bob.h"
#include "Alice.h"
#include "myGraph.h"
#include <stdio.h>
#include <stdlib.h>


Bob::Bob(bool isWiretap)
{
	this->length = 16;
	this->sB = new int[16];
	this->mB = new int[16];
	this->rB = new int[16];

	for (int i = 0; i < 16; i++){
		this->sB[i] = 0;					// ��� ��Ҫ���ڽ������� �� ����������
		this->mB[i] = rand() % 2;			// ������� ����������  0��ʾ D�����룬1��ʾ R������
		this->rB[i] = 0;
	}

	if (!isWiretap)
	{
		//printf("   Bob: ����������\n");
		//for (int i = 0; i < 10; i++)
		//	printf("%d ", sB[i]);
		//printf("\n");

		printf("   Bob: ����������\n");
		for (int i = 0; i < 16; i++){
			//if (this->mB[i] == 0)
			//	printf("D ");
			//else
			//	printf("R ");

			printf("%2d", mB[i]);
		}
		printf("\n\n");
	}
	else
	{
		//printf("   Eve: ����������\n");
		//for (int i = 0; i < 10; i++)
		//	printf("%d ", sB[i]);
		//printf("\n");

		printf("   Eve: ����������\n");
		for (int i = 0; i < 16; i++){
			//if (this->mB[i] == 0)
			//	printf(" D");
			//else
			//	printf(" R");
			printf("%2d", this->mB[i]);
		}
		printf("\n\n");
	}














}

Bob::Bob(int len,bool isWiretap)
{
	this->length = len;
	this->sB = new int[this->length];
	this->mB = new int[this->length];
	this->rB = new int[this->length];

	for (int i = 0; i < this->length; i++){
		this->sB[i] = 0;					// ��� ��Ҫ���ڽ������� �� ����������
		this->mB[i] = rand() % 2;			// ������� ����������  0��ʾ D�����룬1��ʾ R������
		this->rB[i] = 0;
	}

	if (!isWiretap)
	{
		//printf("   Bob: ����������\n");
		//for (int i = 0; i < length; i++)
		//	printf("%d ", sB[i]);
		//printf("\n");

		printf("   Bob: ����������\n");
		for (int i = 0; i < length; i++){
			if (this->mB[i] == 0)
				printf("D ");
			else
				printf("R ");
		}
		printf("\n\n");
	}
	else
	{
		//printf("   Eve: ����������\n");
		//for (int i = 0; i < length; i++)
		//	printf("%d ", sB[i]);
		//printf("\n");

		printf("   Eve: ����������\n");
		for (int i = 0; i < length; i++){
			if (this->mB[i] == 0)
				printf("D ");
			else
				printf("R ");
		}
		printf("\n\n");
	}

}

Bob::~Bob()
{
	delete[] sB;
	delete[] mB;
	sB = NULL;
	mB = NULL;
}

void Bob::bb84recvFromAlice(Alice& a)
{
	printf("   Bob: �յ� ��������Ϣ\n");
	printf("   Bob: ���ڴ��� ��������Ϣ\n");
	printf("   Bob: -----------------------------------\n");
	printf("   Bob: ��Ӧ����ԿΪ\n");

	int sizeOfKey = 0;												// ��Կ����

	for (int i = 0; i < this->length; i++){
		if (this->rB[i] == 1)
			sizeOfKey++;
	}

	this->kB = new int[sizeOfKey];

	int i = 0;
	int j = 0;
	while (i < this->length){
		if (this->rB[i] == 1){
			this->kB[j] = this->sB[i];
			j++;
		}
		i++;
	}

	for (int i = 0; i < sizeOfKey; i++){
		printf("%2d ", kB[i]);
	}

	printf("\n");
}

void Bob::bb84sendToAlice(Alice& a)
{
	printf("   Bob: ���ڴ��� ����������\n");
	printf("   Bob: -----------------------------------\n");
	printf("   Bob: ������� �ȴ�Alice����\n");

	a.bb84recvFromBob(*this, false);

}

bool Bob::bb84checkout(Alice& a)
{
	printf("\n   Bob: ��Կ����");
	printf("\n   Bob: ���ڴ��� ������Կ");
	printf("\n   Bob: -----------------------------------\n");
	
	if (a.bb84checkout(*this))
	{
		printf("��Կƥ��  ��Eve����\n");
		return true;
	}
	else
		printf("��Կ��ƥ��  ��Eve����\n");
	return false;
}

void Bob::bb84wiretap(Alice&a, Bob& b)
{

	printf("   Eve: �������� ����������\n");
	printf("   Eve: -----------------------------------\n");

	a.bb84recvFromBob(*this, true);

	printf("\n   Eve: ���ĺ�Ķ���������Ϊ:\n");
	for (int i = 0; i < length; i++)
		printf("%d ", sB[i]);
	printf("\n\n");


	/*
		��Eve ������
		�� Eve �ı�� ���������� ���ظ� Bob
		��Bob ���� ���ı���Ĵ��� ����
	*/

	for (int i = 0; i < b.length; i++)
	{
		if (b.mB[i] == this->mB[i])
			b.sB[i] = this->sB[i];
		else
			b.sB[i] = rand() % 2;

	}
}

void Bob::b92sendToAlice(Alice&a)
{
	printf("   Bob: ���ڴ��� ����������\n");
	printf("   Bob: -----------------------------------\n");
	printf("   Bob: ������� �ȴ�Alice����\n");
	a.b92recvFromBob(*this, false);
}

void Bob::b92recvFromAlice(Alice&a)
{
	printf("   Bob: �յ� ��������Ϣ\n");
	printf("   Bob: ���ڴ��� ��������Ϣ\n");
	printf("   Bob: -----------------------------------\n");


	printf("   Bob: �յ���ƫ��̬����Ϊ\n");

	for (int i = 0; i < this->length; i++)
	{
		printf("%2d", this->sB[i]);

	}

	printf("\n   Bob: ��Ӧ����ԿΪ\n");

	int sizeOfKey = 0;												// ��Կ����

	for (int i = 0; i < this->length; i++){
		if (this->rB[i] == 1)
			sizeOfKey++;
	}

	this->kB = new int[sizeOfKey];

	int i = 0;
	int j = 0;
	while (i < this->length){
		if (this->rB[i] == 1){
			this->kB[j] = this->sB[i];
			j++;
		}
		i++;
	}

	for (int i = 0; i < sizeOfKey; i++){
		printf("%2d ", kB[i]);
	}

	printf("\n");
}

void Bob::b92wiretap(Alice&a, Bob& b)
{


	printf("   Eve: �������� ����������\n");
	printf("   Eve: -----------------------------------");

	a.b92recvFromBob(*this, true);

	printf("\n   Eve: ���ĺ�Ķ���������Ϊ:\n");
	for (int i = 0; i < length; i++)
		printf("%2d", sB[i]);
	printf("\n\n");



	/*
	��Eve ������
	�� Eve �ı�� ���������� ���ظ� Bob
	��Bob ���� ���ı���Ĵ��� ����
	*/



	for (int i = 0; i < this->length; i++){
		if (this->sB[i] == 0){
			if (b.mB[i] == 0){
				b.sB[i] = 0;
				b.rB[i] = 0;
			}
			else
			{
				b.sB[i] = rand() % 2;
				if (b.sB[i] == 0){
					b.rB[i] = 1;
					this->rB[i] = 1;
				}
				else{
					b.rB[i] = 0;
					this->rB[i] = 0;
				}
			}
		}

		if (this->sB[i] == 1){
			if (b.mB[i] == 1){
				b.sB[i] = 1;
				b.rB[i] = 0;
			}
			else
			{
				b.sB[i] = rand() % 2;
				if (b.sB[i] == 0){
					b.rB[i] = 0;
					this->rB[i] = 0;
				}
				else{
					b.rB[i] = 1;
					this->rB[i] = 1;
				}
			}
		}
	}


}

bool Bob::b92checkout(Alice& a)
{
	printf("\n   Bob: ��Կ����");
	printf("\n   Bob: ���ڴ��� ������Կ");
	printf("\n   Bob: -----------------------------------\n");

	if (a.b92checkout(*this))
	{
		printf("��Կƥ��  ��Eve����\n");
		return true;
	}
	else
		printf("��Կ��ƥ��  ��Eve����\n");
	return false;
}


void Bob::draw(bool isWiretap)
{
	myGraph demo = myGraph();
	if (isWiretap)											// ����
	{
		demo.setFont(28);
		demo.drawText(490, 500, L"Eve");
		demo.setFont(16);

		setlinestyle(PS_SOLID, 3);							// �������Ϊ3
		rectangle(398, 488, 792, 652);						// Bob ���ݿ�
		setlinestyle(PS_SOLID, 1);

		demo.drawText(410, 540, L"����");
		demo.drawText(410, 570, L"������");
		demo.drawText(410, 604, L"���");
		demo.drawText(410, 638, L"��Կ");

		for (int i = 0; i < this->length; i++)							// ��ʾ������ mB����
		{
			Sleep(60);
			if (mB[i] == 0)
			{
				demo.drawD(470 + i * 20, 540);
			}
			else
			{
				demo.drawR(470 + i * 20, 540);
			}
		}
	}
	else
	{
		demo.setFont(28);
		demo.drawText(880, 100, L"Bob");
		demo.setFont(16);

		setlinestyle(PS_SOLID, 3);							// �������Ϊ3
		rectangle(788, 88, 1182, 252);						// Bob ���ݿ�
		setlinestyle(PS_SOLID, 1);

		demo.drawText(800, 140, L"����");
		demo.drawText(800, 170, L"������");
		demo.drawText(800, 204, L"���");
		demo.drawText(800, 238, L"��Կ");

		for (int i = 0; i < this->length; i++)							// ��ʾ������ mB����
		{
			Sleep(60);
			if (mB[i] == 0)
			{
				demo.drawD(860 + i * 20, 140);
			}
			else
			{
				demo.drawR(860 + i * 20, 140);
			}
		}
	}
}

void Bob::drawResult()
{
	myGraph demo = myGraph();
	for (int i = 0; i < this->length; i++)
	{
		Sleep(60);
		if (this->mB[i] == 0)
		{
			if (this->rB[i] == 1)
				setcolor(RED);
			demo.draw1(860 + i * 20, 170, sB[i]);
			setcolor(WHITE);
		}
		else
		{
			if (this->rB[i] == 1)
				setcolor(RED);
			demo.draw2(860 + i * 20, 170, sB[i]);
				setcolor(WHITE);
		}
	}


	int num = 0;

	for (int i = 0; i < this->length; i++)
	{
		if (this->rB[i] == 1)
		{
			Sleep(30);
			demo.drawText(860 + i * 20, 235, this->kB[num]);
			num++;
		}
	}


}

void Bob::drawSend(bool isBB84)
{
	myGraph demo = myGraph();



	demo.drawText(550, 140, L"����ͨ��");

	if (isBB84)
	{
		for (int i = 0; i < this->length; i++)
			demo.drawText(510 + i * 10, 165, this->mB[i]);
	}
	else
	{
		for (int i = 0; i < this->length; i++)
		{
			int n = 0;
			for (int i = 0; i < this->length; i++)
			{
				if (this->rB[i] == 1)
				{
					TCHAR str[10];
					wsprintf(str, L"%2d,", i + 1);
					outtextxy(495 + n * 20, 120, str);
					n++;
				}
			}
		}
	}

	setcolor(GREEN);

	for (int i = 0; i < 39; i++){
		line(780-i*10, 140, 785-i*10, 140);
		Sleep(30);
	}
	line(400, 140, 412, 147);
	line(400, 140, 412, 133);


	setcolor(WHITE);
}

void Bob::drawSend1()
{
	myGraph demo = myGraph();

	clearrectangle(405, 120, 780, 150);

	setcolor(GREEN);
	demo.drawText(520, 160, L"���ڴ��Ͳ�����Կ");

	for (int i = 0; i < 39; i++){
		line(780 - i * 10, 140, 785 - i * 10, 140);
		Sleep(30);
	}
	line(400, 140, 412, 147);
	line(400, 140, 412, 133);
	setcolor(WHITE);
}


void Bob::drawRecev(bool isWiretap)
{
	myGraph demo = myGraph();

	if (isWiretap)
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			if (this->mB[i] == 0)
			{
				demo.draw1(470 + i * 20, 570, sB[i]);
			}
			else
			{
				demo.draw2(470 + i * 20, 570, sB[i]);
			}
		}

		setcolor(YELLOW);
		for (int i = 0; i < 13; i++){
			line(600, 490 - i * 10, 600, 485 - i * 10);
			Sleep(30);
		}

		for (int i = 0; i < 14; i++){

			line(i * 10 + 600, 365, i * 10 + 605, 365);
			Sleep(30);
		}
		for (int i = 0; i < 26; i++){
			line(740, 365 - i * 10, 740, 360 - i * 10);
			Sleep(30);
		}
		for (int i = 0; i < 5; i++){
			line(i * 10 + 740, 110, i * 10 + 745, 110);
			Sleep(30);
		}
		setcolor(WHITE);











		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			if (this->mB[i] == 0)
				demo.draw1(860 + i * 20, 110, sB[i]);
			else
				demo.draw2(860 + i * 20, 110, sB[i]);
		}
	}
	else
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			if (this->mB[i] == 0)
			{
				demo.draw1(860 + i * 20, 170, sB[i]);
			}
			else
			{
				demo.draw2(860 + i * 20, 170, sB[i]);
			}
		}
	}
}