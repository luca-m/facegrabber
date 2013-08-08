/*
 * FlandmarkLocator.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#include <stdlib.h>

#include "FlandmarkLocator.h"
#include "../model/FacePoints.h"
#include "../misc/Utils.h"

using namespace cv;

namespace facegrabber {

FlandmarkLocator::FlandmarkLocator(char * configFilePath) {
	fmModel = flandmark_init(configFilePath);
	assert(fmModel != 0);
	currImg = 0;
	currFaceRegion = 0;
	middlepointThreshold = 0.001;
	// Canny default parameters
	cannyLowThr = 200;
	cannyHighThr = 255;
	cannySobelSize = 3;
}
FlandmarkLocator::~FlandmarkLocator() {
	flandmark_free(fmModel);
}

void FlandmarkLocator::locateEyebrow(cv::Mat & grayimg, bool isLeft,
		IFacePoints * points) {
	if (grayimg.cols == 0 || grayimg.rows == 0)
		return;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	cv::Mat e1 = getStructuringElement(cv::MORPH_RECT, Size(7, 1));
	cv::Mat e11 = getStructuringElement(cv::MORPH_RECT,
			Size((int) (grayimg.cols * 0.05 < 1 ? 1 : grayimg.cols * 0.05),
					(int) (grayimg.rows * 0.3 < 1 ? 1 : grayimg.rows * 0.3)));
	cv::Mat e2 = getStructuringElement(cv::MORPH_RECT, Size(3, 3));
	cv::Mat e3 = getStructuringElement(cv::MORPH_RECT, Size(1, 7));

	/// Filtering
	equalizeHist(grayimg, grayimg);
//	cv::blur(grayimg, grayimg, e1.size());
//	cv::medianBlur(grayimg, grayimg, 5);
//	enancheLocalConstrast(grayimg, grayimg, e2, 1);
	cv::morphologyEx(grayimg, grayimg, cv::MORPH_GRADIENT, e3,
			cv::Point(-1, -1), 1, cv::BORDER_CONSTANT);
	/// Segmentate with kmeans
	kmeansSegmentationGrayScale(grayimg, grayimg, 2, 5);
	equalizeHist(grayimg, grayimg);
	/// Detect edges using canny
	Canny(grayimg, grayimg, cannyLowThr, cannyHighThr, cannySobelSize);
	/// Find contours
	findContours(grayimg.clone(), contours, hierarchy, CV_RETR_EXTERNAL,
			CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	vector<vector<Point> > hull(contours.size());
	cv::Mat drawing = cv::Mat::zeros(grayimg.size(), CV_8UC3);
	cv::RNG rng(11);
	cv::Scalar color = cv::Scalar(255, 127, 127);
	double bigger = std::numeric_limits<double>::min();
	int biggerI = -1;

	for (unsigned int j = 0; j < contours.size(); j++) {
		convexHull(contours[j], hull[j], true);
	}

	for (unsigned int j = 0; j < contours.size(); j++) {
		double area = cv::arcLength(hull.at(j),true);
		if (area > bigger) {
			biggerI = j;
			bigger = area;
		}
		color = cv::Scalar(rng.uniform(127, 255), rng.uniform(127, 255), 0);
		cv::drawContours(drawing, contours, j, color, 1, 8, hierarchy, 0,
				cv::Point());
	}
	color = cv::Scalar(0, 0, 255);
	std::cout << "bigger contous: " << biggerI << "\n";
	cv::drawContours(drawing, contours, biggerI, color, 2, 8, hierarchy, 0,
			cv::Point());

	cv::Point init(0, 0);
	cv::Point mid(0, 0);
	cv::Point ext(0, 0);
	if (contours.size() > 0 && biggerI > 0 && biggerI < contours.size()) {
		getSegmentRelevantPoints(contours.at(biggerI), isLeft, init, mid, ext,
				this->middlepointThreshold);

		CvPoint tmp;
		if (isLeft) {
			tmp.x = this->currFaceRegion->getEyeBrowL()->x + init.x;
			tmp.y = this->currFaceRegion->getEyeBrowL()->y + init.y;
			points->setEyeBrowLCornerR(&tmp);
			tmp.x = this->currFaceRegion->getEyeBrowL()->x + ext.x;
			tmp.y = this->currFaceRegion->getEyeBrowL()->y + ext.y;
			//points->setEyeBrowLCornerL(&tmp);

		} else {
			tmp.x = this->currFaceRegion->getEyeBrowR()->x + ext.x;
			tmp.y = this->currFaceRegion->getEyeBrowR()->y + ext.y;
			//points->setEyeBrowRCornerR(&tmp);
			tmp.x = this->currFaceRegion->getEyeBrowR()->x + init.x;
			tmp.y = this->currFaceRegion->getEyeBrowR()->y + init.y;
			points->setEyeBrowRCornerL(&tmp);
		}
//		circle(drawing, init, 5, color, 4, 0, 0);
//		circle(drawing, mid, 5, color, 4, 0, 0);
//		circle(drawing, ext, 5, color, 4, 0, 0);
	}

	if (isLeft)
		cv::imshow("GRAY LEFT", drawing);
	else
		cv::imshow("GRAY RIGHT", drawing);
}

void FlandmarkLocator::locateEyebrows(IplImage * img_grayscale,
		IFaceRegion * region, IFacePoints * points) {
	if (!region->hasEyeBrowL() && !region->hasEyeBrowR()) {
		return;
	}
	if (region->hasEyeBrowL()) {
		IplImage * roi = getSubImg(img_grayscale, region->getEyeBrowL());
		cv::Mat gray(roi);
		locateEyebrow(gray, true, points);
		cvReleaseImage(&roi);
	}
	if (region->hasEyeBrowL()) {
		IplImage * roi = getSubImg(img_grayscale, region->getEyeBrowR());
		cv::Mat gray(roi);
		locateEyebrow(gray, false, points);
		cvReleaseImage(&roi);
	}

}

IFacePoints * FlandmarkLocator::locate(IplImage * img, IFaceRegion * region) {
	CvPoint tmp;
	IplImage * im_gray;
	FacePoints * points = new FacePoints();
	if (img == 0 || region == 0 || !region->hasFace()) {
		return points;
	}
	currImg = img;
	currFaceRegion = region;
	int *bbox = (int*) malloc(4 * sizeof(int));
	double *landmarks = (double*) malloc(
			2 * fmModel->data.options.M * sizeof(double));

	im_gray = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img, im_gray, CV_RGB2GRAY);
	cvEqualizeHist(im_gray, im_gray);

	bbox[0] = region->getFace()->x;
	bbox[1] = region->getFace()->y;
	bbox[2] = region->getFace()->x + region->getFace()->width;
	bbox[3] = region->getFace()->y + region->getFace()->height;

	flandmark_detect(im_gray, bbox, fmModel, landmarks);

	tmp.x = (int) landmarks[0];
	tmp.y = (int) landmarks[1];
	points->setBasePoint(&tmp);
	tmp.x = (int) landmarks[2];
	tmp.y = (int) landmarks[3];
	points->setEyeRCornerL(&tmp);
	tmp.x = (int) landmarks[4];
	tmp.y = (int) landmarks[5];
	points->setEyeLCornerR(&tmp);
	tmp.x = (int) landmarks[6];
	tmp.y = (int) landmarks[7];
	points->setMouthCornerR(&tmp);
	tmp.x = (int) landmarks[8];
	tmp.y = (int) landmarks[9];
	points->setMouthCornerL(&tmp);
	tmp.x = (int) landmarks[10];
	tmp.y = (int) landmarks[11];
	points->setEyeRCornerR(&tmp);
	tmp.x = (int) landmarks[12];
	tmp.y = (int) landmarks[13];
	points->setEyeLCornerL(&tmp);
	tmp.x = (int) landmarks[14];
	tmp.y = (int) landmarks[15];
	points->setNoseCenter(&tmp);

	locateEyebrows(im_gray, region, points);

	cvReleaseImage(&im_gray);
	free(bbox);
	free(landmarks);
	currImg = 0;
	currFaceRegion = 0;
	return points;
}

} /* namespace facegrabber  */
