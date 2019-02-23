#pragma once
typedef struct _INDEX
{
	int nGroupNumber;//����
	int nIndex;//����ֵ
}INDEX;//������������1��ʼ����



// CImageCtrl

class CImageCtrl : public CWnd,public CErrorLog,public CMemBase
{
	DECLARE_DYNAMIC(CImageCtrl)

public:
	CImageCtrl();
	virtual ~CImageCtrl();
	/***********************************************/
	//�����ⲿ�ӿ�                                 */
	/***********************************************/
	void Init( CString& strImagePath,const CString& strTipText);
	//ѡ��
	void SetCheck() { m_bCheck=TRUE; Invalidate(); }
	//ȡ��ѡ��
	void UnCheck() { m_bCheck=FALSE; Invalidate(); }
	//λ����Ϣ���������ȡ
	void SetIndex(const int nGroupNumber,const int nIndex){m_owerIndex.nGroupNumber=nGroupNumber;m_owerIndex.nIndex=nIndex;}
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
private:
	//˫�����ͼ��Դ
	Gdiplus::Graphics* m_pGraphics;
	Gdiplus::Bitmap* m_pBackBitmap;
	//�ͻ�����С
	CRect m_rcClient;
	//���浱ǰͼƬ������·��
	CString m_strImagePath;
	BOOL m_bMouseOver;
	//������ʾ�Ļ�ˢ
	HBRUSH m_hOverBrush;
	HBRUSH m_hCheckBrush;
	//�Ƿ���ѡ��״̬
	BOOL m_bCheck;
	//�����Լ���λ����Ϣ
	INDEX m_owerIndex;
	//������ʾ�ؼ����ھ��
	HWND m_hTipWnd;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};


