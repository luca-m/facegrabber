/*
 * FacePoints.cpp
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#include "FacePoints.h"

namespace facegrabber {

FacePoints::FacePoints() {
		copy(0, &eyeLCornerR);
		copy(0, &eyeLCornerL);
		copy(0, &eyeRCornerR);
		copy(0, &eyeLPupil);
		copy(0, &eyeRPupil);
		copy(0, &eyeBrowLCornerL);
		copy(0, &eyeBrowLCornerR);
		copy(0, &eyeBrowRCornerL);
		copy(0, &eyeBrowRCornerR);
		copy(0, &noseCenter);
		copy(0, &mouthCornerR);
		copy(0, &mouthCornerL);
		copy(0, &mouthLowerCorner);
}
FacePoints::~FacePoints() {
}

void FacePoints::copy(CvPoint* from, CvPoint * to) {
	if (to != 0) {
		if (from != 0) {
			to->x = from->x;
			to->y = from->y;
		} else {
			to->x = 0;
			to->y = 0;
		}
	}
}

CvPoint * FacePoints::getBasePoint() {
	return &this->basePoint;
}
CvPoint * FacePoints::getEyeLCornerL() {
	return &this->eyeLCornerL;
}
CvPoint * FacePoints::getEyeLCornerR() {
	return &this->eyeLCornerR;
}
CvPoint * FacePoints::getEyeRCornerL() {
	return &this->eyeRCornerL;
}
CvPoint * FacePoints::getEyeRCornerR() {
	return &this->eyeRCornerR;
}
CvPoint * FacePoints::getEyeLPupil() {
	return &this->eyeLPupil;
}
CvPoint * FacePoints::getEyeRPupil() {
	return &this->eyeLPupil;
}

CvPoint * FacePoints::getEyeBrowLCornerL() {
	return &this->eyeBrowLCornerL;
}
CvPoint * FacePoints::getEyeBrowLCornerR() {
	return &this->eyeBrowLCornerR;
}
CvPoint * FacePoints::getEyeBrowRCornerL() {
	return &this->eyeBrowRCornerL;
}
CvPoint * FacePoints::getEyeBrowRCornerR() {
	return &this->eyeBrowRCornerR;
}

CvPoint * FacePoints::getNoseCenter() {
	return &this->noseCenter;
}

CvPoint * FacePoints::getMouthCornerR() {
	return &this->mouthCornerR;
}
CvPoint * FacePoints::getMouthCornerL() {
	return &this->mouthCornerL;
}
CvPoint * FacePoints::getMouthLowerCorner() {
	return &this->mouthLowerCorner;
}

void FacePoints::setBasePoint(CvPoint * p) {
	copy(p, &basePoint);
}
void FacePoints::setEyeLCornerL(CvPoint * p) {
	copy(p, &eyeLCornerL);
}
void FacePoints::setEyeLCornerR(CvPoint * p) {
	copy(p, &eyeLCornerR);
}
void FacePoints::setEyeRCornerL(CvPoint * p) {
	copy(p, &eyeRCornerL);
}
void FacePoints::setEyeRCornerR(CvPoint * p) {
	copy(p, &eyeRCornerR);
}
void FacePoints::setEyeLPupil(CvPoint * p) {
	copy(p, &eyeLPupil);
}
void FacePoints::setEyeRPupil(CvPoint * p) {
	copy(p, &eyeRPupil);
}

void FacePoints::setEyeBrowLCornerL(CvPoint * p) {
	copy(p, &eyeBrowLCornerL);
}
void FacePoints::setEyeBrowLCornerR(CvPoint * p) {
	copy(p, &eyeBrowLCornerR);
}
void FacePoints::setEyeBrowRCornerL(CvPoint * p) {
	copy(p, &eyeBrowRCornerL);
}
void FacePoints::setEyeBrowRCornerR(CvPoint * p) {
	copy(p, &eyeBrowRCornerR);
}

void FacePoints::setNoseCenter(CvPoint * p) {
	copy(p, &noseCenter);
}

void FacePoints::setMouthCornerR(CvPoint * p) {
	copy(p, &mouthCornerR);
}
void FacePoints::setMouthCornerL(CvPoint * p) {
	copy(p, &mouthCornerL);
}
void FacePoints::setMouthLowerCorner(CvPoint * p) {
	copy(p, &mouthLowerCorner);
}

bool FacePoints::hasEyeLCornerL() {
	return (eyeLCornerL.x == 0 && eyeLCornerL.y == 0 ? false : true);
}
bool FacePoints::hasEyeLCornerR() {
	return (eyeLCornerR.x == 0 && eyeLCornerR.y == 0 ? false : true);
}
bool FacePoints::hasEyeRCornerL() {
	return (eyeRCornerL.x == 0 && eyeRCornerL.y == 0 ? false : true);
}
bool FacePoints::hasEyeRCornerR() {
	return (eyeRCornerR.x == 0 && eyeRCornerR.y == 0 ? false : true);
}
bool FacePoints::hasEyeLPupil() {
	return (eyeLPupil.x == 0 && eyeLPupil.y == 0 ? false : true);
}
bool FacePoints::hasEyeRPupil() {
	return (eyeRPupil.x == 0 && eyeRPupil.y == 0 ? false : true);
}

bool FacePoints::hasEyeBrowLCornerL() {
	return (eyeBrowLCornerL.x == 0 && eyeBrowLCornerL.y == 0 ? false : true);
}
bool FacePoints::hasEyeBrowLCornerR() {
	return (eyeBrowLCornerR.x == 0 && eyeBrowLCornerR.y == 0 ? false : true);
}
bool FacePoints::hasEyeBrowRCornerL() {
	return (eyeBrowRCornerL.x == 0 && eyeBrowRCornerL.y == 0 ? false : true);
}
bool FacePoints::hasEyeBrowRCornerR() {
	return (eyeBrowRCornerR.x == 0 && eyeBrowRCornerR.y == 0 ? false : true);
}

bool FacePoints::hasNoseCenter() {
	return (noseCenter.x == 0 && noseCenter.y == 0 ? false : true);
}

bool FacePoints::hasMouthCornerR() {
	return (mouthCornerR.x == 0 && mouthCornerR.y == 0 ? false : true);
}
bool FacePoints::hasMouthCornerL() {
	return (mouthCornerL.x == 0 && mouthCornerL.y == 0 ? false : true);
}
bool FacePoints::hasMouthLowerCorner() {
	return (mouthLowerCorner.x == 0 && mouthLowerCorner.y == 0 ? false : true);
}

bool FacePoints::isComplete() {
	return hasEyeBrowLCornerL() && hasEyeBrowLCornerR() && hasEyeBrowRCornerL()
			&& hasEyeBrowRCornerR() && hasEyeLCornerL() && hasEyeLCornerR()
			&& hasEyeLPupil() && hasEyeRCornerL() && hasEyeRCornerR()
			&& hasEyeRPupil() && hasMouthCornerL() && hasMouthCornerR()
			&& hasMouthLowerCorner()&&hasNoseCenter();
}

} /* namespace facedetect */
