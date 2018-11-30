#pragma once
#include "afxwin.h"

#define WM_MyMessage (WM_USER + n)
// newform2 对话框

class newform2 : public CDialogEx
{
	DECLARE_DYNAMIC(newform2)

public:
	newform2(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~newform2();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
//	int canshu1;
	//virtual BOOL OnInitDialog();
	//CButton m_edit1;
//	CEdit m_edit1;
	//afx_msg void OnBnClickedButton1();
	int canshu;
	// 函数功能：返回保存的 int  
	//int GetIntVal();

	// 函数功能：返回保存的 int  
	//void GetIntVal(int &outIntVal);
	afx_msg void On32793();
	//void ImageEZH1();
	//afx_msg LRESULT OnCountMsg(WPARAM, LPARAM);
	//virtual BOOL OnInitDialog();


//protected:
	//{{AFX_MSG(CChildView)
	//afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedButton1();
	//int zhi;
	afx_msg void OnBnClickedButton2();
	//virtual void OnCancel();
};

