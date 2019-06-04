
// MFCCalculatorDlg.h: 头文件
//

#pragma once


// CMFCCalculatorDlg 对话框
class CMFCCalculatorDlg : public CDialogEx
{
// 构造
public:
	CMFCCalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnKillfocusEdit1();
	CString editString1;
	CString editString2;
	CString editString3;
	afx_msg void OnBnClickedButtonGetAnswer();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonInsertFunction();
	CEdit edit1;
	afx_msg void OnBnClickedButtonBackspace();
	afx_msg void OnBnClickedButtonClear();
};
