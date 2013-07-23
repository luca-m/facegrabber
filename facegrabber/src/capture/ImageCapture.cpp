/*
 * ImageCapture.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "ImageCapture.h"

namespace facedetect {

ImageCapture::ImageCapture(char * filepath) {
	image = cvLoadImage(filepath, CV_LOAD_IMAGE_COLOR);
}

ImageCapture::~ImageCapture() {
	cvReleaseImage(&image);
}

bool ImageCapture::isReady() {
	return (image != 0 ? true : false);
}

IplImage * ImageCapture::nextFrame() {
	IplImage * im = cvCreateImage(cvSize(image->width, image->height),
			IPL_DEPTH_8U, 3);
	cvCopy(image, im, 0);
	return im;
}

} /* namespace facedetect */
