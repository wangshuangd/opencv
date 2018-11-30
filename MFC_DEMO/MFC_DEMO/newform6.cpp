// newform6.cpp : 实现文件
//

#include "stdafx.h"
#include "MFC_DEMO.h"
#include "newform6.h"
#include "afxdialogex.h"
#include <sstream>
using namespace std;
// newform6 对话框

IMPLEMENT_DYNAMIC(newform6, CDialogEx)

newform6::newform6(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	//, neihe(0)
{

}

newform6::~newform6()
{
}

void newform6::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_CBIndex(pDX, IDC_COMBO1, neihe);
	//DDV_MinMaxInt(pDX, neihe, 3, 15);
	DDX_Control(pDX, IDRETRY, m_comboWeb);
}


BEGIN_MESSAGE_MAP(newform6, CDialogEx)
	ON_CBN_SELCHANGE(IDRETRY, &newform6::OnSelchangeIdretry)
	ON_BN_CLICKED(IDC_BUTTON1, &newform6::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &newform6::OnBnClickedButton2)
END_MESSAGE_MAP()


// newform6 消息处理程序


BOOL newform6::OnInitDialog()
{
	CDialogEx::OnInitDialog();



	// TODO:  在此添加额外的初始化
	m_comboWeb.AddString(_T("3"));
	// 为组合框控件的列表框添加列表项“百度”   
	m_comboWeb.AddString(_T("5"));
	// 在组合框控件的列表框中索引为1的位置插入列表项“新浪”   
	m_comboWeb.AddString( _T("7"));
	m_comboWeb.AddString(_T("9"));
	m_comboWeb.AddString(_T("11"));
	m_comboWeb.AddString(_T("21"));
	m_comboWeb.AddString(_T("51"));

	// 默认选择第一项   
	m_comboWeb.SetCurSel(0);
	// 编辑框中默认显示第一项的文字“鸡啄米”   
	//SetDlgItemText(IDC_COMBO1, _T("鸡啄米"));

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void newform6::OnSelchangeIdretry()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strWeb;
	int nSel;



	
	// 获取组合框控件的列表框中选中项的索引   
	nSel = m_comboWeb.GetCurSel();
	// 根据选中项索引获取该项字符串   
	m_comboWeb.GetLBText(nSel, strWeb);
	CString strWeb_2 = strWeb;
	CStringA temp(strWeb_2.GetBuffer(0));
	strWeb_2.ReleaseBuffer();
	string ss = temp.GetBuffer(0);
	 n = atoi(ss.c_str());
	// 将组合框中选中的字符串显示到IDC_SEL_WEB_EDIT编辑框中   
	//SetDlgItemText(IDC_SEL_WEB_EDIT, strWeb);
}



//确定
void newform6::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CDialog::OnOK();
}

//取消
void newform6::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	newform6::OnCancel();
}
