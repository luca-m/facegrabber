/*
 * Face.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "FaceRegion.h"

namespace facegrabber {


FaceRegion::FaceRegion() {
	copy(0, &this->face);
	copy(0, &this->eyeL);
	copy(0, &this->eyeR);
	copy(0, &this->eyeBL);
	copy(0, &this->eyeBR);
	copy(0, &this->nose);
}

FaceRegion::~FaceRegion() {
}

void FaceRegion::copy(CvRect * from, CvRect * to) {
	if (to != 0) {
		if (from != 0) {
			to->x = from->x;
			to->y = from->y;
			to->width = from->width;
			to->height = from->height;

		} else {
			to->x = 0;
			to->y = 0;
			to->width = 0;
			to->height = 0;
		}
	}
}

/**
 *
 * @param r
 */
void FaceRegion::setFace(CvRect * r) {
	copy(r, &face);
}
/**
 *
 * @param r
 */
void FaceRegion::setEyeL(CvRect * r) {
	copy(r, &eyeL);
}
/**
 *
 * @param r
 */
void FaceRegion::setEyeR(CvRect * r) {
	copy(r, &eyeR);
}
/**
 *
 * @param r
 */
void FaceRegion::setEyeBrowL(CvRect * r) {
	copy(r, &eyeBL);
}
/**
 *
 * @param r
 */
void FaceRegion::setEyeBrowR(CvRect * r) {
	copy(r, &eyeBR);
}
/**
 *
 * @param r
 */
void FaceRegion::setNose(CvRect * r) {
	copy(r, &nose);
}
/**
 *
 * @param r
 */
void FaceRegion::setMouth(CvRect * r) {
	copy(r, &mouth);
}

/**
 *
 * @return
 */
CvRect * FaceRegion::getFace() {
	return &face;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getEyeL() {
	return &eyeL;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getEyeR() {
	return &eyeR;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getEyeBrowL() {
	return &eyeBL;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getEyeBrowR() {
	return &eyeBR;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getNose() {
	return &nose;
}
/**
 *
 * @return
 */
CvRect * FaceRegion::getMouth() {
	return &mouth;
}

/**
 *
 * @return
 */
bool FaceRegion::hasFace() {
	return (face.x == 0 && face.y == 0 && face.height == 0 && face.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasEyeL() {
	return (eyeL.x == 0 && eyeL.y == 0 && eyeL.height == 0 && eyeL.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasEyeR() {
	return (eyeR.x == 0 && eyeR.y == 0 && eyeR.height == 0 && eyeR.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasEyeBrowL() {
	return (eyeBL.x == 0 && eyeBL.y == 0 && eyeBL.height == 0
			&& eyeBL.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasEyeBrowR() {
	return (eyeBR.x == 0 && eyeBR.y == 0 && eyeBR.height == 0
			&& eyeBR.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasNose() {
	return (nose.x == 0 && nose.y == 0 && nose.height == 0 && nose.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::hasMouth() {
	return (mouth.x == 0 && mouth.y == 0 && mouth.height == 0
			&& mouth.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool FaceRegion::isComplete() {
	return hasMouth() && hasEyeL() && hasEyeR() && hasNose() && hasEyeBrowL()
			&& hasEyeBrowR() && hasFace();
}

} /* namespace facedetect */
