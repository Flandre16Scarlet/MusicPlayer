#pragma once


typedef struct _LYRIC_DATA
{
	int nStartTime;
	std::string strLyricText;
}LYRIC_DATA,*PLYRIC_DATA;
// CLyricsDlg �Ի���

class CLyricsDlg : public CDialog,   public CErrorLog,public CMemBase
{
	DECLARE_DYNAMIC(CLyricsDlg)

public:
	CLyricsDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLyricsDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_LYRICS };
	enum {left,right,top,bottom};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSetColor();
	afx_msg void OnSetFont();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnRBSetColor();
	afx_msg void OnRBSetFont();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSetOverColor();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	CRect m_rcClient;
	HFONT m_hFont;
	CString m_strShowText;
	std::vector<LYRIC_DATA*> m_vecLyricDatas;
	//�ۼ�ʱ��
	int m_nTotalTime;
	//��ǰ���ŵĸ������
	int m_nIndex;
	//��ʳ��ȴ��ڴ��ڳ��ȵ�ʱ�������ʶ
	BOOL m_bRoll;
	//��ʹ����Ƿ����
	BOOL m_bFinishRoll;
	//���浱ǰ�����DC�ϵ�ʵ�ʳ���
	int m_nTextExtent;
	RECT m_rcDraw;
	RECT m_rcOver;
	/***********************************************************/
	// �ж��Ƿ���Ըı䴰�ڴ�С
	BOOL m_bResizing;
	// ����������ɫ
	COLORREF m_cUnderColor;
	// �ж�����Ƿ��ڴ�����
	BOOL m_bMouseOver;
	int m_iDirect;
	// �жϸ���ļ��Ƿ����
	BOOL m_bFileExist;
	//���浱ǰ���Ÿ����ĸ���ļ�·��
	CString m_strCurLyricsPath;
	// ���ָ���ɫ
	COLORREF m_cOverColor;
	// ��¼��ǰ����ĸ߶�
	int m_nFontHeight;
	//���ڴ�С�Ƿ�ı���
	BOOL m_bSizeChange;
	//�Ƿ���������
	BOOL m_bLock;
	float m_fSpeed;
	CRITICAL_SECTION	cs;
protected:
	// �ֽ���ַ����е�ʱ��͸�����
	void AnaliseString(std::string& str);
	//�ͷ������ڵ�ָ��
	void ReleaseLyricDatas();
	//���Ƹ������
	void DrawLyricText(HDC hDC);
public:
	/******************************�ⲿ�ӿ�****************************/
	// �ı䵱ǰ��ʾ�ĸ�ʵ�ʱ��
	void ChangeCurTime(const int nTime);
	void FileNotExist();
	void SortLyricDatas();//�����ҵ�ʱ������
	void LockLyrics(BOOL ret);
	void SInvalide();
	void RInvalide();
	CString StrCurLyricsPath() const { return m_strCurLyricsPath; }
	void StrCurLyricsPath(const CString& strPath) { m_strCurLyricsPath = strPath; }
	// ��ȡ�ļ��д�ŵĸ�������Ϣ
	BOOL ReadLyricsDialogData(LPRECT pRect);
	// ��ȡ����ļ�
	BOOL ReadLyricsFile();
	// �����������Ϣ��XML�ļ�
	BOOL SaveLyricsDialogData(void);
	//��ȡ�����Ƿ���������Ϣ
	BOOL IsLock()const { return m_bLock; }
	virtual void OnCancel();
protected:
	virtual void PostNcDestroy();
};
