# pragma once
#include "..\CommonDefine\StandarC++.h"
#include <assert.h>

//�ͷ�DC���
void ReleaseDCHandle(HDC*);

//�ͷ�λͼ���
void ReleaseGDIHandle(HANDLE*);

//��ȡϵͳʱ����ַ��� ****-**-** **_**_**��ʽ
std::wstring FormatSystemTimeW();

//��ȡӦ�ó���·��
std::wstring GetAppPathW();
std::string  GetAppPathA();

//ָ����ɫ���DC���ξ���
bool FillDCRect(IN HDC hDC,IN LPRECT lpRect,IN COLORREF color);

//��ȡλͼ��ָ������λͼ���
HBITMAP GetBitmapRect(IN HBITMAP hBitmap,IN LPRECT lpRect);

//��ȡDCָ����С�ı���λͼ���
HBITMAP GetDCBackBitmap(IN HDC hDC,IN int nWidth,IN int nHeight);

//����λͼ�����ָ��·��
bool SaveBitmapA(IN HBITMAP hBitmap,IN const char* pSavePath);
bool SaveBitmapW(IN HBITMAP hBitmap,IN const wchar_t* pSavePath);

//����λͼ���
HBITMAP CopyBitmap(IN HBITMAP hBitmap);












#ifdef UNICODE 
	#define GetAppPath GetAppPathW
	#define SaveBitmap SaveBitmapW
#else
	#define GetAppPath GetAppPathA
	#define SaveBitmap SaveBitmapA
#endif
