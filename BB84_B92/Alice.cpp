#include "Alice.h"
#include "Bob.h"
#include "myGraph.h"
#include <stdio.h>
#include <stdlib.h>



int sizeOfKey = 0;


Alice::Alice(bool isBB84)
{
	if (isBB84)
	{
		this->length = 16;						// Ĭ�ϳ���Ϊ 10
		this->sA = new int[16];					// ��̬���� ����Ϊ10 �Ķ���������
		this->mA = new int[16];					// ���ͻ�����
		this->rA = new int[16];					// �洢ƥ����Ϣ������


		for (int i = 0; i < 16; i++){
			this->sA[i] = rand() % 2;			// ������� ����������
			this->mA[i] = rand() % 2;			// ������� �������  0��ʾ D�����룬1��ʾ R������
			this->rA[i] = 0;					// ����
		}

		printf("   Alice: ����������\n");
		for (int i = 0; i < 16; i++)
			printf("%2d", sA[i]);
		printf("\n");

		printf("   Alice: ���ͻ�����\n");
		for (int i = 0; i < 16; i++){
			printf("%2d", mA[i]);
		}
		printf("\n\n");
	}
	else
	{
		this->length = 16;						// Ĭ�ϳ���Ϊ 10
		this->sA = new int[16];					// ��̬���� ����Ϊ10 �Ķ���������
		this->rA = new int[16];					// �洢ƥ����Ϣ������

		for (int i = 0; i < 16; i++){
			this->sA[i] = rand() % 2;			// ������� ����������
			this->rA[i] = 0;					// ����
		}

		printf("   Alice: ƫ��̬����\n");
		for (int i = 0; i < 16; i++)
			printf("%2d", sA[i]);
		printf("\n\n");
	}

}

Alice::Alice(int len,bool isBB84)
{
	if(isBB84)
	{
		this->length = len;
		this->sA = new int[this->length];
		this->mA = new int[this->length];
		this->rA = new int[this->length];

		for (int i = 0; i < this->length; i++){
			this->sA[i] = rand() % 2;			// ������� ����������
			this->mA[i] = rand() % 2;			// ������� ���ͻ�����  0��ʾ D�����룬1��ʾ R������
			this->rA[i] = 0;					// ����
		}

		printf("   Alice: ����������\n");
		for (int i = 0; i < length; i++)
			printf(" %d ", sA[i]);
		printf("\n");

		printf("   Alice: ���ͻ�����\n");
		for (int i = 0; i < length; i++){
			if (this->mA[i] == 0)
				printf("D ");
			else
				printf("R ");
		}
		printf("\n\n");

	}
	else
	{
		this->length = len;
		this->sA = new int[this->length];
		this->rA = new int[this->length];

		for (int i = 0; i < this->length; i++){
			this->sA[i] = rand() % 2;			// ������� ����������
			this->rA[i] = 0;					// ����
		}

		printf("   Alice: ƫ��̬����\n");
		for (int i = 0; i < length; i++)
			printf("%d ", sA[i]);
		printf("\n\n");
	}
}

Alice::~Alice()
{
	delete[] sA;
	delete[] mA;
	delete[] rA;
	delete[] kA;
	sA = NULL;
	mA = NULL;
	rA = NULL;
	kA = NULL;
}

void Alice::bb84sendToBob(Bob& b)
{



}

void Alice::bb84recvFromBob(Bob& b, bool isWiretap)
{
	if (!isWiretap)
	{
		printf("\n   Alice: �ѽ��յ�������: \n");
		printf("   Alice: -----------------------------------\n");


		printf("   Alice: �ɹ�ƥ��Ĳ�����Ϊ:\n");
		for (int i = 0; i < this->length; i++){
			if (b.mB[i] == this->mA[i]){				// �������������ƥ�� ���֪Bob�˸�λ�ò�������ȷ
				b.sB[i] = this->sA[i];
				b.rB[i] = 1;

				rA[i] = 1;
				sizeOfKey++;

				printf("%2d ", i);
			}
			else{
				b.sB[i] = rand() % 2;					// ��� ���ɴ���Ķ���������
				b.rB[i] = 0;
			}
		}
		printf("\n   Alice: ������ȷ��������Ϣ  ");
		printf("\n   Alice: Alice��Ӧ��� ");

		printf("\n   Alice: ��Bob��Ӧ����ԿΪ:\n");
		this->kA = new int[sizeOfKey]; 
		int i = 0;
		int j = 0;
		while (i < this->length){
			if (this->rA[i] == 1){
				this->kA[j] = this->sA[i];
				j++;
			}
			i++;
		}
		for (int i = 0; i < sizeOfKey; i++){
			printf("%2d ", kA[i]);
		}
		printf("\n\n");

	}
	else{												// ��Eve����
		printf("   Eve: �ɹ�ƥ��Ĳ�����Ϊ:\n");
		for (int i = 0; i < this->length; i++){
			if (b.mB[i] == this->mA[i]){				// �������������ƥ�� ���֪Bob�˸�λ�ò�������ȷ
				b.sB[i] = this->sA[i];

				printf("%2d ", i);
			}
			else{
				b.sB[i] = rand() % 2;					// ��� ���ɴ���Ķ���������
				b.rB[i] = 0;
			}
		}

	}

}

bool Alice::bb84checkout(Bob& b)
{

	printf("\n   Alice: �ɹ����� ������Կ����\n");
	printf("   Alice: ��Կ������\n");
	printf("   Alice: -----------------------------------\n");
	for (int i = 0; i < sizeOfKey; i++){
		if (b.kB[i] != this->kA[i])
			return false;								// ��Կ�޷�ƥ�� ����Eve
	}
	//for (int i = 0; i < this->length; i++)
	//{
	//	if (b.sB[i] != this->sA[i])						// ��ʹ���� ��Կƥ�� ҲҪȷ�϶����������Ƿ���Ϊ�Ķ�
	//		return false;								// �����ͬ �����Eve
	//}

	return true;										// ��Կƥ�� ��Eve
}

void Alice::b92recvFromBob(Bob& b, bool isWiretap)
{

/* 
	Ԥ�ȹ涨 Alice ��� sA �� 0 ���� "һ"��	  1 ���� "�J"
			 Bob   ��� mB �� 0 ���� D�����룬1 ���� R������
								�� "��",		�� "�w"

	�� ��� sA = 0; mB = 0; �������� ����					"һ"  ��Ӧ "��"
			sA = 0; mB = 1;		�� sB = rand()%2			"һ"  ��Ӧ "�w"
				      if sB = 0;	�� ����						"һ"  ��Ӧ "�K"
					  if sB = 1;	�� ����						"һ"  ��Ӧ "�J"

	   ��� 
			sA = 1; mB = 0;		�� sB = rand()%2			"�J"  ��Ӧ "��"
					  if sB = 0;	�� ����						"�J"  ��Ӧ "һ"
					  if sB = 1;	�� ����						"�J"  ��Ӧ "|"
			sA = 1; mB = 1; �������� ����					"�J"  ��Ӧ "�w"
*/


	if (!isWiretap)
	{
		sizeOfKey = 0;


		printf("\n   Alice: �ѽ��յ�������: \n");
		printf("   Alice: -----------------------------------\n");


		printf("   Alice: �ɹ�ƥ��Ĳ�����Ϊ:\n");
		if (!isWiretap)
		{
			for (int i = 0; i < this->length; i++){
				if (this->sA[i] == 0){
					if (b.mB[i] == 0){
						b.sB[i] = 0;
						b.rB[i] = 0;
						this->rA[i] = 0;
					}
					else
					{
						b.sB[i] = rand() % 2;
						if (b.sB[i] == 0){
							b.rB[i] = 1;
							this->rA[i] = 1;
							printf("%2d ", i);
							sizeOfKey++;
						}
						else{
							b.rB[i] = 0;
							this->rA[i] = 0;
						}
					}
				}

				if (this->sA[i] == 1){
					if (b.mB[i] == 1){
						b.sB[i] = 1;
						b.rB[i] = 0;
						this->rA[i] = 0;
					}
					else
					{
						b.sB[i] = rand() % 2;
						if (b.sB[i] == 0){
							b.rB[i] = 0;
							this->rA[i] = 0;
						}
						else{
							b.rB[i] = 1;
							this->rA[i] = 1;
							sizeOfKey++;
							printf("%2d ", i);
						}
					}
				}
			}

			if (this->kA){
				delete[] kA;
				kA = NULL;
			}

			printf("\n   Alice: ��Bob��Ӧ����ԿΪ:\n");
			this->kA = new int[sizeOfKey];
			int i = 0;
			int j = 0;
			while (i < this->length){
				if (this->rA[i] == 1){
					this->kA[j] = this->sA[i];
					j++;
				}
				i++;
			}
			for (int i = 0; i < sizeOfKey; i++){
				printf("%2d ", kA[i]);
			}
			printf("\n\n");
		}
	}

	else
	{
		for (int i = 0; i < this->length; i++){
			if (this->sA[i] == 0){
				if (b.mB[i] == 0){
					b.sB[i] = 0;
					b.rB[i] = 0;
				}
				else
				{
					b.sB[i] = rand() % 2;
					if (b.sB[i] == 0){
						b.rB[i] = 1;
					}
					else{
						b.rB[i] = 0;
					}
				}
			}

			if (this->sA[i] == 1){
				if (b.mB[i] == 1){
					b.sB[i] = 1;
					b.rB[i] = 0;
				}
				else
				{
					b.sB[i] = rand() % 2;
					if (b.sB[i] == 0){
						b.rB[i] = 0;
					}
					else{
						b.rB[i] = 1;
					}
				}
			}
		}
	}
}

bool Alice::b92checkout(Bob& b)
{

	printf("\n   Alice: �ɹ����� ������Կ����\n");
	printf("   Alice: ��Կ������\n");
	printf("   Alice: -----------------------------------\n");
	for (int i = 0; i < sizeOfKey; i++){
		if (b.kB[i] != this->kA[i])
			return false;								// ��Կ�޷�ƥ�� ����Eve
	}

	return true;										// ��Կƥ�� ��Eve
}


void Alice::draw(bool isBB84)
{
	myGraph demo = myGraph();

	demo.setFont(28);								// ����ߴ�28
	demo.drawText(100, 100, L"Alice");				// ��ʾ Alice
	demo.setFont(16);								

	setlinestyle(PS_SOLID, 3);						// �������Ϊ3
	rectangle(8, 88, 402, 252);						// Alice ���ݿ�
	setlinestyle(PS_SOLID, 1);

	demo.drawText(20, 145, L"������");				// ����������
	for (int i = 0; i < this->length; i++)
	{
		Sleep(90);
		demo.drawText(80 + i * 20, 145, this->sA[i]);
	}

	if (isBB84)
	{
		demo.drawText(20, 170, L"���ͻ�");
		demo.drawText(20, 204, L"����");
		demo.drawText(20, 238, L"��Կ");
		for (int i = 0; i < this->length; i++)
		{
			Sleep(90);
			demo.drawText1(75 + i * 20, 140, this->sA[i],this->mA[i]);
		}
	}	
	else
	{
		demo.drawText(20, 170, L"ƫ��̬");
		demo.drawText(20, 204, L"����");
		demo.drawText(20, 238, L"��Կ");
		for (int i = 0; i < this->length; i++)
		{
			Sleep(90);
			demo.drawB92(75 + i * 20, 140, this->sA[i]);
			demo.drawB92(75 + i * 20, 170, this->sA[i]);
		}
	}
}

void Alice::drawSend(bool isBB84,bool isWiretap)
{
	myGraph demo = myGraph();

	if (isWiretap)
	{
		setcolor(YELLOW);
		for (int i = 0; i < 5; i++){
			line(i * 10 + 400, 170, i * 10 + 405, 170);
			Sleep(30);
		}
		for (int i = 0; i < 20; i++){
			line(445, 170 + i * 10, 445, 175 + i * 10);
			Sleep(30);
		}

		for (int i = 0; i < 14; i++){

			line(i * 10 + 445, 365, i * 10 + 450, 365);
			Sleep(30);
		}

		for (int i = 0; i < 13; i++){
			line(580, 365 + i * 10, 580, 370 + i * 10);
			Sleep(30);
		}

		setcolor(WHITE);
	}

	else
	{

		setcolor(YELLOW);
		for (int i = 0; i < 5; i++){
			line(i * 10 + 400, 170, i * 10 + 405, 170);
			Sleep(30);
		}
		for (int i = 0; i < 20; i++){
			line(445, 170 + i * 10, 445, 175 + i * 10);
			Sleep(30);
		}
		for (int i = 0; i < 30; i++){

			line(i * 10 + 445, 365, i * 10 + 450, 365);
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
	}

	demo.drawText(550, 380, L"����ͨ��");
	if (isBB84)
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			if (isBB84)
			{
				if (this->mA[i] == 0)
					demo.draw1(445 + i * 20, 380, sA[i]);
				else
					demo.draw2(445 + i * 20, 380, sA[i]);
			}
			else
			{
				demo.drawB92(445 + i * 20, 380, sA[i]);
			}
		}
	}
	else
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			demo.drawB92(445 + i * 20, 380, sA[i]);
		}
	}

}

void Alice::drawQuantum(bool isBB84,bool isWiretap)
{
	myGraph demo = myGraph();

	if (isWiretap)
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);
			if (isBB84)
			{
				if (this->mA[i] == 0)
					demo.draw1(470 + i * 20, 510, sA[i]);
				else
					demo.draw2(470 + i * 20, 510, sA[i]);
			}
			else
			{
				demo.drawB92(470 + i * 20, 510, sA[i]);
			}
		}
	}

	else
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(60);

			if (isBB84)
			{
				if (this->mA[i] == 0)
					demo.draw1(860 + i * 20, 110, sA[i]);
				else
					demo.draw2(860 + i * 20, 110, sA[i]);
			}
			else
				demo.drawB92(860 + i * 20, 110, sA[i]);

		}
	}
}

void Alice::drawCheckout1(bool isBB84, Bob& b)
{
	myGraph demo = myGraph();

	clearrectangle(65, 130, length * 20 + 70, 150);
	if (isBB84)
	{
		for (int i = 0; i < this->length; i++)
		{
			Sleep(90);
			if (this->mA[i] == 0){
				if (this->rA[i] == 1)
					setcolor(RED);
				demo.drawD(75 + i * 20, 140);
				setcolor(WHITE);
			}
			if (this->mA[i] == 1){
				if (this->rA[i] == 1)
					setcolor(RED);
				demo.drawR(75 + i * 20, 140);
				setcolor(WHITE);
			}
		}
	}

	else
	{
		for (int i = 0; i < this->length; i++)
		{
			if (this->sA[i] == 0){
				if (b.rB[i] == 1)
					setcolor(RED);
				demo.drawB92(75 + i * 20, 140,this->sA[i]);
				setcolor(WHITE);
			}
			if (this->sA[i] == 1){
				if (b.rB[i] == 1)
					setcolor(RED);
				demo.drawB92(75 + i * 20, 140,this->sA[i]);
				setcolor(WHITE);
			}
		}
	}

	int num = 0;
	for (int i = 0; i < this->length; i++)
	{
		if (b.rB[i] == 1)
		{
			Sleep(30);
			demo.drawText(80 + i * 20, 235, this->kA[num]);
			num++;
		}
	}
}

void Alice::drawSend1()
{
	myGraph demo = myGraph();

	clearrectangle(405, 120, 780, 150);

	setcolor(GREEN);

	for (int i = 0; i < 39; i++){
		line(405 + i * 10, 140, 410 + i * 10, 140);
		Sleep(30);
	}
	line(785, 140, 773, 147);
	line(785, 140, 773, 133);


	int n = 0;
	for (int i = 0; i < this->length; i++)
	{
		if (this->rA[i] == 1)
		{
			TCHAR str[10];
			wsprintf(str, L"%2d,", i + 1);
			outtextxy(495 + n * 20, 120, str);
			n++;
		}
	}
	setcolor(WHITE);

}