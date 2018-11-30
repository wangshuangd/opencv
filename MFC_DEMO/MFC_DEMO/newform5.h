#pragma once

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// newform5 对话框

class newform5 : public CDialogEx
{
	DECLARE_DYNAMIC(newform5)

public:
	newform5(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~newform5();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif
private:
	LPVOID adlg;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	void ShowPic1(Mat input_1);
	void ShowPic2(Mat input_1);
	void ShowPic3(Mat input_1);
	void WndCreate(LPVOID pParent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	virtual void OnCancel();
};
