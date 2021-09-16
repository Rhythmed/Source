#pragma once



class Bob;
class myGraph;
class myFrame;

class Alice								// Alice 为发送方
{
private:
	int length;							// 序列位数
	int *sA;							// 随机产生的 二进制序列
	int *mA;							// 随机产生的 发送基序列
	int *rA;							// 记录 匹配成功的测量基 的位置
	int *kA;							// 密钥序列

public:
	 Alice(bool isBB84);				// 判断使用 何种协议
	 Alice(int len,bool isBB84);		
	~Alice();
public:
	void bb84sendToBob(Bob& b);						// 
	void bb84recvFromBob(Bob& b, bool isWiretap);	// 接收 测量基序列 并将正确的测量基 告知接收方
	bool bb84checkout(Bob& b);						// 检验 接收方 传送的部分密钥 如果匹配则返回 true
public:
	void b92recvFromBob(Bob& b, bool isWiretap);	// 接收 Bob 发送的 测量基序列 并 选择保留或抛弃的二进制序列
	bool b92checkout(Bob& b);						// 检验


public:
	void draw(bool isBB84);									// 绘图函数；
	void drawSend(bool isBB84,bool isWiretap);					// 显示量子信道轨迹
	void drawSend1();								// 反馈匹配成功的测量基序号
	void drawQuantum(bool isBB84,bool isWiretap);								// Bob方接收显示量子信息
	void drawCheckout1(bool isBB84, Bob& b);							// 收到测量基 检验是否匹配 匹配显示红色并打印密钥
};

