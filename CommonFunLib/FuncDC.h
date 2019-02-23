#pragma once
#include "ErrorLog.h"
typedef struct _SAVEDATA
{
	HBITMAP hBitmap;
	const char* pSavepath;
}SAVEDATA;
EXPORT_CLASS CFuncDC:public CErrorLog
{
public:
	CFuncDC(void);
	~CFuncDC(void);
private:
	static HDC m_hMemDC;
	static HBITMAP m_hMemBitmap;
	//������Ϣ
	static char* m_pError;
protected:
	//************************************
	// Qualifier:�ͷ�GDI����
	//************************************
	static void Release();
	//************************************
	// Qualifier:���ó�����Ϣ
	//************************************
	static void SetError(const char* pError);
public:
	/******************************************************************/
	/*                          �ⲿ�ӿڲ���                          */
	/******************************************************************/
	//************************************
	// Qualifier: ��ȡĿ��DC�ı���λͼ
	//************************************
	static HBITMAP GetBackBitmap(IN HDC hDC);
	static HBITMAP GetBackBitmap(IN HDC hDC,IN const int nWidth,IN const int nHeight);
	//************************************
	//���汳��λͼ��ָ���ļ�
	static bool SaveBackBitmap(IN HDC hDC,IN const char* pSavePath);
	static bool SaveBackBitmap(IN HDC hDC,IN const int nWidth,IN const int nHeight,IN const char* pSavePath);
	//************************************
	// Qualifier: ����λͼ�����ָ��·���ļ���
	//************************************
	static bool SaveHBitmap(IN HBITMAP hBitmap,IN const char* pSavePath);
	static bool SaveHBitmap(IN HBITMAP hBitmap,IN const wchar_t* pSavePath);
	//************************************
	// Qualifier:����λͼ���
	//************************************
	static HBITMAP CopyHBitmap(IN HBITMAP hBitmap);
	//��ȡλͼ��һ�������λͼ���
	static HBITMAP CutHBitmap(IN HBITMAP hBitmap);
	//************************************
	// Qualifier:��ȡ������Ϣ
	//************************************
	static char* GetError();
};
