/*
 * VideoCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef VIDEOCAPTURE_H_
#define VIDEOCAPTURE_H_

#include <opencv2/opencv.hpp>
#include "ICapture.h"

namespace facedetect {

class VideoCapture: public facedetect::ICapture {
private:
	CvCapture* capture;
public:
	/**
	 *
	 * @param
	 */
	VideoCapture(char *);
	virtual ~VideoCapture();
	/**
	 *
	 * @return
	 */
	CvCapture* getCapture();
};

} /* namespace facedetect */
#endif /* VIDEOCAPTURE_H_ */
