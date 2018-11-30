
// MFC_DEMODlg.h : 头文件
//

#pragma once
#include "cv.h"
#include "highgui.h"
#include "CvvImage.h"

#include"NewForm.h"
#include"newform1.h"
#include"newform5.h"
#include <iostream>  
#include<opencv2/core/core.hpp>  
#include<opencv2/highgui/highgui.hpp>  
#include<opencv2/imgproc/imgproc.hpp>  
#include<string>  
#include "afxwin.h"

using namespace std;
using namespace cv;


// CMFC_DEMODlg 对话框
class CMFC_DEMODlg : public CDialogEx
{
	
	newform1 SonWnd;
	newform5 SonWnd_2;
	
// 构造
public:
	CMFC_DEMODlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_DEMO_DIALOG };
#endif

//private: 
	//newform1  * m_pTipDlg;


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//CEvent start_event;
	Mat image;
	Mat img, hou,out,out2;
	Mat tz_img;//拓展后的图像
	VideoCapture capture;
	string _Path;

	void TZ();
	void ZXH();
	Mat ShowSpectrum(Mat input);
	Mat ShowImage(Mat input);
	void GaussianFilter(Mat& input, float D0, bool);
	void IdealFilter(Mat& input, float D0, bool flag);
	void ButterworthFilter(Mat& input, float D0, float n, bool flag);
	
	

	void cannyS();
	void ShowPic_1(Mat input_1);
	void ShowPic_2(Mat input_2);
	//void ShowPic_3(Mat input_3);
	//CMFC_DEMODlg::~CMFC_DEMODlg();
	//CMenu m_Menu;
	//IplImage * out;
	//void DrawPicToHDC(IplImage *img, UINT ID);
	void save2();
	static void onMouse(int event, int x, int y, int, void*);
	void videoG();
	//void videoG_2();
	
	void open2();
	void save1();
	//Mat open1();
	Mat ImageGray1();
	void ImageEZH1();
	void ImageJZ1();
	void ImageGS1();
	void ImageHUIDU();
	void ImageHUIDU_2();
	void ImageHUIDU_3();
	Mat ImageLPLS1();
	void ImageCANNY1();
	void ImageSOBEL();
    Mat ImageJHH1();
	Mat ImageJHH2();
	Mat ImageJHH3();
	Mat ImageZFT1();
	Mat ImageZFT2();
	Mat ImageZFT3();
	
	Mat ImageLIX_1();
	Mat ImageLIX_2();
	Mat ImageDCT();
	Mat ImageDCT_1();
	Mat ImageDCT_2();
	Mat ImageDCT_3();
	Mat ImageDCT_4();
	Mat ImageLIX_3();
	Mat ImageLIX_4();
	Mat ImageDCT_5();
	Mat ImageDCT_6();
	Mat ImageLIX_5();
	Mat ImageLIX_6();

	afx_msg void On32774();
	afx_msg void On32789();
	afx_msg void On32790();
	afx_msg void On32794();
	afx_msg void On32795();
	afx_msg void On32796();
	afx_msg void On32798();
//	afx_msg void On32801();
	afx_msg void OnStnClickedCancel();
	//afx_msg void OnMenu32802();
	afx_msg void On32799();
	//afx_msg void On32791();
	afx_msg void On32793();
	afx_msg void On32807();
	//virtual void OnCancel();
//	afx_msg void On32808();
	afx_msg void On32809();
	afx_msg void On32810();
	afx_msg void On32775();
	afx_msg void On32811();
	afx_msg void On32812();
	afx_msg void On32813();
	afx_msg void On32814();
	//afx_msg void OnBnClickedButton1();
	//CButton StopButton;
};
