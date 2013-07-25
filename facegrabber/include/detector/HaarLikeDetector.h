/*
 * FaceFeatureDetector.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef FACEFEATUREDETECTOR_H_
#define FACEFEATUREDETECTOR_H_

#include <opencv2/opencv.hpp>
#include "IDetector.h"
#include "../model/FaceRegion.h"

using namespace cv;

namespace facegrabber {

class HaarLikeDetector: public facegrabber::IDetector {

protected:
	CascadeClassifier cascade_f;
	CascadeClassifier cascade_el;
	CascadeClassifier cascade_er;
	CascadeClassifier cascade_n;
	CascadeClassifier cascade_m;
	IplImage * currImg;
	bool printRoi;

	/**
	 * \brief Set face area of a face region with the coordinate of the first face found.
	 * @param img
	 * @param facearea
	 * @return
	 */
	virtual bool detectFace(IplImage*img, IFaceRegion * faceregion);

	/**
	 * \brief Set features areas of a face region. It uses face area coordinate to increase accuracy.
	 * @param img
	 * @param facearea
	 * @return
	 */
	virtual bool detectFeatures(IplImage *img, IFaceRegion * faceregion);

public:
	/**
	 *
	 * @param face_config_file
	 * @param eyeLeft_config_file
	 * @param eyeRight_config_file
	 * @param nose_config_file
	 * @param mouth_config_file
	 * @param printRoi
	 */
	HaarLikeDetector(char * face_config_file, char * eyeLeft_config_file,
			char * eyeRight_config_file, char * nose_config_file,
			char * mouth_config_file, bool printRoi);
	virtual ~HaarLikeDetector();
	/**
	 *
	 * @param image
	 * @return
	 */
	IFaceRegion * detect(IplImage * image);
};

} /* namespace facedetect */
#endif /* FACEFEATUREDETECTOR_H_ */
