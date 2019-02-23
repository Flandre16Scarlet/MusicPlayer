/*********************************************************************************************************/
/*������ʵ�ʿ��������У��漰����������������ļ���ȡ�����Ƶ�����Լ�C++�����ļ���ĳЩ����                */
/*������c++�ļ�������ʵ�֣�ò����ײ�Ҳ����c����ʵ�ֵ�                                                   */
/*���Ǿ����Լ���c++�ѱ�׼C���ļ�����װ����,�Ժ�������Ҳ�ȽϷ���                                          */
/*�������ޣ���ӭ���ߴͽ�                                                                                 */
/*author:Jelin                                                                                           */
/*time:2012-5-6  17:19                                                                                   */
/*********************************************************************************************************/
#ifndef READFILE_H_
#define READFILE_H_
#include "..\\CommonDefine\\StandarC++.h"
#include "ErrorLog.h"
#include <assert.h>

/*********************************************************/
//���弸�ֳ����ı�������
typedef enum{
	ansi,utf8,unicode,big_unicode,unknow
}CODETYPE;

EXPORT_CLASS CReadFile:public CErrorLog
{
public:
	//�����ļ���λ�ñ�ʶ
	CReadFile(const char* pFile);
	CReadFile(const wchar_t* pFile);
	virtual~CReadFile();

	//��ȡcount����СΪsize �ֽڵ�������
	bool Read(void *buffer,const int zise,const int count);
	//��ȡ�ļ���һ�У�countС��һ���ַ�������ʱ���ض�
	bool ReadLine(char* buffer,const int nCount=MAX_PATH);
	bool ReadLine(std::string& s,const int nCount=MAX_PATH);
	bool ReadLine(std::wstring& ws,const int nCount=MAX_PATH);
	//��ȡ�ļ��������ݵ�������
	void GetBuffer(char* buffer);
	//�˺�����Կ��ַ�������ļ���ANSI�½���ʹ��char*�����ĺ���
	void GetBuffer(wchar_t* buffer);
	void GetBuffer(std::string& s);
	//��λ�ļ�ָ�뵽ָ��λ��,��һ���������ƶ����ַ������ڶ�������Ĭ��������Ǵӵ�ǰλ�ÿ�ʼ(begin,current,end)
	bool Seek(const long lOffset,const int nFlag=SEEK_CUR);
	/*********************************************************************/
	//�������ܺ���
	/*********************************************************************/
	//�ж��ļ��Ƿ��Ѿ���
	inline bool IsOpen()const;
	//�ж��ļ�ָ���Ƿ񵽴�ĩβ
	inline bool IsEof()const;
	//��ȡ�ļ�ָ��λ��
	inline long GetPos()const;
	//�ͷ��ļ���Դ
	inline void Release();
	//��ȡ�ļ����뷽ʽ,����ֵ:0->ANSI����.1->UTF-8����,2->UNICODE����,3->BIG_UNICODE����
	inline CODETYPE GetFileCodeType()const ;
	//�ļ�ָ��ص��ļ���ʼ��
	inline void Rewind();
	//��ȡ�ļ��ĳ��ȣ��ֽ���)
	inline long GetLength();
	//��ȡһ���ֽ�
	inline int GetChar();

protected:
	//��ȡ�ļ��ı��뷽ʽ�������������ֽ�
	bool SkipCodeType();
private:
	//�ļ�ָ��
	FILE* m_ptrFile;
	//�����ļ��ı�������
	CODETYPE m_ctType;
};
#endif;