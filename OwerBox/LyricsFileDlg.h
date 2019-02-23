#pragma once
#include "Resource.h"
#include "afxcmn.h"

// CLyricsFileDlg �Ի���

class CLyricsFileDlg : public CDialog,public CErrorLog
{
	DECLARE_DYNAMIC(CLyricsFileDlg)

public:
	CLyricsFileDlg(const CString& strLyricPath,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLyricsFileDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SHOWLYRIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_richEdit;
	CString m_strRichEdit;
public:
	// ��ȡ����ļ����ݣ��ļ���Ϊȫ·��
	void ReadLyricsFile();
	void Init(CString& strFullName);
	virtual BOOL OnInitDialog();
private:
	// ���ڱ���
	CString m_strText;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnRbtCopy();
	afx_msg void OnRbtCopyAll();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CString m_strLyricPath;
};
