/*
 * Face.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "Face.h"

namespace facedetect {

Face::Face(CvRect * face, CvRect * eyeL, CvRect * eyeR, CvRect * eyeBL,
		CvRect * eyeBR, CvRect * nose, CvRect * mouth) {
	copy(face, &this->face);
	copy(eyeL, &this->eyeL);
	copy(eyeR, &this->eyeR);
	copy(eyeBL, &this->eyeBL);
	copy(eyeBR, &this->eyeBR);
	copy(nose, &this->nose);
	copy(mouth, &this->mouth);
}

void Face::copy(CvRect * from, CvRect * to) {
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

Face::~Face() {
}

/**
 *
 * @param r
 */
void Face::setFace(CvRect * r) {
	copy(r, &face);
}
/**
 *
 * @param r
 */
void Face::setEyeL(CvRect * r) {
	copy(r, &eyeL);
}
/**
 *
 * @param r
 */
void Face::setEyeR(CvRect * r) {
	copy(r, &eyeR);
}
/**
 *
 * @param r
 */
void Face::setEyeBrowL(CvRect * r) {
	copy(r, &eyeBL);
}
/**
 *
 * @param r
 */
void Face::setEyeBrowR(CvRect * r) {
	copy(r, &eyeBR);
}
/**
 *
 * @param r
 */
void Face::setNose(CvRect * r) {
	copy(r, &nose);
}
/**
 *
 * @param r
 */
void Face::setMouth(CvRect * r) {
	copy(r, &mouth);
}

/**
 *
 * @return
 */
CvRect * Face::getFace() {
	return face;
}
/**
 *
 * @return
 */
CvRect * Face::getEyeL() {
	return eyeL;
}
/**
 *
 * @return
 */
CvRect * Face::getEyeR() {
	return eyeR;
}
/**
 *
 * @return
 */
CvRect * Face::getEyeBrowL() {
	return eyeBL;
}
/**
 *
 * @return
 */
CvRect * Face::getEyeBrowR() {
	return eyeBR;
}
/**
 *
 * @return
 */
CvRect * Face::getNose() {
	return nose;
}
/**
 *
 * @return
 */
CvRect * Face::getMouth() {
	return mouth;
}

/**
 *
 * @return
 */
bool Face::hasFace() {
	return (face.x == 0 && face.y == 0 && face.height == 0 && face.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool Face::hasEyeL() {
	return (eyeL.x == 0 && eyeL.y == 0 && eyeL.height == 0 && eyeL.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool Face::hasEyeR() {
	return (eyeR.x == 0 && eyeR.y == 0 && eyeR.height == 0 && eyeR.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool Face::hasEyeBrowL() {
	return (eyeBL.x == 0 && eyeBL.y == 0 && eyeBL.height == 0
			&& eyeBL.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool Face::hasEyeBrowR() {
	return (eyeBR.x == 0 && eyeBR.y == 0 && eyeBR.height == 0
			&& eyeBR.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool Face::hasNose() {
	return (nose.x == 0 && nose.y == 0 && nose.height == 0 && nose.width == 0 ?
			false : true);
}
/**
 *
 * @return
 */
bool Face::hasMouth() {
	return (mouth.x == 0 && mouth.y == 0 && mouth.height == 0
			&& mouth.width == 0 ? false : true);
}
/**
 *
 * @return
 */
bool Face::isComplete() {
	return hasMouth() && hasEyeL() && hasEyeR() && hasNose() && hasEyeBrowL()
			&& hasEyeBrowR() && hasFace();
}

} /* namespace facedetect */
