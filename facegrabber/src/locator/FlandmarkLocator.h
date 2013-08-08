/*
 * FlandmarkLocator.h
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#ifndef FLANDMARKLOCATOR_H_
#define FLANDMARKLOCATOR_H_

#include <opencv2/opencv.hpp>

#include "ILocator.h"
#include "../../flandmark/flandmark_detector.h"

namespace facegrabber {
class FlandmarkLocator: public facegrabber::ILocator {

private:
	IplImage * currImg;
	IFaceRegion * currFaceRegion;
	float middlepointThreshold;
	int cannyLowThr ;
	int cannyHighThr;
	int cannySobelSize;

	void locateEyebrow(cv::Mat & grayimg, bool isLeft ,IFacePoints * points);

protected:

	FLANDMARK_Model * fmModel;

	/**
	 *
	 * @param img_grayscale
	 * @param region
	 * @param points
	 */
	void locateEyebrows(IplImage * img_grayscale, IFaceRegion * region,
			IFacePoints * points);

public:
	/**
	 *
	 * @param configFilePath
	 */
	FlandmarkLocator(char * configFilePath);
	virtual ~FlandmarkLocator();
	/**
	 *
	 * @param img
	 * @param region
	 * @return
	 */
	IFacePoints * locate(IplImage * img, IFaceRegion * region);
};
} /* namespace facegrabber */
#endif /* FLANDMARKLOCATOR_H_ */
