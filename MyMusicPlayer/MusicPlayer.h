// MyMusicPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyMusicPlayerApp:
// �йش����ʵ�֣������ MyMusicPlayer.cpp
//

class CMusicPlayerApp : public CWinApp
{
public:
	CMusicPlayerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	// ��������ÿ��ֻһ��������һ��ʵ��
	HANDLE hMutex;
	Gdiplus::GdiplusStartupInput m_GdiplusInput;
	ULONG_PTR m_GdiplusPtr;
public:
	virtual int ExitInstance();
};

extern CMusicPlayerApp theApp;