#pragma once


// CDrawStatic

class CDrawStatic : public CStatic
{
	DECLARE_DYNAMIC(CDrawStatic)

public:
	CDrawStatic();
	virtual ~CDrawStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	RECT m_rcClient;//�ͻ�����С
	COLORREF m_colorText;//������ɫ
	CString m_strText;//��ʾ������
	HFONT m_hFont;//�������ֵ�����
	HDC m_hMemDC;//�ڴ����DC
	HBITMAP m_hMemBitmap;//�ڴ����λͼ���
	HDC m_hBackDC;
	HBITMAP m_hBackBitmap;
public:
	//�ı����ֵ���ɫ
	void ChangeTextColor(COLORREF color) { m_colorText=color; }
	CString GetText() const { return m_strText; }
	void SetText(const CString& val) { m_strText = val; Invalidate();}
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


