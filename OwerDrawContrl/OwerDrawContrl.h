// OwerDrawContrl.h : OwerDrawContrl DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COwerDrawContrlApp
// �йش���ʵ�ֵ���Ϣ������� OwerDrawContrl.cpp
//

class COwerDrawContrlApp : public CWinApp
{
public:
	COwerDrawContrlApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
