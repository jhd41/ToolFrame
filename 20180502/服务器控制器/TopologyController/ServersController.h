
// ServersController.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CServersControllerApp:
// �йش����ʵ�֣������ ServersController.cpp
//

class CServersControllerApp : public CWinApp
{
public:
	CServersControllerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CServersControllerApp theApp;