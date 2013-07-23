/*
 * ImageCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef IMAGECAPTURE_H_
#define IMAGECAPTURE_H_

#include <opencv2/opencv.hpp>
#include "ICapture.h"

namespace facegrabber {

class ImageCapture: public facegrabber::ICapture {

private:
	IplImage * image;

public:
	/**
	 *
	 * @param filepath
	 */
	ImageCapture(char * filepath);
	/**
	 *
	 */
	virtual ~ImageCapture();

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
#endif /* IMAGECAPTURE_H_ */
