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

namespace facegrabber {

class VidCapture: public facegrabber::ICapture {
private:
	CvCapture* capture;
public:
	/**
	 *
	 * @param
	 */
	VidCapture(char * filePath);
	/**
	 *
	 */
	virtual ~VidCapture();
	/**
	 *
	 * @return
	 */
	CvCapture* getCapture();
	/**
	 *
	 * @return
	 */
	bool init();
	/**
	 *
	 * @return
	 */
	bool isReady();
	/**
	 *
	 * @return
	 */
	IplImage * nextFrame();
};

} /* namespace facedetect */
#endif /* VIDEOCAPTURE_H_ */
