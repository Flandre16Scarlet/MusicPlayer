#pragma once
/////////////////////////////////////////////////////////////////////////////////
//�쳣��Ϣ��¼��

#include <string>
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif





//�����쳣��Ϣ�ṹ��
typedef struct _EXCEPTION_INFO
{
	tstring tstrExceptionFunc;//�쳣ģ�麯����
	tstring tstrExceptionInfo;//�쳣��Ϣ�ַ���
	int     nExceptionLine;	//�����쳣�Ĵ�����
	char	szSourcePath[260];//����Դ�ļ�������·��
	DWORD   dwErrorCode;//�쳣��
}EXCEPTION_INFO,LPEXCEPTION_INFO;

//����쳣�ṹ��
inline EXCEPTION_INFO FillExceptionInfo(TCHAR* pErrorInfo,int nLine,char* pSourcePath,DWORD dwErrorCode,TCHAR* pFuncName=NULL)
{
	EXCEPTION_INFO ei;
	if(NULL!=pFuncName)
		ei.tstrExceptionFunc.append(pFuncName);
	ei.tstrExceptionInfo.append(pErrorInfo);
	ei.nExceptionLine=nLine;
	ei.dwErrorCode=dwErrorCode;
	memset(ei.szSourcePath,0,260);
	strcpy(ei.szSourcePath,pSourcePath);
	strcat(ei.szSourcePath,"\r\n");
	return ei;
}
#define THROW_ERROR(x) {ei=FillExceptionInfo(_T(x),__LINE__-2,__FILE__,::GetLastError());throw 1;}

EXPORT_CLASS CErrorLog
{
public:
	CErrorLog(TCHAR* pModuleName);
	virtual~ CErrorLog();
	//��¼�쳣,��������Ϊ��������������Ϣ��ģ����
	bool WriteErrorLog(const EXCEPTION_INFO* pExcept,TCHAR* pModuleName=NULL);
protected:
	/********************�ܱ����ĳ�Ա����**********************/
	//��¼�����쳣
	bool WriteOwerErrorLog(TCHAR* strFuncName,TCHAR* pErrorMsg,int nLine);
	bool WriteOwerErrorLog(const EXCEPTION_INFO* pException);
	//��ʽ����ǰʱ��
	inline std::string FormatTime();
	//��ȡϵͳ������Ϣ
	inline std::string FormatLastError(const DWORD& dwErrorCode);
	//�ֽ�ת��
	char* WcharToChar(const wchar_t* wp);
	wchar_t* CharToWchar(const char* p);
private:
	//���浱ǰģ�������
	tstring m_strModuleName;
	static  TCHAR g_szModulePath[MAX_PATH];
};