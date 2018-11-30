// NewForm.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_DEMO.h"
#include "NewForm.h"
#include "afxdialogex.h"


// NewForm 对话框

IMPLEMENT_DYNAMIC(NewForm, CDialogEx)

NewForm::NewForm(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	
	//, enter1(_T(""))
	//, enter3(0)
{

}

NewForm::~NewForm()
{
}

void NewForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_SCROLLBAR1, m_horiScrollbar1);
	//DDX_Text(pDX, IDC_EDIT2, enter1);
	//DDV_MaxChars(pDX, enter1, 255);
	//DDX_Text(pDX, IDC_EDIT3, enter3);
	//DDV_MinMaxInt(pDX, enter3, 0, 255);
}


BEGIN_MESSAGE_MAP(NewForm, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &NewForm::OnEnChangeEdit1)
	ON_WM_HSCROLL()
	ON_NOTIFY(NM_THEMECHANGED, IDC_SCROLLBAR1, &NewForm::OnNMThemeChangedScrollbar1)
	ON_COMMAND(ID_32787, &NewForm::On32787)
	ON_EN_CHANGE(IDC_EDIT2, &NewForm::OnEnChangeEdit2)
	ON_COMMAND(ID_32785, &NewForm::On32785)
	ON_BN_CLICKED(IDC_BUTTON1, &NewForm::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &NewForm::OnBnClickedButton2)
END_MESSAGE_MAP()



// 函数功能：返回保存的 int  


// NewForm 消息处理程序
BOOL NewForm::OnInitDialog()
{
	CDialogEx::OnInitDialog();


	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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
	//SetIcon(m_hIcon, TRUE);			// 设置大图标
	//SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	// 设置水平滚动条的滚动范围为1到100   
	m_horiScrollbar1.SetScrollRange(1, 100);
	// 设置水平滚动条的初始位置为20   
	m_horiScrollbar1.SetScrollPos(20);
	// 在编辑框中显示20   
	SetDlgItemInt(IDC_EDIT1, 20);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void NewForm::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}



void NewForm::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	//int pos = m_horiScrollbar1.GetScrollPos();    // 获取水平滚动条当前位置
	
	pos = m_horiScrollbar1.GetScrollPos();
	switch (nSBCode)
	{
		// 如果向左滚动一列，则pos减1  
	case SB_LINELEFT:
		pos -= 1;
		break;
		// 如果向右滚动一列，则pos加1  
	case SB_LINERIGHT:
		pos += 1;
		break;
		// 如果向左滚动一页，则pos减10  
	case SB_PAGELEFT:
		pos -= 10;
		break;
		// 如果向右滚动一页，则pos加10  
	case SB_PAGERIGHT:
		pos += 10;
		break;
		// 如果滚动到最左端，则pos为1  
	case SB_LEFT:
		pos = 1;
		break;
		// 如果滚动到最右端，则pos为100  
	case SB_RIGHT:
		pos = 100;
		break;
		// 如果拖动滚动块滚动到指定位置，则pos赋值为nPos的值  
	case SB_THUMBPOSITION:
		pos = nPos;
		break;

		// 下面的m_horiScrollbar.SetScrollPos(pos);执行时会第二次进入此函数，最终确定滚动块位置，并且会直接到default分支，所以在此处设置编辑框中显示数值  
	default:
		SetDlgItemInt(IDC_EDIT1, pos);
		//return pos;
	}

	// 设置滚动块位置  
	m_horiScrollbar1.SetScrollPos(pos);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}








void NewForm::OnNMThemeChangedScrollbar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// 该功能要求使用 Windows XP 或更高版本。
	// 符号 _WIN32_WINNT 必须 >= 0x0501。
	// TODO: 在此添加控件通知处理程序代码

	//IplImage*out = SaveImage();
	UpdateData(TRUE);

	//zhi = canshu;
	// TODO: 在此添加控件通知处理程序代码
	//UpdateData(FALSE);
	CDialog::OnOK();
	*pResult = 0;
}


void NewForm::On32787()
{

}


void NewForm::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}




void NewForm::On32785()
{
	// TODO: 在此添加命令处理程序代码

	//IplImage*out = SaveImage();
	
}

//确定
void NewForm::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	NewForm::OnOK();
}

//取消
void NewForm::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	NewForm::OnCancel();
}


//void NewForm::OnCancel()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	DestroyWindow();
//	CDialogEx::OnCancel();
//}
