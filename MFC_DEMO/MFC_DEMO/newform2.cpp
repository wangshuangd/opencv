// newform2.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_DEMO.h"
#include "newform2.h"
#include "afxdialogex.h"
#include "MFC_DEMODlg.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// newform2 对话框

IMPLEMENT_DYNAMIC(newform2, CDialogEx)

newform2::newform2(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	
	, canshu(0)

{

}

newform2::~newform2()
{

}

void newform2::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//处理控件IDC_EDIT1和变量canshu1之间的数据交换
	//	DDX_Text(pDX, IDC_EDIT1, canshu1);
	//DDX_Control(pDX, IDC_BUTTON1, m_edit1);
	//DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Text(pDX, IDC_EDIT1, canshu);

	//DDX_Text(pDX, IDC_EDIT2, zhi);
}


BEGIN_MESSAGE_MAP(newform2, CDialogEx)
	//ON_BN_CLICKED(IDC_BUTTON1, &newform2::OnBnClickedButton1)

	ON_COMMAND(ID_32793, &newform2::On32793)
	ON_BN_CLICKED(IDC_BUTTON1, &newform2::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &newform2::OnBnClickedButton2)
END_MESSAGE_MAP()


// newform2 消息处理程序



//频域滤波
void newform2::On32793()
{
	// TODO: 在此添加命令处理程序代码
	
}





//确定按钮
void newform2::OnBnClickedButton1()
{
	UpdateData(TRUE);
CDialog::OnOK();
}

//取消按钮
void newform2::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	newform2::OnCancel();
}


//void newform2::OnCancel()
//{
//	// TODO: 在此添加专用代码和/或调用基类
//	DestroyWindow();
//	CDialogEx::OnCancel();
//}
