#pragma once
//#include "MFC_DEMODlg.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
// newform1 对话框

class newform1 : public CDialogEx
{
	DECLARE_DYNAMIC(newform1)

public:
	newform1(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~newform1();
	//~newform1() = delete;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif
private:
	LPVOID adlg;
	//LPVOID pParent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//Mat jie;
	
	void WndCreate2(LPVOID pParent);
	void ShowPic1(Mat input_1);
	void ShowPic2(Mat input_1);
	void ShowPic3(Mat input_1);
	virtual BOOL OnInitDialog();
	//int canshu1;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	virtual void OnCancel();
	//virtual void PostNcDestroy();
};
