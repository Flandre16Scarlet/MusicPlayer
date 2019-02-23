#pragma once


// CLinkButton
#define TOOLTIP 0x0001

EXPORT_CLASS CLinkButton : public CButton,public CErrorLog,CChangeBackBase,CMemBase
{
	DECLARE_DYNAMIC(CLinkButton)

public:
	CLinkButton();
	virtual ~CLinkButton();

protected:
	DECLARE_MESSAGE_MAP()
private:
	// ��ʾ������
	CString m_strDrawText;
	//��ʾ����
	CToolTipCtrl m_toolTip;
	int m_fontHeight;
	COLORREF m_normalColor;//������ɫ
	COLORREF m_overColor;//������ɫ
	COLORREF m_bkColor;//����ɫ
	COLORREF m_textColor;
	HCURSOR m_hCursor;
	CRect m_rcClient;
	HFONT m_hFont;
protected:
	virtual void PreSubclassWindow();
public:
	void Init(const CString& strDrawText,const CString& strTipText=_T("�������"));
	// ������ʾ���ֵ���ɫ
	void SetTextColor(COLORREF& normal, COLORREF& over);
	afx_msg void OnPaint();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	// ���ñ�����ɫ
	void SetBkColor(COLORREF color);
	//����
	void ChangeBack() { m_bChangeBack=TRUE;Invalidate();}
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	BOOL EnableWindow(BOOL bEnable = TRUE);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


