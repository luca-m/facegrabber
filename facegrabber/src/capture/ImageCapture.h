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

namespace facedetect {

class ImageCapture: public facedetect::ICapture {

private:
	IplImage * image;

public:
	ImageCapture(char *);
	virtual ~ImageCapture();
};

} /* namespace facedetect */
#endif /* IMAGECAPTURE_H_ */
