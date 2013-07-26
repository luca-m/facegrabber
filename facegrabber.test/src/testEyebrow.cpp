/*
 * testDetection.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

const char win_detection[] = "Detection";
const char win_localization[] = "Localization";

char face_conf[] = "resources/haarcascade_frontalface_alt.xml";
char eyeL_conf[] = "resources/haarcascade_lefteye_2splits.xml";
char eyeR_conf[] = "resources/haarcascade_righteye_2splits.xml";
char nose_conf[] = "resources/haarcascade_mcs_nose.xml";
char mouth_conf[] = "resources/haarcascade_mcs_mouth.xml";
char fm_model[] = "resources/flandmark_model.dat";

char lena[] = "data/lena.tif";
char video[] = "data/video.avi";

char eyeb1[] = "eyebL/eyebrow1.png";
char eyeb2[] = "eyebL/eyebrow2.png";
char eyeb3[] = "eyebL/eyebrow3.png";
char eyeb4[] = "eyebL/eyebrow4.png";
char eyeb5[] = "eyebL/eyebrow5.png";

vector<const char *> names;
vector<IplImage*> orig;
vector<Mat> images;
vector<Mat> grays;
//Mat src;
//Mat src_gray;
int thresh = 50;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void*);

int main(int argv, char * args[]) {
	try {
		int i;
		names.push_back(eyeb1);
		names.push_back(eyeb2);
		names.push_back(eyeb3);
		names.push_back(eyeb4);
		names.push_back(eyeb5);

		for (i = 0; i < names.size(); i++) {
			orig.push_back(cvLoadImage(names.at(i), CV_LOAD_IMAGE_COLOR));
		}

		cvNamedWindow("Master", 1);

		for (i = 0; i < names.size(); i++) {
			namedWindow(names.at(i), CV_WINDOW_AUTOSIZE);
			string s = names.at(i);
			string ss = s + "_contour";
			namedWindow(ss, CV_WINDOW_AUTOSIZE);
		}

		for (i = 0; i < orig.size(); i++) {
			Mat ima(orig.at((i)));
			Mat e1 = getStructuringElement(cv::MORPH_RECT,
					Size((int) ima.cols * 0.1, (int) ima.rows * 0.05));
			images.push_back(ima);
			Mat gray;
			cvtColor(ima, gray, CV_BGR2GRAY);

			//Mat d,dd;
			//Mat e2 = getStructuringElement(cv::MORPH_RECT, Size(3, 3));
			//cv::morphologyEx(gray, d, cv::MORPH_TOPHAT, e2);
			//cv::morphologyEx(gray, dd, cv::MORPH_BLACKHAT, e2);
			//gray = gray + d - dd;

			cv::blur(gray, gray, Size((int) ima.cols * 0.1, 10));
			cv::medianBlur(gray, gray, 9);
			cv::equalizeHist(gray, gray);

			/* its a opening considering black as foregruond*/
			//cv::morphologyEx(gray, gray, cv::MORPH_CLOSE, e1);
			//cv::dilate(gray, gray, e1);
			//cv::erode(gray, gray, e1);

			//cv::blur(gray, gray, cv::Size(5, 5));
			//cv::medianBlur(gray, gray, 9);
			grays.push_back(gray);
		}
		//src = cv::Mat(image1);

		//blur(src_gray, src_gray, Size(3, 3));
		createTrackbar(" Canny thresh:", "Master", &thresh, max_thresh,
				thresh_callback);
		thresh_callback(0, 0);

		while (true) {

			//imshow(eyeb1, im);
			//cvShowImage(eyeb1, image1);
			//cvShowImage(eyeb2, image2);
			//cvShowImage(eyeb3, image3);

			//cvShowImage(win_detail_1, image);
			//cv::Mat frame(image);
			//cv::imshow(win_detail_1,frame);

			int c = cvWaitKey(0);
			if ((char) c == 'q') {
				break;
			}
		}
	} catch (int e) {
		cout << "Exception #" << e;
	}
}
/** @function thresh_callback */
void thresh_callback(int, void*) {

	for (int i = 0; i < names.size(); i++) {

		Mat src_gray = grays.at(i);
		Mat canny_output;
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		/// Detect edges using canny
		Canny(src_gray, canny_output, thresh, thresh * 2, 3);
		/// Find contours
		findContours(canny_output, contours, hierarchy, CV_RETR_TREE,
				CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

		/// Draw contours
		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
		for (int i = 0; i < contours.size(); i++) {
			Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255),
					rng.uniform(0, 255));
			drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0,
					Point());
		}
		string s = names.at(i);
		string ss = s + "_contour";
		imshow(ss, drawing);
		/// Show in a window
		//namedWindow("Contours", CV_WINDOW_AUTOSIZE);
		//imshow("Contours", drawing);
		imshow(names.at(i), grays.at(i));
	}

}

