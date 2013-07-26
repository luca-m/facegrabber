/*
 * CamCapture.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "CamCapture.h"

namespace facegrabber {

CamCapture::CamCapture(int camNum) {
	camNumber = camNum;
	camCapture = 0;
}

CamCapture::~CamCapture() {
	this->camNumber = -1;
	camCapture = 0;
}

void CamCapture::setCamCapture(CvCapture* camCapt) {
	this->camCapture = camCapt;
}

bool CamCapture::init(void) {
	this->setCamCapture(cvCaptureFromCAM(this->getCamNumber()));
	return this->isReady();
}

bool CamCapture::isReady(void) {
	return (this->getCapture() != 0 ? true : false);
}

IplImage * CamCapture::nextFrame() {
	CvCapture * cam = this->getCapture();
	if (cam == 0)
		return 0;
	IplImage * image = cvQueryFrame(cam);
	return image;
}

int CamCapture::getCamNumber() {
	return this->camNumber;
}

CvCapture * CamCapture::getCapture() {
	return this->camCapture;
}

}
/* namespace facedetect */
