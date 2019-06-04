
// MFCCalculatorDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCCalculator.h"
#include "MFCCalculatorDlg.h"
#include "afxdialogex.h"

#include "Evaluator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 对话框



CMFCCalculatorDlg::CMFCCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCALCULATOR_DIALOG, pParent)
	, editString1(_T(""))
	, editString2(_T(""))
	, editString3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, editString1);
	DDX_Text(pDX, IDC_EDIT2, editString2);
	DDX_Text(pDX, IDC_EDIT3, editString3);
	DDX_Control(pDX, IDC_EDIT1, edit1);
}

BEGIN_MESSAGE_MAP(CMFCCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
//	ON_EN_CHANGE(IDC_EDIT1, &CMFCCalculatorDlg::OnEnChangeEdit1)
ON_EN_KILLFOCUS(IDC_EDIT1, &CMFCCalculatorDlg::OnEnKillfocusEdit1)
ON_BN_CLICKED(IDC_BUTTON15, &CMFCCalculatorDlg::OnBnClickedButtonGetAnswer)
ON_BN_CLICKED(IDC_BUTTON3, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON27, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON26, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON23, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON24, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON25, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON17, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON9, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON10, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON11, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON12, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON6, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON4, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON16, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON7, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON5, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON8, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON22, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON18, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON13, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON14, &CMFCCalculatorDlg::OnBnClickedButtonInsert)
ON_BN_CLICKED(IDC_BUTTON20, &CMFCCalculatorDlg::OnBnClickedButtonBackspace)
ON_BN_CLICKED(IDC_BUTTON19, &CMFCCalculatorDlg::OnBnClickedButtonClear)
ON_BN_CLICKED(IDC_BUTTON21, &CMFCCalculatorDlg::OnBnClickedButtonClear)
ON_BN_CLICKED(IDC_BUTTON35, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON31, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON29, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON33, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON28, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON32, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON30, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON34, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON36, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
ON_BN_CLICKED(IDC_BUTTON37, &CMFCCalculatorDlg::OnBnClickedButtonInsertFunction)
END_MESSAGE_MAP()


// CMFCCalculatorDlg 消息处理程序

BOOL CMFCCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CMFCCalculatorDlg::OnEnKillfocusEdit1()
{
	
}

//= btn
void CMFCCalculatorDlg::OnBnClickedButtonGetAnswer()
{
	// TODO: 在此添加控件通知处理程序代码
	//GetDlgItem(IDC_EDIT1)->GetWindowTextW; //获取编辑框文本方法一
	UpdateData(); //默认参数为True，表示更新编辑框数据到变量
	CString S = editString1; //编辑框1字符串
	if (S.GetLength() == 0) return;
	S.Replace(_T("π"), _T("3.14159265358979"));
	S.Replace(_T("e"), _T("2.71828182845904"));

	char* rpn = (char *)malloc(sizeof(char) * 1024);
	CStringA SA(S);
	static char buf[1024];
	sprintf(buf, "%s", (char*)SA.GetString());
	double res = Evaluator().evaluate(buf, rpn);
	CString S1, S2(rpn);
	S1.Format(_T("%f"), res);
	editString2 = S1;
	editString3 = S2;
	UpdateData(false); //参数为false表示更新变量到编辑框
	
}

//共享click事件,插入数字或运算符
void CMFCCalculatorDlg::OnBnClickedButtonInsert()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos = edit1.CharFromPos(edit1.GetCaretPos()); //获取光标位置
	CString text;
	WPARAM now = GetCurrentMessage()->wParam; //获取调用者编号
	GetDlgItem(now)->GetWindowTextW(text); //获取调用者的文本

	UpdateData(); //默认参数为True，表示更新编辑框数据到变量
	CString S = editString1; //编辑框1字符串
	editString1.Insert(pos, text); //插入文本
	UpdateData(false); //参数为false表示更新变量到编辑框

}

//共享click事件,插入数学函数
void CMFCCalculatorDlg::OnBnClickedButtonInsertFunction()
{
	int pos = edit1.CharFromPos(edit1.GetCaretPos()); //获取光标位置
	CString text;
	WPARAM now = GetCurrentMessage()->wParam; //获取调用者编号
	GetDlgItem(now)->GetWindowTextW(text); //获取调用者的文本
	if (text.Compare(_T("x²")) == 0)
	{
		text = _T("^2");
	}
	else if (text.Compare(_T("√")) == 0)
	{
		text = _T("^0.5");
	}
	else
	{
		text.Append(_T("(")); //为数学函数添加左括号
	}
	UpdateData(); //默认参数为True，表示更新编辑框数据到变量
	CString S = editString1; //编辑框1字符串
	editString1.Insert(pos, text); //插入文本
	UpdateData(false); //参数为false表示更新变量到编辑框
}

//退格键
void CMFCCalculatorDlg::OnBnClickedButtonBackspace()
{
	// TODO: 在此添加控件通知处理程序代码
	int pos = edit1.CharFromPos(edit1.GetCaretPos()); //获取光标位置
	UpdateData(); //默认参数为True，表示更新编辑框数据到变量
	CString S = editString1; //编辑框1字符串
	if (pos > 0) editString1.Delete(pos - 1, 1); //删除一个字符
	UpdateData(false); //参数为false表示更新变量到编辑框
}

//清空键
void CMFCCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(); //默认参数为True，表示更新编辑框数据到变量
	editString1 = CString(); //清空文本框
	editString2 = CString(); //清空文本框
	editString3 = CString(); //清空文本框
	UpdateData(false); //参数为false表示更新变量到编辑框
}

