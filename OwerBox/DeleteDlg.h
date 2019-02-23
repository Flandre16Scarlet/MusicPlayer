#pragma once
#include "Resource.h"
#include "afxwin.h"

// CDeleteDlg �Ի���

class CDeleteDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeleteDlg)

public:
	CDeleteDlg(const CString& strPath,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeleteDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnDeleteOk();
	afx_msg void OnDeleteCancel();
	HICON hIcon;
	CStatic m_icon;
	CButton m_checkBox;
	//������ܻᱻɾ�����ļ���·��
	CString m_strFilePath;
	// ����·��
	void SetFilePath(const CString& strPath);
};
