/****************************************************************/
/*																*/
/*  StarWarsCtrl.cpp											*/
/*																*/
/*  Implementation of the CStarWarsCtrl.cpp class.				*/
/*																*/
/*  Programmed by Pablo van der Meer							*/
/*  Copyright Pablo Software Solutions 2002						*/
/*	http://www.pablovandermeer.nl								*/
/*																*/
/*  Last updated: 10 july 2002									*/
/*																*/
/****************************************************************/


#include "stdafx.h"
#include "resource.h"
#include "StarWarsCtrl.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define getrandom(min,max) ((rand()%(int)(((max)+1)-(min)))+(min));


CStarWarsCtrl::CStarWarsCtrl()
{
	// protected bitmaps to restore the memory DC's
	m_pOldBitmap = NULL;

	m_Font.CreateFont(30, 0, 0, 0, FW_BOLD,
                       FALSE, FALSE, 0, ANSI_CHARSET,
                       OUT_DEFAULT_PRECIS, 
                       CLIP_DEFAULT_PRECIS,
                       DEFAULT_QUALITY, 
                       DEFAULT_PITCH|FF_SWISS, _T("�����п�"));
	m_nScrollSpeed = 8;
	m_nStarsSpeed = 20;
}

CStarWarsCtrl::~CStarWarsCtrl()
{
	if (m_pOldBitmap != NULL)
		m_MainDC.SelectObject(m_pOldBitmap);  
}


BEGIN_MESSAGE_MAP(CStarWarsCtrl, CStatic)
	//{{AFX_MSG_MAP(CStarWarsCtrl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/********************************************************************/
/*																	*/
/* Function name : PreSubclassWindow								*/
/* Description   : Initialize some stuff							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::PreSubclassWindow() 
{
	CClientDC dc(this);

	GetClientRect(m_rectClient);
/*[00:15.58]
[00:24.88]Ѱ�������������Ҷ��
[00:29.47]��ԶҲ��������л
[00:35.76]����ҹɫ�µ�С������
[00:42.43]�����������Ļ�Ұ
[00:45.43]
[00:49.09]÷��ʱ�����į������
[00:54.15]������ֺܿ�����
[01:00.87]���������̻�������
[01:06.26]ҡҷ������ƮԶ
[01:10.26]
[01:13.53]�����Ƿ��¹�ѩ
[01:16.11]�����ź���
[01:18.86]ˮ�к�����ѩ
[01:21.92]ָ������ڽ�
[01:24.92]
[01:25.12]�����Ƿ��¹�ѩ
[01:27.89]�����������
[01:30.90]������Ե�ټ�
[01:34.09]�׵���������ü���
[01:41.93]
[01:42.93]
[02:02.87]
[02:03.87]Ѱ�������������Ҷ��
[02:09.77]��ԶҲ��������л
[02:15.40]����ҹɫ�µ�С������
[02:21.32]�����������Ļ�Ұ
[02:27.16]
[02:27.96]÷��ʱ�����į������
[02:33.43]������ֺܿ�����
[02:39.28]���������̻�������
[02:44.88]ҡҷ������ƮԶ
[02:50.06]
[02:52.07]�����Ƿ��¹�ѩ
[02:54.97]�����ź���
[02:57.85]ˮ�к�����ѩ
[03:01.05]ָ������ڽ�
[03:03.91]
[03:04.26]�����Ƿ��¹�ѩ
[03:07.76]�����������
[03:09.84]������Ե�ټ�
[03:12.97]�׵���������ü���
[03:18.94]
[03:19.94]����������������ṩ
�
*/
	// initialize stars
	for (int i = 0; i < NUM_STARS; i++)
	{
		m_StarArray[i].x = getrandom(0, 1024);
		m_StarArray[i].x -= 512;
		m_StarArray[i].y = getrandom(0, 1024);
		m_StarArray[i].y -= 512;
		m_StarArray[i].z = getrandom(0, 512);
		m_StarArray[i].z -= 256;
	}

	m_TextLines.Add(_T("Ѱ�������������Ҷ��"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("��ԶҲ��������л"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("����ҹɫ�µ�С������ "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("�����������Ļ�Ұ"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("÷��ʱ�����į������"));
	m_TextLines.Add(_T(""));


	m_TextLines.Add(_T("������ֺܿ�����"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("���������̻�������"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("ҡҷ������ƮԶ"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("�����Ƿ��¹�ѩ"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("�����ź���"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("ˮ�к�����ѩ"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("ָ������ڽ�"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("�����Ƿ��¹�ѩ "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("����������� "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("������Ե�ټ� "));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("�׵���������ü���"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("����-�����Ų�ѩ��"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("Jelin �"));
	m_TextLines.Add(_T(""));
	m_TextLines.Add(_T("e-mail:Jelinyao@163.com"));

	m_nScrollPos = m_rectClient.Height();

	// calculate speed so that it scrolls the same speed on a different machine
	DWORD t1 = GetTickCount();
	InvalidateCtrl();
	DWORD t2 = GetTickCount();

	t2 -= t1; // = 50 on my system

	m_nScrollSpeed = (m_nScrollSpeed * t2)/50;

	SetTimer(1, 75, NULL);

	CStatic::PreSubclassWindow();
}


/********************************************************************/
/*																	*/
/* Function name : OnPaint											*/
/* Description   : Called when the application makes a request to	*/
/*				   repaint a portion of the window.					*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CDC memDC;
	CBitmap memBitmap;
	CBitmap* oldBitmap;

	// to avoid flicker, establish a memory dc, draw to it 
	// and then BitBlt it to the client
	memDC.CreateCompatibleDC(&dc);
	memBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
	oldBitmap = (CBitmap *)memDC.SelectObject(&memBitmap);

	if (memDC.GetSafeHdc() != NULL)
	{
		// first drop the bitmap on the memory dc
		memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), &m_MainDC, 0, 0, SRCCOPY);
		// finally send the result to the display
		dc.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), &memDC, 0, 0, SRCCOPY);
	}
	memDC.SelectObject(oldBitmap);
}


/********************************************************************/
/*																	*/
/* Function name : OnSize											*/
/* Description   : The framework calls this member function after	*/
/*				   the window�s size has changed.					*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
	
	// OnSize automatically gets called during the setup of the control
	GetClientRect(m_rectClient);

	// destroy and recreate the main bitmap
	CClientDC dc(this);
	if (m_pOldBitmap && m_MainBitmap.GetSafeHandle() && m_MainDC.GetSafeHdc())
	{
		m_MainDC.SelectObject(m_pOldBitmap);
		m_MainBitmap.DeleteObject();
		m_MainBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
		m_pOldBitmap = m_MainDC.SelectObject(&m_MainBitmap);
	}
}


/********************************************************************/
/*																	*/
/* Function name : DoStars											*/
/* Description   : Draw stars										*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::DoStars(CDC *pDC)
{
	m_MainDC.SetBkColor(RGB(0,0,0));
	m_MainDC.SetTextColor(RGB(255,255,255));
	m_MainDC.FillSolidRect(m_rectClient, RGB(0,0,0));

	int nFunFactor = 100;
	int x, y, z;
	for(int i = 0; i < NUM_STARS; i++)
	{
        m_StarArray[i].z = m_StarArray[i].z - m_nStarsSpeed;
        if (m_StarArray[i].z > 255)
		{
			m_StarArray[i].z = -255;
		}
        if (m_StarArray[i].z < -255)
		{
			m_StarArray[i].z = 255;
		}
        
		z = m_StarArray[i].z + 256;
        x = (m_StarArray[i].x * nFunFactor / z) + (m_rectClient.Width() / 2);
        y = (m_StarArray[i].y * nFunFactor / z) + (m_rectClient.Height() / 2);
		
		CPen myPen;

		// create a white pen which luminosity depends on the z position (for 3D effect!)
		int nColor = 255 - m_StarArray[i].z;
		myPen.CreatePen(PS_COSMETIC, 1, RGB(nColor,nColor,nColor));

		CPen *pOldPen = (CPen *)m_MainDC.SelectObject(&myPen);
		// draw star
		m_MainDC.Ellipse(CRect(x, y, x+3, y+3));
		m_MainDC.SelectObject(pOldPen);
    }
}


/********************************************************************/
/*																	*/
/* Function name : InvalidateCtrl									*/
/* Description   : Draw the Matrix to a bitmap.						*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::InvalidateCtrl()
{
	// in case we haven't established the memory dc's
	CClientDC dc(this);

	// if we don't have one yet, set up a memory dc for the control 
	if (m_MainDC.GetSafeHdc() == NULL)
	{
		m_MainDC.CreateCompatibleDC(&dc);
		m_MainBitmap.CreateCompatibleBitmap(&dc, m_rectClient.Width(), m_rectClient.Height());
		m_pOldBitmap = m_MainDC.SelectObject(&m_MainBitmap);
	}
  
	DoStars(&dc);	
	DoScrollText(&dc);

	// finally, force redraw
	InvalidateRect(m_rectClient);
} 


/********************************************************************/
/*																	*/
/* Function name : OnTimer											*/
/* Description   : Update display									*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == 1)
		InvalidateCtrl();

	CStatic::OnTimer(nIDEvent);
}


/********************************************************************/
/*																	*/
/* Function name : DoScrollText										*/
/* Description   : Do scrolling text like in the movie 'Star Wars'	*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::DoScrollText(CDC *pDC)
{
	int nPosX =0;
	int nPosY =0;

	CDC memDC;
	CBitmap memBitmap;
	CFont *oldFont;

	memDC.CreateCompatibleDC(pDC);
	memBitmap.CreateCompatibleBitmap(pDC, m_rectClient.Width(), m_rectClient.Height());
	memDC.SelectObject(&memBitmap);
	memDC.SetBkColor(RGB(0,0,0));
	memDC.SetTextColor(RGB(0,255,0));
    memDC.SetBkMode(TRANSPARENT);

	oldFont = memDC.SelectObject(&m_Font);

	// black
	memDC.BitBlt(0, 0, m_rectClient.Width(), m_rectClient.Height(), NULL, 0, 0, BLACKNESS);
	
	// draw Credits on the hidden Picture
	for(int i=0; i < m_TextLines.GetSize(); i++)
	{
		// set position for this line
		CSize size = memDC.GetTextExtent(m_TextLines.GetAt(i));

		nPosY = m_nScrollPos + (i * size.cy);
		if (nPosY > 0)
		{
			nPosX = (m_rectClient.Width() / 2) - (size.cx / 2);

			if (nPosY >100)
			{
				memDC.SetTextColor(RGB(150, 0, 200));
			}
			else
			{
				// set fade color
				memDC.SetTextColor(RGB(nPosY, nPosY, nPosY));
			}
			
			
			// print text
			memDC.TextOut(nPosX, nPosY, m_TextLines.GetAt(i));
		}
		else
		{
			// start all over ...
			if (i == (m_TextLines.GetSize()-1))
			{
				m_nScrollPos = m_rectClient.Height();
			}
		}
	}

	int nWidth = m_rectClient.Width();
	int nHeight = m_rectClient.Height();

	// shrink text from bottom to top to create Star Wars effect
	for (int y=0; y <nHeight; y++)
	{
		double nScale = (double)y/(double)nHeight;
		int nOffset = (int)(nWidth - nWidth*nScale)/2;
		m_MainDC.StretchBlt(nOffset, y, (int)(nWidth*nScale), 1, &memDC, 0, y, nWidth, 1, SRCPAINT);
	}

	// restore the font
	memDC.SelectObject(oldFont);

	// move text up one pixel
	m_nScrollPos = m_nScrollPos - m_nScrollSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : SetScrollSpeed									*/
/* Description   : Set speed of scrolling							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::SetScrollSpeed(int nSpeed)
{
	m_nScrollSpeed = nSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : SetStarSpeed										*/
/* Description   : Set speed of the stars							*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::SetStarSpeed(int nSpeed)
{
	m_nStarsSpeed = nSpeed;
}


/********************************************************************/
/*																	*/
/* Function name : UpdateVersionInformation							*/
/* Description   : Show version information from resource.			*/
/*																	*/
/********************************************************************/
/*CString CStarWarsCtrl::GetVersionInformation(LPCTSTR lpszModuleName)
{
/*	CString strResult;
	BYTE		*pDataBlock = NULL;
	DWORD FAR	*translation;
	DWORD FAR	*buffer;     
	DWORD		dwHandle;
	UINT		nBytes;
	
	// WinAPI wants non-const arguments
	LPTSTR lpszExeName = const_cast<LPTSTR>(lpszModuleName); 

	char szName[512];       // StringFileInfo data block.

	// Get the actual size of the information block.
	nBytes = (UINT)GetFileVersionInfoSize(lpszExeName, &dwHandle);

	if (nBytes)
	{
		pDataBlock = new BYTE[nBytes];

		// Get the actual block for the version information
		if (GetFileVersionInfo(lpszExeName, dwHandle, nBytes, pDataBlock))
		{
			if (VerQueryValue(pDataBlock, _T("\\VarFileInfo\\Translation"), (VOID FAR * FAR *)&translation, (UINT FAR *)&nBytes)) 
			{
				// The File Version for this application
				wsprintf(szName, _T("\\StringFileInfo\\%04x%04x\\PrivateBuild"), LOWORD(*translation), HIWORD(*translation));

				if (VerQueryValue(pDataBlock, szName, (VOID FAR * FAR *)&buffer, (UINT FAR *)&nBytes)) 
				{
					strResult.Format((char far *)buffer);
				}
			}
			else 
			{
				// sorry ...
			}
		}
		if (pDataBlock)
			delete[] pDataBlock;
	}
	return strResult;
}*/


/********************************************************************/
/*																	*/
/* Function name : OnLButtonDown									*/
/* Description   : Go to our website...								*/
/*																	*/
/********************************************************************/
void CStarWarsCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // open URL in the browser.

	CStatic::OnLButtonDown(nFlags, point);
}
