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
	void BB84Loop(Alice& a,Bob& b,Bob& e,bool isWiretap);									// BB84协议循环
	void B92Loop(Alice& a, Bob& b, Bob& e, bool isWiretap);									// B92协议循环
};

