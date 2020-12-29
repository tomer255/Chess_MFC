
// MFCchassDlg.h : header file
//

#pragma once


// CMFCchassDlg dialog
class CMFCchassDlg : public CDialogEx
{
// Construction
public:
	CMFCchassDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHASS_DIALOG };
#endif
	bool isPressed;
	CPoint startP;
	CPoint endP;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CString turnDS;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton5();
};
