#pragma once

EXPORT_CLASS CChangeBackBase
{
public:
	CChangeBackBase(void);
	~CChangeBackBase(void);
	//�����ӿ�
	virtual void ChangeBack()=0;
protected:
	//����
	HDC m_hBackDC;
	HBITMAP m_hBackBitmap;
	BOOL m_bChangeBack;
};
