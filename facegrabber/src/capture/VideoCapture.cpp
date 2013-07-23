/*
 * VideoCapture.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "VideoCapture.h"

namespace facedetect {

VideoCapture::VideoCapture(char * filePath) {
	capture = cvCaptureFromAVI(filePath);
}

VideoCapture::~VideoCapture() {
	capture = 0;
}

bool VideoCapture::init() {
	return this->isReady();
}

bool VideoCapture::isReady() {
	return (this->getCapture() != 0 ? true : false);
}

IplImage * VideoCapture::nextFrame() {
	CvCapture * cam = this->getCapture();
	if (cam == 0)
		return 0;
	IplImage * image = cvQueryFrame(cam);
	return image;
}

CvCapture* VideoCapture::getCapture() {
	return this->capture;
}

} /* namespace facedetect */
