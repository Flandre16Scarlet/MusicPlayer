// OwerBox.h : OwerBox DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// COwerBoxApp
// �йش���ʵ�ֵ���Ϣ������� OwerBox.cpp
//

class COwerBoxApp : public CWinApp
{
public:
	COwerBoxApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
private:
	Gdiplus::GdiplusStartupInput m_start;
	ULONG_PTR m_ptr;
};
