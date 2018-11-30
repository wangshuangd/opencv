#include "stdafx.h"
#include "MFC_DEMO.h"
#include "MFC_DEMODlg.h"
#include "afxdialogex.h"
#include "NewForm.h"
#include "newform2.h"
#include "newform3.h"
#include "newform6.h"
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
//读取图像函数

//打开图像
void CMFC_DEMODlg::open2()
{
	
	
	CFileDialog Openfiledlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, NULL);
	if (Openfiledlg.DoModal() == IDOK) //弹出模态对话框  
	{
		//CString类型转换为string类型  
	
		CString  filepath;
		filepath = Openfiledlg.GetPathName();
		CStringA temp(filepath.GetBuffer(0));
		filepath.ReleaseBuffer();
		_Path = temp.GetBuffer(0);
		temp.ReleaseBuffer();
		//return _Path;

		//int delay = 20;
		string ext = strrchr(_Path.c_str(), '.') + 1;
		string ext2 = "avi";
		if (ext == ext2) {
			//ShowPic_1(out);

			capture.open(_Path);
			while (1) {
			

				Mat frame;//定义一个Mat变量，用于存储每一帧的图像
				capture >> frame;  //读取当前帧
								   // GaussianBlur(frame,frame, cvSize(3,3), 2, 2, BORDER_DEFAULT);//高斯平滑
								   // Canny(frame,frame,20,100,3);//边缘检测
				Mat imagedst;
				ShowPic_1(frame);
				waitKey(70);  //延时30ms
				
			}
		}
		else
		{
			image = imread(_Path);
			ShowPic_1(image);
		}
	}
	}


//保存图像
void CMFC_DEMODlg::save1()
{
	imwrite("H:\\MFC_DEMO\\Alppa.png", out);
}
//另存为
void CMFC_DEMODlg::save2()
{
	//TCHAR szFilter[] = _T("jpg图像(*.jpg)|*.jpg|png文件(*.png*)|*.png*||");
	CFileDialog fileDlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		TEXT("Supported Types (*.jpg;*.png;*.gif;*.bmp;...)|*.jpg;*.png;*.gif;*.bmp|Tiff(*.tiff;*.tif)|*.tiff;*.tif|All Files(*.*)|*.*||"), NULL);
	if (fileDlg.DoModal() == IDOK) //弹出模态对话框  
	{

		//CString类型转换为string类型  
		//strFilePath = fileDlg.GetPathName();
		CString  filepath;
		filepath = fileDlg.GetPathName();
		//CStringA temp(filepath.GetBuffer(0));
		//filepath.ReleaseBuffer();
		//string _Path_2 = temp.GetBuffer(0);
	
		char *s_path;
		s_path = filepath.GetBuffer(filepath.GetLength());

		imwrite(s_path, out);
		//temp.ReleaseBuffer();
		filepath.ReleaseBuffer();
		//UpdateData(false);
	}
}
//视频边缘检测
void CMFC_DEMODlg::cannyS()
{
	string out = _Path;
	capture.open(out);
	while (1) {
		Mat frame;//定义一个Mat变量，用于存储每一帧的图像
		capture >> frame;  //读取当前帧
						    GaussianBlur(frame,frame, cvSize(3,3), 2, 2, BORDER_DEFAULT);//高斯平滑
						    Canny(frame,frame,20,100,3);//边缘检测
		Mat imagedst;
		ShowPic_2(frame);
		waitKey(70);  //延时30ms
	}
}
//视频跟踪
Mat images;
bool backprojMode = false; //表示是否要进入反向投影模式，ture表示准备进入反向投影模式  
bool selectObject = false;//代表是否在选要跟踪的初始目标，true表示正在用鼠标选择  
int trackObject = 0; //代表跟踪目标数目  
bool showHist = true;//是否显示直方图  
Point origin;//用于保存鼠标选择第一次单击时点的位置  
Rect selection;//用于保存鼠标选择的矩形框  
int vmin = 10, vmax = 50, smin = 30;

 void CMFC_DEMODlg::onMouse(int event, int x, int y, int, void*)
{
	if (selectObject)
	{
		selection.x = MIN(x, origin.x);//矩形左上角顶点坐标  
		selection.y = MIN(y, origin.y);
		selection.width = std::abs(x - origin.x);//矩形宽  
		selection.height = std::abs(y - origin.y);//矩形高  

		selection &= Rect(0, 0, images.cols, images.rows);//用于确保所选的矩形区域在图片范围内
	}

	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		origin = Point(x, y);
		selection = Rect(x, y, 0, 0);
		selectObject = true;
		break;
	case CV_EVENT_LBUTTONUP:
		selectObject = false;
		if (selection.width > 0 && selection.height > 0)
			trackObject = -1;
		break;
	}
}
const char* keys =
{
	"{1|  | 0 | camera number}"
};

void CMFC_DEMODlg::videoG()
{
	//int argc; const char** argv;
	string out = _Path;
	capture.open(out);

	
	//help();

	//VideoCapture cap;//实例化
	Rect trackWindow;
	int hsize = 16;
	//hranges在后面的计算直方图函数中要用到
	float hranges[] = { 0,180 };
	const float* phranges = hranges;
	//命令解析器函数
	//CommandLineParser parser(argc, argv, keys);
	
	//cap.open("Walk.avi");//读取视频文件
						 //cap.open(0);

	//if (!cap.isOpened())//打开失败
	//{
	//	help();
	//	cout << "***Could not initialize capturing...***\n";
	//	cout << "Current parameter's value: \n";
	//	parser.printParams();
	//	return -1;
	//}

	//namedWindow("Histogram", 0);
	//namedWindow("CamShift Demo", 0);
	//鼠标响应函数
	setMouseCallback("view2", onMouse, 0);
	//创建滑动条
	//最后一个参数为0代表没有调用滑动拖动的响应函数
	//createTrackbar("Vmin", "view2", &vmin, 256, 0);
	//createTrackbar("Vmax", "view2", &vmax, 256, 0);
	//createTrackbar("Smin", "view2", &smin, 256, 0);

	Mat frame, hsv, hue, mask, hist, histimg = Mat::zeros(200, 320, CV_8UC3), backproj;
	bool paused = false;

	for (;;)
	{
		if (!paused)//没有暂停
		{
			//从摄像头抓取一帧图像并输出到frame中 
			capture >> frame;
			if (frame.empty())
				break;
		}

		frame.copyTo(images);

		if (!paused)//没有按暂停键
		{
			//将颜色空间转换到HSV
			cvtColor(images, hsv, COLOR_BGR2HSV);
			//trackObject初始化为0,或者按完键盘的'c'键后也为0，当鼠标单击松开后为-1 
			if (trackObject)
			{
				int _vmin = vmin, _vmax = vmax;
				//inRange()函数检查输入数组每个元素大小是否在2个给定数值之间
				inRange(hsv, Scalar(0, smin, MIN(_vmin, _vmax)),
					Scalar(180, 256, MAX(_vmin, _vmax)), mask);
				int ch[] = { 0, 0 };
				//hue初始化为与hsv大小深度一样的矩阵，色调的度量是用角度表示的，
				//红绿蓝之间相差120度，反色相差180度 
				hue.create(hsv.size(), hsv.depth());
				//通道拆分
				mixChannels(&hsv, 1, &hue, 1, ch, 1);
				//鼠标选择区域松开后，该函数内部又将其赋值1
				if (trackObject < 0)
				{
					//此处的构造函数roi用的是Mat hue的矩阵头，且roi的数据指针指向hue，
					//即共用相同的数据，select为其感兴趣的区域
					Mat roi(hue, selection), maskroi(mask, selection);
					//calcHist计算直方图
					calcHist(&roi, 1, 0, maskroi, hist, 1, &hsize, &phranges);
					//归一化
					normalize(hist, hist, 0, 255, CV_MINMAX);

					trackWindow = selection;
					trackObject = 1;

					histimg = Scalar::all(0);
					int binW = histimg.cols / hsize;
					Mat buf(1, hsize, CV_8UC3);
					for (int i = 0; i < hsize; i++)
						buf.at<Vec3b>(i) = Vec3b(saturate_cast<uchar>(i*180. / hsize), 255, 255);
					cvtColor(buf, buf, CV_HSV2BGR);

					for (int i = 0; i < hsize; i++)
					{
						int val = saturate_cast<int>(hist.at<float>(i)*histimg.rows / 255);
						//在一幅输入图像上画一个简单抽的矩形，指定左上角和右下角，并定义颜色，大小，线型等
						rectangle(histimg, Point(i*binW, histimg.rows),
							Point((i + 1)*binW, histimg.rows - val),
							Scalar(buf.at<Vec3b>(i)), -1, 8);
					}
				}
				//计算直方图的反向投影，计算hue图像0通道直方图hist的反向投影，
				//并让入backproj中
				calcBackProject(&hue, 1, 0, hist, backproj, &phranges);
				backproj &= mask;
				//trackWindow为鼠标选择的区域，TermCriteria为确定迭代终止的准则
				RotatedRect trackBox = CamShift(backproj, trackWindow,
					//CV_TERMCRIT_EPS是通过forest_accuracy,CV_TERMCRIT_ITER
					TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1));
				if (trackWindow.area() <= 1)
				{
					int cols = backproj.cols, rows = backproj.rows, r = (MIN(cols, rows) + 5) / 6;
					trackWindow = Rect(trackWindow.x - r, trackWindow.y - r,
						trackWindow.x + r, trackWindow.y + r) &
						Rect(0, 0, cols, rows);
					//Rect函数为矩阵的偏移和大小，即第一二个参数为矩阵的左上角点坐标，第三四个参数为矩阵的宽和高
				}

				if (backprojMode)
					//因此投影模式下显示的也是rgb图
					cvtColor(backproj, images, COLOR_GRAY2BGR);
				//跟踪的时候以椭圆为代表目标
				ellipse(images, trackBox, Scalar(0, 0, 255), 3, CV_AA);
			}
		}
		else if (trackObject < 0)
			paused = false;

		if (selectObject && selection.width > 0 && selection.height > 0)
		{
			Mat roi(images, selection);
			bitwise_not(roi, roi);
		}

		//imshow("CamShift Demo", images);
		//imshow("Histogram", histimg);
		ShowPic_2(images);

		char c = (char)waitKey(70);
		if (c == 27)
			break;
		switch (c)
		{
		case 'b':
			backprojMode = !backprojMode;
			break;
		case 'c':
			trackObject = 0;
			histimg = Scalar::all(0);
			break;
		case 'h':
			showHist = !showHist;
			if (!showHist)
				destroyWindow("Histogram");
			else
				namedWindow("Histogram", 1);
			break;
		case 'p':
			paused = !paused;
			break;
		default:
			;
		}
	}

	//return 0;
}
//转换成灰度图像
Mat CMFC_DEMODlg::ImageGray1()
{
	Mat huidu, out2;
	cvtColor(image, huidu, COLOR_BGR2GRAY);
	return huidu;
	/*CRect rect2;
	GetDlgItem(IDCANCEL)->GetClientRect(&rect2);
	Rect dst2(rect2.left, rect2.top, rect2.right, rect2.bottom);
	resize(huidu, out2, cv::Size(rect2.Width(), rect2.Height()));
	imshow("view2", out2);*/
}


//二值化函数
void CMFC_DEMODlg::ImageEZH1()
{
	//newform2 a;
	//int n=a.newform2::GetIntVal();
	Mat huidu;
	newform2  Dl;
	if (Dl.DoModal() == IDOK) {
		int k = Dl.canshu;
		//GetIntVal();
		
		cvtColor(image, huidu, COLOR_BGR2GRAY);
		//int num2 = NewForm.dig;
		//int num2 = NewForm::dig();


		threshold(huidu, out, k, 255, CV_THRESH_BINARY);
		//return erzhi;
		ShowPic_2(out);
	}
}

//均值滤波
void CMFC_DEMODlg::ImageJZ1()
{
	newform6  D;
	if (D.DoModal() == IDOK) {
		int k = D.n;
		//Mat junzhi,out2;
		out.create(image.size(), image.type());
		blur(image, out, Size(k, k));
		ShowPic_2(out);
	}
}
//高斯滤波
void CMFC_DEMODlg::ImageGS1()
{
	newform6  D;
	if (D.DoModal() == IDOK) {
		int k = D.n;
		GaussianBlur(image, out, Size(k,k), 0, 0);
		ShowPic_2(out);
	}
}
//拉普拉斯
Mat CMFC_DEMODlg::ImageLPLS1()
{
	Mat lpls;
	Mat K = (Mat_<double>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
	filter2D(image, lpls, image.depth(), K);
	return lpls;

}

//canny算子
void CMFC_DEMODlg::ImageCANNY1()
{
	//Mat huidu;
	NewForm  Dl;
	if (Dl.DoModal() == IDOK) {
		//NewForm q;
		int m= Dl.pos;
		//Mat out2=image.clone();
		//Mat cay, out2;
		
		cvtColor(image, out, COLOR_BGR2GRAY);
		Canny(out, out, m, m*3, 3);

		ShowPic_2(out);
	}
	
	//return huidu;
}
//sobel算子
void CMFC_DEMODlg::ImageSOBEL()
{
	//Mat out2, sob;
	newform6  Dl;
	if (Dl.DoModal() == IDOK) {
	
		int m = Dl.n;
		Sobel(image, out, image.depth(), 1, 1, m);
		ShowPic_2(out);
	}

	//return sob;
}

//彩色图像直方图
Mat CMFC_DEMODlg::ImageJHH1()
{
	Mat out2;
	Mat P;
	vector<Mat>V;  //定义Mat向量容器保存拆分后的数据
	Mat B;
	Mat G;
	Mat R;
	split(image, V);//通道分离
	B = V.at(0);//蓝色通道
	G = V.at(1);//绿色通道
	R = V.at(2);//红色通道

				//直方图均衡化
	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);

	merge(V, P);
	return P;
}
Mat  CMFC_DEMODlg::ImageJHH2()
{
	Mat out2;

	MatND BHist, GHist, RHist; //多维矩阵     
	int dims = 1;//一维直方图
				 //int dims = 3;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	//int channels = 0;
	int channels_b[] = { 0 };
	int channels_g[] = { 1 };
	int channels_r[] = { 2 };

	calcHist(&image, 1, channels_b, Mat(), BHist, dims, &size, ranges);
	calcHist(&image, 1, channels_g, Mat(), GHist, dims, &size, ranges);
	calcHist(&image, 1, channels_r, Mat(), RHist, dims, &size, ranges);
	// cout<<dstHist;//输出各个灰度级频数
	//cout<<"行"<<dstHist.rows;//输出计算值的行数
	//cout<<"列"<<dstHist.cols;//输出直方图的列数
	//cout << "nihao";


	int scale = 1;
	//获取最大值和最小值
	//double minValue = 0;
	double maxValue_b, maxValue_g, maxValue_r;
	//在数组中找到全局最小值和最大值
	//返回最小值和最大值
	minMaxLoc(BHist, 0, &maxValue_b, 0, 0);
	minMaxLoc(GHist, 0, &maxValue_g, 0, 0);
	minMaxLoc(RHist, 0, &maxValue_r, 0, 0);
	//绘制直方图的矩阵
	//static MatExpr Mat::zeros(int rows, int cols, int type)
	Mat New = Mat::zeros(256, 256 * 3, CV_8UC3);

	//int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		//各灰度级频数，注意hist中是float类型
		float binValue_b = BHist.at<float>(i);
		float binValue_g = GHist.at<float>(i);
		float binValue_r = RHist.at<float>(i);
		//要绘制的真实高度
		int realValue_b = saturate_cast<int>(binValue_b * 256 / maxValue_b);
		int realValue_g = saturate_cast<int>(binValue_g * 256 / maxValue_g);
		int realValue_r = saturate_cast<int>(binValue_r * 256 / maxValue_r);
		//矩形会画在New上面
		//Point(i*scale, size - 1)矩形顶点
		// Point((i+1)*scale - 1, size - realValue)前一个的对角顶点
		//蓝色部分
		rectangle(New, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue_b), CV_RGB(0, 0, 255));
		rectangle(New, Point((i + 256)*scale, size - 1), Point((i + 256 + 1)*scale - 1, size - realValue_g), CV_RGB(0, 255, 0));
		rectangle(New, Point((i + 256 * 2)*scale, size - 1), Point((i + 256 * 2 + 1)*scale - 1, size - realValue_r), CV_RGB(255, 0, 0));
	}
	return New;

}
Mat CMFC_DEMODlg::ImageJHH3()
{
	Mat out2;
	Mat P;
	vector<Mat>V;  //定义Mat向量容器保存拆分后的数据
	Mat B;
	Mat G;
	Mat R;
	split(image, V);//通道分离
	B = V.at(0);//蓝色通道
	G = V.at(1);//绿色通道
	R = V.at(2);//红色通道
				//直方图均衡化
	equalizeHist(B, B);
	equalizeHist(G, G);
	equalizeHist(R, R);

	merge(V, P);
	MatND BHist, GHist, RHist; //多维矩阵     
	int dims = 1;//一维直方图
				 //int dims = 3;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	//int channels = 0;
	int channels_b[] = { 0 };
	int channels_g[] = { 1 };
	int channels_r[] = { 2 };
	//计算图像的直方图
	//&yuan输入数组，1图像个数， &channels需要统计的通道索引，Mat()，OutArray类型的hist计算得到的直方图
	//int类型的dims，需要计算的直方图的维数
	//&size每个维度直方图横坐标的区间数，就是 bin的个数
	//const float**类型的ranges，是一个二维数组，用来指出每个区间的范围
	calcHist(&P, 1, channels_b, Mat(), BHist, dims, &size, ranges);
	calcHist(&P, 1, channels_g, Mat(), GHist, dims, &size, ranges);
	calcHist(&P, 1, channels_r, Mat(), RHist, dims, &size, ranges);
	int scale_2 = 1;
	//获取最大值和最小值
	//double minValue = 0;
	double maxValue_b2, maxValue_g2, maxValue_r2;
	//在数组中找到全局最小值和最大值
	//返回最小值和最大值
	minMaxLoc(BHist, 0, &maxValue_b2, 0, 0);
	minMaxLoc(GHist, 0, &maxValue_g2, 0, 0);
	minMaxLoc(RHist, 0, &maxValue_r2, 0, 0);
	//绘制直方图的矩阵
	//static MatExpr Mat::zeros(int rows, int cols, int type)
	Mat New_2 = Mat::zeros(256, 256 * 3, CV_8UC3);

	//int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		//各灰度级频数，注意hist中是float类型
		float binValue_b2 = BHist.at<float>(i);
		float binValue_g2 = GHist.at<float>(i);
		float binValue_r2 = RHist.at<float>(i);
		//要绘制的真实高度
		int realValue_b2 = saturate_cast<int>(binValue_b2 * 256 / maxValue_b2);
		int realValue_g2 = saturate_cast<int>(binValue_g2 * 256 / maxValue_g2);
		int realValue_r2 = saturate_cast<int>(binValue_r2 * 256 / maxValue_r2);
		//矩形会画在New上面
		//Point(i*scale, size - 1)矩形顶点
		// Point((i+1)*scale - 1, size - realValue)前一个的对角顶点
		//蓝色部分
		rectangle(New_2, Point(i*scale_2, size - 1), Point((i + 1)*scale_2 - 1, size - realValue_b2), CV_RGB(0, 0, 255));
		rectangle(New_2, Point((i + 256)*scale_2, size - 1), Point((i + 256 + 1)*scale_2 - 1, size - realValue_g2), CV_RGB(0, 255, 0));
		rectangle(New_2, Point((i + 256 * 2)*scale_2, size - 1), Point((i + 256 * 2 + 1)*scale_2 - 1, size - realValue_r2), CV_RGB(255, 0, 0));
	}
	return New_2;
}

//灰度图像直方图
Mat CMFC_DEMODlg::ImageZFT1()
{
	Mat yuan, out2;
	cvtColor(image, yuan, COLOR_BGR2GRAY);
	Mat yuan2;
	equalizeHist(yuan, yuan2);//直方图均衡化
	return yuan2;
}
Mat CMFC_DEMODlg::ImageZFT2()
{
	Mat yuan,out2;
 cvtColor(image, yuan, COLOR_BGR2GRAY);
									

	MatND dstHist; //多维矩阵     
	int dims = 1;//一维直方图
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;
	//计算图像的直方图
	//&yuan输入数组，1图像个数， &channels需要统计的通道索引，Mat()，OutArray类型的hist计算得到的直方图
	//int类型的dims，需要计算的直方图的维数
	//&size每个维度直方图横坐标的区间数，就是 bin的个数
	//const float**类型的ranges，是一个二维数组，用来指出每个区间的范围
	calcHist(&yuan, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	// cout<<dstHist;//输出各个灰度级频数
	//cout<<"行"<<dstHist.rows;//输出计算值的行数
	//cout<<"列"<<dstHist.cols;//输出直方图的列数
	//cout << "nihao";
	int scale = 1;
	Mat New(size, size * scale, CV_8U, Scalar(0));
	//获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	//在数组中找到全局最小值和最大值
	//返回最小值和最大值
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	//绘制出直方图
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i); //各灰度级频数，注意hist中是float类型  
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		//矩形会画在New上面
		//Point(i*scale, size - 1)矩形顶点
		// Point((i+1)*scale - 1, size - realValue)前一个的对角顶点
		// Scalar(255)颜色
		rectangle(New, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	return New;
}
Mat CMFC_DEMODlg::ImageZFT3()
{
	Mat yuan, out2;
	cvtColor(image, yuan, COLOR_BGR2GRAY);


	MatND dstHist; //多维矩阵     
	int dims = 1;//一维直方图
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;
	calcHist(&yuan, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	Mat yuan2;
	equalizeHist(yuan, yuan2);//直方图均衡化

	MatND dstHist_2;
	calcHist(&yuan2, 1, &channels, Mat(), dstHist_2, dims, &size, ranges);
	//cout<<"均衡化后直方图信息"<<dstHist_2;//输出各个灰度级频数
	//cout<<"行"<<dstHist_2.rows;//输出计算值的行数
	//cout<<"列"<<dstHist_2.cols;//输出直方图的列数
	int scale_2 = 1;
	Mat New2(size, size * scale_2, CV_8U, Scalar(0));
	//获取最大值和最小值
	double minValue_2 = 0;
	double maxValue_2 = 0;
	//在数组中找到全局最小值和最大值
	//返回最小值和最大值
	minMaxLoc(dstHist_2, &minValue_2, &maxValue_2, 0, 0);
	//绘制出直方图
	int hpt_2 = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist_2.at<float>(i); //各灰度级频数，注意hist中是float类型  
		int realValue = saturate_cast<int>(binValue * hpt_2 / maxValue_2);
		//矩形会画在New上面
		//Point(i*scale, size - 1)矩形顶点
		// Point((i+1)*scale - 1, size - realValue)前一个的对角顶点
		// Scalar(255)颜色
		rectangle(New2, Point(i*scale_2, size - 1), Point((i + 1)*scale_2 - 1, size - realValue), Scalar(255));
		
	}
	return New2;
}



//彩色图像线性灰度变换
void CMFC_DEMODlg::ImageHUIDU()
{
	//读取Mat信息
	//Mat out2;
	out = Mat::zeros(image.size(), image.type());
	//Mat dstImg = Mat::zeros(image.size(), image.type());
	CV_Assert(image.depth() != sizeof(uchar));
	int channels = image.channels();
	int nRows = image.rows;
	int nCols = image.cols * channels;
	uchar *p, *q;
	newform3  Dl;
	if (Dl.DoModal() == IDOK) {
		//Mat out2, sob;
		int k = Dl.liangdu;
		int b= Dl.duibidu;
		for (int i = 0; i < nRows; i++)
		{
			p = image.ptr<uchar>(i);
			q = out.ptr<uchar>(i);
			for (int j = 0; j < nCols; j++)
				q[j] = saturate_cast<uchar> (k * p[j] * 0.01 + b - 100);
		}
		ShowPic_2(out);
	}
	//return dstImg;
}
//灰度图像分段线性
struct coordinate
{
	uchar x;
	uchar y;
};
coordinate v1{ 0,50 };
coordinate v2{ 205,255 };
coordinate p1{ 20,20 };
coordinate p2{ 125,120 };
coordinate p3{ 230,230 };
void CMFC_DEMODlg::ImageHUIDU_2()
{
	Mat image_2 = Mat::zeros(image.size(), CV_8UC1);
	//Mat image_2;
	cvtColor(image, image_2, COLOR_BGR2GRAY);
	//判断p1的横坐标是否小于p2的横坐标
	if (p1.x >= p2.x)
		return ;

	//创建一个和原图片同样大小的Mat
	Mat out = Mat::zeros(image.size(), CV_8UC1);
	//Mat out;
	//p1,p2为拐点的映射表创建
	uchar table[256];
	for (int i = 0; i < p1.x; i++)
	{
		table[i] = i * p1.y / p1.x;
	}
	for (int i = p1.x; i < p2.x; i++)
	{
		table[i] = (i - p1.x) * (p2.y - p1.y) / (p2.x - p1.x) + p1.y;
	}
	for (int i = p2.x; i < 256; i++)
	{
		table[i] = (i - p2.x) * (255 - p2.y) / (255 - p2.x) + p2.y;
	}

	//读取Mat信息
	CV_Assert(image_2.depth() != sizeof(uchar));
	int channels = image_2.channels();
	int nRows = image_2.rows;
	int nCols = image_2.cols * channels;

	//根据table表循环遍历找到对应的值赋值到newImg中
	uchar *p, *q;
	for (int i = 0; i < nRows; i++)
	{
		p = image_2.ptr<uchar>(i);
		q = out.ptr<uchar>(i);
		for (int j = 0; j < nCols; j++)
			q[j] = table[p[j]];
		ShowPic_2(out);
	}
	
}
//灰度图像非线性
void CMFC_DEMODlg::ImageHUIDU_3()
{
	//Mat image_2 = Mat::zeros(image.size(), CV_8UC1);
	//cvtColor(image, image_2, COLOR_BGR2GRAY);
	////判断p1的横坐标是否小于p2的横坐标
	//if (p1.x >= p2.x)
	//	return ;

	////创建一个和原图片同样大小的Mat
	//Mat out = Mat::zeros(image_2.size(), CV_8UC1);

	////读取Mat信息
	//CV_Assert(image_2.depth() != sizeof(uchar));
	//int channels = image_2.channels();
	//int nRows = image_2.rows;
	//int nCols = image_2.cols * channels;

	////p1,p2,p3确定幂律函数曲线；0到p1 和 p3到255为两个斜率为0的线性方程
	//uchar table[256];
	//for (int i = 0; i < p1.x; i++)
	//{
	//	table[i] = p1.y;
	//}
	//for (int i = p1.x; i < p3.x; i++)
	//{
	//	//根据三点求出幂律函数曲线，再将像素点通过函数映射到table表中
	//	
	//}
	//for (int i = p3.x; i < 256; i++)
	//{
	//	table[i] = p3.y;
	//}

	////根据table表循环遍历找到对应的值赋值到newImg中
	//uchar *p, *q;
	//for (int i = 0; i < nRows; i++)
	//{
	//	p = image_2.ptr<uchar>(i);
	//	q = out.ptr<uchar>(i);
	//	for (int j = 0; j < nCols; j++)
	//		q[j] = table[p[j]];
	//}
	//ShowPic_2(out);
	newform2  Dl;
	if (Dl.DoModal() == IDOK) {
		int o = Dl.canshu;
		Mat image_2 = Mat::zeros(image.size(), CV_8UC1);
		cvtColor(image, image_2, COLOR_BGR2GRAY);
		out = Mat::zeros(image_2.size(), CV_8UC1);
		int channels = image_2.channels();
		int nRows = image_2.rows;
		int nCols = image_2.cols* channels;
		uchar* p;

		int k;
		//cout << "请输入常数k:的值：";
		//cin >> k;
		double g = 0;
		//double o = 5.0;
		for (int x = 0; x < nRows; x++) {
			for (int y = 0; y < nCols; y++) {
				g = image_2.ptr(x)[y];
				g = 1 * saturate_cast<uchar>(pow((double)g / 255., o)*255.0f);
				out.ptr(x)[y] = g;
			}
		}
		ShowPic_2(out);
	}
}




//newform1 *pe;

		   //频谱图
Mat CMFC_DEMODlg::ImageDCT()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	//img = imread("input.jpg", 0);
	TZ();
	//imshow("拓展图",tz_img);
	ZXH();
	//imshow("原始图",img);
	//imshow("中心化",tz_img);
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat outs = ShowSpectrum(complexImg);
	return outs;
	//傅里叶逆变换及复原图像显示

	//Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	//IdealFilter(complexFilter, 100, true);//true低通
	//IdealFilter(complexFilter, 50, false);//false高通

	///////////高斯低/高通滤波器//////////
	//GaussianFilter(complexFilter, 100, true);//true低通
	//GaussianFilter(complexFilter, 100, false);//false高通

	/////////巴特沃斯低/高通滤波器///////////
	//ButterworthFilter(complexFilter, 10, 10, true);
	//ButterworthFilter(complexFilter, 100, 2, false);

	//ShowSpectrum(complexFilter, "filtered_spectrum");
	//idft(complexFilter, complexFilter);
	//Mat out = ShowImage(complexFilter);//滤波处理后图像显示
	//return out;
	//waitKey();
}
//理想低通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_1()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	IdealFilter(complexFilter, 100, true);//true低通
	Mat outs=ShowSpectrum(complexFilter);
	//pe->ShowPic2(out);
	return outs;
}
//理想高通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_2()
{
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	//IdealFilter(complexFilter, 100, true);//true低通
										  IdealFilter(complexFilter, 100, false);//false高通

	Mat outs = ShowSpectrum(complexFilter);
	return outs;
}
//理想低通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_1()
{
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);

	Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	IdealFilter(complexFilter, 100, true);//true低通
	idft(complexFilter, complexFilter);
	Mat dd=ShowImage(complexFilter);//滤波处理后图像显示
	return dd;
}
//理想高通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_2()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	//img = imread("input.jpg", 0);
	TZ();
	//imshow("拓展图",tz_img);
	ZXH();
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);

	Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	//IdealFilter(complexFilter, 100, true);//true低通
										  IdealFilter(complexFilter, 100, false);//false高通

	idft(complexFilter, complexFilter);
	Mat dd_2 = ShowImage(complexFilter);//滤波处理后图像显示
	return dd_2;

}

//高斯低通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_3()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();

										  ///////////高斯低/高通滤波器//////////
										  GaussianFilter(complexFilter, 100, true);//true低通
									
	Mat outs = ShowSpectrum(complexFilter);
	return outs;
}
//高斯高通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_4()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	//img = imread("input.jpg", 0);
	TZ();
	//imshow("拓展图",tz_img);
	ZXH();
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	// ZXH();
	//Mat out = ShowSpectrum(complexImg);
	//return out;
	//傅里叶逆变换及复原图像显示

	Mat complexFilter = complexImg.clone();
										  GaussianFilter(complexFilter, 100, false);//false高通

									
	Mat outs = ShowSpectrum(complexFilter);
	return outs;
}
//高斯低通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_3()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	//img = imread("input.jpg", 0);
	TZ();
	//imshow("拓展图",tz_img);
	ZXH();

	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);

	//ShowSpectrum(complexImg, "DFT_Image");
	//傅里叶逆变换及复原图像显示

	Mat complexFilter = complexImg.clone();
	////////理想低/高通滤波器/////////////
	//IdealFilter(complexFilter, 100, true);//true低通
										  //IdealFilter(complexFilter, 50, false);//false高通

										  ///////////高斯低/高通滤波器//////////
										  GaussianFilter(complexFilter, 100, true);//true低通
									
	idft(complexFilter, complexFilter);
	Mat dd_3 = ShowImage(complexFilter);//滤波处理后图像显示
	return dd_3;
	
}
//高斯高通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_4()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();

	ZXH();

	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);

	//ShowSpectrum(complexImg, "DFT_Image");
	//傅里叶逆变换及复原图像显示

	Mat complexFilter = complexImg.clone();
	
										  ///////////高斯低/高通滤波器//////////
										  //GaussianFilter(complexFilter, 100, true);//true低通
										  GaussianFilter(complexFilter, 100, false);//false高通

	idft(complexFilter, complexFilter);
	Mat dd = ShowImage(complexFilter);//滤波处理后图像显示
	return dd;
}

//巴特沃斯低通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_5()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	

	Mat complexFilter = complexImg.clone();


											 /////////巴特沃斯低/高通滤波器///////////
											 ButterworthFilter(complexFilter, 50, 2, true);
											 //ButterworthFilter(complexFilter, 100, 2, false);

	Mat outs = ShowSpectrum(complexFilter);
	return outs;
}
//巴特沃斯高通滤波后频谱图
Mat CMFC_DEMODlg::ImageDCT_6()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();

											  /////////巴特沃斯低/高通滤波器///////////
											  //ButterworthFilter(complexFilter, 10, 10, true);
											  ButterworthFilter(complexFilter, 50, 2, false);

	Mat outs = ShowSpectrum(complexFilter);
	return outs;
}
//巴特沃斯低通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_5()
{
	// 读入图像
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();
											 /////////巴特沃斯低/高通滤波器///////////
											 ButterworthFilter(complexFilter, 50, 2, true);
											 //ButterworthFilter(complexFilter, 100, 2, false
	idft(complexFilter, complexFilter);
	Mat dd = ShowImage(complexFilter);//滤波处理后图像显示
	return dd;
}
//巴特沃斯高通频域滤波器复原图
Mat CMFC_DEMODlg::ImageLIX_6()
{
	cvtColor(image, img, COLOR_BGR2GRAY);
	TZ();
	ZXH();
	//为傅立叶变换的结果(实部和虚部)分配存储空间
	//这里是获取了两个mat，一个用于存放dft变换的实部，一个用于存放虚部，初始的时候，实部就是图像本身，虚部全为0
	Mat plane[] = { tz_img, Mat::zeros(tz_img.size(), CV_32F) };
	Mat complexImg;
	merge(plane, 2, complexImg); //将plane融合合并成一个多通道数组complexI
								 //将几个单通道的mat融合成一个多通道的mat，这里融合的complexImg即有实部，又有虚部
								 //快速傅里叶变换及频谱显示
	dft(complexImg, complexImg);
	Mat complexFilter = complexImg.clone();
											  /////////巴特沃斯低/高通滤波器///////////
											  //ButterworthFilter(complexFilter, 10, 10, true);
											  ButterworthFilter(complexFilter, 50, 2, false);
	idft(complexFilter, complexFilter);
	Mat dd = ShowImage(complexFilter);//滤波处理后图像显示
	return dd;
}


//拓展图像以进行高效的DFT
void CMFC_DEMODlg::TZ()
{
	int h = getOptimalDFTSize(img.rows);//返回DFT最优尺寸大小
	int w = getOptimalDFTSize(img.cols);
	if (w > img.cols || h > img.rows)
		copyMakeBorder(img, tz_img, 0, h - img.rows, 0, w - img.cols, BORDER_CONSTANT, Scalar::all(0));
	else
		img.copyTo(tz_img);
}
//谱的中心化
void CMFC_DEMODlg::ZXH()
{
	tz_img.convertTo(tz_img, CV_32FC1);
	for (int i = 0; i<tz_img.rows; i++)
	{
		float *ptr = tz_img.ptr<float>(i);
		for (int j = 0; j < tz_img.cols; j++)
			ptr[j] *= pow(-1.0, i + j);//用(-1)^(x+y)乘以拓展后的图像
	}
}

// 显示DFT后的频谱
Mat CMFC_DEMODlg::ShowSpectrum(Mat input)
{
	Mat plane[2];
	//将complexImg重新拆分成两个mat，一个是实部，一个是虚部
	split(input, plane); //即plane[0]为实部,planes[1]为虚部
						 //将两个mat对应位置相乘
	magnitude(plane[0], plane[1], plane[0]);//计算二维矢量的幅值
	plane[0] += Scalar::all(1);
	log(plane[0], plane[0]);//对傅里叶谱执行对数变换，增强细节
	normalize(plane[0], plane[0], 0, 1, CV_MINMAX);//归一化
	Mat tmp = plane[0];
	return tmp;
												   //窗口大小会自动调整以适应所显示的图像
	//cvNamedWindow(caption.c_str(), CV_WINDOW_AUTOSIZE);
	//imshow(caption.c_str(), plane[0]);
}
// 显示IDFT后的复原图像
Mat CMFC_DEMODlg::ShowImage(Mat input)
{
	Mat plane[2];
	split(input, plane);//将complexImg重新拆分成两个mat，一个是实部，一个是虚部
	for (int i = 0; i<plane[0].rows; i++)//取消输入图像的乘数
	{
		float *ptr = plane[0].ptr<float>(i);
		for (int j = 0; j < plane[0].cols; j++)
			ptr[j] *= pow((double)(-1), (double)(i + j));
	}
	normalize(plane[0], plane[0], 0, 1, CV_MINMAX);//归一化
	Mat tmp = plane[0];
	return tmp;
	/*cvNamedWindow(caption.c_str(), CV_WINDOW_AUTOSIZE);
	imshow(caption.c_str(), plane[0]);*/
	//return plane[0];

}
//高斯低/高通滤波器
void CMFC_DEMODlg::GaussianFilter(Mat& input, float D0, bool flag)
{
	Mat GaussianKernel(input.size(), CV_32FC2);
	float d0 = 2 * pow(double(D0), 2.0);
	for (int i = 0; i<input.rows; i++)
	{
		float*p = GaussianKernel.ptr<float>(i);
		for (int j = 0; j<input.cols; j++)
		{
			float d2 = pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0);
			if (flag)//true为低通
			{
				p[2 * j] = expf(-d2 / d0);
				p[2 * j + 1] = expf(-d2 / d0);
			}
			else//高通
			{
				p[2 * j] = 1 - expf(-d2 / d0);
				p[2 * j + 1] = 1 - expf(-d2 / d0);
			}
		}
	}
	multiply(input, GaussianKernel, input);
}
//理想低/高通滤波器
void CMFC_DEMODlg::IdealFilter(Mat& input, float D0, bool flag)
{
	Mat IdealKernel(input.size(), CV_32FC2);

	for (int i = 0; i<input.rows; i++)
	{
		float*p = IdealKernel.ptr<float>(i);
		for (int j = 0; j<input.cols; j++)
		{
			float d2 = pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0);
			float d3 = sqrt(d2);
			if (flag)//true为低通
			{
				if (d3 <= D0)
				{//指定距离之内的低频成分全部保留
					p[2 * j] = 1;
					p[2 * j + 1] = 1;
				}
				else
				{//指定距离之外的高频成分全部被截断
					p[2 * j] = 0;
					p[2 * j + 1] = 0;
				}
			}
			else//高通
			{
				if (d3 <= D0)
				{//指定距离之内的低频成分全部被截断
					p[2 * j] = 0;
					p[2 * j + 1] = 0;
				}
				else
				{//指定距离之外的高频成分全部保留
					p[2 * j] = 1;
					p[2 * j + 1] = 1;
				}
			}
		}
	}
	multiply(input, IdealKernel, input);
}

//巴特沃斯低/高通滤波器
void CMFC_DEMODlg::ButterworthFilter(Mat& input, float D0, float n, bool flag)
{
	Mat ButterworthKernel(input.size(), CV_32FC2);
	for (int i = 0; i<input.rows; i++)
	{
		float*p = ButterworthKernel.ptr<float>(i);
		for (int j = 0; j<input.cols; j++)
		{
			float d2 = pow(i - input.rows / 2, 2.0) + pow(j - input.cols / 2, 2.0);
			float d3 = sqrt(d2);
			if (flag)//true低通
			{
				p[2 * j] = 1 / (pow(d3 / D0, (2 * n)) + 1);
				p[2 * j + 1] = 1 / (pow(d3 / D0, (2 * n)) + 1);
			}
			else//false高通
			{
				p[2 * j] = 1 / (pow(D0 / d3, (2 * n)) + 1);
				p[2 * j + 1] = 1 / (pow(D0 / d3, (2 * n)) + 1);
			}
		}
	}
	multiply(input, ButterworthKernel, input);
}
