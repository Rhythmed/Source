#include "stdafx.h"





int main(int argc, char** argv){
	srand(time(NULL));
	bool isBB84    = false;								// ѡ�� bb84Э�� �� b92Э��
	bool isWiretap = false;								// ѡ�� �������

	/*******************************************************************************/
	myFrame mainFrame = myFrame();						// ���������
	initgraph(640, 480);

	mainFrame.mainInterface();							// ���������
	mainFrame.mainButton();								// ���水ť����
	mainFrame.buttonRespond(isBB84, isWiretap);			// ��ť��Ӧ

	closegraph();
	/*********************************************************************************/

	initgraph(1200,742);									// ��ʼ��graphics

	TCHAR len[5];											// ���ڴ���û���������г���
	InputBox(len, 5, _T("������������г��ȣ�"), _T("BB84Э��"), _T("16"), 0, 0, 1);
	int n = _wtoi(len);										// TCHAR תΪ int


	if (isBB84)												// bb84Э��
	{
		if (isWiretap)										// �м���
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
	if (!isBB84)													// B92Э��
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


	closegraph();													// �ر�graphics

	return 0;
}