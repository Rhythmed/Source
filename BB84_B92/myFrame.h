#pragma once

class Alice;
class Bob;


class myFrame
{
public:
	 myFrame();
	~myFrame();
public:
	void mainInterface();
	void mainButton();
	void buttonRespond(bool& isBB84,bool& isWireta);
	void BB84Loop(Alice& a,Bob& b,Bob& e,bool isWiretap);									// BB84Э��ѭ��
	void B92Loop(Alice& a, Bob& b, Bob& e, bool isWiretap);									// B92Э��ѭ��
};

