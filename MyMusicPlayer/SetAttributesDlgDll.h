// SetAttributesDlgDll.h : SetAttributesDlgDll DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSetAttributesDlgDllApp
// �йش���ʵ�ֵ���Ϣ������� SetAttributesDlgDll.cpp
//

class CSetAttributesDlgDllApp : public CWinApp
{
public:
	CSetAttributesDlgDllApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
