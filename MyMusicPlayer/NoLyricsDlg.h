#pragma once

// CNoLyricsDlg �Ի���

class CNoLyricsDlg : public CDialog
{
	DECLARE_DYNAMIC(CNoLyricsDlg)

public:
	CNoLyricsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNoLyricsDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// �����Ӱ�ť
	CLinkButton m_linkBtn1;
public:
	afx_msg void OnLoadLyrics();
	virtual BOOL OnInitDialog();
};
