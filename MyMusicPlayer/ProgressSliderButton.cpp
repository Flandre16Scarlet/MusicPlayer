#include "StdAfx.h"
#include "ProgressSliderButton.h"

CProgressSliderButton::CProgressSliderButton(void)
:m_nTotalSecond(0)
{
}

CProgressSliderButton::~CProgressSliderButton(void)
{
}
BEGIN_MESSAGE_MAP(CProgressSliderButton, CSliderButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CProgressSliderButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strTipText=_T("");
	if(0==m_nTotalSecond)//û�п�ʼ���� 
		strTipText=_T("������������");
	else
	{
		int nCurrentSecond=point.x/(float)m_rcClient.Width()*m_nTotalSecond;
		strTipText.Format(_T("%d:%02d"),nCurrentSecond/60,nCurrentSecond%60);
	}
	SetToolTipText(strTipText);
	//CSliderButton::OnMouseMove(nFlags, point);
}

void CProgressSliderButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(0!=m_nTotalSecond)
	{
		//������Ϣ��֪��������ȵĵ�ǰֵ
		UINT uCurSecond=point.x/(float)m_rcClient.Width()*m_nTotalSecond;
		::SendMessage(::GetParent(m_hWnd),WM_SLIDER_SETPROGRESS,uCurSecond,0);
	}
	CSliderButton::OnLButtonDown(nFlags, point);
}
