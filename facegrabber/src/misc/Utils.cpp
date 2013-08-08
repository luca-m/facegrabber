/*
 * Utils.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "Utils.h"

void showHistogram(char* window_title, IplImage* src, char* channel_name) {
	IplImage* img, *canvas;
	int bins = 256;
	int hist[bins];
	double scale;
	int i, j, channel, max = 0;

	CvScalar colors[] = { CV_RGB(0,0,255), CV_RGB(0,255,0), CV_RGB(255,0,0),
	CV_RGB(0,0,0) };

	channel = strcmp(channel_name, "blue") == 0 ? 0 :
				strcmp(channel_name, "green") == 0 ? 1 :
				strcmp(channel_name, "red") == 0 ? 2 :
				strcmp(channel_name, "gray") == 0 ? 3 : 0;

	if (src->nChannels == 3 && channel == 3) {
		img = cvCreateImage(cvGetSize(src), 8, 1);
		cvCvtColor(src, img, CV_BGR2GRAY);
	} else if (channel > src->nChannels)
		return;
	else
		img = cvCloneImage(src);

	canvas = cvCreateImage(cvSize(256, 125), IPL_DEPTH_8U, 3);
	cvSet(canvas, CV_RGB(255,255,255), NULL);

	/* Reset histogram */
	for (j = 0; j < bins - 1; hist[j] = 0, j++)
		;
	for (i = 0; i < img->height; i++) {
		uchar* ptr = (uchar*) (img->imageData + i * img->widthStep);
		for (j = 0; j < img->width; j += img->nChannels)
			hist[ptr[j + (channel == 3 ? 0 : channel)]]++;
	}
	/* Get histogram peak */
	for (i = 0; i < bins - 1; i++)
		max = hist[i] > max ? hist[i] : max;
	scale = max > canvas->height ? (double) canvas->height / max : 1.;
	/* Draw histogram */
	for (i = 0; i < bins - 1; i++) {
		CvPoint pt1 = cvPoint(i, canvas->height - (hist[i] * scale));
		CvPoint pt2 = cvPoint(i, canvas->height);
		cvLine(canvas, pt1, pt2, colors[channel], 1, 8, 0);
	}
	cvShowImage(window_title, canvas);
	cvReleaseImage(&img);
}
IplImage* getImgCopy(IplImage* img) {
	IplImage* copy = cvCreateImage(cvSize(img->width, img->height), img->depth,
			img->nChannels);
	cvCopy(img, copy, 0);
	return copy;
}
IplImage* getSubImg(IplImage* img, CvRect *roiRect) {
	cvSetImageROI(img, *roiRect);
	IplImage* subImg = cvCreateImage(cvSize(roiRect->width, roiRect->height),
			img->depth, img->nChannels);
	cvCopy(img, subImg, 0);
	cvResetImageROI(img);
	return subImg;
}
cv::Point pointAtManhattanDist(std::vector<cv::Point> segment, float length) {
	float len = 0.0f;
	for (unsigned int j = 1; j < segment.size(); j++) {
		len += abs(segment.at(j - 1).x - segment.at(j).x)
				+ abs(segment.at(j - 1).y - segment.at(j).y);
		if (len >= length) {
			return segment.at(j);
		}
	}
	return segment.at(segment.size() - 1);
}
cv::Point pointEuclideanDist(std::vector<cv::Point> segment, float length) {
	float len = 0.0f;
	length *= length;
	for (unsigned int j = 1; j < segment.size(); j++) {
		len += (segment.at(j - 1).x - segment.at(j).x)
				* (segment.at(j - 1).x - segment.at(j).x)
				+ (segment.at(j - 1).y - segment.at(j).y)
						* (segment.at(j - 1).y - segment.at(j).y);
		if (len >= length) {
			return segment.at(j);
		}
	}
	return segment.at(segment.size() - 1);
}
float lenManhattan(std::vector<cv::Point> segment) {
	float len = 0.0f;
	for (unsigned int j = 1; j < segment.size(); j++) {
		len += abs(segment.at(j - 1).x - segment.at(j).x)
				+ abs(segment.at(j - 1).y - segment.at(j).y);
	}
	return len;
}
float lenEuclideanSquared(std::vector<cv::Point> segment) {
	float len = 0.0f;
	for (unsigned int j = 1; j < segment.size(); j++) {
		len += (segment.at(j - 1).x - segment.at(j).x)
				* (segment.at(j - 1).x - segment.at(j).x)
				+ (segment.at(j - 1).y - segment.at(j).y)
						* (segment.at(j - 1).y - segment.at(j).y);
	}
	return len;
}
int pointAtMinX(std::vector<cv::Point> & segment) {
	unsigned int index = 0;
	float min = std::numeric_limits<float>::max();
	for (unsigned int i = 0; i < segment.size(); i++) {
		if (segment.at(i).x < min) {
			min = segment.at(i).x;
			index = i;
		}
	}
	return index;
}
int pointAtMaxX(std::vector<cv::Point> & segment) {
	unsigned int index = 0;
	float max = std::numeric_limits<float>::min();
	for (unsigned int i = 0; i < segment.size(); i++) {
		if (segment.at(i).x > max) {
			max = segment.at(i).x;
			index = i;
		}
	}
	return index;
}
int pointAtX(std::vector<cv::Point> & segment, int x, float threshold) {
	unsigned int index = 0;
	for (unsigned int i = 0; i < segment.size(); i++) {
		if (abs(segment.at(i).x - x) <= threshold) {
			index = i;
			return index;
		}
	}
	return index;
}
bool getSegmentRelevantPoints(std::vector<cv::Point> & segment, bool isLeft,
		cv::Point & inter, cv::Point & middle, cv::Point & exter,
		float threshold) {

	if (segment.size() < 1) {
		return false;
	}
	if (isLeft) {
		int iinter = pointAtMinX(segment);
		int iexter = pointAtMaxX(segment);
		int imiddle = pointAtX(segment,
				segment.at(iinter).x
						+ (segment.at(iexter).x - segment.at(iinter).x) / 2,
				threshold);
		inter.x = segment.at(iinter).x;
		inter.y = segment.at(iinter).y;
		exter.x = segment.at(iexter).x;
		exter.y = segment.at(iexter).y;
		middle.x = segment.at(imiddle).x;
		middle.y = segment.at(imiddle).y;
	} else {
		int iinter = pointAtMaxX(segment);
		int iexter = pointAtMinX(segment);
		int imiddle = pointAtX(segment,
				segment.at(iinter).x
						+ (segment.at(iinter).x - segment.at(iexter).x) / 2,
				threshold);
		inter.x = segment.at(iinter).x;
		inter.y = segment.at(iinter).y;
		exter.x = segment.at(iexter).x;
		exter.y = segment.at(iexter).y;
		middle.x = segment.at(imiddle).x;
		middle.y = segment.at(imiddle).y;
	}
	return true;
}

void hitAndMiss(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel) {
	CV_Assert(src.type() == CV_8U && src.channels() == 1);

	cv::Mat k1 = (kernel == 1) / 255;
	cv::Mat k2 = (kernel == -1) / 255;

	cv::normalize(src, src, 0, 1, cv::NORM_MINMAX);

	cv::Mat e1, e2;
	cv::erode(src, e1, k1, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
			cv::Scalar(0));
	cv::erode(1 - src, e2, k2, cv::Point(-1, -1), 1, cv::BORDER_CONSTANT,
			cv::Scalar(0));
	dst = e1 & e2;
}
void enhanceLocalConstrast(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel,
		double scaleFactor) {
	cv::Mat toph, both;
	cv::morphologyEx(src, toph, cv::MORPH_TOPHAT, kernel);
	cv::morphologyEx(src, both, cv::MORPH_BLACKHAT, kernel);
	dst = src + scaleFactor * toph - scaleFactor * both;
}
void imReconstruct(cv::Mat& marker_src, cv::Mat& dst, cv::Mat& mask,
		cv::Mat& kernel, unsigned int maxIter) {
	bool stop = false;
	unsigned int iter = 0;
	cv::Mat marker(marker_src);
	while (!stop && iter < maxIter) {
		cv::morphologyEx(marker, dst, cv::MORPH_DILATE, kernel);
		cv::min(dst, mask, dst);
		cv::Mat tmp;
		cv::subtract(dst, marker, tmp);
		if (cv::countNonZero(tmp) > 0) {
			dst.copyTo(marker);
			iter++;
		} else {
			stop = true;
		}
	}
}
/**
 * Perform one thinning iteration.
 * Normally you wouldn't call this function directly from your code.
 *
 * @param  im    Binary image with range = 0-1
 * @param  iter  0=even, 1=odd
 */
void _thinningIteration(cv::Mat& im, int iter) {
	cv::Mat marker = cv::Mat::zeros(im.size(), CV_8UC1);

	for (int i = 1; i < im.rows - 1; i++) {
		for (int j = 1; j < im.cols - 1; j++) {
			uchar p2 = im.at<uchar>(i - 1, j);
			uchar p3 = im.at<uchar>(i - 1, j + 1);
			uchar p4 = im.at<uchar>(i, j + 1);
			uchar p5 = im.at<uchar>(i + 1, j + 1);
			uchar p6 = im.at<uchar>(i + 1, j);
			uchar p7 = im.at<uchar>(i + 1, j - 1);
			uchar p8 = im.at<uchar>(i, j - 1);
			uchar p9 = im.at<uchar>(i - 1, j - 1);

			int A = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1)
					+ (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1)
					+ (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1)
					+ (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
			int B = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
			int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
			int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

			if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
				marker.at<uchar>(i, j) = 1;
		}
	}

	im &= ~marker;
}

/**
 * Function for thinning the given binary image.
 *
 *  <a href="http://dl.acm.org/citation.cfm?id=358023">Zhang-Suen Algorithm</a>
 *
 * @param  im  Binary image with range = 0-255
 */
void thinning(cv::Mat& im) {
	im /= 255;

	cv::Mat prev = cv::Mat::zeros(im.size(), CV_8UC1);
	cv::Mat diff;

	do {
		_thinningIteration(im, 0);
		_thinningIteration(im, 1);
		cv::absdiff(im, prev, diff);
		im.copyTo(prev);
	} while (cv::countNonZero(diff) > 0);

	im *= 255;
}

void kmeansSegmentationGrayScale(cv::Mat & src, cv::Mat & dst, int clusterCount,
		int attempts) {
	cv::Mat samples(src.rows * src.cols, 1, CV_32F);
	// Extract pixels from image and place it in a single row per sample, one col per channel
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			samples.at<float>(y + x * src.rows, 0) = src.at<uchar>(y, x);
		}
	}
	cv::Mat labels;
	cv::Mat centers;
	cv::kmeans(samples, clusterCount, labels,
			cv::TermCriteria(
			CV_TERMCRIT_ITER | CV_TERMCRIT_EPS /* termination criteria*/,
					10000 /*iterations*/, 0.0001/*precision*/), attempts,
			cv::KMEANS_PP_CENTERS, centers);
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++) {
			int cluster_idx = labels.at<int>(y + x * src.rows, 0);
			dst.at<uchar>(y, x) = centers.at<float>(cluster_idx, 0);
		}
}

void kmeansSegmentation3Chan(cv::Mat & src, cv::Mat & dst, int clusterCount,
		int attempts) {
	cv::Mat samples(src.rows * src.cols, 3, CV_32F);
	// Extract pixels from image and place it in a single row per sample, one col per channel
	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			for (int z = 0; z < 3; z++) {
				samples.at<float>(y + x * src.rows, z) =
						src.at<cv::Vec3b>(y, x)[z];
			}
		}
	}
	cv::Mat labels;
	cv::Mat centers;
	cv::kmeans(samples, clusterCount, labels,
			cv::TermCriteria(
			CV_TERMCRIT_ITER | CV_TERMCRIT_EPS /* termination criteria*/,
					10000 /*iterations*/, 0.0001/*precision*/), attempts,
			cv::KMEANS_PP_CENTERS, centers);
	for (int y = 0; y < src.rows; y++)
		for (int x = 0; x < src.cols; x++) {
			int cluster_idx = labels.at<int>(y + x * src.rows, 0);
			dst.at<cv::Vec3b>(y, x)[0] = centers.at<float>(cluster_idx, 0);
			dst.at<cv::Vec3b>(y, x)[1] = centers.at<float>(cluster_idx, 1);
			dst.at<cv::Vec3b>(y, x)[2] = centers.at<float>(cluster_idx, 2);
		}
}

void getGaborBank(std::vector<cv::Mat> & bank) {
	double _sigma;	/// Sigma of the Gaussian envelope
	double _theta; /// Orientation of the normal to the parallel stripes of the Gabor function
	double _lambda;	/// Wavelength of sinusoidal factor
	double _gamma; /// Spatial aspect ratio (ellipticity of the support of the Gabor function)
	double _psi;	/// Phase offset

	_gamma = 1.0;
	_sigma = 2.0;
	_lambda = 1.0;
	for (_lambda = 4.0; _lambda < 16.0; _lambda += 2.5) {
		cv::Size kernelSize(_lambda,_lambda);
		for (_theta = 0.0; _theta < (2.0 * CV_PI); _theta += (CV_PI / 4.0)) {

			bank.push_back(
					cv::getGaborKernel(kernelSize, (double) _sigma,
							(double) _theta, (double) _lambda,
							(double) _gamma));
		}
	}

	return;
}
