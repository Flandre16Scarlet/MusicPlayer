#pragma once
#include "stdafx.h"
#define ID_TOOLTIP 110
// CSliderButton

class __declspec(dllexport) CSliderButton : public CButton,  public CErrorLog,public CMemBase//,CChangeBackBase
{
	DECLARE_DYNAMIC(CSliderButton)

public:
	CSliderButton();
	virtual ~CSliderButton();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

protected:
	DECLARE_MESSAGE_MAP()
protected:
	virtual void PreSubclassWindow();
	CToolTipCtrl m_toolTip;
	//�ͻ������δ�С
	CRect m_rcClient;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private://��Ա����
	// �����ȵ���ɫ
	COLORREF m_bkColor;
	//��ɽ��ȵ���ɫ
	COLORREF m_overColor;
	//��ǰ���ȶ�Ӧ�ڿؼ��ͻ�����λ��
	int m_nCurrentPos;
	//��ǰ����xλ��
	int m_nxPos;
	//���õĽ������ֵ
	int m_nMaxPos;
	//����λͼ����DC���
	HDC m_hSliderDC;
	//����λͼ
	HBITMAP m_hSliderBitmap;
	//������ˢ
	HBRUSH m_hBkBrush;
	int m_nSliderWidth;
	//����洢��Ϣ������
	UINT m_uMessage;
	WPARAM	m_wParam;
public://�ⲿ�ӿ�
	// ����/��ȡ������ɫ
	void SetBkColor(COLORREF color){m_bkColor=color;ReleaseGDIHandle((HANDLE*)&m_hBkBrush);m_hBkBrush=CreateSolidBrush(m_bkColor);}
	COLORREF GetBkColor()const {return m_bkColor;}
	//����/��ȡ��ɽ��ȵ���ɫ
	void SetFinishColor(COLORREF color){m_overColor=color;}
	COLORREF GetFinishColor()const{return m_overColor;}
	//����/��ȡ��ǰ����ֵ
	int GetCurPos()const {return m_nCurrentPos;}
	void SetCurPos(const int nPos)
	{
		m_nCurrentPos=nPos>m_nMaxPos?m_nMaxPos:nPos;
		m_nxPos=nPos/(float)m_nMaxPos*m_rcClient.Width();
		SendOwerMessage();
		Invalidate();
	}
	BOOL MaxTest()const {return m_nCurrentPos==m_nMaxPos;}
	BOOL MinTest()const {return m_nCurrentPos==0;}
	void SetToolTipText(const CString& strText){m_toolTip.UpdateTipText(strText,this,ID_TOOLTIP);}
	//��ȡ�ؼ����
	int GetWidth()const {return m_rcClient.Width();}
	//��ʼ���ؼ����������
	void InitCtrl(UINT uBitmapID,const CString& strTipText,int nMaxPos=100,UINT uMessage=0,WPARAM wParam=0);
	//���ݱ��������ý���
	void SetRatio(float fRatio){m_nCurrentPos=int(fRatio*m_nMaxPos);m_nxPos=int(fRatio*GetWidth());}
	float GetRatio()const {return m_nCurrentPos/(float)m_nMaxPos;}
	//�򸸴��ڵĸ����ڷ�����Ϣ
	inline BOOL SendOwerMessage();
};


