
// Traffic_Light.h : Traffic_Light Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CTraffic_LightApp:
// �йش����ʵ�֣������ Traffic_Light.cpp
//

class CTraffic_LightApp : public CWinApp
{
public:
	CTraffic_LightApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTraffic_LightApp theApp;
