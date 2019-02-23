// MyMusicPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include <Shlwapi.h>
#include "MusicPlayerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
////////////////////////////////////////////////////////////////////////////////////////////////
//�̺߳���
/************************************************************/
/*���ʱ��У׼�߳�											*/
/*�������壺												*/
BOOL		g_bLyricSwitch=TRUE;
/************************************************************/
DWORD WINAPI LyricsCheckThread(LPVOID lpParam)
{
	TRACE("�������߳�LyricsCheckThread\n");
	VERIFY(NULL!=lpParam);
	CMusicPlayerDlg* pDlg=(CMusicPlayerDlg*)lpParam;
	TStreamTime pos;
	long lTime=0;
	while(g_bLyricSwitch)
	{
		if(pDlg->LyricFileExist())
		{
			CMusicPlayerDlg::player->GetPosition(&pos);
			lTime=(pos.hms.minute*60+pos.hms.second)*1000+pos.hms.millisecond;
			SetLyricsTime(lTime);
		}
		Sleep(100);
	}
	TRACE(_T("�߳�LyricsCheckThread�����˳�\n"));
	return 0;
}
/************************************************************/
/*����ģʽ�л��߳�	                                        */
/*�������壺											    */
PLAYMODE	g_playMode=PLAYMODE::order_play;  //����ģʽ
BOOL		g_bModeThreadSwitch=TRUE;  //�߳̿���
/************************************************************/
DWORD WINAPI PlayModeSwitchThread(LPVOID lpParam)
{
	TRACE("�������߳�PlayModeSwitchThread\n");
	DWORD dwResult=0;
	try
	{
		CMusicPlayerDlg* pDlg=(CMusicPlayerDlg*)lpParam;
		if((NULL==lpParam)||(!::IsWindow(pDlg->m_hWnd)))
			throw   1;
		TStreamStatus status;
		while(g_bModeThreadSwitch)
		{
			//��ʼ���
			ENSURE(NULL!=CMusicPlayerDlg::player);
			if(CMusicPlayerDlg::m_bPlaying)
			{
				CMusicPlayerDlg::player->GetStatus(&status);
				if((!status.fPlay)&&(!status.fPause))
				{
					switch(g_playMode)
					{
					case PLAYMODE::order_play:
						{
							if(CMusicPlayerDlg::m_nowPlayIndex==\
								(pDlg->m_defPlaylist.GetCount()-1))
								CMusicPlayerDlg::m_nowPlayIndex=0;
							else
								CMusicPlayerDlg::m_nowPlayIndex++;
						}
						break;
					case PLAYMODE::rand_play:  //�������
						{
							int nCount=pDlg->m_defPlaylist.GetCount();
							srand(time(NULL));
							CMusicPlayerDlg::m_nowPlayIndex=rand()%nCount;	
						}
						break;
					case PLAYMODE::single_play:	//����ѭ������
						break;
					default:
						break;
					}
					pDlg->StartPlay();
				}
			}
			Sleep(100);
		}
	}
	catch(...)
	{
		_tprintf(_T("�߳�PlayModeSwitchThread�쳣\n"));
		dwResult=1;
	}
	TRACE(_T("�߳�PlayModeSwitchThread�����˳�!\n"));
	return dwResult;
}
volatile BOOL g_bDrawSwitch=TRUE;//�Ƿ����̣߳���������û��ͼƬʱ�����߳�
/************************************************************/
/*ʵ�ֶ�̬����
/*
/************************************************************/
DWORD WINAPI DrawMoveNoteThread(LPVOID pParam)
{
	TRACE("�������߳�DrawMoveNoteThread\n");
	RECT_DATA data[16];
	CMusicPlayerDlg* pDlg=(CMusicPlayerDlg*)pParam;
	CDC* pDC=pDlg->GetDC();
	while(g_bDrawSwitch)
	{
		static int flag=0;//�߶�
		for(int i=0;i<14;++i)
		{
			do
			{
				flag=rand()%78;
			}
			while(flag<2);
			data[i].rcBig.left=203+6*i;
			data[i].rcBig.top=112-flag;
			data[i].rcBig.right=207+6*i;
			data[i].rcBig.bottom=110;
			data[i].rcSmall.left=data[i].rcBig.left;
			data[i].rcSmall.top=data[i].rcBig.top-8;
			data[i].rcSmall.bottom=data[i].rcSmall.top+3;
			data[i].rcSmall.right=data[i].rcBig.right;
			pDC->FillSolidRect(data[i].rcBig,RGB(255,0,255));
			pDC->FillSolidRect(data[i].rcSmall,RGB(0,255,0));
		}
		Sleep(300);
	}
	pDC->DeleteDC();
	TRACE(_T("�߳�DrawMoveNoteThread�����˳�!\n"));
	return 0;
}
// HRESULT ShowPic(HDC hDC,CString lpstrFile,int x,int y, int nScrWidth, int nScrHeight)//��ָ��·���ļ����Ŵ���
// {
//     IPicture  *pPic;  
//     IStream   *pStm;  
//     BOOL      bResult;  
// 
//     HANDLE    hFile=NULL;  
//     DWORD     dwFileSize,dwByteRead;  
// 
//     //��Ӳ���е�ͼ���ļ�  
//     hFile=CreateFile(lpstrFile,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);  
//     if (hFile!=INVALID_HANDLE_VALUE)  
//     {  
//         dwFileSize=GetFileSize(hFile,NULL);//��ȡ�ļ��ֽ���  
//         if(dwFileSize==0xFFFFFFFF)  
//         {
//             CloseHandle(hFile);
//             return E_FAIL;  
//         }
//     }  
//     else  
//     {  
//         return E_FAIL;  
//     }  
// 
// 
//     //����ȫ�ִ洢�ռ�  
//     HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,dwFileSize);  
//     if(hGlobal==NULL)  
//         return E_FAIL;  
// 
//     LPVOID  pvData =GlobalLock(hGlobal);  
// 
//     if(pvData==NULL)//���������ڴ��  
//     {
//         GlobalFree(hGlobal);
//         return E_FAIL;  
//     }
//     ReadFile(hFile,pvData,dwFileSize,&dwByteRead,NULL);//���ļ������ڴ滺����  
//     CloseHandle(hFile);//�رմ򿪵��ļ�  
// 
//     GlobalUnlock(hGlobal);  
// 
//     CreateStreamOnHGlobal(hGlobal,TRUE,&pStm);  
// 
//     //װ��ͼ���ļ�  
//     bResult=OleLoadPicture(pStm,dwFileSize,TRUE,IID_IPicture,(LPVOID*)&pPic);  
//     GlobalFree(hGlobal);
//     if(FAILED(bResult))  
//         return E_FAIL;  
// 
//     long   hmWidth;//ͼƬ����ʵ���  
//     long   hmHeight;//ͼƬ����ʵ�߶�  
//     pPic->get_Width(&hmWidth);  
//     pPic->get_Height(&hmHeight);  
//     //��ͼ���������Ļ�ϣ��е���BitBlt��  
//     bResult=pPic->Render(hDC,x,y,nScrWidth,nScrHeight,0,hmHeight,hmWidth,-hmHeight,NULL);  
// // 	HBITMAP hBitmap=NULL;
// // 	pPic->get_Handle((OLE_HANDLE*)&hBitmap);
// // 	CFuncDC::SaveHBitmap(hBitmap,"c:\\save.bmp");
//     pPic->Release();  
//     if(SUCCEEDED(bResult))   
//         return   S_OK;   
//     else  
//         return   E_FAIL;  
// }




CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
, m_bMax(FALSE)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ABOUT, m_transparent);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_WM_SIZE()
	ON_STN_DBLCLK(IDC_ABOUT, &CAboutDlg::OnStnDblclickAbout)
END_MESSAGE_MAP()
BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_transparent.SetScrollSpeed(10);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAboutDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(IsWindow(m_transparent.GetSafeHwnd()))
	{
		GetClientRect(&client);
		m_transparent.MoveWindow(&client,TRUE);
	}
	// TODO: �ڴ˴������Ϣ����������
}

void CAboutDlg::OnStnDblclickAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bMax)
	{
		MoveWindow(&client,TRUE);
		m_bMax=FALSE;
	}
	else
	{
		int mX=::GetSystemMetrics(SM_CXSCREEN);
		int mY=::GetSystemMetrics(SM_CYSCREEN);
		MoveWindow(0,0,mX,mY,TRUE);
		m_bMax=TRUE;
	}
}
// CMyMusicPlayerDlg �Ի���



ZPlay* CMusicPlayerDlg::player=NULL;
int CMusicPlayerDlg::m_nowPlayIndex=-1;
BOOL CMusicPlayerDlg::m_bPlaying=FALSE;
CMusicPlayerDlg::CMusicPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMusicPlayerDlg::IDD, pParent)
	, CErrorLog(_T("CMusicPlayerDlg"))
	, m_bMiniStyle(FALSE)
	, m_bCaptureFlag(FALSE)
	, m_bQuietVoice(FALSE)
	, m_bTimeOver(FALSE)
	, m_strPictruePath(_T(""))
	, m_rollFlag(173)
	, m_IsGet(FALSE)
	, m_index(0)
//	, m_bDrawMiniText(FALSE)
	, m_bShowLyrics(TRUE)
	, m_bLyricExist(FALSE)
	, m_iIndex(0)
	, m_bLockLyrics(FALSE)
	, m_strBmpName(_T(""))
	,m_strModulePath(_T(""))
	,m_hFont(NULL)
	,m_pGraphic(NULL)
	,m_pBackBitmap(NULL)
	,m_pAuthorImage(NULL)
	,m_strTempBackImage(_T(""))
	,m_strSelectBackImage(_T(""))
	, m_bShowChangeClothDlg(FALSE)
	,m_bAlphaValue(255)
{
	m_strTitle=_T("���֣������������");
	player=CreateZPlay();
	m_uCurrentMinute=m_uCurrentSecond=m_uMinuteCount=m_uSecondCount=0;
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
	ZeroMemory(&id3_infoEx,sizeof(TID3InfoExW));
}

void CMusicPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXIT, m_btnExit);
	DDX_Control(pDX, IDC_HIDE, m_btnHide);
	DDX_Control(pDX, IDC_MINI, m_btnMini);
	DDX_Control(pDX, IDC_PREV, m_btnPrev);
	DDX_Control(pDX, IDC_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_NEXT, m_btnNext);
	//	DDX_Control(pDX, IDC_TIME, m_ctrlTime);
	DDX_Control(pDX, IDC_BUTTONVOICE, m_btnProcess);
	DDX_Control(pDX, IDC_ADD, m_btnAdd);
	DDX_Control(pDX, IDC_LIST1, m_defPlaylist);
	DDX_Control(pDX, IDC_VOICE, m_btnVoiceQuiet);
	DDX_Control(pDX, IDC_SETVOICE, m_btnVoiceSetting);
	DDX_Control(pDX, IDC_PLAYMODE, m_btnPlayMode);
	//	DDX_Control(pDX, IDC_LIST3, m_enjoyPlaylist);
	DDX_Control(pDX, IDC_BUTTON1, m_btnDefaultList);
	//	DDX_Control(pDX, IDC_BUTTON2, m_btnEnjoyList);
	DDX_Control(pDX, IDC_BUTTON3, m_btnFeedBack);
	DDX_Control(pDX, IDC_BUTTON_CLOTH, m_btnCloth);
}

BEGIN_MESSAGE_MAP(CMusicPlayerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_MESSAGE(MYWM_NOTIFYICON,CMusicPlayerDlg::OnNotifyIcon)
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_ICON_32772, &CMusicPlayerDlg::OnIconExit)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_EXIT, &CMusicPlayerDlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_HIDE, &CMusicPlayerDlg::OnBnClickedHide)
	ON_BN_CLICKED(IDC_MINI, &CMusicPlayerDlg::OnBnClickedMini)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_ADD_32775, &CMusicPlayerDlg::OnAddFile)
	ON_COMMAND(ID_ADD_32776, &CMusicPlayerDlg::OnAddFolder)
	ON_BN_CLICKED(IDC_ADD, &CMusicPlayerDlg::OnBnClickedAdd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VOICE, &CMusicPlayerDlg::OnBnClickedVoice)
	ON_BN_CLICKED(IDC_PREV, &CMusicPlayerDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_PLAY, &CMusicPlayerDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_NEXT, &CMusicPlayerDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PLAYMODE, &CMusicPlayerDlg::OnBnClickedPlaymode)
	ON_COMMAND(ID_MODE_32777, &CMusicPlayerDlg::OnModeOnly)
	ON_COMMAND(ID_MENU_ONLY, &CMusicPlayerDlg::OnModeOnly)
	ON_COMMAND(ID_MODE_32778, &CMusicPlayerDlg::OnModeOrder)
	ON_COMMAND(ID_MENU_ORDER, &CMusicPlayerDlg::OnModeOrder)
	ON_COMMAND(ID_MODE_32779, &CMusicPlayerDlg::OnModeRand)
	ON_COMMAND(ID_MENU_RAND, &CMusicPlayerDlg::OnModeRand)
	ON_COMMAND(ID_MENU_SCAP,&CMusicPlayerDlg::OnScreenCapture)
	ON_COMMAND(ID_ICON_32771, &CMusicPlayerDlg::OnIconAbout)
	ON_COMMAND(ID_ADD_32780, &CMusicPlayerDlg::OnAddDeleteAll)
	ON_COMMAND(ID_32785, &CMusicPlayerDlg::On32785Play)
	ON_COMMAND(ID_32783, &CMusicPlayerDlg::On32783Prev)
	ON_COMMAND(ID_32784, &CMusicPlayerDlg::On32784Next)
	ON_COMMAND(ID_ICON_32786, &CMusicPlayerDlg::OnIconSetAttributes)
	ON_COMMAND(ID_32789, &CMusicPlayerDlg::On32789)
	ON_COMMAND(ID_32788, &CMusicPlayerDlg::On32788)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
//	ON_BN_CLICKED(IDC_BUTTON2, &CMusicPlayerDlg::OnBnClickedMyLike)
//	ON_BN_CLICKED(IDC_BUTTON1, &CMusicPlayerDlg::OnBnClickedList1)
	ON_COMMAND(ID_32791, &CMusicPlayerDlg::OnShowLyricsDlg)
	ON_COMMAND(ID_32793, &CMusicPlayerDlg::OnSetLyricsColor)
	ON_COMMAND(ID_32794, &CMusicPlayerDlg::OnSetLyricsFont)
	ON_COMMAND(ID_32795, &CMusicPlayerDlg::OnLyricsLock)
	ON_MESSAGE(WM_HOTKEY,CMusicPlayerDlg::OnHotKey)
	ON_BN_CLICKED(IDC_BUTTON3, &CMusicPlayerDlg::OnSendEmail)
	ON_BN_CLICKED(IDC_BUTTON_CLOTH, &CMusicPlayerDlg::OnChangeCloth)
END_MESSAGE_MAP()


// CMyMusicPlayerDlg ��Ϣ�������

BOOL CMusicPlayerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	srand((UINT)time(NULL));
 	SetWindowLong(m_hWnd,GWL_EXSTYLE,GetWindowLong(m_hWnd,GWL_EXSTYLE)|0x80000);
	SetWindowText(_T("MusicPlayer"));
	m_strModulePath.Append(GetAppPath().c_str());
	m_hFont=::CreateFont(12, 6, 0, 0, 500,
		FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, 
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, 
		DEFAULT_PITCH|FF_SWISS, _T("����"));
	CreateNotifyIcon();
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);
	ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW, SWP_DRAWFRAME);
	SetTimer(1,1000,NULL);// ��ʾʱ��
	SetTimer(3,100,NULL);//����Ƿ���������
	SetTimer(5,400,NULL);//ˢ��ͼƬ����
	player->SetMasterVolume(100,100);//�����ⲿ�豸����Ϊ���ֵ
	m_uPlayVolume=100;
	m_bMouseOverVoice=FALSE;
	m_bLockLyrics=InitLyricsDlg();
	RegisterHotKeys();
	CRect rect;
	GetClientRect(&rect);  
	m_nWidth=rect.Width();
	m_nHeight=rect.Height();
	CRgn rg;   
    rg.CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, 10, 10);   
	SetWindowRgn(rg, FALSE);
	m_playList.reserve(100);
	InitButtons();
	InitFile();
	SetLayeredWindowAttributes(0xffffff,m_bAlphaValue	,LWA_ALPHA);
	DrawPictrue(TRUE);
	//��������ģʽ����߳�
	StartPlayModeThread();
	//�����϶������ļ���ͼ����Ϣ
	CString strCmd(theApp.m_lpCmdLine);
	if(strCmd!=_T(""))
	{
		if(strCmd.GetAt(0)=='\"')
		{
			strCmd.Delete(0);
			strCmd.Delete(strCmd.GetLength()-1);
		}
		if(IsSupportFile(strCmd))
		{
			m_playList.push_back(strCmd);
			m_defPlaylist.AddString(GetShortName(strCmd));
			m_nowPlayIndex=m_playList.size()-1;
			StartPlay();
		}
	}
	m_strTempBackImage=m_strSelectBackImage;
	m_pBackBitmap=Gdiplus::Bitmap::FromFile(m_strTempBackImage.GetBuffer());
	if(0==m_pBackBitmap->GetHeight())
		m_pBackBitmap=Gdiplus::Bitmap::FromResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_BACK1));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMusicPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CMusicPlayerDlg::OnPaint()
{
	EXCEPTION_INFO ei;
	try
	{
		if (IsIconic())
		{
			CPaintDC dc(this); // ���ڻ��Ƶ��豸������

			SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

			// ʹͼ���ڹ����������о���
			CRect rect;
			GetClientRect(&rect);
			int cxIcon = GetSystemMetrics(SM_CXICON);
			int cyIcon = GetSystemMetrics(SM_CYICON);
			int x = (rect.Width() - cxIcon + 1) / 2;
			int y = (rect.Height() - cyIcon + 1) / 2;

			// ����ͼ��
			dc.DrawIcon(x, y, m_hIcon);
		}
		else
		{
			CPaintDC dc(this);
			if(NULL==m_hMemDC)
			{
				if(NULL==(m_hMemDC=::CreateCompatibleDC(dc.m_hDC)))
				{
					ei=FillExceptionInfo(_T("CreateCompatibleDC����ʧ�ܣ�"),__LINE__-2,__FILE__,::GetLastError());
					throw 1;
				}
				if(NULL==(m_hMemBitmap=::CreateCompatibleBitmap(dc.m_hDC,m_nWidth,m_nHeight)))
				{
					ei=FillExceptionInfo(_T("CreateCompatibleBitmap����ʧ�ܣ�"),__LINE__-2,__FILE__,::GetLastError());
					throw 1;
				}
				::SelectObject(m_hMemDC,m_hMemBitmap);
			}
			if(NULL==m_pGraphic)
				m_pGraphic=Gdiplus::Graphics::FromHDC(m_hMemDC);
			m_pGraphic->DrawImage(m_pBackBitmap,Gdiplus::RectF(0,0,m_nWidth,m_nHeight),\
				0,0,m_pBackBitmap->GetWidth(),m_pBackBitmap->GetHeight(),Gdiplus::UnitPixel);
			if(m_IsGet)
				DrawMyTextA(m_hMemDC);//�������ȴ��ھ�������ʱ����
			else
				DrawMyText(m_hMemDC);//�������
			//���Ʋ��Ž���ʱ��
			::SetTextColor(m_hMemDC,0xff00ff);
			HFONT hOldFont=(HFONT)::SelectObject(m_hMemDC,m_hFont);
			static RECT rcTime={6,94,194,110};
			::DrawText(m_hMemDC,m_strProgressTime,m_strProgressTime.GetLength(),&rcTime,DT_VCENTER);
			::SelectObject(m_hMemDC,hOldFont);
			if(m_bPlaying)
			{
				if(!g_bDrawSwitch)//��ͼƬ�Ͱ�ͼƬ����ȥ
				{
					static CString strBmp,strBmpName;
					if(strBmpName!=m_strBmpName)
					{
						strBmpName=m_strBmpName;
						strBmp=m_strPictruePath+_T("\\")+m_strBmpName+_T(".jpg");
						if(NULL!=m_pAuthorImage)
						{
							delete m_pAuthorImage;
							m_pAuthorImage=NULL;
						}
						m_pAuthorImage=Gdiplus::Image::FromFile(strBmp);
					}
					m_pGraphic->DrawImage(m_pAuthorImage,Gdiplus::RectF(203,28,80,82),\
						0,0,m_pAuthorImage->GetWidth(),m_pAuthorImage->GetHeight(),Gdiplus::UnitPixel,NULL);
					//ShowPic(m_hMemDC,strBmp,203,28,80,82);
				}
			}
// 			static BLENDFUNCTION bf;
// 			memset(&bf,0,sizeof(bf));
// 			bf.BlendOp=AC_SRC_OVER;
// 			bf.SourceConstantAlpha=255;
// 			BOOL bResult=AlphaBlend(m_hMemDC,0,0,m_rcClient.Width(),m_rcClient.Height(),\
// 				dc.m_hDC,0,0,m_rcClient.Width(),m_rcClient.Height(),bf);
			::BitBlt(dc.m_hDC,0,0,m_nWidth,m_nHeight,\
				m_hMemDC,0,0,SRCCOPY);
		}
	}
	catch(...)
	{
		ei.tstrExceptionFunc=_T("OnPaint");
		WriteErrorLog(&ei);
	}
	CDialog::OnPaint();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMusicPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMusicPlayerDlg::CreateNotifyIcon(CString strTip)
{
	nd.cbSize=sizeof(NOTIFYICONDATA);
	nd.hWnd=m_hWnd;
	nd.uID=IDI_ICON1;
	nd.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP; 
    nd.uCallbackMessage=MYWM_NOTIFYICON;
    nd.hIcon = m_hIcon; 
	wcscpy_s(nd.szTip,strTip.GetBuffer());
	nd.szTip[_tcslen(nd.szTip)] = '\0';
	Shell_NotifyIcon(NIM_ADD, &nd);//
}

void CMusicPlayerDlg::DeleteNotifyIcon(void)
{
//	NOTIFYICONDATA nd;
	nd.cbSize=sizeof(NOTIFYICONDATA);
	nd.hIcon=m_hIcon;
	nd.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP;
	nd.hWnd=m_hWnd;
	nd.uCallbackMessage=MYWM_NOTIFYICON;
	nd.uID=IDI_ICON1;
	Shell_NotifyIcon(NIM_DELETE,&nd); 
}
LRESULT CMusicPlayerDlg::OnNotifyIcon(WPARAM wParam,LPARAM lParam)
{
	if(lParam==WM_LBUTTONDOWN)
	{
		UINT mode=IsWindowVisible()?SW_HIDE:SW_SHOW;
		ShowWindow(mode);
		return 1;
	}
	else if(lParam==WM_RBUTTONDOWN)
	{
		ShowMainMenu();
		return 2;
	}
	else
		return 0;
}

void CMusicPlayerDlg::OnIconExit()
{
	// TODO: �ڴ���������������
	//PostQuitMessage(WM_QUIT);
	SendMessage(WM_CLOSE);
}
void CMusicPlayerDlg::InitFile()//��ʼ������������ȡ�ļ���
{
	SetPictruePath(m_strModulePath+_T("\\MusicPictrue"));
	CString str=m_strModulePath+_T("\\Lyrics");
	CreateDirectory(str,NULL);
	str=m_strModulePath+_T("\\AppData");
	CreateDirectory(str,NULL);
	CFileFind findFile;
	if(!findFile.FindFile(GetPictruePath()))
	{
		if(!CreateDirectory(GetPictruePath(),NULL))
		{
			DWORD dwError=GetLastError();
			CString strError;
			strError.Format(_T("������Ϣ:%s"),dwError);
			AfxMessageBox(strError,MB_OK|MB_ICONERROR);
		}
	}
	ReadConfig();
	switch(g_playMode)//Ĭ��Ϊ2��˳�򲥷�
	{
	case single_play://��������
		m_btnPlayMode.Init(IDB_ONLY1,IDB_ONLY2,_T("����ģʽ"));
		break;
	case order_play://˳�򲥷�
		m_btnPlayMode.Init(IDB_ORDER1,IDB_ORDER2,_T("����ģʽ"));
		break;
	case rand_play://�������
		m_btnPlayMode.Init(IDB_RAND1,IDB_RAND2,_T("����ģʽ"));
		break;
	default:
		g_playMode=order_play;
		m_btnPlayMode.Init(IDB_ORDER1,IDB_ORDER2,_T("����ģʽ"));
		break;
	}
}
LRESULT CMusicPlayerDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���
	switch(message)
	{
	case WM_CLOSE:
		{
			g_bDrawSwitch=FALSE;
			g_bModeThreadSwitch=FALSE;
			g_bLyricSwitch=FALSE;
			ShowWindow(SW_HIDE);
			ShowLyricsDlg(FALSE);
			WriteListFile();
			ReleaseChangeClothDlg();
			ReleaseAttributeDlg();
			ReleaseDeleteDlg();
			ReleaseInfoDlg();
			Sleep(300);
			DeleteNotifyIcon();
			ReleaseLyricsDlg();
			player->Stop();
			player->Release();
			Release();
			PostQuitMessage(1);
			break;
		}
	case WM_DELETE_DIALOG:
		{
			switch((int)wParam)
			{
			case 1:	//ɾ��
				{
					DeleteSelectItem();
					ReBeginDrawText();
				}
			case 2:
				ReleaseDeleteDlg();
				break;
			default:
				break;
			}
			return TRUE;
		}
	case WM_DROPFILES:
		{
			HDROP hDropInfo;
			hDropInfo=(HDROP)wParam;
			GetDropFiles(hDropInfo);
			DragFinish(hDropInfo);
			::DeleteObject(hDropInfo);
			return TRUE;
		}
	case WM_LISTBOX_MESSAGE	:
		{   //�����б��Ҽ��˵���Ϣ�����ﴦ��
			switch((int)wParam)
			{
			case 1:	//�鿴��ʣ����������ʾ�Ի���
				ShowLyricFile();
				break;
			case 2://�鿴������Ϣ
				{
					CString strPath=m_playList[m_defPlaylist.GetCurSel()];
					//MessageBox(strPath);
					std::wstring ws(strPath.GetBuffer());
					ShowInfoDlg(ws);
					break;
				}
			case 3://ɾ���ڵ���Ϣ
				{
					CString strFullPath=m_playList[m_defPlaylist.GetCurSel()];
					std::wstring ws(strFullPath.GetBuffer());
					ShowDeleteDlg(ws);
					break;
				}
			case 4://˫���ڵ�
				{
					int nCurSel=m_defPlaylist.GetCurSel();
					int nCount=m_defPlaylist.GetCount();
					if(PathFileExists(m_playList[nCurSel]))
					{
						player->Stop();
						m_bPlaying=FALSE;
						Sleep(200);
						m_nowPlayIndex=nCurSel;
						StartPlay();
					}
					else
					{//�ļ������ڣ������
						std::vector<CString>::iterator itor=m_playList.begin()+nCurSel;
						m_playList.erase(itor);
						m_defPlaylist.DeleteString(nCurSel);
						for(int i=nCurSel;i<m_defPlaylist.GetCount();++i)
							m_defPlaylist.DeleteString(nCurSel);
						AddPlayListToPlayer(nCurSel);
					}
					ReBeginDrawText();
					break;
				}
			default:
				break;
			}
			return TRUE;
		}
	case WM_SETATTRIBUTE_MESSAGE:
		{
			switch(wParam)
			{
			case 1://������
				{
					UINT uRightVoice=0;
					player->GetPlayerVolume(NULL,&uRightVoice);
					player->SetPlayerVolume((UINT)lParam,uRightVoice);
				}
				break;
			case 2://������
				{
					UINT uLeftVoice=0;
					player->GetPlayerVolume(&uLeftVoice,NULL);
					player->SetPlayerVolume(uLeftVoice,(UINT)lParam);
				}
				break;
			case 3://������
				{
					player->SetRate((UINT)lParam);
					break;
				}
			case 4://����
				player->SetPitch((UINT)lParam);
				break;
			case 5://�����ٶ�
				player->SetTempo((UINT)lParam);
				break;
			default:
				break;
			}
			return TRUE;
		}
	case WM_SLIDER_SETPROGRESS:
		{
			TStreamTime seekTo;
			seekTo.sec=(unsigned int)wParam;
			player->Seek(tfSecond,&seekTo,smFromBeginning);
			m_btnPlay.ReInit(IDB_NORMAL_PLAY1,IDB_OVER_PLAY1,_T("��ͣ"));
			return TRUE;
		}
	case WM_SLIDER_SETVOICE:
		{
			player->SetPlayerVolume((UINT)wParam,(UINT)wParam);
			return TRUE;
		}
	case WM_IMAGECTRL_MESSAGE:
		{
			switch(wParam)
			{
			case 1://��ʱ����Ƥ��
				{
					LPWSTR pPath=(LPWSTR)lParam;
					m_strTempBackImage.Format(_T("%s"),pPath);
					ChangeBack();
					break;
				}
			case 2://ȡ������Ƥ��
				{
					m_strTempBackImage=m_strSelectBackImage;
					ChangeBack();
					break;
				}
			case 3://ѡ��Ƥ��
				{
					LPWSTR pPath=(LPWSTR)lParam;
					m_strTempBackImage.Format(_T("%s"),pPath);
					m_strSelectBackImage=m_strTempBackImage;
					ChangeBack();
					break;
				}
			case 4://����͸����
				{
					m_bAlphaValue=(BYTE)lParam;
					SetLayeredWindowAttributes(0xffffff,m_bAlphaValue,LWA_ALPHA);
				}
			default:
				break;
			}
			return TRUE;
		}
	default:
		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}

void CMusicPlayerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonDown(nFlags, point);
	SetFocus();
	if(HideChangeClothDlg())
		m_bShowChangeClothDlg=FALSE;
	PostMessage(WM_NCLBUTTONDOWN, 
		 HTCAPTION,       
         MAKELPARAM(point.x,   point.y)); 
}

void CMusicPlayerDlg::InitButtons(void)
{
	m_btnExit.MoveWindow(270,0,16,16);
	m_btnHide.MoveWindow(254,0,16,16);
	m_btnMini.MoveWindow(238,0,16,16);
	m_btnCloth.MoveWindow(222,0,16,16);
	m_btnPrev.MoveWindow(35,2,25,25);
	m_btnPlay.MoveWindow(75,2,25,25);
	m_btnNext.MoveWindow(115,2,25,25);
	m_btnAdd.MoveWindow(252,430,25,20);
	m_btnVoiceQuiet.MoveWindow(155,2,25,25);
	m_btnPlayMode.MoveWindow(247,112,30,20);
	m_btnProcess.MoveWindow(16,67,168,5);
	m_btnVoiceSetting.MoveWindow(180,20,100,5);
	/////////////////////////////////////////
	m_btnExit.Init(IDB_NORMAL_EXIT,IDB_OVER_EXIT,_T("�ر�"));
	m_btnHide.Init(IDB_NORMAL_HIDE,IDB_OVER_HIDE,_T("����"));
	m_btnMini.Init(IDB_NORMAL_MINI1,IDB_OVER_MINI1,_T("MINIģʽ"));
	m_btnCloth.Init(IDB_NORMAL_CLOTH,IDB_OVER_CLOTH,_T("����"));
	m_btnPrev.Init(IDB_NORMAL_PREV,IDB_OVER_PREV,_T("��һ��"));
	m_btnPlay.Init(IDB_NORMAL_PLAY2,IDB_OVER_PLAY2,_T("����"));
	m_btnNext.Init(IDB_NORMAL_NEXT,IDB_OVER_NEXT,_T("��һ��"));
	m_btnAdd.Init(IDB_NORMAL_ADD,IDB_OVER_ADD,_T("��Ӳ˵�"));
	m_btnVoiceQuiet.Init(IDB_NORMAL_VOICE,IDB_OVER_VOICE,_T("����"));
	m_btnFeedBack.Init(_T("��������"),_T("��������ʼ�"));
	m_btnFeedBack.SetBkColor(RGB(204,102,204));
	m_btnProcess.InitCtrl(IDB_SLIDER_PROGRESS,_T("������"));
	m_strProgressTime=_T("��ǰ���ȣ�00:00   ��ʱ�䣺00:00");
	m_btnVoiceSetting.InitCtrl(IDB_SLIDER_VOICE,_T("��������"));
	m_btnVoiceSetting.SetBkColor(RGB(255,100,0));
	m_btnVoiceSetting.ShowWindow(SW_HIDE);
	m_btnDefaultList.Init(IDB_NORMAL_LIST11,IDB_OVER_LIST1,_T("Ĭ���б�"));
//	m_btnEnjoyList.Init(IDB_NORMAL_LIST2,IDB_OVER_LIST2,_T("�ղ��б�"));
	m_defPlaylist.MoveWindow(20,137,250,292);
	m_defPlaylist.ShowWindow(SW_SHOW);
//	m_enjoyPlaylist.ShowWindow(SW_HIDE);
//	m_bPlayListFlag=FALSE;
}

void CMusicPlayerDlg::OnBnClickedExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	SendMessage(WM_CLOSE);
}

void CMusicPlayerDlg::OnBnClickedHide()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}

void CMusicPlayerDlg::OnBnClickedMini()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	if(m_bMiniStyle)//��������ģʽ
	{
		MoveWindow(rc.left,rc.top,303,455);
		m_btnMini.SetBitmap(IDB_NORMAL_MINI1,IDB_OVER_MINI1);
		m_btnMini.SetToolTipText(_T("MINIģʽ"));
		m_bMiniStyle=FALSE;
	}
	else//����MINIģʽ
	{
		MoveWindow(rc.left,rc.top,303,112);//27
		m_btnMini.SetBitmap(IDB_NORMAL_MINI2,IDB_OVER_MINI2);
		m_btnMini.SetToolTipText(_T("����ģʽ"));
		m_bMiniStyle=TRUE;
	}
	//Invalidate();
}

BOOL CMusicPlayerDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//pDC->FillSolidRect(&m_rcClient,0XFFFFFF);
	//Invalidate(FALSE);
	//UpdateWindow();
	return TRUE;
	//return CDialog::OnEraseBkgnd(pDC);
}
void CMusicPlayerDlg::OnAddFile()
{
	// TODO: �ڴ���������������
	CString strFilter;
	strFilter=_T("����֧���ļ�(*.mp3,*.wav,*.wma,*.ogg,*.ac3)|*.mp3;*.wav;*.wma;*.ogg;*.ac3||");
    CFileDialog fdlg(TRUE,NULL,NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT| OFN_FILEMUSTEXIST ,strFilter);
	fdlg.m_ofn.lpstrTitle=_T("��ѡ�������ļ���������ͬʱѡ��100���ļ�");
	fdlg.m_ofn.nMaxFile=100*MAX_PATH;//���ͬʱѡ��100���ļ�
	fdlg.m_ofn.lpstrFile=new TCHAR[fdlg.m_ofn.nMaxFile];
	RtlZeroMemory(fdlg.m_ofn.lpstrFile,fdlg.m_ofn.nMaxFile*(sizeof(TCHAR)));
	if(fdlg.DoModal()==IDOK)
	{
		CString strFormat,strFileName;
		int count=0;
		POSITION   pos  =  fdlg.GetStartPosition(); 
        while(pos!=NULL)
        {
            strFileName = fdlg.GetNextPathName(pos);
			m_playList.push_back(strFileName);
			count++;
        }
		AddPlayListToPlayer(m_playList.size()-count);
	}
}

void CMusicPlayerDlg::OnAddFolder()
{
	// TODO: �ڴ���������������
	LPMALLOC pMalloc;
	if(SHGetMalloc(&pMalloc)==NOERROR)
	{
		BROWSEINFO  bi;
		wchar_t szBuffer[MAX_PATH];
		LPITEMIDLIST pidl;
         
		bi.hwndOwner=GetSafeHwnd();
		bi.pidlRoot=NULL;
		bi.pszDisplayName=szBuffer;
		bi.lpszTitle=TEXT("ѡ���ļ���");
		bi.ulFlags = BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		bi.lParam=0;

		pidl=SHBrowseForFolder(&bi);

		if(pidl!=NULL)
		{
			if(SHGetPathFromIDList(pidl,szBuffer))
			{
				m_defPlaylist.SetRedraw(FALSE);
				AddFolderFiles(szBuffer);
				m_defPlaylist.SetRedraw(TRUE);
				m_defPlaylist.RedrawWindow();
			}
			pMalloc->Free(pidl);
		}
		pMalloc->Release();
	}
}

void CMusicPlayerDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint pt;
	GetCursorPos(&pt);
	CMenu menu,*pMenu;
	menu.LoadMenuW(IDR_MENU3);
	pMenu=menu.GetSubMenu(0);
	if(m_defPlaylist.GetCount()==0)
		pMenu->ModifyMenuW(2,MF_BYPOSITION|MF_GRAYED,ID_ADD_32780,_T("����б�"));
	else
		pMenu->ModifyMenuW(2,MF_BYPOSITION,ID_ADD_32780,_T("����б�"));
	pMenu->TrackPopupMenu(TPM_LEFTBUTTON,pt.x,pt.y,this);
	pMenu=NULL;
}

CString CMusicPlayerDlg::GetShortName(const CString& strFullName)
{
	CString strResult=_T("");
	int nPos=strFullName.ReverseFind('\\');
	if(-1!=nPos)
	{
		int nLength=strFullName.GetLength()-nPos-1;
		strResult=strFullName.Right(nLength);
		strResult=strResult.Left(nLength-4);
	}
	return strResult;
}

// ��ʼ�����ļ�
void CMusicPlayerDlg::StartPlay(void)
{
	if(!g_bModeThreadSwitch)
		StartPlayModeThread();
	player->Stop();
	CString strPlayFilePath=m_playList[m_nowPlayIndex];
	int result = player->OpenFileW(strPlayFilePath, sfAutodetect);
	int nPos=strPlayFilePath.ReverseFind('\\');
	m_strTitle=strPlayFilePath.Right(strPlayFilePath.GetLength()-nPos-1);
	m_strTitle=m_strTitle.Left(m_strTitle.GetLength()-4);
    if(result == 0)
    {
		wchar_t* cError=player->GetErrorW();
		m_defPlaylist.DeleteString(m_nowPlayIndex);
		m_nowPlayIndex --;
		OnBnClickedNext();
		//MessageBox(cError,_T("������Ϣ:"),MB_OK|MB_ICONERROR);
		return;
    }
	player->Play();
	m_defPlaylist.SetCurSel(m_nowPlayIndex);
	m_defPlaylist.RedrawWindow();
	if(player->LoadID3ExW(&id3_infoEx,1))
	{
		if(id3_infoEx.Picture.PicturePresent!=0)//��ͼ
		{
			if(id3_infoEx.Artist)
				m_strBmpName.Format(_T("%s-%s"),id3_infoEx.Artist,id3_infoEx.Album);
			else
			{
				static UINT COUNT=0;
				m_strBmpName.Format(_T("δ֪%06d"),COUNT);
			}
			m_strBmpName.Remove('/');
// 			m_strBmpName.Remove('\\');
// 			m_strBmpName.Remove(':');
// 			m_strBmpName.Remove('*');
// 			m_strBmpName.Remove('?');
			CString strFilePath=m_strPictruePath+_T("\\")+m_strBmpName+_T(".jpg");
			if(!PathFileExists(strFilePath))//�ļ��������򴴽�
			{
				BYTE* pData=(BYTE*)id3_infoEx.Picture.PictureData;
				if(!id3_infoEx.Picture.CanDrawPicture)//������λͼ���
					pData++;
				FILE* fp=_tfopen(strFilePath,_T("wb"));
				if(fp)
				{
					fwrite(pData,id3_infoEx.Picture.PictureDataSize,1,fp);
					fclose(fp);
				}
				else
				{
					CString strError;
					strError.Format(_T("д���ļ�ʧ�ܣ������룺%d"),GetLastError());
					MessageBox(strError);
				}

			}
			DrawPictrue(FALSE);
			KillTimer(5);
		}
		else//��ͼ
		{
			if(!g_bDrawSwitch)
			{
				DrawPictrue(TRUE);
				SetTimer(5,500,NULL);
			}
		}
	}
	else//��ȡ��Ϣʧ��
	{
	}
	InvalidateRect(CRect(200,26,285,110));
	m_bPlaying=TRUE;
	TStreamInfoW stream_info;
	player->GetStreamInfoW(&stream_info);
	m_uMinuteCount=stream_info.Length.hms.minute;
	m_uSecondCount=stream_info.Length.hms.second;
	m_btnProcess.SetTotalSecond(m_uMinuteCount*60+m_uSecondCount);
	m_btnProcess.SetCurPos(0);
	m_btnProcess.Invalidate();
	m_btnPlay.ReInit(IDB_NORMAL_PLAY1,IDB_OVER_PLAY1,_T("��ͣ"));
	CString strLyricsName=m_strModulePath+_T("\\Lyrics\\")+m_strTitle+_T(".lrc");
	if(PathFileExists(strLyricsName))//��ʴ���
	{
		m_bLyricExist=TRUE;
		g_bLyricSwitch=TRUE;
		HANDLE hThread=::CreateThread(NULL,0,LyricsCheckThread,this,0,NULL);
		::CloseHandle(hThread);
		std::wstring ws;
		ws.append(strLyricsName.GetBuffer());
		SendLyricsMsg(ws);
	}
	else//����ļ�������
	{
		g_bLyricSwitch=FALSE;
		Sleep(100);
		m_bLyricExist=FALSE;
		NoLyricsFile();
	}
	DeleteNotifyIcon();
	CreateNotifyIcon(m_strTitle);
}

void CMusicPlayerDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(1==nIDEvent)
	{
		if(!m_IsGet)
		{
			m_rollFlag-=10;
			if(m_rollFlag<=17)
				m_IsGet=TRUE;
		}
		else
		{
			m_index-=1;
			if(m_index==0)
			{
				m_rollFlag=173;
				m_IsGet=FALSE;
			}
		}
		InvalidateRect(CRect(0,40,173,59));
		if(m_bPlaying)
		{
			TStreamTime pos;
			player->GetPosition(&pos);
			m_uCurrentMinute=pos.hms.minute;
			m_uCurrentSecond=pos.hms.second;
			m_strProgressTime.Format(_T("��ǰ���ȣ�%02u:%02u   ��ʱ�䣺%02u:%02u"),
				m_uCurrentMinute,m_uCurrentSecond,m_uMinuteCount,m_uSecondCount);
			InvalidateRect(CRect(6,94,194,110));
			float rate=((float)(m_uCurrentMinute*60+m_uCurrentSecond))/(float)(m_uMinuteCount*60+m_uSecondCount);
			m_btnProcess.SetRatio(rate);
			m_btnProcess.Invalidate();
		}
	}
	if(3==nIDEvent)
	{
		static CRect rc1(155,2,180,27),rc2(180,20,280,25);
		CWnd* pWnd=NULL;
		if(IsCursorInRect(rc1))
		{
			m_btnVoiceSetting.ShowWindow(SW_SHOW);
			m_bMouseOverVoice=TRUE;
			SetTimer(4,600,NULL);
			m_bTimeOver=FALSE;
		}
		else
		{
			if(!m_bTimeOver)
			{
				if(IsCursorInRect(rc2))
				{
					m_btnVoiceSetting.ShowWindow(SW_SHOW);
					SetForegroundWindow();
					m_bMouseOverVoice=TRUE;
					SetTimer(4,600,NULL);
				}
			}
			else
				KillTimer(4);
		}
	}
	if(4==nIDEvent)
	{
		m_btnVoiceSetting.ShowWindow(SW_HIDE);
		m_bMouseOverVoice=FALSE;
		m_bTimeOver=TRUE;
	}
	if(5==nIDEvent)//ˢ��ͼƬ��ʾ����
	{
		InvalidateRect(CRect(200,26,285,110));
	}
	CDialog::OnTimer(nIDEvent);
}

void CMusicPlayerDlg::OnBnClickedVoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_bQuietVoice)
	{
		player->SetPlayerVolume(m_uPlayVolume,m_uPlayVolume);
		m_btnVoiceQuiet.SetBitmap(IDB_NORMAL_VOICE,IDB_OVER_VOICE);
		m_btnVoiceQuiet.SetToolTipText(_T("����"));
		m_bQuietVoice=FALSE;
	}
	else
	{
		player->GetPlayerVolume(&m_uPlayVolume,&m_uPlayVolume);
		player->SetPlayerVolume(0,0);
		m_btnVoiceQuiet.SetBitmap(IDB_NORMAL_NOVOICE,IDB_OVER_NOVOICE);
		m_btnVoiceQuiet.SetToolTipText(_T("����"));
		m_bQuietVoice=TRUE;
	}
}

// �жϵ�ǰ����Ƿ���������
inline BOOL CMusicPlayerDlg::IsCursorInRect(CRect& rc)
{
	BOOL bResult=FALSE;
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);
	if(rc.PtInRect(pt))
		bResult=TRUE;
	return bResult;
}
// ���ƶ�̬����
void CMusicPlayerDlg::DrawPictrue(BOOL bRun)
{
	if(bRun)//û��ͼƬ�������߳�
	{
		g_bDrawSwitch=TRUE;
		HANDLE hThread=CreateThread(NULL,0,DrawMoveNoteThread,this,0,NULL);
		CloseHandle(hThread);
	}
	else//��ͼƬ���ر��߳�
	{
		g_bDrawSwitch=FALSE;
		::Sleep(300);
	}
}


void CMusicPlayerDlg::OnBnClickedPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nCuSel=m_defPlaylist.GetCurSel();
	if(LB_ERR!=nCuSel)
	{
		player->Stop();
		m_bPlaying=FALSE;
		::Sleep(200);
		int count=m_defPlaylist.GetCount();
		if(rand_play==g_playMode)//�������ʱ
		{
			srand(time(NULL));
			m_nowPlayIndex=rand()%count;
		}
		else
		{
			if(m_nowPlayIndex==0)
				m_nowPlayIndex=count-1;
			else
				m_nowPlayIndex--;
		}
		StartPlay();
		ReBeginDrawText();
	}
}

void CMusicPlayerDlg::OnBnClickedPlay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(m_defPlaylist.GetCount()!=0)//û������ļ�
	{
		if(!m_bPlaying)
		{
			int nCurSel=m_defPlaylist.GetCurSel();
			if(LB_ERR==nCurSel)//û��ѡ����
				m_nowPlayIndex=0;
			else
				m_nowPlayIndex=nCurSel;
			StartPlay();
		}
		else
		{
			TStreamStatus status;
			player->GetStatus(&status);
			if(status.fPlay)
			{
				StopPlayModeThread();
				m_btnPlay.ReInit(IDB_NORMAL_PLAY2,IDB_OVER_PLAY2,_T("����"));
				player->Pause();
			}
			if(status.fPause)
			{
				StartPlayModeThread();
				m_btnPlay.ReInit(IDB_NORMAL_PLAY1,IDB_OVER_PLAY1,_T("��ͣ"));
				player->Play();
			}
		}
	}
}

void CMusicPlayerDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//int nCurSel=m_defPlaylist.GetCurSel();
	if( LB_ERR != m_nowPlayIndex )
	{
		player->Stop();
		m_bPlaying=FALSE;
		//::Sleep(200);
		int count=m_defPlaylist.GetCount();
		if(rand_play==g_playMode)//�������ģʽ
		{
			srand(time(NULL));
			m_nowPlayIndex=rand()%count;
		}
		else
		{
			if(m_nowPlayIndex==(count-1))
				m_nowPlayIndex=0;
			else
				m_nowPlayIndex++;
		}
		StartPlay();
		ReBeginDrawText();
	}
}

// ��ͼƬ����
void CMusicPlayerDlg::SaveBitmap(HBITMAP hBmp,CString& strFullName)
{
		CDC dc;
		dc.CreateCompatibleDC(NULL);
		CBitmap Bmp;
		Bmp.Attach(hBmp);
		BITMAP btm;
		Bmp.GetBitmap(&btm);
		BITMAPFILEHEADER   bmfHeader;    
		BITMAPINFOHEADER   bi;
		bi.biSize = sizeof(BITMAPINFOHEADER);    
		bi.biWidth = btm.bmWidth;    
		bi.biHeight = btm.bmHeight;  
		bi.biPlanes = 1;    
		bi.biBitCount = 32;    
		bi.biCompression = BI_RGB;    
		bi.biSizeImage = 0;  
		bi.biXPelsPerMeter = 0;    
		bi.biYPelsPerMeter = 0;    
		bi.biClrUsed = 0;    
		bi.biClrImportant = 0;

		DWORD dwBmpSize =((btm.bmWidth*bi.biBitCount+31)/32) 
			*4*btm.bmHeight;
		HANDLE hDIB = ::GlobalAlloc(GHND,dwBmpSize);  
		LPBITMAPINFOHEADER lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);    
		*lpbi = bi;

		// Gets the "bits" from the bitmap and copies them into a buffer 
		// which is pointed to by lpbi
		::GetDIBits(dc.operator HDC(),hBmp,0,
			(UINT)btm.bmHeight,lpbi,
			(BITMAPINFO*)lpbi,DIB_RGB_COLORS);    

		CFile bf;
		if(bf.Open(strFullName,CFile::modeCreate|CFile::modeWrite))
		{
			//Offset to where the actual bitmap bits start.
			bmfHeader.bfOffBits=(DWORD)sizeof(BITMAPFILEHEADER)+ 
				(DWORD)sizeof(BITMAPINFOHEADER); 
			
			//Size of the Data
			bmfHeader.bfSize=dwBmpSize; 

			//bfType must always be BM for Bitmaps
			bmfHeader.bfType=0x4D42; //BM  	
		
			bf.Write((LPSTR)&bmfHeader,sizeof(BITMAPFILEHEADER));
			bf.Write((LPSTR)&bi,sizeof(BITMAPINFOHEADER));
			bf.Write((LPSTR)lpbi,dwBmpSize);
		}
	
		//Unlock and Free the DIB from the heap
		GlobalUnlock(hDIB);    
		GlobalFree(hDIB);
}

void CMusicPlayerDlg::OnBnClickedPlaymode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu menu,*pMenu=NULL;
	menu.LoadMenuW(IDR_MENU4);
	CPoint pt;
	::GetCursorPos(&pt);
	pMenu=menu.GetSubMenu(0);
	int nIndex=0;
	UINT uItemID=ID_MENU_ONLY;
	CString strItemText;
	switch(g_playMode)
	{
	case PLAYMODE::single_play:
		strItemText=MENU_SINGLE_PLAY;
		break;
	case PLAYMODE::order_play:
		strItemText=MENU_ORDER_PLAY;
		nIndex++;
		uItemID++;
		break;
	case PLAYMODE::rand_play:
		strItemText=MENU_RAND_PLAY;
		nIndex+=2;
		uItemID+=2;
		break;
	}
	CBitmap bmp;
	bmp.LoadBitmap(IDB_NORMAL_EXIT);
	pMenu->ModifyMenu(nIndex,MF_BYPOSITION|MF_CHECKED,uItemID,strItemText);
	pMenu->TrackPopupMenu(TPM_LEFTBUTTON,pt.x,pt.y,this);
	pMenu->DestroyMenu();
}

void CMusicPlayerDlg::OnModeOnly()
{
	// TODO: �ڴ���������������
	m_btnPlayMode.ReInit(IDB_ONLY1,IDB_ONLY2,_T("����ģʽ����"));
	g_playMode=single_play;
}

void CMusicPlayerDlg::OnModeOrder()
{
	// TODO: �ڴ���������������
	m_btnPlayMode.ReInit(IDB_ORDER1,IDB_ORDER2,_T("����ģʽ����"));
	g_playMode=order_play;
}

void CMusicPlayerDlg::OnModeRand()
{
	// TODO: �ڴ���������������
	m_btnPlayMode.ReInit(IDB_RAND1,IDB_RAND2,_T("����ģʽ����"));
	g_playMode=rand_play;
}

// �ж��Ƿ���֧�ֵ��ļ�����
BOOL CMusicPlayerDlg::IsSupportFile(const CString& strFileName)
{
	CString strType=strFileName.Right(3);
	strType.MakeUpper();//��д
	if(strType==_T("MP3")||strType==_T("WMA")||strType==_T("OGG")||strType==_T("AC3"))
		return TRUE;
	return FALSE;
}


// ��ȡ�ļ����������ļ�
void CMusicPlayerDlg::AddFolderFiles(const CString& strDir)
{
	try
	{
		CFileFind ff;
		BOOL bFind=ff.FindFile(strDir+_T("\\*.*"));
		CString strValue;
		while(bFind)
		{
			bFind=ff.FindNextFile();
			if(!ff.IsDots())
			{
				if(ff.IsDirectory())//�ļ��У���������
					AddFolderFiles(ff.GetFilePath());
				else//�ļ�
				{
					if(IsSupportFile(ff.GetFileName()))
					{
						m_playList.push_back(ff.GetFilePath());
						CString strName=GetShortName(ff.GetFilePath());
						strValue.Format(_T("%02d  %s"),m_defPlaylist.GetCount()+1,strName);
						m_defPlaylist.AddString(strValue);
					}
				}
			}
		}
	}
	catch(TCHAR* pError)
	{
		 _tprintf(_T("AddFolderFiles�쳣��%s\n"),pError);
	}
}

// ������ǰ���Ÿ�����


void CMusicPlayerDlg::DrawMyText( HDC hDC )
{									   
	try
	{
		static CRect rc(0,40,173,55);
		rc.left=m_rollFlag;
		m_index=m_strTitle.GetLength();
		::SetBkMode(hDC,TRANSPARENT);
		::SetTextColor(hDC,RGB(155,0,200));
		::DrawText(hDC,m_strTitle,m_strTitle.GetLength(),&rc,DT_LEFT);
	}
	catch(...)
	{
		_tprintf(_T("CMusicPlayerDlg::DrawMyText�쳣��\n"));
	}
}

void CMusicPlayerDlg::DrawMyTextA( HDC hDC )
{
	static CRect rc(18,40,173,57);
	::SetBkMode(hDC,TRANSPARENT);
	::SetTextColor(hDC,RGB(155,0,200));
	CString strOut=m_strTitle.Right(m_index);
	::DrawText(hDC,strOut,m_index,&rc,DT_LEFT|DT_VCENTER);
}

void CMusicPlayerDlg::OnIconAbout()
{
	// TODO: �ڴ���������������
	CAboutDlg dlg;
	dlg.DoModal();
}
void CMusicPlayerDlg::CreateListFile(const CString& strPath)
{
	CMarkup xml;
	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>"));
	xml.AddElem(_T("config"));
	xml.Save(strPath);
}
void CMusicPlayerDlg::CreateConfigFile(const CString& strPath)
{
	CMarkup xml;
	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"GB2312\"?>"));
	xml.AddElem(_T("config"));
	xml.Save(strPath);
}
////////////////////////////////////////////////////////
// ��ȡָ���ļ�������
void CMusicPlayerDlg::ReadConfig()
{
	CString strListPath=m_strModulePath+_T("\\AppData\\PlayerList.xml");
	if(!PathFileExists(strListPath))
		CreateListFile(strListPath);
	CMarkup xml;
	xml.Load(strListPath);
	while (xml.FindElem(_T("config")))
	{
		xml.IntoElem();
		CString strValue=_T("");
		while (xml.FindElem(_T("Path")))
		{
			strValue=xml.GetData();
			if(PathFileExists(strValue))
				if(IsSupportFile(strValue))
					m_playList.push_back(strValue);
		}
	}
	AddPlayListToPlayer();
	strListPath=m_strModulePath+_T("\\AppData\\PlayerData.xml");
	if(!PathFileExists(strListPath))
		CreateConfigFile(strListPath);
	xml.Load(strListPath);
	while(xml.FindElem(_T("config")))
	{
		xml.IntoElem();
		int nLVoice=100,nRVoice=100;
		PLAYMODE mode=(PLAYMODE)1;
		CString strValue=_T("");
		if(xml.FindElem(_T("LeftVoice")))
		{
			strValue=xml.GetData();
			nLVoice=_ttoi(strValue.GetBuffer());
			strValue.ReleaseBuffer();
		}
		else
			xml.AddElem(_T("LeftVoice"),nLVoice);
		if(xml.FindElem(_T("RightVoice")))
		{
			strValue=xml.GetData();
			nRVoice=_ttoi(strValue.GetBuffer());
		}
		else
			xml.AddElem(_T("RightVoice"),nRVoice);
		player->SetPlayerVolume(nLVoice,nRVoice);
		m_btnVoiceSetting.SetCurPos(nLVoice);
		if(xml.FindElem(_T("PlayMode")))
		{
			strValue=xml.GetData();
			mode=(PLAYMODE)_ttoi(strValue.GetBuffer());
		}
		else
			xml.AddElem(_T("PlayMode"),(int)mode);
		g_playMode=mode;
		if(xml.FindElem(_T("BackImagePath")))
			m_strSelectBackImage=xml.GetData();
		else
			xml.AddElem(_T("BackImagePath"),m_strSelectBackImage);
		if(xml.FindElem(_T("AlphaValue")))
			m_bAlphaValue=(BYTE)_ttoi(xml.GetData().GetBuffer());
		else
			xml.AddElem(_T("AlphaValue"),m_bAlphaValue);
		xml.OutOfElem();
	}
	xml.Save(strListPath);
}

// д���ļ�
void CMusicPlayerDlg::WriteListFile()
{
	CString strListPath=m_strModulePath+_T("\\AppData\\PlayerList.xml");
	::DeleteFile(strListPath);
	CreateListFile(strListPath);
	CMarkup xml;
	xml.Load(strListPath);
	while (xml.FindElem(_T("config")))
	{
		xml.IntoElem();
		for(int i=0;i<m_defPlaylist.GetCount();++i)
			xml.AddElem(_T("Path"),m_playList[i]);
		xml.OutOfElem();
	}
	xml.Save(strListPath);
	//��������
	strListPath=m_strModulePath+_T("\\AppData\\PlayerData.xml");
	xml.Load(strListPath);
	if(!PathFileExists(strListPath))
		CreateConfigFile(strListPath);
	while(xml.FindElem(_T("config")))
	{
		xml.IntoElem();
		UINT uLeftVoice=0,uRightVoice=0;
		player->GetPlayerVolume(&uLeftVoice,&uRightVoice);
		if(xml.FindElem(_T("LeftVoice")))
			xml.SetData(uLeftVoice);
		else
			xml.AddElem(_T("LeftVoice"),uLeftVoice);
		if(xml.FindElem(_T("RightVoice")))
			xml.SetData(uRightVoice);
		else
			xml.AddElem(_T("RightVoice"),uRightVoice);
		if(xml.FindElem(_T("PlayMode")))
			xml.SetData((int)g_playMode);
		else
			xml.AddElem(_T("PlayMode"),(int)g_playMode);
		if(xml.FindElem(_T("BackImagePath")))
			xml.SetData(m_strSelectBackImage);
		else
			xml.AddElem(_T("BackImagePath"),m_strSelectBackImage);
		if(xml.FindElem(_T("AlphaValue")))
			xml.SetData(m_bAlphaValue);
		else
			xml.AddElem(_T("AlphaValue"),m_bAlphaValue);
		xml.OutOfElem();
	}
	xml.Save(strListPath);
}


BOOL CMusicPlayerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_ESCAPE||pMsg->wParam==VK_RETURN||pMsg->wParam==VK_SPACE)
			return TRUE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CMusicPlayerDlg::AddPlayListToPlayer(const int nStartPos)
{
	VERIFY(nStartPos>=0);
	m_defPlaylist.SetRedraw(FALSE);
	CString strFormartText;
	for(int i=nStartPos;i<m_playList.size();++i)
	{
		strFormartText.Format(_T("%02d  %s"),i+1,GetShortName(m_playList[i]));
		m_defPlaylist.AddString(strFormartText);
	}
	m_defPlaylist.SetRedraw(TRUE);
	m_defPlaylist.RedrawWindow();
}
// ɾ���ڵ�
void CMusicPlayerDlg::DeleteSelectItem(void)
{
	try
	{
		m_defPlaylist.SetRedraw(FALSE);
		int nCurSel=m_defPlaylist.GetCurSel();
		std::vector<CString>::iterator itor=m_playList.begin()+nCurSel;
		m_playList.erase(itor);
		if(1==m_defPlaylist.GetCount())
		{//ɾ�����б��ѿ�
			StopPlayModeThread();
			player->Stop();
			m_nowPlayIndex=-1;
			m_defPlaylist.DeleteString(0);
			goto END;
		}
		int nCount=m_defPlaylist.GetCount()-1;
		if(m_nowPlayIndex==nCurSel)//ɾ�����ڲ��ŵĸ���
		{
			StopPlayModeThread();
			player->Stop();
			if(m_nowPlayIndex==nCount)//���ڲ������һ�ף�ɾ���󲥷ŵ�һ��
				m_nowPlayIndex=0;
			StartPlay();
		}
		else if(m_nowPlayIndex>nCurSel)//ɾ���Ĳ������ڲ��ŵ�
			--m_nowPlayIndex;
		while(nCount>=nCurSel)
		{
			m_defPlaylist.DeleteString(nCount);
			nCount=m_defPlaylist.GetCount()-1;
		}
		AddPlayListToPlayer(nCurSel);///
		m_defPlaylist.SetCurSel(m_nowPlayIndex);
END:
		m_defPlaylist.SetRedraw(TRUE);
		m_defPlaylist.RedrawWindow();
	}
	catch(...)
	{

	}
}

void CMusicPlayerDlg::OnAddDeleteAll()
{
	// TODO: �ڴ���������������
	if(m_defPlaylist.GetCount()==0)
	{
		MessageBox(_T("�б��ѿ�"));
		return;
	}
	if(MessageBox(_T("��ȷ��Ҫ����б���"),_T("��ܰ��ʾ:"),MB_YESNO|MB_ICONINFORMATION)==IDNO)
		return;
	TStreamStatus status;
	player->GetStatus(&status);
	if(status.fPlay||status.fPause)
	{
		player->Stop();
		m_bPlaying=FALSE;
		m_btnProcess.SetRatio(0);
	}
	m_defPlaylist.SetRedraw(FALSE);
	m_defPlaylist.ResetContent();
	m_defPlaylist.SetRedraw(TRUE);
	m_defPlaylist.RedrawWindow();
	m_playList.clear();
}

void CMusicPlayerDlg::GetDropFiles(HDROP hDrop)
{
	UINT nFiles;
	TCHAR szFileName[MAX_PATH];
	int count=m_defPlaylist.GetCount();
	nFiles=DragQueryFile(hDrop,(UINT)0xffffffff,NULL,NULL);
	for(UINT i=0;i<nFiles;i++)
	{		
		DragQueryFile(hDrop,i,szFileName,MAX_PATH);
		if(IsSupportFile(szFileName))
			m_playList.push_back(szFileName);
	}
	AddPlayListToPlayer(count);
}

// MINI�����ϻ������� 
// void CMusicPlayerDlg::DrawTextOnMiniWindow( HDC hDC )
// {
// 	HFONT hOldFont=(HFONT)::SelectObject(hDC,m_hFont);
// 	::SetBkMode(hDC,TRANSPARENT);
// 	::SetTextColor(hDC,RGB(0,255,0));
// 	int len=m_strTitle.GetLength();
// 	if(20*len>(m_rcClient.Width()-30))
// 	{
// 		int pos1=m_strTitle.Find(_T("-"));
// 		int pos2=m_strTitle.FindOneOf(_T("("));
// 		if(pos2==-1)
// 			pos2=m_strTitle.FindOneOf(_T("��"));
// 		if(pos2==-1)
// 			m_strTitle=m_strTitle.Mid(pos1+1);
// 		else
// 			m_strTitle=m_strTitle.Mid(pos1+1,pos2-pos1-1);
// 	}
// 	::DrawText(hDC,m_strTitle,m_strTitle.GetLength(),m_rcClient,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
// 	::SelectObject(hDC,hOldFont);
// }

// Ҫ��MINI������д��ʱ���ذ�ť
void CMusicPlayerDlg::HideButtons(void)
{
	m_btnPrev.ShowWindow(SW_HIDE);
	m_btnPlay.ShowWindow(SW_HIDE);
	m_btnNext.ShowWindow(SW_HIDE);
	m_btnVoiceQuiet.ShowWindow(SW_HIDE);
	m_btnHide.ShowWindow(SW_HIDE);
	m_btnMini.ShowWindow(SW_HIDE);
	m_btnExit.ShowWindow(SW_HIDE);
}

// MINI��������������ʾ��ť
void CMusicPlayerDlg::ShowButtons(void)
{
	m_btnPrev.ShowWindow(SW_SHOW);
	m_btnPlay.ShowWindow(SW_SHOW);
	m_btnNext.ShowWindow(SW_SHOW);
	m_btnVoiceQuiet.ShowWindow(SW_SHOW);
	m_btnHide.ShowWindow(SW_SHOW);
	m_btnMini.ShowWindow(SW_SHOW);
	m_btnExit.ShowWindow(SW_SHOW);
}

void CMusicPlayerDlg::On32785Play()
{
	// TODO: �ڴ���������������
	OnBnClickedPlay();
}

void CMusicPlayerDlg::On32783Prev()
{
	// TODO: �ڴ���������������
	OnBnClickedPrev();
}

void CMusicPlayerDlg::On32784Next()
{
	// TODO: �ڴ���������������
	OnBnClickedNext();
}

void CMusicPlayerDlg::OnIconSetAttributes()
{
	// TODO: �ڴ���������������
	ShowAttributeDlg();
}

void CMusicPlayerDlg::On32789()
{
	// TODO: �ڴ���������������
	this->OnAddFile();
}

void CMusicPlayerDlg::On32788()
{
	// TODO: �ڴ���������������
	this->OnAddFolder();
}
void CMusicPlayerDlg::ShowMainMenu()
{
	CPoint MousePos;
	GetCursorPos(&MousePos);
	CMenu menu;
	menu.LoadMenu(IDR_MENU1);
	SetForegroundWindow();
	CMenu* pMenu=menu.GetSubMenu(0);
	TStreamStatus status1;
	player->GetStatus(&status1);
	if(m_bLockLyrics)
		pMenu->GetSubMenu(6)->ModifyMenu(1,MF_BYPOSITION,ID_32795,MENU_UNLOCK_LYRIC);
	else
		pMenu->GetSubMenu(6)->ModifyMenu(1,MF_BYPOSITION,ID_32795,MENU_LOCK_LYRIC);
	if(m_bShowLyrics)
		pMenu->GetSubMenu(6)->ModifyMenu(0,MF_BYPOSITION,ID_32791,MENU_HIDE_LYRIC);
	else
		pMenu->GetSubMenu(6)->ModifyMenu(0,MF_BYPOSITION,ID_32791,MENU_SHOW_LYRIC);
	if(!m_bPlaying)
	{
		pMenu->GetSubMenu(0)->ModifyMenu(0,MF_BYPOSITION|MF_GRAYED,ID_32785,MENU_PLAY);
		pMenu->GetSubMenu(0)->ModifyMenu(1,MF_BYPOSITION|MF_GRAYED,ID_32783,MENU_PREV);
		pMenu->GetSubMenu(0)->ModifyMenu(2,MF_BYPOSITION|MF_GRAYED,ID_32784,MENU_NEXT);
	}
	else
	{
		if(status1.fPause)//��ͣ��
			pMenu->GetSubMenu(0)->ModifyMenu(0,MF_BYPOSITION,ID_32785,MENU_PLAY);
		else
			pMenu->GetSubMenu(0)->ModifyMenu(0,MF_BYPOSITION,ID_32785,MENU_PAUSE);
	}
	int nIndex=0;
	UINT uItemID=ID_MENU_ONLY;
	CString strItemText;
	switch(g_playMode)
	{
	case PLAYMODE::single_play:
		strItemText=MENU_SINGLE_PLAY;
		break;
	case PLAYMODE::order_play:
		strItemText=MENU_ORDER_PLAY;
		nIndex++;
		uItemID++;
		break;
	case PLAYMODE::rand_play:
		strItemText=MENU_RAND_PLAY;
		nIndex+=2;
		uItemID+=2;
		break;
	}
	pMenu->GetSubMenu(1)->ModifyMenu(nIndex,MF_BYPOSITION|MF_CHECKED,uItemID,strItemText);
	HBITMAP hOverBitmap;
	hOverBitmap=LoadBitmap(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDB_OVER_EXIT));
	SetMenuItemBitmaps(pMenu->GetSafeHmenu(),10,MF_BYPOSITION,hOverBitmap,hOverBitmap);
	pMenu->TrackPopupMenu(TPM_RIGHTBUTTON,
		MousePos.x,MousePos.y,this,NULL);
	pMenu->DestroyMenu();
	::DeleteObject(hOverBitmap);
}
void CMusicPlayerDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ShowMainMenu();
	CDialog::OnRButtonDown(nFlags, point);
}

void CMusicPlayerDlg::ReBeginDrawText(void)
{
	m_IsGet=FALSE;
	m_rollFlag=176;
}

BOOL CMusicPlayerDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_bMouseOverVoice)
	{
		m_btnVoiceSetting.SetFocus();
		HWND hWnd=::SetFocus(m_btnVoiceSetting.m_hWnd);	
		if(zDelta==120)//���Ϲ���,������С
			ChangePlayerVoice(-5);
		if(zDelta==-120)//��������
			ChangePlayerVoice(5);
	}
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

// void CMusicPlayerDlg::OnBnClickedMyLike()
// {
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	if(!m_bPlayListFlag)
// 		ShowEnjoyPlayList();
// }

// void CMusicPlayerDlg::ShowDefaultPlayList(void)
// {
// 	m_btnDefaultList.ReInit(IDB_NORMAL_LIST11,IDB_OVER_LIST1,_T("Ĭ���б�"));
// //	m_btnEnjoyList.ReInit(IDB_NORMAL_LIST2,IDB_OVER_LIST2,_T("�ղ��б�"));
// 	m_defPlaylist.MoveWindow(20,137,250,292);
// 	m_defPlaylist.ShowWindow(SW_SHOW);
// //	m_enjoyPlaylist.ShowWindow(SW_HIDE);
// 	m_bPlayListFlag=FALSE;
// }
// 
// void CMusicPlayerDlg::ShowEnjoyPlayList(void)
// {
// 	m_btnDefaultList.ReInit(IDB_NORMAL_LIST11,IDB_OVER_LIST1,_T("Ĭ���б�"));
// //	m_btnEnjoyList.ReInit(IDB_NORMAL_LIST22,IDB_OVER_LIST2,_T("�ղ��б�"));
// //	m_enjoyPlaylist.MoveWindow(20,137,250,292);
// //	m_enjoyPlaylist.ShowWindow(SW_SHOW);
// 	m_defPlaylist.ShowWindow(SW_HIDE);
// 	m_bPlayListFlag=TRUE;
// }

// void CMusicPlayerDlg::OnBnClickedList1()
// {
// 	// TODO: �ڴ���ӿؼ�֪ͨ����������
// 	if(!m_bPlayListFlag)
// 		return;
// 	ShowDefaultPlayList();
// }

void CMusicPlayerDlg::OnShowLyricsDlg()
{
	// TODO: �ڴ���������������
	if(m_bShowLyrics)
	{
		ShowLyricsDlg(FALSE);
		m_bShowLyrics=FALSE;
	}
	else
	{
		ShowLyricsDlg(TRUE);
		m_bShowLyrics=TRUE;
	}
}

void CMusicPlayerDlg::OnSetLyricsColor()
{
	// TODO: �ڴ���������������
	SetLyricsColor();
}

void CMusicPlayerDlg::OnSetLyricsFont()
{
	// TODO: �ڴ���������������
	SetLyricsFont();
}

void CMusicPlayerDlg::OnLyricsLock()
{
	// TODO: �ڴ���������������
	LockLyricsDlg(!m_bLockLyrics);
	m_bLockLyrics=!m_bLockLyrics;
}
LRESULT CMusicPlayerDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{
	switch((UINT)wParam)
	{
	case WM_LOCK_LYRICS:
		OnLyricsLock();
		break;
	case WM_PLAY_NEXT:
		OnBnClickedNext();
		break;
	case WM_PLAY_PREV:
		OnBnClickedPrev();
		break;
	case WM_PLAY:
		OnBnClickedPlay();
		break;
	case WM_HIDE_LYRICS:
		OnShowLyricsDlg();
		break;
	case WM_SCREEN_CAPTURE:
		if(!m_bCaptureFlag)
			OnScreenCapture();
		break;
	case WM_VOICE_RAISE:
		ChangePlayerVoice(5);
		break;
	case WM_VOICE_REDUCE:
		ChangePlayerVoice(-5);
		break;
	default:
		break;
	}
	return 1;
}

void CMusicPlayerDlg::ShowLyricFile()
{
	// TODO: �ڴ���������������
	CString strLyricsName;
	int index=m_defPlaylist.GetCurSel();
	strLyricsName=m_strModulePath+_T("\\Lyrics\\")+GetShortName(m_playList[index])+_T(".lrc");
	if(PathFileExists(strLyricsName))
	{
		CString s=m_strModulePath+_T("\\CommonDlgLib.dll");
		HINSTANCE hIns=LoadLibrary(s);
		if(hIns)
		{
			typedef void (*SHOW)(CString&);
			SHOW show=NULL;
			show=(SHOW)GetProcAddress(hIns,"ShowLyricsFileDlg");
			if(show)
				show(strLyricsName);
			else
				AfxMessageBox(_T("��������ShowLyricsFileDlgʧ��!"));
			FreeLibrary(hIns);
		}
		else
			AfxMessageBox(_T("����ShowLyricsFileModule.dllʧ��!"));
	}
	else
	{
		CNoLyricsDlg dlg;
		dlg.DoModal();
	}

}


void CMusicPlayerDlg::OnSendEmail()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(this->m_hWnd,+_T("open"),_T("mailto:Jelinyao@163.com"),_T(""),_T(""),SW_SHOW );
}

// ��ʼ����
void CMusicPlayerDlg::OnScreenCapture(void)
{
	HMODULE hIns=NULL;
	hIns=::LoadLibrary(_T("ScreenCaptureDll.dll"));
	if(hIns)
	{
		typedef void (*FUN)();
		FUN f=NULL;
		f=(FUN)::GetProcAddress(hIns,"InitCaptureDlg");
		if(f)
		{
			m_bCaptureFlag=TRUE;
			f();
		}
		else
			::AfxMessageBox(_T("��ȡ������ַʧ�ܣ�"),MB_OK|MB_ICONERROR);
		::FreeLibrary(hIns);
		m_bCaptureFlag=FALSE;
	}
	else
		::AfxMessageBox(_T("���ؽ���ģ��ʧ�ܣ�\r\n�����°�װScreenCaptureDll.dll."),\
		MB_OK|MB_ICONERROR);
}

void CMusicPlayerDlg::RegisterHotKeys(void)
{
	//����\����������
	::RegisterHotKey(m_hWnd,WM_LOCK_LYRICS,MOD_CONTROL|MOD_ALT,'L');
	//��һ��
	::RegisterHotKey(m_hWnd,WM_PLAY_NEXT,MOD_CONTROL|MOD_ALT,VK_RIGHT);
	//��һ��
	::RegisterHotKey(m_hWnd,WM_PLAY_PREV,MOD_CONTROL|MOD_ALT,VK_LEFT);
	//����\��ͣ
	::RegisterHotKey(m_hWnd,WM_PLAY,MOD_CONTROL|MOD_ALT,'P');
	//��ʾ\���ظ�����
	::RegisterHotKey(m_hWnd,WM_HIDE_LYRICS,MOD_CONTROL|MOD_ALT,'H');
	//������ݼ�
	::RegisterHotKey(m_hWnd,WM_SCREEN_CAPTURE,MOD_CONTROL|MOD_ALT,'C');
	//��������
	::RegisterHotKey(m_hWnd,WM_VOICE_RAISE,MOD_CONTROL,VK_UP);
	//������С
	::RegisterHotKey(m_hWnd,WM_VOICE_REDUCE,MOD_CONTROL,VK_DOWN);
}
void CMusicPlayerDlg::Release()
{
	try
	{
		if(NULL!=m_pGraphic)
		{
			delete m_pGraphic;
			m_pGraphic=NULL;
		}
		if(NULL!=m_pBackBitmap)
		{
			delete m_pBackBitmap;
			m_pBackBitmap=NULL;
		}
		if(NULL!=m_pAuthorImage)
		{
			delete m_pAuthorImage;
			m_pAuthorImage=NULL;
		}
		ReleaseGDIHandle((HANDLE*)&m_hFont);
	}
	catch(...)
	{
		EXCEPTION_INFO ei=FillExceptionInfo(_T("λ���쳣"),__LINE__,__FILE__,\
			::GetLastError(),_T("Release"));
		WriteErrorLog(&ei);
	}
}
void CMusicPlayerDlg::OnChangeCloth()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	static BOOL bInit=FALSE;
	if(!bInit)
	{
		bInit=TRUE;
		InitChangeClothDlg(m_bAlphaValue,m_strSelectBackImage);
	}
	BOOL bRet=FALSE;
	if(!m_bShowChangeClothDlg)
		bRet=ShowChangeClothDlg();
	else
		bRet=HideChangeClothDlg();
	if(bRet)
		m_bShowChangeClothDlg=!m_bShowChangeClothDlg;
// 	HANDLE hThread=::CreateThread(NULL,0,FocusMoniterThread,this,0,NULL);
// 	::CloseHandle(hThread);
}
void CMusicPlayerDlg::ChangeBack()
{
	if(m_pBackBitmap)
	{
		delete m_pBackBitmap;
		m_pBackBitmap=NULL;
	}
	m_pBackBitmap=Gdiplus::Bitmap::FromFile(m_strTempBackImage.GetBuffer());
	Invalidate();
	//���пؼ���Ҫ������λͼ
	m_defPlaylist.ChangeBack();
	m_btnExit.ChangeBack();
	m_btnHide.ChangeBack();
	m_btnMini.ChangeBack();
	m_btnCloth.ChangeBack();
	m_btnVoiceQuiet.ChangeBack();
	m_btnPrev.ChangeBack();
	m_btnPlay.ChangeBack();
	m_btnNext.ChangeBack();
	m_btnDefaultList.ChangeBack();
	m_btnPlayMode.ChangeBack();
	m_btnAdd.ChangeBack();
	m_btnFeedBack.ChangeBack();
}

void CMusicPlayerDlg::StartPlayModeThread()
{
	g_bModeThreadSwitch=TRUE;
	HANDLE hThread=::CreateThread(NULL,0,PlayModeSwitchThread,this,0,NULL);
	::CloseHandle(hThread);
}

void CMusicPlayerDlg::StopPlayModeThread()
{
	g_bModeThreadSwitch=FALSE;
	Sleep(100);
}

