// LyricsModule.cpp : ���� DLL �ĳ�ʼ�����̡�
//
/******************************************/
/*�޸�ʱ�䣺2013��2��21��18:24:30         */
/*Ҧ����								  */
/******************************************/
#include "stdafx.h"
#include "LyricsModule.h"
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

// CLyricsModuleApp




BEGIN_MESSAGE_MAP(CLyricsModuleApp, CWinApp)
END_MESSAGE_MAP()


// CLyricsModuleApp ����

CLyricsModuleApp::CLyricsModuleApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CLyricsModuleApp ����

CLyricsModuleApp theApp;


// CLyricsModuleApp ��ʼ��

BOOL CLyricsModuleApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

int CLyricsModuleApp::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	return CWinApp::ExitInstance();
}


/**********************************************************/
//***************����ȫ�ֱ���
//������Ի���ָ��
CLyricsDlg* g_pLyricsDlg=NULL;
//��Ϣѭ���߳̾��
HANDLE      g_hMsgLoopThread=NULL;
//�߳����п���
BOOL		g_bSwitch=TRUE;
//�쳣��־��¼����
CErrorLog   g_logError=CErrorLog(LYRICS_MOUDLE_GLOBALFUN);


//�̺߳������жԻ�����Ϣѭ��
DWORD WINAPI DialogMessageLoopThread(LPVOID lpParam)
{
	DWORD dwRet=0;
	try
	{
		if(NULL!=g_pLyricsDlg)
		{
			HWND hLyricsDlg=g_pLyricsDlg->GetSafeHwnd();
			if(NULL==hLyricsDlg)
				throw _T("��ȡ�Ի�����ʧ�ܣ�");
			//������Ϣѭ��
			BOOL bRet=0;
			MSG msg;
			while(g_bSwitch&&(bRet=::GetMessage(&msg,hLyricsDlg,0,0)))
			{
				if(-1==bRet)
					throw ;
				if(hLyricsDlg&&(!IsDialogMessage(hLyricsDlg,&msg)))
				{
					::TranslateMessage(&msg);
					::DispatchMessage(&msg);
				}
			}
			g_pLyricsDlg->DestroyWindow();
			delete g_pLyricsDlg;
			g_pLyricsDlg=NULL;
			hLyricsDlg=NULL;
			g_hMsgLoopThread=NULL;
		}
	}
	catch(TCHAR* pError)
	{
		_tprintf(_T("DialogMessageLoopThread�쳣��Ϣ:%s\n"),pError);
		EXCEPTION_INFO ei=FillExceptionInfo(pError,__LINE__,__FILE__,::GetLastError(),_T("DialogMessageLoopThread"));
		g_logError.WriteErrorLog(&ei);
		dwRet=1;
	}
	return dwRet;
}
inline BOOL EnsureDlg()
{
	return g_pLyricsDlg!=NULL&&(::IsWindow(g_pLyricsDlg->m_hWnd));
}
//////////////////////////////////////////////////////////////////////
//ģ��ӿ�
BOOL InitLyricsDlg()//��ʼ��������
{
	try
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());
		HINSTANCE hOldInst=AfxGetResourceHandle();
		AfxSetResourceHandle(theApp.m_hInstance);
		g_pLyricsDlg=new CLyricsDlg;
		if(NULL==g_pLyricsDlg)
			throw _T("�����ڴ�ʧ�ܣ�");
		g_pLyricsDlg->Create(IDD_DIALOG_LYRICS);
		g_pLyricsDlg->ShowWindow(SW_SHOW);
		g_pLyricsDlg->UpdateWindow();
// 		if(NULL==g_hMsgLoopThread)
// 		{
// 			//������������Ϣѭ���߳�
// 			g_hMsgLoopThread=::CreateThread(NULL,0,DialogMessageLoopThread,\
// 				NULL,0,NULL);
// 			if(NULL==g_hMsgLoopThread)//�����߳�ʧ��
// 				throw _T("������Ϣѭ���߳�ʧ�ܣ�");
// 			::CloseHandle(g_hMsgLoopThread);
// 			g_bSwitch=TRUE;
// 		}
		AfxSetResourceHandle(hOldInst);
	}
	catch(TCHAR* pError)
	{
		_tprintf(_T("InitLyricsDlg�쳣��Ϣ:%s\n"),pError);
		EXCEPTION_INFO ei=FillExceptionInfo(pError,__LINE__,__FILE__,::GetLastError(),_T("InitLyricsDlg"));
		g_bSwitch=FALSE;
		g_logError.WriteErrorLog(&ei);
	}
	return g_pLyricsDlg->IsLock();
}
void ShowLyricsDlg(BOOL bShow)//��ʾ\���ظ�����
{
	try
	{
		if(!EnsureDlg())
			throw _T("������Ի���ָ��Ϊ��!");
		if(bShow)
			g_pLyricsDlg->ShowWindow(SW_SHOW);
		else
			g_pLyricsDlg->ShowWindow(SW_HIDE);
	}
	catch(TCHAR* pError)
	{
		_tprintf(_T("InitLyricsDlg�쳣��Ϣ:%s\n"),pError);
		EXCEPTION_INFO ei=FillExceptionInfo(pError,__LINE__,__FILE__,::GetLastError(),_T("ShowLyricsDlg"));
		g_pLyricsDlg->WriteErrorLog(&ei);
	}
}
void SendLyricsMsg(std::wstring& wstrPath)//���͸���ļ���Ϣ��ģ����
{
	try
	{
		if(!EnsureDlg())
			throw _T("������Ի���ָ��Ϊ��!");
		g_pLyricsDlg->StrCurLyricsPath(CString(wstrPath.c_str()));
		g_pLyricsDlg->ReadLyricsFile();
	}
	catch(TCHAR* pError)
	{
		_tprintf(_T("SendLyricsMsg�쳣��Ϣ:%s\n"),pError);
		EXCEPTION_INFO ei=FillExceptionInfo(pError,__LINE__,__FILE__,::GetLastError(),_T("SendLyricsMsg"));
		g_logError.WriteErrorLog(&ei);
	}
}
void SetLyricsTime(int nCurTime)//����˻����˺���֮�������Ӧ����
{
	if(EnsureDlg())
		g_pLyricsDlg->ChangeCurTime(nCurTime);
}
void SetLyricsColor()//�ı�����ɫ
{
	if(EnsureDlg())
		g_pLyricsDlg->OnRBSetColor();
}
void SetLyricsFont()//�ı�������
{
	if(EnsureDlg())
		g_pLyricsDlg->OnRBSetFont();
}
void NoLyricsFile()//û���ҵ�����ļ�
{
	if(EnsureDlg())
		g_pLyricsDlg->FileNotExist();
}
void LockLyricsDlg(BOOL lock)//������������ʶԻ���
{
	if(EnsureDlg())
		g_pLyricsDlg->LockLyrics(lock);
}
void ReleaseLyricsDlg()//�ͷŶԻ�����Դ
{
	if(EnsureDlg())
	{
		//�߳��˳�ǰ���ٴ���
		g_pLyricsDlg->SaveLyricsDialogData();
		g_pLyricsDlg->OnCancel();
	}
}