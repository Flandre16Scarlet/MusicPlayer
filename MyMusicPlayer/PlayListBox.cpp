// PlayListBox.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "PlayListBox.h"


// CPlayListBox

IMPLEMENT_DYNAMIC(CPlayerList, CListBox)

CPlayerList::CPlayerList()
:CErrorLog(_T("CPlayerList"))
,m_pParent(NULL)
,m_nHeight(25)
,m_hFont(NULL)
,m_nCursorPos(-1)
,m_hPen(NULL)
,m_nMaxWidth(0)
{
}

CPlayerList::~CPlayerList()
{
	ReleaseGDIHandle((HANDLE*)&m_hFont);
	ReleaseGDIHandle((HANDLE*)&m_hPen);
}


BEGIN_MESSAGE_MAP(CPlayerList, CListBox)
	ON_COMMAND(ID_LISTBOX_32773, &CPlayerList::OnListboxAttribute)
	ON_COMMAND(ID_LISTBOX_32774, &CPlayerList::OnListboxDeleteItem)
ON_COMMAND(ID_LISTBOX_32796, &CPlayerList::OnListboxLookLyrics)
ON_WM_MOUSEMOVE()
ON_WM_ERASEBKGND()
ON_WM_PAINT()
ON_WM_MOUSEHOVER()
ON_WM_MOUSELEAVE()
ON_WM_SIZE()
END_MESSAGE_MAP()



// CPlayListBox ��Ϣ�������

// ��ͼƬ����
void CPlayerList::OnListboxAttribute()
{
	// TODO: �ڴ���������������
	LRESULT lRet=::SendMessage(::GetParent(m_hWnd),WM_LISTBOX_MESSAGE,2,0);
	if(lRet!=1)
		MessageBox(_T("SendMessage����ʧ�ܣ�"));

}

void CPlayerList::OnListboxDeleteItem()
{
	// TODO: �ڴ���������������
	EXCEPTION_INFO ei;
	try
	{
		if(GetCurSel()!=LB_ERR)//û��ѡ����
			::SendMessage(::GetParent(m_hWnd),WM_LISTBOX_MESSAGE,3,0);
	}
	catch(...)
	{
		ei.tstrExceptionFunc=_T("OnListboxDeleteItem");
		WriteErrorLog(&ei);
	}
}

void CPlayerList::OnListboxLookLyrics()
{
	// TODO: �ڴ���������������
	::SendMessage(::GetParent(m_hWnd),WM_LISTBOX_MESSAGE,1,0);
}
void CPlayerList::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_hFont=::CreateFont(16,0,0,0,900,FALSE,FALSE,FALSE,134,\
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,2,\
		DEFAULT_PITCH,_T("����"));
	m_hPen=::CreatePen(PS_DOT,1,0xf000f0);
	GetClientRect(&m_rcClient);
	ZeroMemory(&m_hScrollInfo,sizeof(m_hScrollInfo));
	CListBox::PreSubclassWindow();
}
void CPlayerList::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{

	// TODO:  ������Ĵ�����ȷ��ָ����Ĵ�С
	lpMeasureItemStruct->itemHeight=m_nHeight;
}
void CPlayerList::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  ������Ĵ����Ի���ָ����
	EXCEPTION_INFO ei;
	try
	{
	}
	catch(...)
	{
		WriteErrorLog(&ei);
	}
}
int CPlayerList::AddString(LPCTSTR lpszItem)
{
	EXCEPTION_INFO ei;
	int nRet=0;
	try
	{
		nRet=CListBox::AddString(lpszItem);
		CClientDC dc(this);
		TEXTMETRIC tm;
		::GetTextMetrics(dc.m_hDC,&tm);
		CSize sz;
		::GetTextExtentPoint32(dc.m_hDC,lpszItem,_tcslen(lpszItem),&sz);
		m_nMaxWidth=max(m_nMaxWidth,sz.cx);
		SetHorizontalExtent(m_nMaxWidth);
	}
	catch(...)
	{
		ei.tstrExceptionFunc=_T("AddString");
		WriteErrorLog(&ei);
	}
	return nRet;
}
inline void CPlayerList::GetSInfo(SCROLLINFO& sInfo,const int nFlag/* =SB_HORZ */)
{
	memset(&sInfo,0,sizeof(SCROLLINFO));
	sInfo.cbSize=sizeof(SCROLLINFO);
	sInfo.fMask=SIF_ALL;
	GetScrollInfo(nFlag,&sInfo);
}
LRESULT CPlayerList::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)
	{
		case WM_RBUTTONDOWN:	
			{
				int yPos=GET_Y_LPARAM(lParam);
				//��Ҫ�������λ���Ƿ���Ч�����ж�
				int nCurrentSel=yPos/m_nHeight+GetTopIndex();
				if(nCurrentSel<=GetCount()-1)//ѡ���Ҽ��������һ��
				{
					SetCurSel(nCurrentSel);
					Invalidate();
					CMenu menu,*pMenu;
					menu.LoadMenu(IDR_MENU2);
					pMenu=menu.GetSubMenu(0);
					CPoint pt;
					GetCursorPos(&pt);
					pMenu->TrackPopupMenu(TPM_RIGHTBUTTON,pt.x,pt.y,this);
					pMenu->DestroyMenu();
				}
				break;
			}
		case WM_LBUTTONDBLCLK:
			{
				int yPos=GET_Y_LPARAM(lParam);
				//��Ҫ�������λ���Ƿ���Ч�����ж�
				int nCurrentSel=yPos/m_nHeight+GetTopIndex();
				if(nCurrentSel<=GetCount()-1)
					::PostMessage(::GetParent(m_hWnd),WM_LISTBOX_MESSAGE,4,nCurrentSel);
				break;
			}
		case WM_MOUSEWHEEL://�������
			{
				short sState=GET_WHEEL_DELTA_WPARAM(wParam);
				SCROLLINFO si;
				GetSInfo(si,SB_VERT);
				if(sState>0&&(0==si.nPos))//���Ϲ���
					break;
				if(sState<0&&(si.nMax<si.nPos+si.nPage))//���¹���
					break;
			}
		case WM_LBUTTONDOWN:
		case WM_VSCROLL://������ֱ������
		case WM_HSCROLL://����ˮƽ������
		case WM_KEYDOWN:
		Invalidate();
		default:
			break;
	}
	return CListBox::WindowProc(message, wParam, lParam);
}
void CPlayerList::DrawColorItem( HDC hdc,const CRect& rect )
{
	try
	{
		if(NULL==hdc)
			throw _T("��������pDCΪ��ָ�롣");
		if(rect.IsRectEmpty())
			throw _T("��������rectΪ�վ��Ρ�");
		COLORREF firstColor=RGB(255,0,255),secondColor=RGB(255,255,0);
		//���Ի��Ƶ���ĸ���
		int nCount=rect.Height()/m_nHeight;
		//�����ಿ�ֵĸ߶�
		int nRemain=rect.Height()%m_nHeight;
		CRect rcTemp;
		rcTemp.left=0;
		rcTemp.right=rect.Width();
		for(int i=0;i<nCount;++i)
		{
			rcTemp.top=rect.top+i*m_nHeight;
			rcTemp.bottom=rcTemp.top+m_nHeight;
			if(i%2)
				FillDCRect(hdc,&rcTemp,secondColor);
			else
				FillDCRect(hdc,&rcTemp,firstColor);
		}
		//���ƶ��ಿ��
		rcTemp.top=rect.bottom-nRemain;
		rcTemp.bottom=rect.bottom;
		FillDCRect(hdc,&rcTemp,nCount%2?secondColor:firstColor);
	}
	catch(TCHAR* pError)
	{
		EXCEPTION_INFO ei=FillExceptionInfo(pError,__LINE__,__FILE__,::GetLastError(),_T("DrawColorItem"));
		WriteErrorLog(&ei);
	}
}

BOOL CPlayerList::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
}

void CPlayerList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	GetSInfo(m_hScrollInfo);
	static CRect rcBack(0,0,0,0);
	rcBack.bottom=m_rcClient.Height();
	rcBack.right=max(m_hScrollInfo.nMax,m_rcClient.Width());
	if(NULL==m_hBackDC)
		m_hBackDC=::CreateCompatibleDC(dc.m_hDC);
	if(m_bChangeBack)
	{
		m_bChangeBack=FALSE;
		ReleaseGDIHandle((HANDLE*)&m_hBackBitmap);
		m_hBackBitmap=GetDCBackBitmap(dc.m_hDC,m_rcClient.Width(),m_rcClient.Height());
		::SelectObject(m_hBackDC,m_hBackBitmap);
	}
	::BitBlt(dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),m_hBackDC,0,0,SRCCOPY);
	//CFuncDC::SaveBackBitmap(dc.m_hDC,m_rcClient.Width(),m_rcClient.Height(),"c:\\b1.bmp");
	//::SelectObject(m_hBackDC,hOldBitmap);
	if(NULL==m_hMemDC)
	{
		m_hMemDC=::CreateCompatibleDC(dc.m_hDC);
		::SetBkMode(m_hMemDC,TRANSPARENT);
		::SetTextColor(m_hMemDC,RGB(0,255,0));
	}
	if(NULL==m_hMemBitmap)
	{
		m_hMemBitmap=::CreateCompatibleBitmap(dc.m_hDC,rcBack.Width(),rcBack.Height());
		TRACE0("�ڴ����DC�����Ĵ�С��");
		TRACE2("Width: %d,Height: %d\n",rcBack.Width(),rcBack.Height());
		::SelectObject(m_hMemDC,m_hMemBitmap);
	}
	FillDCRect(m_hMemDC,&rcBack,0xffffff);
	//CFuncDC::SaveBackBitmap(m_hMemDC,rcBack.Width(),rcBack.Height(),"c:\\b2.bmp");
	//DrawColorItem(m_hMemBkDC,rcBack);
	if(0!=GetCount())
	{
		int nTopIndex=GetTopIndex();
		int numPerPage=m_rcClient.Height()/m_nHeight;
		//int nRemain=m_rcClient.Height()%m_nHeight;//���ʣ���һ���ֵĸ߶�
		CString strText;
		RECT rcItem;
		rcItem.left=0;
		rcItem.right=rcBack.Width();
		HFONT hOldFont=(HFONT)::SelectObject(m_hMemDC,m_hFont);
		for(int i=0;i<=numPerPage;++i)
		{
			if(i+nTopIndex>=GetCount())
				break;
			strText.Empty();
			GetText(i+nTopIndex,strText);
			if(_T("")==strText)
				break;
			rcItem.top=m_nHeight*i;
			rcItem.bottom=rcItem.top+m_nHeight;
			if(GetCurSel()==i+nTopIndex)
				FillDCRect(m_hMemDC,&rcItem,RGB(200,0,0));
			if(m_nCursorPos==i)
				FillDCRect(m_hMemDC,&rcItem,RGB(200,0,100));
			//::FrameRect()
			rcItem.left=15;
			rcItem.top+=5;
			//�������ֲ���
			::DrawText(m_hMemDC,strText,strText.GetLength(),&rcItem,DT_VCENTER|DT_NOCLIP);
			rcItem.left=0;
			rcItem.top-=5;
		}
		::SelectObject(m_hMemDC,hOldFont);
	}
	//CFuncDC::SaveBackBitmap(m_hMemDC,rcBack.Width(),rcBack.Height(),"c:\\b3.bmp");
	DrawLines(m_hMemDC);
	//CFuncDC::SaveBackBitmap(m_hMemDC,rcBack.Width(),rcBack.Height(),"c:\\b4.bmp");
	//::BitBlt(dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),m_hMemBkDC,m_hScrollInfo.nPos,0,SRCCOPY);
	int nPos=m_hScrollInfo.nPos;
// 	if(nPos>0&&nPos>m_hScrollInfo.nMax-m_rcClient.Width())
// 		nPos-=2;
	::TransparentBlt(dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),\
		m_hMemDC,nPos,0,m_rcClient.Width(),m_rcClient.Height(),0xffffff);
}
void CPlayerList::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TRACKMOUSEEVENT tm;
	tm.cbSize=sizeof(tm);
	tm.dwFlags=TME_HOVER|TME_LEAVE;
	tm.dwHoverTime=10;
	tm.hwndTrack=m_hWnd;
	_TrackMouseEvent(&tm);
	CListBox::OnMouseMove(nFlags, point);
}
void CPlayerList::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static int nFormalIndex=0;
	if(0!=GetCount())
	{
		nFormalIndex=m_nCursorPos;
		m_nCursorPos=point.y/m_nHeight;
		if(nFormalIndex!=m_nCursorPos)
		{
			RECT rcItem;
			rcItem.left=0;
			rcItem.right=max(m_rcClient.Width(),m_hScrollInfo.nMax);
			rcItem.top=nFormalIndex*m_nHeight;
			rcItem.bottom=rcItem.top+m_nHeight;
			InvalidateRect(&rcItem);
			rcItem.top=m_nCursorPos*m_nHeight;
			rcItem.bottom=rcItem.top+m_nHeight;
			InvalidateRect(&rcItem);
		}
	}
	CListBox::OnMouseHover(nFlags, point);
}

void CPlayerList::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	RECT rcItem;
	rcItem.left=0;
	rcItem.right=max(m_rcClient.Width(),m_hScrollInfo.nMax);
	rcItem.top=m_nCursorPos*m_nHeight;
	rcItem.bottom=rcItem.top+m_nHeight;
	InvalidateRect(&rcItem);
	m_nCursorPos=-1;
	CListBox::OnMouseLeave();
}

void CPlayerList::OnSize(UINT nType, int cx, int cy)
{
	//CPlayerList::OnSize(nType, cx, cy);
	if(::IsWindow(m_hWnd))
		GetClientRect(&m_rcClient);
	// TODO: �ڴ˴������Ϣ����������
	
}

void CPlayerList::DrawLines( HDC hdc )
{
	HPEN hOldPen=(HPEN)::SelectObject(hdc,m_hPen);
	static POINT pt;
	int nCount=m_rcClient.Height()/m_nHeight;
	for(int i=1;i<=nCount;++i)
	{
		::MoveToEx(hdc,m_hScrollInfo.nPos,i*m_nHeight,&pt);
		::LineTo(hdc,m_hScrollInfo.nPos+m_rcClient.Width(),i*m_nHeight);
	}
	::SelectObject(hdc,hOldPen);
}

