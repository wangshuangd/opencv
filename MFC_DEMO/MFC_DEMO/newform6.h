#pragma once
#include "afxwin.h"


// newform6 对话框

class newform6 : public CDialogEx
{
	DECLARE_DYNAMIC(newform6)

public:
	newform6(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~newform6();
	int n;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//int neihe;
	virtual BOOL OnInitDialog();
	CComboBox m_comboWeb;
	afx_msg void OnSelchangeIdretry();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
