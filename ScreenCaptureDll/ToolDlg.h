#pragma once
#include "afxwin.h"


// CToolDlg �Ի���

class CToolDlg : public CDialog,CMemBase
{
	DECLARE_DYNAMIC(CToolDlg)

public:
	CToolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CToolDlg();

// �Ի�������
	enum { IDD = IDD_TOOL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void SetSize(const int nWidth,const int nHeight) 
	{ 
		if((m_nWidth!=nWidth)||(m_nHeight!=nHeight))
		{
			m_nWidth=nWidth; m_nHeight=nHeight;
			InvalidateRect(&m_rcText);
		}
	}
private:
	int m_nWidth;
	int m_nHeight;
	CSkinButton m_btnExit;
	CSkinButton m_btnSave;
	CRect m_rcClient;
	RECT m_rcText;
	HFONT m_hFont;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg void OnExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
