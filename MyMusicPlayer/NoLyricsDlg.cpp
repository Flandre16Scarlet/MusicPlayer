// NoLyricsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "NoLyricsDlg.h"


// CNoLyricsDlg �Ի���

IMPLEMENT_DYNAMIC(CNoLyricsDlg, CDialog)

CNoLyricsDlg::CNoLyricsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoLyricsDlg::IDD, pParent)
{

}

CNoLyricsDlg::~CNoLyricsDlg()
{
}

void CNoLyricsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_linkBtn1);
}


BEGIN_MESSAGE_MAP(CNoLyricsDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CNoLyricsDlg::OnLoadLyrics)
END_MESSAGE_MAP()


// CNoLyricsDlg ��Ϣ�������

void CNoLyricsDlg::OnLoadLyrics()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(m_hWnd,_T("open"), _T("http://www.5ilrc.com"),_T(""),_T(""),SW_SHOW );
}

BOOL CNoLyricsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_linkBtn1.Init(_T("������ظ��"),_T("���Ӹ����վ"));
	m_linkBtn1.SetBkColor(RGB(240,240,240));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
