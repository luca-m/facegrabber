/*
 * ICCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef ICAPTURE_H_
#define ICAPTURE_H_

#include <opencv2/opencv.hpp>

namespace facegrabber {

/**
 * \brief frame capture interface
 */
class ICapture {
public:
	virtual ~ICapture(){}
	/**
	 *
	 * @return
	 */
	virtual bool init()=0;
	/**
	 *
	 * @return
	 */
	virtual bool isReady()=0;
	/**
	 *
	 * @return
	 */
	virtual IplImage * nextFrame()=0;
};

} /* namespace facedetect */
#endif /* ICCAPTURE_H_ */
