// SetAttributeDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "SetAttributeDlg.h"
#include <Shlwapi.h>

/////////////////////////////////////////////////////////////////////////////////
//���ó����Զ������߳�
DWORD WINAPI BootStartThread(LPVOID lpParam)
{
	CString strRunPath=CString(GetAppPath().c_str())+_T("\\MusicPlayer.exe");//���������Ҫ���ҵ�ִ���ļ�����   
	CFileFind   fFind;   
	BOOL  bSuccess;   
	bSuccess=fFind.FindFile(strRunPath);   
	fFind.Close();   
	if(bSuccess)   
	{   
		HKEY hKey=NULL;  
		LONG lResult=ERROR_SUCCESS;//HKEY_LOCAL_MACHINE
		lResult=::RegOpenKey(HKEY_CURRENT_USER,\
			_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&hKey); 
		int nLength=strRunPath.GetLength()*2;
		BYTE* pData=(BYTE*)strRunPath.GetBuffer();
		lResult=::RegSetValueEx(hKey,_T("MusicPlayer"),0,REG_SZ,\
			pData,nLength);//�����������Ҫ��ע�����ע�������   
		::RegCloseKey(hKey); 
	}   
	else    
		::AfxMessageBox(_T("û�ҵ�ִ�г����Զ�����ʧ��"));      
	return 0;
}
DWORD WINAPI RemoveBootStartThread(LPVOID lpParam)
{
	HKEY hKey=NULL;
	::RegOpenKey(HKEY_CURRENT_USER,\
		_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),&hKey);
	if(NULL==hKey)
	{
		::AfxMessageBox(_T("��ָ��ע���λ��ʧ��!"));
		return 1;
	}
	CString strKeyName=_T("MusicPlayer");
	::RegDeleteValue(hKey,strKeyName);
	::RegCloseKey(hKey);
	return 0;
}
// CSetAttributeDlg �Ի���

IMPLEMENT_DYNAMIC(CSetAttributeDlg, CDialog)

CSetAttributeDlg::CSetAttributeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetAttributeDlg::IDD, pParent)
	,CErrorLog(_T("CSetAttributeDlg"))
	, m_strConfigPath(_T(""))
	,m_bRunBoot(FALSE)
{

}

CSetAttributeDlg::~CSetAttributeDlg()
{
}

void CSetAttributeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LVOICE, m_leftVoice);
	DDX_Control(pDX, IDC_RVOICE, m_rightVoice);
	DDX_Control(pDX, IDC_RUNBOOT, m_checkButton);
	DDX_Control(pDX, IDC_RATIO, m_btnRate);
	DDX_Control(pDX, IDC_PITCH, m_btnPitch);
	DDX_Control(pDX, IDC_SPEED, m_btnSpeed);
}


BEGIN_MESSAGE_MAP(CSetAttributeDlg, CDialog)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RUNBOOT, &CSetAttributeDlg::OnBnClickedCheck1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSetAttributeDlg ��Ϣ�������

BOOL CSetAttributeDlg::OnInitDialog()
{
// 	try
// 	{
		CDialog::OnInitDialog();

		// TODO:  �ڴ���Ӷ���ĳ�ʼ��
		m_leftVoice.MoveWindow(94,66,130,6);
		m_leftVoice.InitCtrl(IDB_BITMAP_RED,_T("������"),100,WM_SETATTRIBUTE_MESSAGE,1);
		m_leftVoice.SetBkColor(RGB(155,0,200));
		m_rightVoice.MoveWindow(94,92,130,6);
		m_rightVoice.InitCtrl(IDB_BITMAP_RED,_T("������"),100,WM_SETATTRIBUTE_MESSAGE,2);
		m_rightVoice.SetBkColor(RGB(200,0,155));

		m_btnRate.MoveWindow(94,136,130,6);
		m_btnRate.InitCtrl(IDB_BITMAP_YELLOW,_T("������"),200,WM_SETATTRIBUTE_MESSAGE,3);
		m_btnRate.SetBkColor(RGB(100,0,200));
		m_btnRate.SetRatio(0.5);

		m_btnPitch.MoveWindow(94,167,130,6);
		m_btnPitch.InitCtrl(IDB_BITMAP_YELLOW,_T("����"),200,WM_SETATTRIBUTE_MESSAGE,4);
		m_btnPitch.SetBkColor(RGB(0,200,155));
		m_btnPitch.SetRatio(0.5);

		m_btnSpeed.MoveWindow(94,199,130,6);
		m_btnSpeed.InitCtrl(IDB_BITMAP_YELLOW,_T("�����ٶ�"),200,WM_SETATTRIBUTE_MESSAGE,5);
		m_btnSpeed.SetBkColor(RGB(0,200,0));
		m_btnSpeed.SetRatio(0.5);

		CString strTemp;
		strTemp.Append(GetAppPath().c_str());
		m_strConfigPath=strTemp+_T("\\AppData\\PlayerData.xml");
		ReadConfigData();
		HKEY hKey=NULL;
		LONG lResult=::RegGetValue(HKEY_CURRENT_USER,_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"),\
			_T("MusicPlayer"),RRF_RT_REG_SZ,NULL,NULL,NULL);
		if(lResult==ERROR_SUCCESS)
		{
			m_bRunBoot=TRUE;
			((CButton*)GetDlgItem(IDC_RUNBOOT))->SetCheck(TRUE);
		}
		else
			m_bRunBoot=FALSE;
// 	}
// 	catch(...)
// 	{
// 		CString strError;
// 		strError.Format(_T("�����쳣���쳣�룺%d"),GetLastError());
// 		MessageBox(strError);
// 	}
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CSetAttributeDlg::ReadConfigData(void)
{
	if(!PathFileExists(m_strConfigPath))
		CreateConfigFile();
	//�ļ����ڣ�ֱ�Ӷ�ȡ
	CMarkup xml;
	xml.Load(m_strConfigPath);
	while(xml.FindElem(_T("config")))
	{
		xml.IntoElem();
		CString strValue=_T("");
		int nData=100;
		if(xml.FindElem(_T("LeftVoice")))
		{
			strValue=xml.GetData();
			nData=_ttoi(strValue.GetBuffer());
			strValue.ReleaseBuffer();
			if(nData<0||nData>100)
				nData=100;
		}
		else
			xml.AddElem(_T("LeftVoice"),100);
		m_leftVoice.SetCurPos(nData);
		if(xml.FindElem(_T("RightVoice")))
		{
			strValue=xml.GetData();
			nData=_ttoi(strValue.GetBuffer());
			strValue.ReleaseBuffer();
			if(nData<0||nData>100)
				nData=100;
		}
		else
			xml.AddElem(_T("RightVoice"),100);
		m_rightVoice.SetCurPos(nData);
		xml.OutOfElem();
	}
}

void CSetAttributeDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SaveConfigData();
	CDialog::OnClose();
}

void CSetAttributeDlg::SaveConfigData(void)
{
	if(!PathFileExists(m_strConfigPath))
		CreateConfigFile();
	else
	{
		CMarkup xml;
		xml.Load(m_strConfigPath);
		xml.FindElem(_T("config"));
		xml.IntoElem();
		int nValue=0;
		nValue=m_leftVoice.GetCurPos();
		if(xml.FindElem(_T("LeftVoice")))
			xml.SetData(nValue);
		else
			xml.AddElem(_T("LeftVoice"),nValue);
		nValue=m_rightVoice.GetCurPos();
		if(xml.FindElem(_T("RightVoice")))
			xml.SetData(nValue);
		else
			xml.AddElem(_T("RightVoice"),nValue);
		nValue=m_btnRate.GetCurPos();
		xml.OutOfElem();
		xml.Save(m_strConfigPath);
	}
}

void CSetAttributeDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(!m_bRunBoot)
	{
		SetBootStart();
		m_bRunBoot=TRUE;
	}
	else
	{
		m_bRunBoot=FALSE;
		RemoveBootStart();
	}
}

void CSetAttributeDlg::SetBootStart(void)
{
	HANDLE hThread=::CreateThread(NULL,0,BootStartThread,NULL,0,NULL);
	::CloseHandle(hThread);
}
void CSetAttributeDlg::RemoveBootStart()
{
	HANDLE hThread=::CreateThread(NULL,0,RemoveBootStartThread,NULL,0,NULL);
	::CloseHandle(hThread);
}
void CSetAttributeDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
// 	CBrush* pBr=NULL;
// 	CBrush br(RGB(255,0,20));
// 	pBr=dc.SelectObject(&br);
// 	//dc.Ellipse(&CRect(162,146,172,164));
// 	dc.FillSolidRect(CRect(164,144,168,204),RGB(200,0,0));
// 	dc.SelectObject(pBr);
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

void CSetAttributeDlg::CreateConfigFile(void)
{
	CMarkup xml;
	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>\r\n"));
	xml.AddElem(_T("config"));
	xml.IntoElem();
	m_leftVoice.SetRatio(1);
	xml.AddElem(_T("LeftVoice"),100);
	m_rightVoice.SetRatio(1);
	xml.AddElem(_T("RightVoice"),100);
	m_btnRate.SetRatio(0.5);
	xml.AddElem(_T("PlayRate"),100);
	m_btnPitch.SetRatio(0.5);
	xml.AddElem(_T("PlayPitch"),100);
	m_btnSpeed.SetRatio(0.5);
	xml.AddElem(_T("PlaySpeed"),100);
	xml.OutOfElem();
	xml.Save(m_strConfigPath);
}

void CSetAttributeDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::OnCancel();
}

void CSetAttributeDlg::PostNcDestroy()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialog::PostNcDestroy();
	delete this;
	g_pSetAttributeDlg=NULL;
}
