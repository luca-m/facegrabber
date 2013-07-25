/*
 * VideoCapture.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "../../include/capture/VidCapture.h"

namespace facegrabber {

VidCapture::VidCapture(char * filePath) {
	capture = cvCaptureFromAVI(filePath);
}

VidCapture::~VidCapture() {
	capture = 0;
}

bool VidCapture::init() {
	return this->isReady();
}

bool VidCapture::isReady() {
	return (this->getCapture() != 0 ? true : false);
}

IplImage * VidCapture::nextFrame() {
	CvCapture * cam = this->getCapture();
	if (cam == 0)
		return 0;
	IplImage * image = cvQueryFrame(cam);
	return image;
}

CvCapture* VidCapture::getCapture() {
	return this->capture;
}

} /* namespace facedetect */
