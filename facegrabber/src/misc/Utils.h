/*
 * Utils.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdexcept>
#include <opencv2/opencv.hpp>

/**
 *
 * @param window_title
 * @param src
 * @param channel_name
 */
void showHistogram(char* window_title, IplImage* src, char* channel_name);
/**
 *
 * @param img
 * @return
 */
IplImage* getImgCopy(IplImage* img);
/**
 *
 * @param img
 * @param roiRect
 * @return
 */
IplImage* getSubImg(IplImage* img, CvRect *roiRect);
/**
 *
 * @param segment
 * @param length
 * @return
 */
cv::Point pointAtManhattanDist(std::vector<cv::Point> segment, float length);
/**
 *
 * @param segment
 * @param length
 * @return
 */
cv::Point pointEuclideanDist(std::vector<cv::Point> segment, float length);
/**
 *
 * @param segment
 * @return
 */
float lenManhattan(std::vector<cv::Point> segment);
/**
 *
 * @param segment
 * @return
 */
float lenEuclideanSquared(std::vector<cv::Point> segment);
/**
 *
 * @param segment
 * @return
 */
int pointAtMinX(std::vector<cv::Point> & segment);
/**
 *
 * @param segment
 * @return
 */
int pointAtMaxX(std::vector<cv::Point> & segment);
/**
 *
 * @param segment
 * @param x
 * @param threshold
 * @return
 */
int pointAtX(std::vector<cv::Point> & segment, int x, float threshold);
/**
 *
 * @param segment
 * @param isLeft
 * @param inter
 * @param middle
 * @param exter
 * @param threshold
 * @return
 */
bool getSegmentRelevantPoints(std::vector<cv::Point> & segment, bool isLeft,
		cv::Point & inter, cv::Point & middle, cv::Point & exter,
		float threshold);
/**
 * Hit-or-miss transform function
 * @param src The source image, 8 bit single-channel matrix
 * @param dst
 * @param kernel The kernel matrix. 1=foreground, -1=background, 0=don't care
 */
void hitAndMiss(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel);

/**
 *
 * @param src
 * @param dst
 * @param kernel
 * @param scaleFactor
 */
void enhanceLocalConstrast(cv::Mat& src, cv::Mat& dst, cv::Mat& kernel,
		double scaleFactor);
/**
 *
 * @param marker_src Opened image
 * @param dst
 * @param mask	Original Image
 * @param kernel Structuring Element
 * @param maxIter
 */
void imReconstruct(cv::Mat& marker_src, cv::Mat& dst, cv::Mat& mask,
		cv::Mat& kernel, unsigned int maxIter);
/**
 * Function for thinning the given binary image.
 *
 * <a href="http://dl.acm.org/citation.cfm?id=358023">Zhang-Suen Algorithm</a>
 *
 * <a href="https://github.com/bsdnoobz/zhang-suen-thinning"> implementation</a>
 *
 * @param im  Binary image with range = 0-255
 */
void thinning(cv::Mat& im);
/**
 * kmeans image semgmentation (1 channel images)
 *
 * @param src original image
 * @param dst destination image (same size and channel of the original)
 * @param clusterCount number of cluster to find
 * @param attempts number of attemps
 */
void kmeansSegmentationGrayScale(cv::Mat & src, cv::Mat & dst, int clusterCount,
		int attempts);
/**
 *
 * kmeans image semgmentation (3 channel images)
 *
 * @param src original image
 * @param dst destination image (same size and channel of the original)
 * @param clusterCount number of cluster to find
 * @param attempts number of attemps
 */
void kmeansSegmentation3Chan(cv::Mat & src, cv::Mat & dst,int clusterCount, int attempts);

#endif /* UTILS_H_ */
