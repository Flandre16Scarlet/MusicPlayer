// LyricsModule.h : LyricsModule DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "LyricsDlg.h"

// CLyricsModuleApp
// �йش���ʵ�ֵ���Ϣ������� LyricsModule.cpp
//

class CLyricsModuleApp : public CWinApp
{
public:
	CLyricsModuleApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};
