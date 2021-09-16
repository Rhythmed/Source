#pragma once


class Alice;
class myGraph;
class myFrame;

class Bob								// 接收方类 或者窃听方
{
private:
	int length;							// 序列位数
	int *sB;							// 用于接收 Alice 发送的二进制序列
	int *mB;							// 随机产生的 测量基序列
	int *rB;							// 记录 匹配成功的测量基 的位置
	int *kB;							// 密钥序列
public:
	 Bob(bool isWiertap);				// isWiretap 为 真 则为监听方
	 Bob(int len,bool isWiretap);
	~Bob();
public:								// BB84协议部分
	void bb84recvFromAlice(Alice& a);		// 接收 匹配成功的 测量基信息
	void bb84sendToAlice(Alice& a);			// 发送 测量基
	bool bb84checkout(Alice& a);			// 判断是否有监听存在 返回 真 则无窃听者 通信安全
	void bb84wiretap(Alice& a, Bob& b);		// 窃听者 窃听 发送者的二进制序列 并将窃听后的序列 传递给接收者
public:								// B92协议部分
	void b92recvFromAlice(Alice& a);		// 接收
	void b92sendToAlice(Alice& a);			// 发送 测量基
	bool b92checkout(Alice& a);		// 判断是否存在窃听
	void b92wiretap(Alice&a, Bob& b);		// b92协议 窃听
public:
	void draw(bool isWiretap);				// Eve 和 Bob 位置不同
	void drawRecev(bool isWiretap);
	void drawResult();
	void drawSend(bool isBB84);
	void drawSend1();
public:
	friend class Alice;						// 友元类
};

