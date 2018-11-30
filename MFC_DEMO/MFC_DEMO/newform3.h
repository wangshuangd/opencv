#pragma once


// newform3 对话框

class newform3 : public CDialogEx
{
	DECLARE_DYNAMIC(newform3)

public:
	newform3(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~newform3();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int liangdu;
	int duibidu;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
//	virtual void OnCancel();
};
