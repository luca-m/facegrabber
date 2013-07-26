/*
 * FacePoints.h
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#ifndef FACEPOINTS_H_
#define FACEPOINTS_H_

#include "IFacePoints.h"

namespace facegrabber {

class FacePoints: public IFacePoints {

private:
	CvPoint basePoint;
	CvPoint eyeLCornerL;
	CvPoint eyeLCornerR;
	CvPoint eyeRCornerL;
	CvPoint eyeRCornerR;
	CvPoint eyeLPupil;
	CvPoint eyeRPupil;
	CvPoint eyeBrowLCornerL;
	CvPoint eyeBrowLCornerR;
	CvPoint eyeBrowRCornerL;
	CvPoint eyeBrowRCornerR;
	CvPoint noseCenter;
	CvPoint mouthCornerR;
	CvPoint mouthCornerL;
	CvPoint mouthLowerCorner;

	/**
	 *
	 * @param from
	 * @param to
	 */
	void copy(CvPoint *from, CvPoint * to);

public:
	FacePoints();
	virtual ~FacePoints();

	CvPoint * getBasePoint();
	CvPoint * getEyeLCornerL();
	CvPoint * getEyeLCornerR();
	CvPoint * getEyeRCornerL();
	CvPoint * getEyeRCornerR();
	CvPoint * getEyeLPupil();
	CvPoint * getEyeRPupil();

	CvPoint * getEyeBrowLCornerL();
	CvPoint * getEyeBrowLCornerR();
	CvPoint * getEyeBrowRCornerL();
	CvPoint * getEyeBrowRCornerR();

	CvPoint * getNoseCenter();

	CvPoint * getMouthCornerR();
	CvPoint * getMouthCornerL();
	CvPoint * getMouthLowerCorner();

	void setBasePoint(CvPoint * p);
	void setEyeLCornerL(CvPoint * p);
	void setEyeLCornerR(CvPoint * p);
	void setEyeRCornerL(CvPoint * p);
	void setEyeRCornerR(CvPoint * p);
	void setEyeLPupil(CvPoint * p);
	void setEyeRPupil(CvPoint * p);

	void setEyeBrowLCornerL(CvPoint * p);
	void setEyeBrowLCornerR(CvPoint * p);
	void setEyeBrowRCornerL(CvPoint * p);
	void setEyeBrowRCornerR(CvPoint * p);

	void setNoseCenter(CvPoint * p);

	void setMouthCornerR(CvPoint * p);
	void setMouthCornerL(CvPoint * p);
	void setMouthLowerCorner(CvPoint * p);

	bool hasBasePoint();
	bool hasEyeLCornerL();
	bool hasEyeLCornerR();
	bool hasEyeRCornerL();
	bool hasEyeRCornerR();
	bool hasEyeLPupil();
	bool hasEyeRPupil();

	bool hasEyeBrowLCornerL();
	bool hasEyeBrowLCornerR();
	bool hasEyeBrowRCornerL();
	bool hasEyeBrowRCornerR();

	bool hasNoseCenter();

	bool hasMouthCornerR();
	bool hasMouthCornerL();
	bool hasMouthLowerCorner();

	bool isComplete();

};
} /* namespace facegrabber */
#endif /* FACEPOINTS_H_ */
