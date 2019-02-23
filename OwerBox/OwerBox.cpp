// OwerBox.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "OwerBox.h"
#include "DeleteDlg.h"
#include "InfoDlg.h"
#include "ChangeClothDlg.h"
#include "SetAttributeDlg.h"
#include "LyricsFileDlg.h"
#include <iostream>
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// COwerBoxApp

BEGIN_MESSAGE_MAP(COwerBoxApp, CWinApp)
END_MESSAGE_MAP()


// COwerBoxApp ����
CDeleteDlg*			g_pDeleteDlg=NULL;
CInfoDlg*			g_pInfoDlg=NULL;
CChangeClothDlg*	g_pChangeClothDlg=NULL;
CSetAttributeDlg*	g_pSetAttributeDlg=NULL;
inline BOOL EnsureWindow(CWnd* pWnd)
{
	BOOL bResult=FALSE;
	if(pWnd&&IsWindow(pWnd->GetSafeHwnd()))
		bResult=TRUE;
	return bResult;
}
////////////////////////////////////////////////////////////////////////////
//�̺߳���
BOOL g_bShowThreadRun=FALSE;
BOOL g_bShowChangeClothDlg=TRUE;
DWORD WINAPI MoveChangeChothDlgThread(LPVOID lpParam)
{
	g_bShowThreadRun=TRUE;
	CRect rcParent;
	CWnd* pWnd=g_pChangeClothDlg->GetParent();
	pWnd->GetClientRect(&rcParent);
	pWnd->ClientToScreen(&rcParent);
	g_pChangeClothDlg->ShowWindow(SW_SHOW);
	int nAdd=6;
	int nWidth=0,nHeight=0;
	BYTE alpha=0;
	for(int i=1;i<=44;++i)
	{
		if(g_bShowChangeClothDlg)//ֵΪ1����ʾ�Ի���
		{
			nWidth=5*i;
			nHeight=6*i;
			alpha=nAdd*i;
		}
		else
		{
			nWidth=220-5*i;
			nHeight=267-6*i;
			alpha=255-nAdd*i;
		}
		g_pChangeClothDlg->MoveWindow(rcParent.left+284,rcParent.top,nWidth,nHeight);
		g_pChangeClothDlg->SetLayeredWindowAttributes(0xffffff,alpha,LWA_ALPHA);
		Sleep(10);
	}
	if(g_bShowChangeClothDlg)
		g_pChangeClothDlg->SetLayeredWindowAttributes(0xffffff,255,LWA_ALPHA);
	else
		g_pChangeClothDlg->ShowWindow(SW_HIDE);
	g_bShowThreadRun=FALSE;
	return 0;
}
COwerBoxApp::COwerBoxApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� COwerBoxApp ����

COwerBoxApp theApp;

// COwerBoxApp ��ʼ��

BOOL COwerBoxApp::InitInstance()
{
	CWinApp::InitInstance();
	AfxInitRichEdit();
	//while(NULL==g_pDeleteDlg)
	Gdiplus::GdiplusStartup(&m_ptr,&m_start,NULL);
	return TRUE;
}
int COwerBoxApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	Gdiplus::GdiplusShutdown(m_ptr);
	return CWinApp::ExitInstance();
}

//����ģ��ӿ�
void ReleaseDeleteDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pDeleteDlg))
	{
		delete g_pDeleteDlg;
		g_pDeleteDlg=NULL;
	}
}
void ShowDeleteDlg(std::wstring& ws)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hOldInst=AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);
	ReleaseDeleteDlg();
	CString strPath;
	strPath.Append(ws.c_str());
	g_pDeleteDlg=new CDeleteDlg(strPath);
	g_pDeleteDlg->Create(IDD_DIALOG1);
	g_pDeleteDlg->ShowWindow(SW_SHOW);
	AfxSetResourceHandle(hOldInst);
}
/*********************************************************************/
void ReleaseInfoDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pInfoDlg))
	{
		g_pInfoDlg->DestroyWindow();
		delete g_pInfoDlg;
		g_pInfoDlg=NULL;
	}
}
void ShowInfoDlg(std::wstring& ws)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hOldInst=AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);
	ReleaseInfoDlg();
	CString strPath;
	strPath.Append(ws.c_str());
	g_pInfoDlg=new CInfoDlg(strPath);
	g_pInfoDlg->Create(IDD_DIALOG2);
	g_pInfoDlg->ShowWindow(SW_SHOW);
	AfxSetResourceHandle(hOldInst);
}
/***********************************************************************/
void ReleaseChangeClothDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pChangeClothDlg))
	{
		delete g_pChangeClothDlg;
		g_pChangeClothDlg=NULL;
	}
}
BOOL ShowChangeClothDlg()
{	
	BOOL bResult=FALSE;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pChangeClothDlg))
	{
		if(!g_pChangeClothDlg->IsWindowVisible())

		{
			if(!g_bShowThreadRun)
			{
				g_bShowChangeClothDlg=TRUE;
				HANDLE hThread=CreateThread(NULL,0,MoveChangeChothDlgThread,NULL,0,NULL);
				CloseHandle(hThread);
				bResult=TRUE;
			}
		}
	}
	return bResult;
}
void InitChangeClothDlg(const BYTE bValue,const CString& strBackImagePath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(NULL==g_pChangeClothDlg)
	{
		HINSTANCE hOldInst=AfxGetResourceHandle();
		AfxSetResourceHandle(theApp.m_hInstance);
		g_pChangeClothDlg=new CChangeClothDlg(bValue,strBackImagePath);
		g_pChangeClothDlg->Create(IDD_DIALOG_CHANGECLOTH);
		g_pChangeClothDlg->ShowWindow(SW_SHOW);
		g_pChangeClothDlg->ShowWindow(SW_HIDE);
		AfxSetResourceHandle(hOldInst);
	}
}
BOOL HideChangeClothDlg()
{
	BOOL bResult=FALSE;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pChangeClothDlg))
	{
		if(g_pChangeClothDlg->IsWindowVisible())
		{
			if(!g_bShowThreadRun)
			{
				g_bShowChangeClothDlg=FALSE;
				HANDLE hThread=CreateThread(NULL,0,MoveChangeChothDlgThread,NULL,0,NULL);
				CloseHandle(hThread);
				bResult=TRUE;
			}
		}
	}
	return bResult;
}
/********************************************************************************/
void ReleaseAttributeDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	if(EnsureWindow(g_pSetAttributeDlg))
	{
		delete g_pSetAttributeDlg;
		g_pSetAttributeDlg=NULL;
	}
}
void ShowAttributeDlg()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	HINSTANCE hOldInst=AfxGetResourceHandle();
	AfxSetResourceHandle(theApp.m_hInstance);
	ReleaseAttributeDlg();
	if(NULL==g_pSetAttributeDlg)
	{
		g_pSetAttributeDlg=new CSetAttributeDlg;
		g_pSetAttributeDlg->Create(IDD_DIALOG_SETATTRIBUTE);
		g_pSetAttributeDlg->ShowWindow(SW_SHOW);
	}
	AfxSetResourceHandle(hOldInst);
}
/********************************************************************************/
void ShowLyricsFileDlg(const CString& strLyricPath)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CLyricsFileDlg dlg(strLyricPath);
	dlg.DoModal();
}