#pragma once
#include "Resource.h"
#include "ImageCtrl.h"
#include "afxwin.h"
#include "e:\mymusicplayer\owerdrawcontrl\linkbutton.h"
#include "e:\mymusicplayer\owerdrawcontrl\skinbutton.h"


// CChangeClothDlg �Ի���

class CChangeClothDlg : public CDialog,public CErrorLog,public CMemBase
{
	DECLARE_DYNAMIC(CChangeClothDlg)

public:
	CChangeClothDlg(const BYTE bAlphaValue,const CString& strBackImagePath,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeClothDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_CHANGECLOTH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
public:
	virtual BOOL OnInitDialog();
private:
	// ���ڴ���͸����
	CSliderButton m_btnTransparent;
	CImageCtrl* m_arrContrls[2][9];
	//���浱ǰѡ�е�ͼƬλ��
	INDEX m_indSelect;
	//���洰�ڴ�С
	CRect m_rcClient;
	// ���洰�ڵ�ALPHAֵ
	BYTE m_bAlphaValue;
	CSkinButton m_btnChange;
	//����ѡ�е�Ƥ����·��
	CString m_strBackImagePath;
protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnChangeImages();
};
