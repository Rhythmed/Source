#pragma once



class Bob;
class myGraph;
class myFrame;

class Alice								// Alice Ϊ���ͷ�
{
private:
	int length;							// ����λ��
	int *sA;							// ��������� ����������
	int *mA;							// ��������� ���ͻ�����
	int *rA;							// ��¼ ƥ��ɹ��Ĳ����� ��λ��
	int *kA;							// ��Կ����

public:
	 Alice(bool isBB84);				// �ж�ʹ�� ����Э��
	 Alice(int len,bool isBB84);		
	~Alice();
public:
	void bb84sendToBob(Bob& b);						// 
	void bb84recvFromBob(Bob& b, bool isWiretap);	// ���� ���������� ������ȷ�Ĳ����� ��֪���շ�
	bool bb84checkout(Bob& b);						// ���� ���շ� ���͵Ĳ�����Կ ���ƥ���򷵻� true
public:
	void b92recvFromBob(Bob& b, bool isWiretap);	// ���� Bob ���͵� ���������� �� ѡ�����������Ķ���������
	bool b92checkout(Bob& b);						// ����


public:
	void draw(bool isBB84);									// ��ͼ������
	void drawSend(bool isBB84,bool isWiretap);					// ��ʾ�����ŵ��켣
	void drawSend1();								// ����ƥ��ɹ��Ĳ��������
	void drawQuantum(bool isBB84,bool isWiretap);								// Bob��������ʾ������Ϣ
	void drawCheckout1(bool isBB84, Bob& b);							// �յ������� �����Ƿ�ƥ�� ƥ����ʾ��ɫ����ӡ��Կ
};

