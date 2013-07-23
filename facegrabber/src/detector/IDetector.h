/*
 * IDetector.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef IDETECTOR_H_
#define IDETECTOR_H_

namespace facedetect {

class IDetector {
public:
	IDetector();
	virtual ~IDetector();
	/**
	 *
	 * @param image
	 * @return
	 */
	virtual IFaceRegion & detect(IplImage * image);

};

} /* namespace facedetect */
#endif /* IDETECTOR_H_ */
