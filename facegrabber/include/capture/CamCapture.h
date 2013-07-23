/*
 * CamCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef CAMCAPTURE_H_
#define CAMCAPTURE_H_

#include "ICapture.h"

namespace facegrabber {

class CamCapture: public facegrabber::ICapture {

private:
	int camNumber;
	CvCapture* camCapture;

protected:
	/**
	 *
	 * @param camCapt
	 */
	void setCamCapture(CvCapture* camCapt);

public:
	/**
	 *
	 * @param camNum
	 */
	CamCapture(int camNum);
	/**
	 *
	 */
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
#endif /* CAMCAPTURE_H_ */
