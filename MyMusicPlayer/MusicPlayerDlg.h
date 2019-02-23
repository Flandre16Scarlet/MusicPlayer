// MyMusicPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include <vector>
#include "Resource.h"
#include "libzplay.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "NoLyricsDlg.h"
#include "direct.h"
#include "PlayListBox.h"
#include "atltypes.h"
#include "VoiceSliderButton.h"
#include "ProgressSliderButton.h"
#include "DrawStatic.h"

#pragma comment(lib,"libzplay.lib")
#include <wtypes.h>
using namespace libZPlay;
/*********************************************************************************/
// ��ģ��Ľӿ�����

//������Դ���
void ShowAttributeDlg();
void ReleaseAttributeDlg();
////////////////////////////////////////////
//�����崰��
BOOL InitLyricsDlg();
void ShowLyricsDlg(BOOL bShow);
void ReleaseLyricsDlg();
void SendLyricsMsg(std::wstring& ws);
void SetLyricsTime(int nCurTime);
void StopInvalide();
void ReInvalide();
void SetLyricsColor();
void SetLyricsFont();
void NoLyricsFile();
void LockLyricsDlg(BOOL lock);
////////////////////////////////////////////
//ɾ����������
void ShowDeleteDlg(std::wstring& ws);
void ReleaseDeleteDlg();
void ShowInfoDlg(std::wstring& ws);
void ReleaseInfoDlg();
////////////////////////////////////////////
//��������
void InitChangeClothDlg(const BYTE bValue,const CString& strBackImagePath);
void ReleaseChangeClothDlg();
BOOL ShowChangeClothDlg();
BOOL HideChangeClothDlg();
/*********************************************************************************/
//using namespace std;

//���������ṹ
typedef struct _RECT_DATA
{
	CRect rcBig;
	CRect rcSmall;
}RECT_DATA,*PRECT_DATA;
//ö�ٲ���ģʽ
typedef enum{
	single_play,order_play,rand_play
}PLAYMODE;
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
#include "StarWarsCtrl.h"
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
private:
	CStarWarsCtrl m_transparent;
public:
	//afx_msg void OnStnClickedAbout();
private:
	// ��ǰ�����Ƿ��Ѿ����
	BOOL m_bMax;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CRect client;
public:
	afx_msg void OnStnDblclickAbout();
};
// CMyMusicPlayerDlg �Ի���

class CMusicPlayerDlg : public CDialog,	public CErrorLog,CMemBase
{
// ����
public:
	CMusicPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYMUSICPLAYER_DIALOG };
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	/*****************************************************************************/
	/*                               ���ſ��ƹ��ܺ���                            */
	/*****************************************************************************/
	//�鿴����ļ�
	void ShowLyricFile();
	/*****************************************************************************/
	/*                              ��ʼ���ӿؼ�����λ��                         */
	/*****************************************************************************/
	void InitButtons(void);
	// Ҫ��MINI������д��ʱ���ذ�ť
	void HideButtons(void);
	// MINI��������������ʾ��ť
	void ShowButtons(void);
	//ע��ϵͳ�ȼ�
	void RegisterHotKeys(void);
	//��ʼ���ļ��б�
	void InitFile();
	/*****************************************************************************/
	/*                                �����б��ά��                             */
	/*****************************************************************************/
	// ����ļ��������пɲ����ļ��������б�
	void AddFolderFiles(const CString& strDir);
	// ����ļ����������б�����
	void AddPlayListToPlayer(const int nStartPos=0);
	// ɾ�������б��е�ǰѡ�еĽڵ�
	void DeleteSelectItem(void);
	//��ʾĬ�ϲ����б�
	void ShowDefaultPlayList(void);
	//��ʾ�ҵ��ղ��б�
	void ShowEnjoyPlayList(void);
private:
	/*****************************************************************************/
	/*                              ���Ʊ����Լ����ֺ���                         */
	/*****************************************************************************/
	void DrawMyText(HDC hDC);
	void DrawMyTextA(HDC hDC);
	// ���ƶ�̬�����̣߳�û��ͼƬʱ�����̣߳���ͼƬ�ر��߳�
	void DrawPictrue(BOOL run);
	// MINI�����ϻ������� 
/*	void DrawTextOnMiniWindow(HDC hDC);*/
	void ReBeginDrawText(void);
	//����رպ��ͷ���Դ
	void Release();
	//��ʾ���˵�
	void ShowMainMenu();
	/*****************************************************************************/
	/*                            ����״̬����߳̿��ƺ���                       */
	/*****************************************************************************/	
	//��������״̬����߳�
	inline void StartPlayModeThread();
	//��������״̬����߳�
	inline void StopPlayModeThread();
private:
	/*****************************************************************************/
	/*                                  �ؼ�����                                 */
	/*****************************************************************************/
	CSkinButton m_btnExit;
	CSkinButton m_btnHide;
	CSkinButton m_btnMini;
	CSkinButton m_btnPrev;
	CSkinButton m_btnPlay;
	CSkinButton m_btnNext;
	// ����Ƥ����ť
	CSkinButton m_btnCloth;
	//Ĭ�ϲ����б�ť
	CSkinButton m_btnDefaultList;
	//�ҵ��ղذ�ť
	//CSkinButton m_btnEnjoyList;
	// ������
	CProgressSliderButton m_btnProcess;
	CSkinButton m_btnAdd;
	// �ҵ��ղ��б�,δ���
	//CListBox m_enjoyPlaylist;
	// �������ð�ť
	CSkinButton m_btnVoiceQuiet;
	// ����������С
	CVoiceSliderButton m_btnVoiceSetting;
	// ���Ʋ���ģʽ
	CSkinButton m_btnPlayMode;
	// ���ͷ�����Ϣ��ť
	CLinkButton m_btnFeedBack;
	//��ʾ����ʱ����ȵĿؼ�
//	CDrawStatic m_ctrlTime;
	/*****************************************************************************/
	/*                                 ˽�г�Ա����                              */
	/*****************************************************************************/
	//�Ƿ���MINI����״̬
	BOOL m_bMiniStyle;
	// ���ڲ��ŵ��ļ�����·����
	//CString m_strPlayFilePath;
	std::vector<CString> m_playList;
	// ��ǰ��Ŀ��ʱ��
	UINT m_uMinuteCount;
	UINT m_uSecondCount;
	UINT m_uCurrentMinute;
	UINT m_uCurrentSecond;
	UINT m_uPlayVolume;//������
	// �Ƿ���
	BOOL m_bQuietVoice;
	// �ж���ʱ�Ƿ����
	BOOL m_bTimeOver;
	// �Ƿ��ܹ���MINI�����ϻ�������
//	BOOL m_bDrawMiniText;
	// ������Ϣ�Ի���ָ��
	BOOL m_bMouseOverVoice;//MouseOnProgress;
//	BOOL m_bPlayListFlag;
	// ����ͼƬ��·��
	CString m_strPictruePath;
	int m_rollFlag;
	CString m_strText;
	CString m_strTitle;
	// �жϵ�ǰ�����Ƿ񵽴�����x=38��
	BOOL m_IsGet;
	// ����CStringָ������
	int m_index;
	// ָʾ�������Ƿ���ʾ
	BOOL m_bShowLyrics;
	// �жϸ���ļ��Ƿ����
	BOOL m_bLyricExist;
	// ��ȡ�����������
	int m_iIndex;
	// �жϸ������Ƿ�����
	BOOL m_bLockLyrics;
	//CHotKeyCtrl m_hotKey;
	NOTIFYICONDATA nd;
	// ����λͼ����
	CString m_strBmpName;
	TID3InfoExW id3_infoEx;
	//�����ڴ����DC���
// 	HDC m_hBkMemDC;
// 	//����λͼ���
// 	HBITMAP m_hBkMemBitmap;
	//������
	HFONT m_hFont;
	//GDI+��ͼָ��
	Gdiplus::Graphics* m_pGraphic;
	//����ͼƬָ��
	Gdiplus::Bitmap* m_pBackBitmap;
	//����ͼƬָ��
	Gdiplus::Image* m_pAuthorImage;
	//���浱ǰ���ڵĴ�С
	//CRect m_rcClient;
	//���洰�ڵĿ��
	int m_nWidth;
	//���洰�ڵĸ߶�
	int m_nHeight;
	//����ģ��·��
	CString m_strModulePath;
	//�Ƿ����ڽ����ı�ʶ
	BOOL m_bCaptureFlag;
	//��ʾ���Ÿ�����ʱ�����
	CString m_strProgressTime;
	//������ʱ����ͼƬ��·��
	CString m_strTempBackImage;
	//�����û�ѡ��ı���ͼƬ��·��
	CString m_strSelectBackImage;
	// ָʾ�Ƿ���ʾ�����Ի���
	BOOL m_bShowChangeClothDlg;
	//ALPHA͸����
	BYTE m_bAlphaValue;
public:
		/*****************************************************************************/
		/*                                 ��Ϣ��Ӧ����                              */
		/*****************************************************************************/
		afx_msg void OnIconExit();
		afx_msg void OnBnClickedVoice();
		afx_msg void OnBnClickedPrev();
		afx_msg void OnBnClickedPlay();
		afx_msg void OnBnClickedNext();
		afx_msg void OnBnClickedPlaymode();
		afx_msg void OnChangeCloth();
		afx_msg void OnModeOnly();
		afx_msg void OnModeOrder();
		afx_msg void OnModeRand();
		afx_msg void OnAddDeleteAll();
		afx_msg void On32785Play();
		afx_msg void On32783Prev();
		afx_msg void On32784Next();
		afx_msg void OnIconSetAttributes();
		afx_msg void On32789();
		afx_msg void On32788();
		afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnShowLyricsDlg();
		afx_msg void OnSetLyricsColor();
		afx_msg void OnSetLyricsFont();
		afx_msg LRESULT OnHotKey(WPARAM wParam,LPARAM lParam);
		afx_msg void OnLyricsLock();
		afx_msg void OnSendEmail();
		afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
/*		afx_msg void OnBnClickedMyLike();*/
		afx_msg void OnBnClickedExit();
		afx_msg void OnBnClickedHide();
		afx_msg void OnBnClickedMini();
		afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		afx_msg void OnAddFile();
		afx_msg void OnAddFolder();
		afx_msg BOOL OnEraseBkgnd(CDC* pDC);
		afx_msg void OnBnClickedAdd();
		afx_msg void OnIconAbout();
//		afx_msg void OnBnClickedList1();
		afx_msg void OnTimer(UINT_PTR nIDEvent);
		//��ҷ�ļ�����
		void GetDropFiles(HDROP hDrop);
		/*****************************************************************************/
		/*                              ϵͳ����ͼ�괦����                         */
		/*****************************************************************************/
		//��������ͼ��
		void CreateNotifyIcon(CString strTip=_T("Love Music,Love Life"));
		//ɾ������ͼ��
		void DeleteNotifyIcon(void);
		//����ͼ����Ϣ��Ӧ
		LRESULT OnNotifyIcon(WPARAM wParam,LPARAM lParam);
		/*****************************************************************************/
		/*                                ��̬���ܺ���                               */
		/*****************************************************************************/
		// ��ͼƬ����
		static void SaveBitmap(HBITMAP hBmp,CString& strFullName);
		// �ж��Ƿ���֧�ֵ��ļ�����
		inline static BOOL IsSupportFile(const CString& strFileName);
		inline static CString GetShortName(const CString& strFullName);
		/*****************************************************************************/
		/*                              �ⲿ�ӿں���                                 */
		/*****************************************************************************/
		//��ȡ�������ÿؼ���ָ��
		CSliderButton* GetVoiceSettingCtrl() { return &m_btnVoiceSetting; }
		// �жϵ�ǰ����Ƿ���������
		BOOL IsCursorInRect(CRect& rc);
		// ���ý���ģ���DLL����ʼ����
		void OnScreenCapture(void);
		// ��ȡ�ļ���Ϣ�����ò�������
		void CreateListFile(const CString& strPath);
		void CreateConfigFile(const CString& strPath);
		void ReadConfig();
		// ��������Ϣ����д���ļ�
		void WriteListFile();
		// ��ʼ�����ļ�
		void StartPlay(void);
		//����ͼƬĿ¼����
		CString GetPictruePath() const { return m_strPictruePath; }
		void SetPictruePath(const CString& val) { m_strPictruePath = val; }
		void ChangePlayerVoice(const int nValue)
		{
			VERIFY(0!=nValue);//������0������
			if((nValue>0&&!m_btnVoiceSetting.MaxTest())||(nValue<0&&!m_btnVoiceSetting.MinTest()))//��������
			{
				int nPos=m_btnVoiceSetting.GetCurPos();
				nPos+=nValue;
				m_btnVoiceSetting.SetCurPos(nPos);
				player->SetPlayerVolume(nPos,nPos);
			}
		}
		BOOL LyricFileExist()const {return m_bLyricExist;}
		//��������ͼƬ
		void ChangeBack();
		static ZPlay* player;
		// ��ǰ������Ŀ������
		static int m_nowPlayIndex;
		// �Ƿ����ڲ���
		static BOOL m_bPlaying;
		CPlayerList m_defPlaylist;
};
/////////////////////////////////////////////////////////////////////////////////////////////
//�������������������ﴦŮ����ǡ��������������������//
/*******************************************************************************************/
/*���������ر𲻺ã����ڻ������ϣ����˴�Լһ����д��һǧ���д��룬
/*ȫ����������룬������������ᰡ����
/*ʱ�䣺2011-11-9
/*******************************************************************************************/
/*�����ϰ಻æ������ǰд�����߰���Ĵ�������£�����������ע�͡��ӿڡ���
/*���ֳ���ܶ�ط������Ż�����ʱ��Ļ��һ�����ĵ�
/*ʱ�䣺2012-11-16 11:18:55
/*******************************************************************************************/