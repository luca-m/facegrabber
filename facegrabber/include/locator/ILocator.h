/*
 * ILocator.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef ILOCATOR_H_
#define ILOCATOR_H_

#include "../model/IFacePoints.h"
#include "../model/IFaceRegion.h"

namespace facegrabber {
/**
 *
 */
class ILocator {
public:
	virtual ~ILocator() {
	}
	/**
	 *
	 * @param img
	 * @param region
	 * @return
	 */
	virtual IFacePoints * locate(IplImage * img, IFaceRegion * region)=0;
};

} /* namespace facedetect */
#endif /* ILOCATOR_H_ */
