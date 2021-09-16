#pragma once


class Alice;
class myGraph;
class myFrame;

class Bob								// ���շ��� ����������
{
private:
	int length;							// ����λ��
	int *sB;							// ���ڽ��� Alice ���͵Ķ���������
	int *mB;							// ��������� ����������
	int *rB;							// ��¼ ƥ��ɹ��Ĳ����� ��λ��
	int *kB;							// ��Կ����
public:
	 Bob(bool isWiertap);				// isWiretap Ϊ �� ��Ϊ������
	 Bob(int len,bool isWiretap);
	~Bob();
public:								// BB84Э�鲿��
	void bb84recvFromAlice(Alice& a);		// ���� ƥ��ɹ��� ��������Ϣ
	void bb84sendToAlice(Alice& a);			// ���� ������
	bool bb84checkout(Alice& a);			// �ж��Ƿ��м������� ���� �� ���������� ͨ�Ű�ȫ
	void bb84wiretap(Alice& a, Bob& b);		// ������ ���� �����ߵĶ��������� ��������������� ���ݸ�������
public:								// B92Э�鲿��
	void b92recvFromAlice(Alice& a);		// ����
	void b92sendToAlice(Alice& a);			// ���� ������
	bool b92checkout(Alice& a);		// �ж��Ƿ��������
	void b92wiretap(Alice&a, Bob& b);		// b92Э�� ����
public:
	void draw(bool isWiretap);				// Eve �� Bob λ�ò�ͬ
	void drawRecev(bool isWiretap);
	void drawResult();
	void drawSend(bool isBB84);
	void drawSend1();
public:
	friend class Alice;						// ��Ԫ��
};

