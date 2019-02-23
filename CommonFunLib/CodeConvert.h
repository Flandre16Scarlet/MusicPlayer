/*****************************************************************************************/
/*                             ��������������                                */
/*����:CCodeTrans���ñ�׼C++����Ȼ��������Windows API�ĵ��ã�д��һ�������ַ������ʽת��*/
/*���࣬���������һ����쳣����ϣ�����ڴ�����ȶ����ܹ�������ǿ�����������ķ���,����*/
/*�ܷ���ض�һЩ����C++���ͼ������ת����                                                */
/*��ע�����ڸ���������ʱ�����ޣ�����bug�������⣬ϣ������ָ��                            */
/*���ߣ�Jelin                                                                            */
/*ʱ�䣺2012��12��27��22:19:05                                                           */
/*���䣺jelinyao@163.com                                                                 */
/*****************************************************************************************/
#ifndef CODE_CONVER_H_
#define CODE_CONVER_H_
#pragma once
#include <iostream>
#include <string>
/*#include <tchar.h>*/
//���������ｫ���ർ����DLL�� 
EXPORT_CLASS CCodeCovert
{
public:
	//Ĭ�Ϲ��캯������ʼ����Ա����
	CCodeCovert();
	//�����������ͷ���Դ
	virtual~ CCodeCovert();
	//UNICODEָ��תANSCIIָ��
	char* WcharToChar(const wchar_t* wpRes);
	//wstringתANSCIIָ��
	char* WstringToChar(const std::wstring& wstrRes);
	//ANSCIIָ��תUNICODEָ��
	wchar_t* CharToWchar(const char* pRes);
	//string����תUNICODEָ��
	wchar_t* StringToWchar(const std::string& strRes);
	//string����תwstring����
	std::wstring StringToWstring(const std::string& strRes);
	//wstring����תstring����
	std::string WstringToString(const std::wstring& wstrRes);
	//UTF8�����ַ���תUNICODE�����ַ���
	static std::wstring Utf8ToUnicode(const std::string& strUtf8); 
	//UTF8�����ַ���תASCII�����ַ���
	std::string Utf8ToAscii(const std::string& strUtf8);
	//UNICODE�����ַ���תUTF8�����ַ���
	static std::string UnicodeToUtf8(const std::wstring& wstrUnicode); 
	//ASCII�����ַ���תUTF8�����ַ���
	std::string AsciiToUtf8(const std::string& strUnicode);
	//ɾ���ַ���ǰ��������ո�
	bool RemoveSpaces(std::string& strRes);
	bool RemoveSpaces(std::wstring& wstrRes);
	//��ȡ�ַ�ת��������Ϣ
	inline std::string GetCodeError()const;
	inline char* GetCodeError();
private:
	//ת���õ��ڲ�������
	char* m_pBuffer;
	wchar_t* m_wpBuffer;
	//������Ϣ
	static std::string m_strError;
protected: 
	//��ӡ������Ϣ
	static void PrintErrorString();
	//�ͷŶ�̬������ڴ���Դ
	bool Release();
	//�����ַ�ת��������Ϣ
	static bool SetCodeError(const char* pError);
	static bool SetCodeError(const std::string& strError);
	//�ͷ�ָ��ָ����ڴ���Դ
	inline void Free(wchar_t* pBuffer){if(pBuffer){delete[] pBuffer;pBuffer=NULL;}}
	inline void Free(char* pBuffer){if(pBuffer){delete[] pBuffer;pBuffer=NULL;}}
};
#endif
/*****************************************************************************************************/
/*����ڿ���һ��С����ʱ���������������ַ������͵��໥ת�������������о��ܶ���붼�Ǹ���ճ��         */
/*���˷�ʱ��Ҳ�����ڲ��Դ��룬���Ǿ���C++��װ����һ�𣬵�������Ҳ�����ɶ���                          */
/*�������ޡ���ӭ���ߴͽ�                                                                             */
/*����:Jelin                                                                                       */
/*ʱ��:2012-4-20  10:14                                                                              */
/*****************************************************************************************************/
/*===================================================================================================*/
/*****************************************************************************************************/
/*���ھ�̬��Ա����Ϊ��������������У��᲻�����һ�������ڴ����ַ���ʱ��һ������Ҳ�ڽ��д����أ�     */
/*�����ͻᵼ����ν�ġ��������ݡ�����ô���������ٽ�����������ͻ�İ취�ɣ�                           */
/*���ڿ��ܴ��ڶ���߳�ͬʱת���ַ��������⣬����ȥ��static����                                       */
/*��ˣ�����ת�����ָ������Լ�����Release()�ͷ�                                                    */
/*����:Jelin                                                                                       */
/*ʱ��:2012-12-27  16:38                                                                             */
/*****************************************************************************************************/