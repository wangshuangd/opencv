// newform5.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_DEMO.h"
#include "newform5.h"
#include "afxdialogex.h"
#include "MFC_DEMODlg.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// newform5 对话框

IMPLEMENT_DYNAMIC(newform5, CDialogEx)

newform5::newform5(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

}

newform5::~newform5()
{
}

void newform5::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(newform5, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &newform5::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &newform5::OnBnClickedButton2)
END_MESSAGE_MAP()


// newform5 消息处理程序


BOOL newform5::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	namedWindow("view_4", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view_4");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDHELP)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	namedWindow("view_5", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND)cvGetWindowHandle("view_5");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDCANCEL)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);

	namedWindow("view_6", WINDOW_AUTOSIZE);
	HWND hWnd3 = (HWND)cvGetWindowHandle("view_6");
	HWND hParent3 = ::GetParent(hWnd3);
	::SetParent(hWnd3, GetDlgItem(IDCLOSE)->m_hWnd);
	::ShowWindow(hParent3, SW_HIDE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
void newform5::WndCreate(LPVOID pParent)

{
	if (adlg == NULL) {
		Create(IDD_DIALOG5);                         //创建对话框

		ShowWindow(SW_SHOW);                         //显示对话框

		adlg = pParent;                         //将父窗口指针传递进来
	}
}


void newform5::ShowPic1(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDHELP)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_4", imagedst);
}
void newform5::ShowPic2(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDCANCEL)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_5", imagedst);
}
void newform5::ShowPic3(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDCLOSE)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_6", imagedst);
}
//彩色图像
void newform5::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ain;
	ain = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	//Mat out1 = ain->ImageJHH1();
	ain->out = ain->ImageJHH1();
	ShowPic1(ain->out);
	Mat out2 = ain->ImageJHH2();
	ShowPic2(out2);
	Mat out3 = ain->ImageJHH3();
	ShowPic3(out3);
	//CMFC_DEMODlg::ImageJHH1();
}

//灰度图像
void newform5::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ain;
	ain = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	//Mat out1 = ain->ImageZFT1();
	ain->out = ain->ImageZFT1();
	ShowPic1(ain->out);
	Mat out2 = ain->ImageZFT2();
	ShowPic2(out2);
	Mat out3 = ain->ImageZFT3();

	ShowPic3(out3);
}


void newform5::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	DestroyWindow();
	adlg = NULL;
	CDialogEx::OnCancel();
}
