// TransDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TransDlg.h"
#include "ScreenCaptureDll.h"

// CTransDlg �Ի���

IMPLEMENT_DYNAMIC(CInfoDlg, CDialog)

CInfoDlg::CInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInfoDlg::IDD, pParent)
{
	m_rValue=m_gValue=m_bValue=0;
	m_nWidth=m_nHeight=0;
	m_hRedPen=NULL;
	m_hBlackPen=NULL;
	m_hFont=NULL;
	m_hBrush=NULL;
	m_hBkMemBitmap=NULL;
}

CInfoDlg::~CInfoDlg()
{
	ReleaseDCHandle(&m_hBkMemDC);
	ReleaseGDIHandle((HANDLE*)&m_hBkMemBitmap);
	m_hBkMemBitmap=NULL;
	ReleaseGDIHandle((HANDLE*)&m_hRedPen);
	m_hRedPen=NULL;
	ReleaseGDIHandle((HANDLE*)&m_hBlackPen);
	m_hBlackPen=NULL;
	ReleaseGDIHandle((HANDLE*)&m_hFont);
	m_hFont=NULL;
	ReleaseGDIHandle((HANDLE*)&m_hBrush);
	m_hBrush=NULL;
}

void CInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInfoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CTransDlg ��Ϣ�������

BOOL CInfoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//����͸���Ի���
	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)|0x80000);
	SetLayeredWindowAttributes(0xffffff,128,LWA_COLORKEY);
	m_rcClient=CRect(0,0,200,160);
	m_hBlackPen=::CreatePen(PS_SOLID,1,RGB(155,0,200));
	m_hRedPen=::CreatePen(PS_SOLID,2,0X0000FF);
	LOGFONT lf;
	memset(&lf,0,sizeof(lf));
	GetFont()->GetLogFont(&lf);
	lf.lfWeight=700;
	lf.lfHeight=16;
	_tcscpy(lf.lfFaceName,_T("����"));
	m_hFont=::CreateFontIndirect(&lf);
	m_hBrush=::CreateSolidBrush(RGB(0,0,200));
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CInfoDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	if(NULL==m_hBkMemDC)
	{
		m_hBkMemDC=::CreateCompatibleDC(dc.m_hDC);
		m_hBkMemBitmap=::CreateCompatibleBitmap(dc.m_hDC,m_rcClient.Width(),m_rcClient.Height());
		::SelectObject(m_hBkMemDC,m_hBkMemBitmap);
	}
	::SetBkColor(m_hBkMemDC, 0xffffff);
	::ExtTextOut(m_hBkMemDC, 0, 0, ETO_OPAQUE, &m_rcClient, NULL, 0, NULL);
	::FrameRect(m_hBkMemDC,&m_rcClient,m_hBrush);
	DrawText(m_hBkMemDC);
	DrawBitmap(m_hBkMemDC);
	DrawLine(m_hBkMemDC);
	::BitBlt(dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),m_hBkMemDC,0,0,SRCCOPY);
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
}

void CInfoDlg::DrawText( HDC hDC )
{
	static	RECT rcText={2,86,m_rcClient.Width(),m_rcClient.Height()};
	HFONT hOldFont=(HFONT)::SelectObject(hDC,m_hFont);
	::SetBkMode(hDC,TRANSPARENT);
	::SetTextColor(hDC,RGB(0,255,0));
	static CString strText;
	strText.Format(_T(" ��ǰ�����С:\n         %d  ��  %d\n  RGB(%d,%d,%d)\n ˫�����������Ƶ�������"),\
		m_nWidth,m_nHeight,m_rValue,m_gValue,m_bValue);
	::DrawText(hDC,strText,strText.GetLength(),&rcText,DT_LEFT);
	::SelectObject(hDC,hOldFont);
}

BOOL CInfoDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//pDC->FillSolidRect(&m_rcClient,0xffffff);
    return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}

void CInfoDlg::DrawBitmap(HDC hDC)
{
	if(m_hMemBitmap==NULL)
		return;
	if(m_hMemDC==NULL)
		m_hMemDC=CreateCompatibleDC(hDC);//�����ڴ����DC
	HBITMAP hOldBmp=(HBITMAP)::SelectObject(m_hMemDC,m_hMemBitmap);
	::StretchBlt(hDC,0,0,100,80,m_hMemDC,0,0,18,18,SRCCOPY);
	::SelectObject(m_hMemDC,hOldBmp);
}

// �����߽���
void CInfoDlg::DrawLine(HDC hDC)
{
	HPEN hOldPen=(HPEN)::SelectObject(hDC,m_hBlackPen);
	static POINT pt;
	::MoveToEx(hDC,0,80,&pt);
	::LineTo(hDC,100,80);
	::LineTo(hDC,100,0);
	::LineTo(hDC,0,0);
	::LineTo(hDC,0,80);
	::SelectObject(hDC,m_hRedPen);
	::MoveToEx(hDC,0,40,&pt);
	::LineTo(hDC,100,40);
	::MoveToEx(hDC,50,0,&pt);
	::LineTo(hDC,50,80);
	::SelectObject(hDC,hOldPen);
}

// ����RGB��ɫֵ�ӿ�
void CInfoDlg::SetRGBValue( const int r, const int g,const int b )
{
	m_rValue=r;
	m_gValue=g;
	m_bValue=b;
}

// ���ý�ȡ�����С�ӿ�
void CInfoDlg::SetRectValue( const int nWidth, const int nHeight )
{
	m_nWidth=nWidth;
	m_nHeight=nHeight;
}

// ���õ�ǰ�����������λͼ���
void CInfoDlg::SetBitmap(HBITMAP hBmp)
{
	::DeleteObject(m_hMemBitmap);
	m_hMemBitmap=NULL;
	m_hMemBitmap=hBmp;
}
