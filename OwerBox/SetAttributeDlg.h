#pragma once
#include "Resource.h"
#include "afxwin.h"

// CSetAttributeDlg �Ի���

class CSetAttributeDlg : public CDialog,CErrorLog
{
	DECLARE_DYNAMIC(CSetAttributeDlg)

public:
	CSetAttributeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetAttributeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_SETATTRIBUTE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
private:
	void ReadConfigData(void);
	void SaveConfigData(void);
public:
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//��ӿ�������
	void SetBootStart(void);
	//ɾ����������
	void RemoveBootStart();
private:
	// ���ò����ٶ�
	CSliderButton m_btnSpeed;
	// ���ñ�����
	CSliderButton m_btnRate;
	// ��������
	CSliderButton m_btnPitch;
	CButton m_checkButton;
	BOOL m_bRunBoot;
	CString m_strConfigPath;
	// ����������
	CSliderButton m_leftVoice;
	// ����������
	CSliderButton m_rightVoice;
public:
	void CreateConfigFile(void);
	virtual void OnCancel();
protected:
	virtual void PostNcDestroy();
};
extern CSetAttributeDlg*	g_pSetAttributeDlg;