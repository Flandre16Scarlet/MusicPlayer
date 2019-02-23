#include "StdAfx.h"
#include "VoiceSliderButton.h"

CVoiceSliderButton::CVoiceSliderButton(void)
{
}

CVoiceSliderButton::~CVoiceSliderButton(void)
{
}
BEGIN_MESSAGE_MAP(CVoiceSliderButton, CSliderButton)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CVoiceSliderButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CString strTipText=_T("");
	int nVoice=(int)(point.x/(float)m_rcClient.Width()*100)+10;
	strTipText.Format(_T("������%d%%"),nVoice);
	SetToolTipText(strTipText);
	//CSliderButton::OnMouseMove(nFlags, point);
}

void CVoiceSliderButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nCurVoice=point.x/(float)m_rcClient.Width()*100;
	::SendMessage(::GetParent(m_hWnd),WM_SLIDER_SETVOICE,nCurVoice,0);
	CSliderButton::OnLButtonDown(nFlags, point);
}
