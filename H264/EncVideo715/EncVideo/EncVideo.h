
// EncVideo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CEncVideoApp:
// �йش����ʵ�֣������ EncVideo.cpp
//

class CEncVideoApp : public CWinApp
{
public:
	CEncVideoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CEncVideoApp theApp;