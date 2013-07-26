/*
 * FlandmarkLocator.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#include <stdlib.h>


#include "FlandmarkLocator.h"
#include "../model/FacePoints.h"

namespace facegrabber {

FlandmarkLocator::FlandmarkLocator(char * configFilePath) {
	fmModel = flandmark_init(configFilePath);
	assert(fmModel != 0);
}
FlandmarkLocator::~FlandmarkLocator() {
	flandmark_free(fmModel);
}

IFacePoints * FlandmarkLocator::locate(IplImage * img, IFaceRegion * region) {
	CvPoint tmp;
	IplImage * im_gray;
	FacePoints * points = new FacePoints();
	if (img == 0 || region == 0 || !region->hasFace()) {
		return points;
	}
	int *bbox = (int*) malloc(4 * sizeof(int));
	double *landmarks = (double*) malloc(
			2 * fmModel->data.options.M * sizeof(double));

	im_gray = cvCreateImage(cvSize(img->width, img->height), IPL_DEPTH_8U, 1);
	cvCvtColor(img, im_gray, CV_RGB2GRAY);
	cvEqualizeHist(im_gray, im_gray);

	bbox[0] = region->getFace()->x;
	bbox[1] = region->getFace()->y;
	bbox[2] = region->getFace()->x + region->getFace()->width;
	bbox[3] = region->getFace()->y + region->getFace()->height;

	flandmark_detect(im_gray, bbox, fmModel, landmarks);

	tmp.x = (int) landmarks[0];
	tmp.y = (int) landmarks[1];
	points->setBasePoint(&tmp);
	tmp.x = (int) landmarks[2];
	tmp.y = (int) landmarks[3];
	points->setEyeRCornerL(&tmp);
	tmp.x = (int) landmarks[4];
	tmp.y = (int) landmarks[5];
	points->setEyeLCornerR(&tmp);
	tmp.x = (int) landmarks[6];
	tmp.y = (int) landmarks[7];
	points->setMouthCornerR(&tmp);
	tmp.x = (int) landmarks[8];
	tmp.y = (int) landmarks[9];
	points->setMouthCornerL(&tmp);
	tmp.x = (int) landmarks[10];
	tmp.y = (int) landmarks[11];
	points->setEyeRCornerR(&tmp);
	tmp.x = (int) landmarks[12];
	tmp.y = (int) landmarks[13];
	points->setEyeLCornerL(&tmp);
	tmp.x = (int) landmarks[14];
	tmp.y = (int) landmarks[15];
	points->setNoseCenter(&tmp);

	cvReleaseImage(&im_gray);
	free(bbox);
	free(landmarks);
	return points;
}

} /* namespace facegrabber  */
