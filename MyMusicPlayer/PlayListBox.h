#pragma once

// CPlayListBox


class CPlayerList : public CListBox ,public CErrorLog,public CChangeBackBase,CMemBase
{
	DECLARE_DYNAMIC(CPlayerList)

public:
	CPlayerList();
	virtual ~CPlayerList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnListboxAttribute();
	afx_msg void OnListboxDeleteItem();
	//�����Ի�ؼ�
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	//����AddString����
	int AddString(LPCTSTR lpszItem);
	//����
	void ChangeBack() { m_bChangeBack=TRUE;Invalidate(); }
private:
	// ��ȡ������ָ��
	CWnd* m_pParent;
	//�ͻ��Ⱦ���
	CRect m_rcClient;
	//ÿ���ڵ�ĸ߶�
	int m_nHeight;
	//ˮƽ���������ֵ��ٽ�ֵ
	int m_nMaxWidth;
	SCROLLINFO m_hScrollInfo;
	//������
	HFONT m_hFont;
	HPEN m_hPen;
	//��ǰ�������λ������
	int m_nCursorPos;
public:
	afx_msg void OnListboxLookLyrics();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//�ü��������ɫ����������
	void DrawColorItem(HDC hdc,const CRect& rect);
	//���Ƽ������
	void DrawLines(HDC hdc);
	//��ȡ�������Ĵ�С����Ϣ,��������
	void GetSInfo(SCROLLINFO& sInfo,const int nFlag =SB_HORZ);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


