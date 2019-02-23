#pragma once

#include "resource.h"
// CTransDlg �Ի���

class CInfoDlg : public CDialog,CMemBase
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
private:
	//������굱ǰλ�õ�RGB��ɫֵ
	int m_rValue;
	int m_gValue;
	int m_bValue;
	//���浱ǰ��������Ĵ�С
	int m_nWidth;
	int m_nHeight;
	CRect m_rcClient;
	HDC m_hBkMemDC;
	//����λͼ���
	HBITMAP m_hBkMemBitmap;
	//����
	HPEN m_hRedPen;
	HPEN m_hBlackPen;
	//����
	HFONT m_hFont;
	//��ˢ
	HBRUSH m_hBrush;
private:
	void DrawText(HDC hDC);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	void DrawBitmap(HDC hDC);
	// �����߽���
	void DrawLine(HDC hDC);
public:
	///////////////////////////////////////////////////����ӿڲ���
	// ����RGB��ɫֵ�ӿ�
	void SetRGBValue(const int r, const int g,const int b);
	// ���ý�ȡ�����С�ӿ�
	void SetRectValue(const int nWidth, const int nHeight);
	// ���õ�ǰ�����������λͼ���
	void SetBitmap(HBITMAP hBmp);
};
