/*
 * FlandmarkLocator.h
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#ifndef FLANDMARKLOCATOR_H_
#define FLANDMARKLOCATOR_H_

#include "ILocator.h"
#include "../../flandmark/flandmark_detector.h"

namespace facegrabber {
class FlandmarkLocator: public facegrabber::ILocator {

protected:

	FLANDMARK_Model * fmModel;

public:
	/**
	 *
	 * @param configFilePath
	 */
	FlandmarkLocator(char * configFilePath);
	virtual ~FlandmarkLocator();

	IFacePoints * locate(IplImage * img, IFaceRegion * region);
};
} /* namespace facegrabber */
#endif /* FLANDMARKLOCATOR_H_ */
