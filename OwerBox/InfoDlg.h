#pragma once

#include "libzplay.h"
#pragma comment(lib,"libzplay")
#include "FileAttribute.h"
// CInfoDlg �Ի���

class CInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CInfoDlg)

public:
	CInfoDlg(const CString& strPath,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInfoDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CString m_strFilePath;
public:
	virtual BOOL OnInitDialog();
};
