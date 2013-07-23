/*
 * CamCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef CAMCAPTURE_H_
#define CAMCAPTURE_H_

#include "ICapture.h"
#include <opencv2/opencv.hpp>

namespace facedetect {

class CamCapture: public facedetect::ICapture {

private:
	int camNumber;
	CvCapture* camCapture;

protected:
	/**
	 *
	 * @param
	 */
	void setCamCapture(CvCapture*);

public:
	/**
	 *
	 * @param
	 */
	CamCapture(int);
	virtual ~CamCapture();
	/**
	 *
	 * @return
	 */
	int getCamNumber();
	/**
	 *
	 * @return
	 */
	CvCapture* getCapture();
};

} /* namespace facedetect */
#endif /* CAMCAPTURE_H_ */
