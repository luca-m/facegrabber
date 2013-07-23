/*
 * ICCapture.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef ICCAPTURE_H_
#define ICCAPTURE_H_

namespace facedetect {

/**
 * \brief frame capture interface
 */
class facedetect::ICapture {
public:
	virtual ~ICapture() {
	}
	;
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
