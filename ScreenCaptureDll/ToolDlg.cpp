// ToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenCaptureDll.h"
#include "ToolDlg.h"
#include "resource.h"


// CToolDlg �Ի���

IMPLEMENT_DYNAMIC(CToolDlg, CDialog)

CToolDlg::CToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDlg::IDD, pParent)
	,m_nWidth(0)
	,m_nHeight(0)
	,m_hFont(NULL)
{

}

CToolDlg::~CToolDlg()
{
	if(m_hFont)
		ReleaseGDIHandle((HANDLE*)&m_hFont);
}

void CToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON2, m_btnExit);
	DDX_Control(pDX, IDC_BUTTON1, m_btnSave);
}


BEGIN_MESSAGE_MAP(CToolDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, &CToolDlg::OnSave)
	ON_BN_CLICKED(IDC_BUTTON2, &CToolDlg::OnExit)
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CToolDlg ��Ϣ�������

void CToolDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	if(NULL==m_hMemDC)
	{
		m_hMemDC=CreateCompatibleDC(dc.m_hDC);
		m_hMemBitmap=CreateCompatibleBitmap(dc.m_hDC,m_rcClient.Width(),m_rcClient.Height());
		::SelectObject(m_hMemDC,m_hMemBitmap);
		::SelectObject(m_hMemDC,m_hFont);
		::SetTextColor(m_hMemDC,0XFF0000);
		::SetBkMode(m_hMemDC,TRANSPARENT);
	}
	FillDCRect(m_hMemDC,&m_rcClient,0xffffff);
	CString strText;
	strText.Format(_T("%d��%d"),m_nWidth,m_nHeight);
	::DrawText(m_hMemDC,strText,strText.GetLength(),&m_rcText,DT_CENTER|DT_VCENTER);
	::BitBlt(dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),m_hMemDC,0,0,SRCCOPY);
}

BOOL CToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
 	ModifyStyleEx(0, WS_EX_LAYERED);// | WS_EX_TRANSPARENT); 
 	SetLayeredWindowAttributes(0, 150, LWA_ALPHA);
	LOGFONT lf;
	GetFont()->GetLogFont(&lf);
	lf.lfHeight=28;
	lf.lfWeight=700;
	m_hFont=CreateFontIndirect(&lf);
	m_rcText.left=0;
	m_rcText.top=0;
	m_rcText.right=140;
	m_rcText.bottom=30;
	m_btnSave.MoveWindow(140,2,25,25);
	m_btnSave.Init(IDB_BITMAP_SAVE1,IDB_BITMAP_SAVE2,_T("����"));
	m_btnExit.MoveWindow(165,2,25,25);
	m_btnExit.Init(IDB_BITMAP_EXIT1,IDB_BITMAP_EXIT2,_T("ȡ��"));
	GetClientRect(&m_rcClient);
	SetTimer(1,100,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CToolDlg::OnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(::GetParent(m_hWnd),WM_COMMAND,IDC_BUTTON1,0);
}

void CToolDlg::OnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	::SendMessage(::GetParent(m_hWnd),WM_COMMAND,IDC_BUTTON2,0);
}

void CToolDlg::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	if(IsWindow(m_hWnd))
		GetClientRect(&m_rcClient);
}

BOOL CToolDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
	return __super::OnEraseBkgnd(pDC);
}
