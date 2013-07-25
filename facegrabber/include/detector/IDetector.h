/*
 * IDetector.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef IDETECTOR_H_
#define IDETECTOR_H_

#include "../model/IFaceRegion.h"

namespace facegrabber {

class IDetector {
public:
	virtual ~IDetector(){}
	/**
	 *
	 * @param image
	 * @return
	 */
	virtual IFaceRegion * detect(IplImage * image)=0;

};

} /* namespace facedetect */
#endif /* IDETECTOR_H_ */
