/*
 * testDetection.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <limits>

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/opencv.hpp>
#include "Utils.h"

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
char eyeb6[] = "eyebL/eyebrow6.png";
char eyeb7[] = "eyebL/eyebrow7.png";
char eyeb8[] = "eyebL/eyebrow8.png";
char eyeb9[] = "eyebL/eyebrow9.png";
char eyeb10[] = "eyebL/eyebrow10.png";

vector<const char *> names;
vector<IplImage*> orig;
vector<Mat> images;
vector<Mat> grays;
//Mat src;
//Mat src_gray;
int thresh = 200;
int max_thresh = 255;
RNG rng(12345);

void thresh_callback(int, void*);

int main(int argv, char * args[]) {
	try {
		unsigned int i;
		//names.push_back(eyeb1);
//		names.push_back(eyeb2);
//		names.push_back(eyeb3);
//		names.push_back(eyeb4);
//		names.push_back(eyeb5);
//		names.push_back(eyeb6);
		names.push_back(eyeb7);
		names.push_back(eyeb8);
		names.push_back(eyeb9);
		names.push_back(eyeb6);
		names.push_back(eyeb10);

		for (i = 0; i < names.size(); i++) {
			orig.push_back(cvLoadImage(names.at(i), CV_LOAD_IMAGE_COLOR));
		}

		cvNamedWindow("Master", 1);

		for (i = 0; i < names.size(); i++) {
			namedWindow(names.at(i), CV_WINDOW_AUTOSIZE);
			string s = names.at(i);
			string ss = s + "_contour";
			//namedWindow(ss, CV_WINDOW_AUTOSIZE);
		}

		for (i = 0; i < orig.size(); i++) {
			Mat ima(orig.at((i)));
			images.push_back(ima);
			Mat gray;
			cvtColor(ima, gray, CV_BGR2GRAY);
			grays.push_back(gray);
		}

		createTrackbar(" Canny thresh:", "Master", &thresh, max_thresh,
				thresh_callback);

		thresh_callback(0, 0);

		while (true) {
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

	for (unsigned int i = 0; i < grays.size(); i++) {

		Mat src_gray = grays.at(i);
		Mat canny_output;
		src_gray.copyTo(canny_output);
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		Mat e1 = getStructuringElement(cv::MORPH_RECT, Size(7, 1));
		Mat e11 =
				getStructuringElement(cv::MORPH_RECT,
						Size(
								(int) (src_gray.cols * 0.05 < 1 ?
										1 : src_gray.cols * 0.05),
								(int) (src_gray.rows * 0.3 < 1 ?
										1 : src_gray.rows * 0.3)));
		Mat e2 = getStructuringElement(cv::MORPH_RECT, Size(3, 3));
		Mat e3 = getStructuringElement(cv::MORPH_RECT, Size(1, 7));
		/// Filtering
		equalizeHist(canny_output, canny_output);
//		cv::blur(canny_output, canny_output, e1.size());
//		cv::medianBlur(canny_output, canny_output, 5);
//		enancheLocalConstrast(canny_output, canny_output, e2, 1);
		cv::morphologyEx(canny_output, canny_output, cv::MORPH_GRADIENT, e3,
				cv::Point(-1, -1), 1, cv::BORDER_CONSTANT);

		vector<Point2f> corners;
		goodFeaturesToTrack(canny_output, corners, 500, (thresh+1)/256.0, 10, Mat(), 3, 0, 0.04);
		cornerSubPix(canny_output, corners, Size(10, 10), Size(-1, -1),
				TermCriteria(TermCriteria::COUNT | TermCriteria::EPS, 20,
						0.03));


		/// Segmentate with kmeans
		kmeansSegmentationGrayScale(canny_output, canny_output, 2, 5);
		equalizeHist(canny_output, canny_output);
		/// Detect edges using canny
		Canny(canny_output, canny_output, thresh, thresh * 2, 3);
		/// Find contours
		findContours(canny_output.clone(), contours, hierarchy,
				CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));


		/// Draw contours
		vector<vector<Point> > hull(contours.size());
		Mat drawing = Mat::zeros(canny_output.size(), CV_8UC1);
		drawing += src_gray;


		Scalar color = Scalar(rng.uniform(127, 255), rng.uniform(127, 255),
				rng.uniform(0, 255));
		double bigger = std::numeric_limits<double>::min();
		int biggerI = -1;
		for (unsigned int j = 0; j < contours.size(); j++) {
			convexHull(contours[j], hull[j], true);
		}

		for (unsigned int j = 0; j < contours.size(); j++) {
			double area = cv::arcLength(hull.at(j), true);
			if (area > bigger) {
				biggerI = j;
				bigger = area;
			}
			color = Scalar(rng.uniform(127, 255), rng.uniform(127, 255), 0);
			drawContours(drawing, contours, j, color, 1, 8, hierarchy, 0,
					Point());
		}
		color = Scalar(0, 0, 255);
		cout << "bigger hull: " << biggerI << "\n";
		drawContours(drawing, contours, biggerI, color, 1, 8, hierarchy, 0,
				Point());
		Mat d = cv::Mat::zeros(canny_output.size(), CV_8UC1);
		if (contours.size() > 0)
			drawContours(drawing, contours, biggerI, Scalar(255), CV_FILLED, 8,
					hierarchy, 0, Point());
		//thinning(d);
		//biggerI=0;
		Point init(0, 0);
		Point mid(0, 0);
		Point ext(0, 0);
		if (contours.size() > 0 && biggerI > 0) {
			getSegmentRelevantPoints(contours.at(biggerI), true, init, mid, ext,
					0.001);
			circle(drawing, init, 3, color, 2, 0, 0);
			circle(drawing, mid, 3, color, 2, 0, 0);
			circle(drawing, ext, 3, color, 2, 0, 0);
		}
		for (int j = 0; j < corners.size(); j++) {
			circle(drawing, corners.at(j), 3, Scalar(0, 255, 0), -1, 8);
		}


		string s = names.at(i);
		string ss = s + "_contour";
		imshow(ss, drawing);
		imshow(names.at(i), canny_output);

	}

}

