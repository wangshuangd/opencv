// newform1.cpp : 实现文件
//


#include "stdafx.h"
#include "MFC_DEMO.h"

#include "MFC_DEMODlg.h"
#include "newform1.h"
#include "afxdialogex.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// newform1 对话框

IMPLEMENT_DYNAMIC(newform1, CDialogEx)

newform1::newform1(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	//, canshu1(0)
{

}

newform1::~newform1()
{

}

void newform1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, canshu1);
}


BEGIN_MESSAGE_MAP(newform1, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &newform1::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &newform1::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &newform1::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &newform1::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &newform1::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &newform1::OnBnClickedButton6)
END_MESSAGE_MAP()


// newform1 消息处理程序


BOOL newform1::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	namedWindow("view_1", WINDOW_AUTOSIZE);
	HWND hWnd = (HWND)cvGetWindowHandle("view_1");
	HWND hParent = ::GetParent(hWnd);
	::SetParent(hWnd, GetDlgItem(IDD_ABOUTBOX)->m_hWnd);
	::ShowWindow(hParent, SW_HIDE);

	namedWindow("view_2", WINDOW_AUTOSIZE);
	HWND hWnd2 = (HWND)cvGetWindowHandle("view_2");
	HWND hParent2 = ::GetParent(hWnd2);
	::SetParent(hWnd2, GetDlgItem(IDD_DIALOG2)->m_hWnd);
	::ShowWindow(hParent2, SW_HIDE);

	namedWindow("view_3", WINDOW_AUTOSIZE);
	HWND hWnd3 = (HWND)cvGetWindowHandle("view_3");
	HWND hParent3 = ::GetParent(hWnd3);
	::SetParent(hWnd3, GetDlgItem(IDD_DIALOG4)->m_hWnd);
	::ShowWindow(hParent3, SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void newform1::WndCreate2(LPVOID pParent)

{
	if (NULL == adlg) {
		Create(IDD_DIALOG3);                         //创建对话框

	//	ShowWindow(SW_SHOW);                         //显示对话框
		ShowWindow(SW_SHOW);
		adlg = pParent;                         //将父窗口指针传递进来

	}
	
}

void newform1::ShowPic1(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDD_ABOUTBOX)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_1", imagedst);
}
void newform1::ShowPic2(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDD_DIALOG2)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_2", imagedst);
}
void newform1::ShowPic3(Mat input_1)
{
	Mat imagedst;
	CRect rect;
	GetDlgItem(IDD_DIALOG4)->GetClientRect(&rect);
	Rect dst(rect.left, rect.top, rect.right, rect.bottom);
	resize(input_1, imagedst, cv::Size(rect.Width(), rect.Height()));
	imshow("view_3", imagedst);
}

//理想低通
void newform1::OnBnClickedButton1()
{

	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
			
														 
	
	Mat out_1= ai->ImageDCT();
	ShowPic1( out_1);
	Mat out_2 = ai->ImageDCT_1();
	 //ai->ImageDCT_1();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_1();
	//imshow("w", ai->out);
	ShowPic3(ai->out);//Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换

}
//理想高通
void newform1::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	Mat out_1 = ai->ImageDCT();
	ShowPic1(out_1);
	Mat out_2 = ai->ImageDCT_2();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_2();
	ShowPic3(ai->out);
}

//高斯低通
void newform1::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
					
//Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	Mat out_1 = ai->ImageDCT();
	ShowPic1(out_1);
	Mat out_2 = ai->ImageDCT_3();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_3();
	ShowPic3(ai->out);
}

//高斯高通
void newform1::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	Mat out_1 = ai->ImageDCT();
	ShowPic1(out_1);
	Mat out_2 = ai->ImageDCT_4();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_4();
	ShowPic3(ai->out);
}

//巴特沃斯低通
void newform1::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	Mat out_1 = ai->ImageDCT();
	ShowPic1(out_1);
	Mat out_2 = ai->ImageDCT_5();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_5();
	ShowPic3(ai->out);
}

//巴特沃斯高通
void newform1::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CMFC_DEMODlg*ai;
	ai = (CMFC_DEMODlg*)adlg;                            //强制将LPVOID类型转换
														  //Main = (CProjectDlg*)m_pFather;                            //强制将LPVOID类型转换
	Mat out_1 = ai->ImageDCT();
	ShowPic1(out_1);
	Mat out_2 = ai->ImageDCT_6();
	ShowPic2(out_2);
	ai->out = ai->ImageLIX_6();
	ShowPic3(ai->out);
}

void newform1::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	DestroyWindow();
	adlg=NULL;
	CDialogEx::OnCancel();
}


//void newform1::PostNcDestroy()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	//delete this;
//	CDialogEx::PostNcDestroy();
//}
