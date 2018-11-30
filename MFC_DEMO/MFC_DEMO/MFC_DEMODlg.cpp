// MFC_DEMODlg.cpp : 实现文件
//
#include <opencv2/opencv.hpp>

#include "stdafx.h"
#include "MFC_DEMO.h"
#include "MFC_DEMODlg.h"
#include "afxdialogex.h"
#include "NewForm.h"
#include "newform2.h"
//#include "newform1.h"
#include "newform6.h"
using namespace cv;
using namespace std;
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


// CMFC_DEMODlg 对话框


CMFC_DEMODlg::CMFC_DEMODlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_pTipDlg = NULL;
}

void CMFC_DEMODlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON1, StopButton);
}

BEGIN_MESSAGE_MAP(CMFC_DEMODlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_COMMAND(ID_32774, &CMFC_DEMODlg::On32774)
	ON_COMMAND(ID_32789, &CMFC_DEMODlg::On32789)
	ON_COMMAND(ID_32790, &CMFC_DEMODlg::On32790)
	ON_COMMAND(ID_32794, &CMFC_DEMODlg::On32794)
	ON_COMMAND(ID_32795, &CMFC_DEMODlg::On32795)
	ON_COMMAND(ID_32796, &CMFC_DEMODlg::On32796)
	ON_COMMAND(ID_32798, &CMFC_DEMODlg::On32798)
	//ON_COMMAND(ID_32801, &CMFC_DEMODlg::On32801)
	ON_STN_CLICKED(IDCANCEL, &CMFC_DEMODlg::OnStnClickedCancel)
//	ON_COMMAND(ID_Menu32802, &CMFC_DEMODlg::OnMenu32802)
	ON_COMMAND(ID_32799, &CMFC_DEMODlg::On32799)
	//ON_COMMAND(ID_32791, &CMFC_DEMODlg::On32791)
	ON_COMMAND(ID_32793, &CMFC_DEMODlg::On32793)
	ON_COMMAND(ID_32807, &CMFC_DEMODlg::On32807)
	//ON_COMMAND(ID_32808, &CMFC_DEMODlg::On32808)
	ON_COMMAND(ID_32809, &CMFC_DEMODlg::On32809)
	ON_COMMAND(ID_32810, &CMFC_DEMODlg::On32810)
	ON_COMMAND(ID_32775, &CMFC_DEMODlg::On32775)
	ON_COMMAND(ID_32811, &CMFC_DEMODlg::On32811)
	ON_COMMAND(ID_32812, &CMFC_DEMODlg::On32812)
	ON_COMMAND(ID_32813, &CMFC_DEMODlg::On32813)
	ON_COMMAND(ID_32814, &CMFC_DEMODlg::On32814)
	//ON_BN_CLICKED(IDC_BUTTON1, &CMFC_DEMODlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFC_DEMODlg 消息处理程序

BOOL CMFC_DEMODlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CMenu menu;
	//menu.LoadMenuA(IDR_MENU2);  //IDR_MENU1为菜单栏ID号  
	menu.LoadMenuA(IDR_MENU2);
	SetMenu(&menu);

	//m_Menu.LoadMenu(IDR_MENU1);
	//SetMenu(&m_Menu);

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
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	namedWindow("view", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDC_STATIC)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	namedWindow("view2", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND)cvGetWindowHandle("view2");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDD_DIALOG1)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);

	//namedWindow("view3", WINDOW_AUTOSIZE);
	//HWND hWnd3 = (HWND)cvGetWindowHandle("view3");
	//HWND hParent3 = ::GetParent(hWnd3);
	//::SetParent(hWnd3, GetDlgItem(IDCLOSE)->m_hWnd);
	//::ShowWindow(hParent3, SW_HIDE);



	// 设置水平滚动条的滚动范围为1到100   
    // m_horiScrollbar1.SetScrollRange(1, 100);
	// 设置水平滚动条的初始位置为20   
	// m_horiScrollbar1.SetScrollPos(20);
	// 在编辑框中显示20   
	//SetDlgItemInt(IDC_EDIT1, 20);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}




void CMFC_DEMODlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFC_DEMODlg::OnPaint()
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
HCURSOR CMFC_DEMODlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





//显示到第一个Pic控件
void CMFC_DEMODlg::ShowPic_1(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view", imagedst);
}
//显示到第二个Pic控件
void CMFC_DEMODlg::ShowPic_2(Mat input_2)
{
	Mat imagedst;
	CRect rect2;
	GetDlgItem(IDD_DIALOG1)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(input_2, imagedst, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view2", imagedst);
}
//显示到第三个Pic控件
//void CMFC_DEMODlg::ShowPic_3(Mat input_3)
//{
//	Mat imagedst;
//
//	CRect rect3;
//	GetDlgItem(IDCLOSE)->GetClientRect(&rect3);
//	Rect dst3(rect3.left, rect3.top, rect3.right, rect3.bottom);
//	resize(input_3, imagedst, cv::Size(rect3.Width(), rect3.Height()));
//	imshow("view3", imagedst);
//}
//打开
void CMFC_DEMODlg::On32774()
{
     open2();
	//string ext = strrchr(out.c_str(), '.') + 1;
	//string ext2 = "avi";
	//if (ext == ext2) {
	//	//ShowPic_1(out);
	//	capture.open(out);
	//	while (1) {
	//		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
	//		capture >> frame;  //读取当前帧
	//						   // GaussianBlur(frame,frame, cvSize(3,3), 2, 2, BORDER_DEFAULT);//高斯平滑
	//						   // Canny(frame,frame,20,100,3);//边缘检测
	//		Mat imagedst;
	//		ShowPic_1(frame);
	//		waitKey(30);  //延时30ms
	//	}
	//}
	//else
	//{
	//	image = imread(out);
	//	ShowPic_1(image);
	//}

}



//灰度化
void CMFC_DEMODlg::On32789()
{
	// TODO: 在此添加命令处理程序代码
	out=ImageGray1();
	ShowPic_2(out);
}

//二值化
void CMFC_DEMODlg::On32790()
{
	// TODO: 在此添加命令处理程序代码
	
//	NewForm  Dlg;
	//Dlg.DoModal();
	//newform2  Dl;
	
		//out=ImageEZH1();
	ImageEZH1();
			//ShowPic_2(out);
		
}

//均值滤波
void CMFC_DEMODlg::On32794()
{
	ImageJZ1();
}

//高斯滤波
void CMFC_DEMODlg::On32795()
{
	// TODO: 在此添加命令处理程序代码
	 ImageGS1();
}

//拉普拉斯滤波
void CMFC_DEMODlg::On32796()
{
	// TODO: 在此添加命令处理程序代码
	out = ImageLPLS1();
	ShowPic_2(out);

}

//
//canny算子
void CMFC_DEMODlg::On32798()
{
	 ImageCANNY1();
	
}

void CMFC_DEMODlg::OnStnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
}

//sobel算子
void CMFC_DEMODlg::On32799()
{
	// TODO: 在此添加命令处理程序代码
	 ImageSOBEL();
}

//直方图
void CMFC_DEMODlg::On32807()
{
	// TODO: 在此添加命令处理程序代码
	SonWnd_2.WndCreate(this);
}
//频域滤波
void CMFC_DEMODlg::On32793()
{
	// TODO: 在此添加命令处理程序代码
	SonWnd.WndCreate2(this);
	//UpdateData(FALSE);
}



//void CMFC_DEMODlg::OnCancel()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	DestroyWindow();
//	CDialogEx::OnCancel();
//}


//视频边缘检测
void CMFC_DEMODlg::On32809()
{
	// TODO: 在此添加命令处理程序代码
	cannyS();
}

//视频跟踪
void CMFC_DEMODlg::On32810()
{
	// TODO: 在此添加命令处理程序代码
	videoG();
}

//保存
void CMFC_DEMODlg::On32775()
{
	// TODO: 在此添加命令处理程序代码
	save1();
}

//另存为
void CMFC_DEMODlg::On32811()
{
	// TODO: 在此添加命令处理程序代码
	save2();
}

//彩色线性
void CMFC_DEMODlg::On32812()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU();
}

//灰度分段线性
void CMFC_DEMODlg::On32813()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU_2();
}

//灰度非线性
void CMFC_DEMODlg::On32814()
{
	// TODO: 在此添加命令处理程序代码
	ImageHUIDU_3();
}

//暂停

//void CMFC_DEMODlg::OnBnClickedButton1()
//{
//	// TODO: 在此添加控件通知处理程序代码
//	CString buttonText;
//	StopButton.GetWindowText(buttonText);
//
//	if (buttonText.Compare(_T("暂停")) == 0)
//	{
//		start_event.ResetEvent();
//		StopButton.SetWindowTextA(_T("继续"));
//
//	}
//	else
//	{
//		start_event.SetEvent();
//		StopButton.SetWindowText(_T("暂停"));
//	}
//}
