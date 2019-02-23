// MyMusicPlayer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "MusicPlayer.h"
#include "MusicPlayerDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyMusicPlayerApp

BEGIN_MESSAGE_MAP(CMusicPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMyMusicPlayerApp ����

CMusicPlayerApp::CMusicPlayerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMyMusicPlayerApp ����

CMusicPlayerApp theApp;


// CMyMusicPlayerApp ��ʼ��

BOOL CMusicPlayerApp::InitInstance()
{
//TODO: call AfxInitRichEdit2() to initialize richedit2 library.
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
#ifdef DEBUG
	//��ʾ����̨
	AllocConsole();
	_tfreopen(_T("CONOUT$"), _T("w"),stdout);
	setlocale(LC_CTYPE, "chs");
#endif
	AfxEnableControlContainer();
	//AfxMessageBox(_T("1"));
	Gdiplus::GdiplusStartup(&m_GdiplusPtr,&m_GdiplusInput,NULL);
	hMutex=CreateMutex(NULL,FALSE,_T("MyMusicPlayer"));
	//AfxMessageBox(_T("2"));
// 	if(GetLastError()==ERROR_ALREADY_EXISTS)
// 	{
// 		HWND hWnd=FindWindow(NULL,_T("MusicPlayer"));
// 		if(hWnd)
// 		{
// 			if(::IsWindowVisible(hWnd))
// 				return FALSE;
// 			 SendMessage(hWnd,MYWM_NOTIFYICON,NULL,(LPARAM)WM_LBUTTONDOWN);
// 		}
// 		return FALSE;
// 	}
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	CMusicPlayerDlg dlg;
	//AfxMessageBox(_T("3"));
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int CMusicPlayerApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
#ifdef DEBUG
	::FreeConsole();//�ͷſ���̨��Դ
#endif
	Gdiplus::GdiplusShutdown(m_GdiplusPtr);
	return CWinApp::ExitInstance();
}
