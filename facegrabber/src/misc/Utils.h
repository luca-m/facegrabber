/*
 * Utils.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <opencv2/opencv.hpp>

namespace facegrabber {

/**
 *
 * @param window_title
 * @param src
 * @param channel_name
 */
void show_histogram(char* window_title, IplImage* src, char* channel_name);
/**
 *
 * @param img
 * @param roiRect
 * @return
 */
IplImage* getSubImg(IplImage* img, CvRect *roiRect);

} /* namescpace facegrabber */

#endif /* UTILS_H_ */
