#pragma once
#include <windows.h>
#include <iostream>
using std::cout;
using std::endl;
class CFileAttribute
{
public:
	CFileAttribute(const wchar_t* fileName);
	~CFileAttribute(void);
	//�����ļ���С��KBΪ��λ)
	float GetSize()const;
	SYSTEMTIME GetCreateTime()const;//��ȡ�ļ�����ʱ��
	SYSTEMTIME GetAccessTime()const;//��ȡ�ļ�������ʱ��
	SYSTEMTIME GetWriteTime()const;//��ȡ�ļ����д��ʱ��
	SYSTEMTIME FiletimeToSystemtime(const FILETIME& ft)const;
	BOOL GetFileAttribute();//��ȡ�ļ�����
	void ResetFile(const wchar_t* fileName);//�ı��ļ�
private:
	wchar_t* pFile;//ָ���ļ���ָ��
	WIN32_FILE_ATTRIBUTE_DATA attributeData;
};
