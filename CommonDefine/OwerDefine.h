//////////////////////////////////////////////////////
//�Զ�����Ϣ����Ƚṹ

#pragma once 

/*****************************************************/
/*�Զ�����Ϣ                                         */
/*                                                   */
/*****************************************************/
#define MYWM_NOTIFYICON			WM_USER+101			//������Ϣ

//CDeleteDlg��Ϣ
#define WM_DELETE_OK			WM_USER+106			//ȷ��ɾ�������ļ�
#define WM_DELETE_CANCEL		WM_USER+107			//ȡ��ɾ�������ļ�

//�Զ���ϵͳ��ݼ�
#define WM_LOCK_LYRICS			WM_USER+109			//����\����������
#define WM_PLAY_NEXT			WM_USER+110			//��һ��
#define WM_PLAY_PREV			WM_USER+111			//��һ��
#define WM_PLAY					WM_USER+112					//����\��ͣ����
#define WM_HIDE_LYRICS			WM_USER+113			//��ʾ\���ظ�����
#define WM_SCREEN_CAPTURE		WM_USER+114			//����
#define WM_VOICE_RAISE			WM_USER+115			//�������
#define WM_VOICE_REDUCE			WM_USER+116			//��������

//ListBox�Ҽ��˵����͵��������Ϣ
#define WM_LISTBOX_MESSAGE		WM_USER+117
/****************************************************/
/*Ϊ�����ֲ�ͬ����Ϣ����WPARAM������
/*1			//�鿴��ʣ����������ʾ�Ի���
/*2			//�鿴������Ϣ
/*3			//ɾ���ڵ���Ϣ 
/*4			//˫���ڵ���Ϣ��LPARAM����˫���Ľڵ�����
/****************************************************/

//DeleteDialog���͵��������Ϣ
#define WM_DELETE_DIALOG		WM_USER+118
/****************************************************/
/*����ɾ���ɹ���ʧ���Լ�ȡ��
/*wParam=1					//�Ӳ����б���ɾ��
/*wParam=2					//ȡ��ɾ��
/****************************************************/
//SliderButton�����Ϣ
#define WM_SLIDER_SETPROGRESS	WM_USER+119			//�������������ؼ����ý���
#define WM_SLIDER_SETVOICE		WM_USER+120			//��������������

//CImageCtrl����Ϣ
#define WM_IMAGECTRL_MESSAGE	WM_USER+121
/***************************************************/
/*WPARAM����������Ϣ���
/*wParam=1					//���λ��ͼƬ�ؼ�֮��
/*wParam=2					//����뿪��ͼƬ�ؼ�
/*wParam=3					//ѡ���˸�ͼƬ��Ϊ����
/***************************************************/

//SetAttributeDlg����Ϣ
#define WM_SETATTRIBUTE_MESSAGE	WM_USER+122
/***************************************************/
/*WPARAM����������Ϣ���
/*wParam=1					//������������С
/*wParam=2					//������������С
/*wParam=3					//���ڲ��ű�����
/*wParam=4                  //���ڲ�������
/*wParam=5                  //���ڲ����ٶ�
/***************************************************/



/*****************************************************/
/*�Զ���DLL���������ʽ                              */
/*                                                   */
/*****************************************************/
#define EXPORT_CLASS class __declspec(dllexport)
#define IMPORT_CLASS class __declspec(dllexport)


/*****************************************************/
/*�Զ�����滻                                       */
/*                                                   */
/*****************************************************/

//�˵�����
#define MENU_PLAY				_T("����     Ctrl+Alt+P")
#define MENU_PAUSE				_T("��ͣ     Ctrl+Alt+P")
#define MENU_PREV				_T("��һ��  Ctrl+Alt+��")
#define MENU_NEXT				_T("��һ��  Ctrl+Alt+��")

#define MENU_UNLOCK_LYRIC		_T("�������  Ctrl+Alt+L")
#define MENU_LOCK_LYRIC			_T("�������  Ctrl+Alt+L")
#define MENU_HIDE_LYRIC			_T("���ظ��  Ctrl+Alt+H")
#define MENU_SHOW_LYRIC			_T("��ʾ���  Ctrl+Alt+H")

#define MENU_SINGLE_PLAY		_T("��������(&O)")
#define MENU_ORDER_PLAY			_T("˳�򲥷�(&C)")
#define MENU_RAND_PLAY			_T("�������(&R)")





/*****************************************************/
/*���弸�ֳ������쳣����                             */
/*                                                   */
/*****************************************************/
#define CREATE_COMDC_ERROR			"�����ڴ����DCʧ�ܣ�"
#define CREATE_COMBITMAP_ERROR		"�����ڴ����λͼʧ�ܣ�"
#define BITBLT_ERROR				"BitBlt��ͼʧ�ܣ�"
#define GDIPLUS_DRAWIMAGE_ERROR		"GDI+��ͼʧ�ܣ�"
#define GETBACK_HBITMAP_ERROR		"��ȡ����λͼ���ʧ�ܣ�"
#define LOAD_RESOURCE_ERROR			"������Դ�ļ�ʧ�ܣ�"
#define NULL_POINT_ERROR			"ָ��Ϊ�գ�"
#define EMPTY_BUFFER_ERROR			"ָ��ָ��Ļ�����Ϊ�գ�"
#define OPEN_FILE_ERROR				"���ļ�ʧ�ܣ��������ļ������ڣ�"
#define READ_FILE_ERROR				"��ȡ�ļ�ʧ�ܣ�"
#define PARAMETER_ERROR				"�����������"
#define UNKNOW_ERROR				"δ֪�쳣��"
#define GETOBJECT_ERROR				"��ȡGDI������Ϣʧ�ܣ�"