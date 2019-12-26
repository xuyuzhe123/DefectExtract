#include "opencv2/opencv.hpp"
#include "iostream"

using namespace std;
using namespace cv;



#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
	Mat image, imagemean, diff, Mask;
	string path = "I:\\defectdata\\pers\\func\\pers14.png";
	image = cv::imread(path);
	blur(image, imagemean, Size(35,35));
	subtract(imagemean, image, diff);
	threshold(diff, Mask, 3, 255, THRESH_BINARY_INV);
	imshow("imagemean", imagemean);
	imshow("diff", diff);
	imshow("Mask", Mask);
	Mat imagegray;
	cvtColor(Mask, imagegray, CV_RGB2GRAY);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	findContours(imagegray, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	Mat drawing = Mat::zeros(Mask.size(), CV_8U);
	int j = 0;
	for (int i = 0; i < contours.size(); i++)
	{
		Moments moms = moments(Mat(contours[i]));
		double area = moms.m00;

		if (area > 50 && area < 10000)
		{
			drawContours(drawing, contours, i, Scalar(255), 1, 8, hierarchy, 0, Point());
			j = j + 1;
		}

	}

	Mat element15(3, 3, CV_8U, Scalar::all(1));
	Mat close;
	morphologyEx(drawing, close, MORPH_CLOSE, element15);
	imshow("drawing", drawing);


	vector<vector<Point> > contours1;
	vector<Vec4i> hierarchy1;
	findContours(close, contours1, hierarchy1, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));
	imshow("close", close);
	j = 0;
	int m = 0;
	for (int i = 0; i < contours1.size(); i++)
	{
		Moments moms = moments(Mat(contours1[i]));
		double area = moms.m00;//零阶矩即为二值图像的面积  double area = moms.m00;
		//如果面积超出了设定的范围，则不再考虑该斑点

		double area1 = contourArea(contours1[i]);
		if (area > 50 && area < 100000)
		{
			drawContours(image, contours1, i, Scalar(0, 0, 255), 1, 8, hierarchy1, 0, Point());
			j = j + 1;

		}
		/*else if (area >= 0 && area <= 50)
		{
			drawContours(image, contours1, i, Scalar(255, 0, 0), 1, 8, hierarchy1, 0, Point());
			m = m + 1;

		}*/
	}

	
	string txt = "" ;
	putText(image, txt, Point(20, 30), CV_FONT_HERSHEY_COMPLEX, 1,
		Scalar(0, 0, 255), 2, 8);

	
	imshow("result", image);


	cv::waitKey(0);


}

