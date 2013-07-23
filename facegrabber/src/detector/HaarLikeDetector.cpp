/*
 * FaceFeatureDetector.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "HaarLikeDetector.h"

using namespace std;

namespace facedetect {

HaarLikeDetector::HaarLikeDetector(char * face_config_file,
		char * eyeLeft_config_file, char * eyeRight_config_file,
		char * nose_config_file, char * mouth_config_file, bool printRoi) {

	cascade_f.load(face_config_file);
	cascade_el.load(eyeLeft_config_file);
	cascade_er.load(eyeRight_config_file);
	cascade_n.load(nose_config_file);
	cascade_m.load(mouth_config_file);

	assert(
			!cascade_f.empty() && !cascade_el.empty() && !cascade_n.empty()
					&& !cascade_m.empty());
	this->currImg = 0;
	this->printRoi = printRoi;
}

HaarLikeDetector::~HaarLikeDetector() {
}

IFaceRegion & HaarLikeDetector::detect(IplImage * frame) {
	IFaceRegion & face = new Face(0, 0, 0, 0, 0, 0, 0);
	IplImage * im_gray;
	if (frame == 0)
		return face;

	this->currImg = frame;
	im_gray = cvCreateImage(cvSize(frame->width, frame->height), IPL_DEPTH_8U,
			1);

	cvEqualizeHist(im_gray, im_gray);

	if (detectFace(im_gray, face)) {
		detectFeatures(im_gray, face);
	}

	cvReleaseImage(&im_gray);

	return face;
}

bool HaarLikeDetector::detectFace(IplImage * img, IFaceRegion & faceregion) {
	vector<Rect> faces;
	CvRect * facearea = faceregion.getFace();
	bool hasFace = false;
	/* detect faces */
	cascade_f.detectMultiScale(img, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE,
			cvSize(40, 60));
	if (faces.size() > 0) {
		facearea->x = faces[0].x;
		facearea->y = faces[0].y;
		facearea->width = faces[0].width;
		facearea->height = faces[0].height;
		hasFace = true;
	} else {
		facearea->x = 0;
		facearea->y = 0;
		facearea->width = 0;
		facearea->height = 0;
	}
	return hasFace;
}

bool HaarLikeDetector::detectFeatures(IplImage * img,
		IFaceRegion & faceregion) {
	vector<Rect> eyeL, eyeR, noses, mouths;
	CvRect eyeROIL, eyeROIR, noseROI, mouthROI, eyeBrow, *tmp_area;
	bool hasEyes = false;
	bool hasNose = false;
	bool hasMouth = false;
	tmp_area = faceregion.getFace();

	/* Set the Region of Interest for lower pattern matching area */
	eyeROIL = cvRect(tmp_area->x + tmp_area->width / 2,
			tmp_area->y + (tmp_area->height / 5.5), tmp_area->width / 2,
			tmp_area->height / 3.0);
	eyeROIR = cvRect(tmp_area->x, tmp_area->y + (tmp_area->height / 5.5),
			tmp_area->width / 2, tmp_area->height / 3.0);
	noseROI = cvRect(tmp_area->x, tmp_area->y + tmp_area->height / 2.5,
			tmp_area->width, tmp_area->height / 3.0);
	mouthROI = cvRect(tmp_area->x, tmp_area->y + (tmp_area->height / 1.5),
			tmp_area->width, tmp_area->height / 2.5);

	if (printRoi && currImg != 0) {
		/* Print Region of interest (for debugging purposes) */
		cvRectangle(currImg, cvPoint(eyeROIL.x, eyeROIL.y),
				cvPoint(eyeROIL.x + eyeROIL.width, eyeROIL.y + eyeROIL.height),
				CV_RGB(255, 0, 0), 1, 8, 0);
		cvRectangle(currImg, cvPoint(eyeROIL.x, eyeROIL.y),
				cvPoint(eyeROIR.x + eyeROIR.width, eyeROIR.y + eyeROIR.height),
				CV_RGB(255, 0, 0), 1, 8, 0);
		cvRectangle(currImg, cvPoint(noseROI.x, noseROI.y),
				cvPoint(noseROI.x + noseROI.width, noseROI.y + noseROI.height),
				CV_RGB(0, 255, 0), 1, 8, 0);
		cvRectangle(currImg, cvPoint(mouthROI.x, mouthROI.y),
				cvPoint(mouthROI.x + mouthROI.width,
						mouthROI.y + mouthROI.height), CV_RGB(0, 0, 255), 1, 8,
				0);
	}

	/* detect eyes (first ones)*/
	cvSetImageROI(img, eyeROIL);
	cascade_el.detectMultiScale(img, eyeL, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE,
			Size(20, 20));
	cvResetImageROI(img);
	if (eyeL.size() > 0) {
		tmp_area = (CvRect*) &eyeL[0];
		tmp_area->x += eyeROIL.x;
		tmp_area->y += eyeROIL.y + tmp_area->height / 4;
		faceregion.setEyeL(tmp_area);
		hasEyes = true;
	} else {
		faceregion.setEyeL(0);
	}

	cvSetImageROI(img, eyeROIR);
	cascade_er.detectMultiScale(img, eyeR, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE,
			Size(20, 20));
	cvResetImageROI(img);
	if (eyeR.size() > 0) {
		tmp_area = (CvRect*) &eyeR[0];
		tmp_area->x += eyeROIR.x;
		tmp_area->y += eyeROIR.y;
		faceregion.setEyeR(tmp_area);
		hasEyes &= true;
	} else {
		faceregion.setEyeR(0);
	}

	/* detect nose (first one) */
	cvSetImageROI(img, noseROI);
	cascade_n.detectMultiScale(img, noses, 1.1, 3, 0 | CV_HAAR_SCALE_IMAGE,
			Size(10, 5));
	cvResetImageROI(img);
	if (noses.size() > 0) {
		tmp_area = (CvRect*) &noses[0];
		tmp_area->x += noseROI.x;
		tmp_area->y += noseROI.y;
		faceregion.setNose(tmp_area);
		hasNose = true;
	} else {
		faceregion.setNose(0);
	}

	/* detect mouth (first one) */
	cvSetImageROI(img, mouthROI);
	cascade_m.detectMultiScale(img, mouths, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE,
			Size(30, 30));
	cvResetImageROI(img);
	if (mouths.size() > 0) {
		tmp_area = (CvRect*) &mouths[0];
		tmp_area->x += mouthROI.x;
		tmp_area->y += mouthROI.y;
		faceregion.setMouth(tmp_area);
		hasMouth = true;
	} else {
		faceregion.setMouth(0);
	}

	/* estimate eyebrows using face proportions */
	if (faceregion.hasEyeL()) {
		eyeBrow = cvRect(0, 0, 0, 0);
		eyeBrow.x = faceregion.getEyeL()->x - 10;
		eyeBrow.y = faceregion.getEyeL()->y - faceregion.getEyeL()->height / 2;
		eyeBrow.width = faceregion.getEyeL()->width + 13;
		eyeBrow.height = faceregion.getEyeL()->height;
		faceregion.setEyeBrowL(&eyeBrow);
	}
	if (faceregion.hasEyeR()) {
		eyeBrow.x = faceregion.getEyeR()->x - 13;
		eyeBrow.y = faceregion.getEyeR()->y - faceregion.getEyeR()->height / 2;
		eyeBrow.width = faceregion.getEyeR()->width + 10;
		eyeBrow.height = faceregion.getEyeR()->height;
		faceregion.setEyeBrowR(&eyeBrow);
	}
	return faceregion.isComplete();
}

}/* namespace facedetect */
