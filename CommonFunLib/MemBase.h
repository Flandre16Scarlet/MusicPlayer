#pragma once
//˫�����ͼ���࣬��Ҫ��GDI����ĳ�ʼ���Լ�����
/*class __declspec(dllexport)*/
EXPORT_CLASS CMemBase
{
public:
	CMemBase(void);
	virtual ~CMemBase(void);
protected:
	HDC m_hMemDC;
	HBITMAP m_hMemBitmap;
};
