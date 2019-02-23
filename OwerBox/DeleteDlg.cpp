// DeleteDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OwerBox.h"
#include "DeleteDlg.h"

//�Զ�����Ϣ

// CDeleteDlg �Ի���

IMPLEMENT_DYNAMIC(CDeleteDlg, CDialog)

CDeleteDlg::CDeleteDlg(const CString& strPath,CWnd* pParent /*=NULL*/)
	: CDialog(CDeleteDlg::IDD, pParent)
	,m_strFilePath(strPath)
{

}

CDeleteDlg::~CDeleteDlg()
{
}

void CDeleteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IMAGE, m_icon);
	DDX_Control(pDX, IDC_CHECK3, m_checkBox);
}


BEGIN_MESSAGE_MAP(CDeleteDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDeleteDlg::OnDeleteOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CDeleteDlg::OnDeleteCancel)
END_MESSAGE_MAP()


// CDeleteDlg ��Ϣ�������

BOOL CDeleteDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	hIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	//GetDlgItem(IDC_IMAGE)->SetIcon(hIcon,TRUE);
	m_icon.SetIcon(hIcon);
	int pos=m_strFilePath.ReverseFind('\\');
	CString strName=m_strFilePath.Mid(pos+1);
	pos=strName.ReverseFind('.');
	strName=_T("�Ƿ�ɾ��������")+strName.Left(pos);
	SetWindowText(strName);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDeleteDlg::OnDeleteOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_checkBox.GetCheck())//ѡ���ˣ�ɾ���ļ�
	{
		if(!DeleteFile(m_strFilePath))
			MessageBox(_T("�������ļ����ڱ�ʹ��"),_T("ɾ���ļ�ʧ��!"),MB_OK|MB_ICONQUESTION);
	}
	::PostMessage(::GetParent(m_hWnd),WM_DELETE_DIALOG,1,0);
}

void CDeleteDlg::OnDeleteCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::PostMessage(::GetParent(m_hWnd),WM_DELETE_DIALOG,2,0);
}

// ����·��
void CDeleteDlg::SetFilePath(const CString& strPath)
{
	m_strFilePath=strPath;
}
