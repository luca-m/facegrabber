/*
 * IFacePoints.h
 *
 *  Created on: Jul 25, 2013
 *      Author: stk
 */

#ifndef IFACEPOINTS_H_
#define IFACEPOINTS_H_

#include <opencv2/opencv.hpp>

class IFacePoints {
public:
	virtual ~IFacePoints() {	}

	virtual CvPoint * getBasePoint()=0;

	virtual CvPoint * getEyeLCornerL()=0;
	virtual CvPoint * getEyeLCornerR()=0;
	virtual CvPoint * getEyeRCornerL()=0;
	virtual CvPoint * getEyeRCornerR()=0;
	virtual CvPoint * getEyeLPupil()=0;
	virtual CvPoint * getEyeRPupil()=0;

	virtual CvPoint * getEyeBrowLCornerL()=0;
	virtual CvPoint * getEyeBrowLCornerR()=0;
	virtual CvPoint * getEyeBrowRCornerL()=0;
	virtual CvPoint * getEyeBrowRCornerR()=0;

	virtual CvPoint * getNoseCenter()=0;

	virtual CvPoint * getMouthCornerR()=0;
	virtual CvPoint * getMouthCornerL()=0;
	virtual CvPoint * getMouthLowerCorner()=0;

	virtual void setBasePoint(CvPoint * p)=0;

	virtual void setEyeLCornerL(CvPoint * p)=0;
	virtual void setEyeLCornerR(CvPoint * p)=0;
	virtual void setEyeRCornerL(CvPoint * p)=0;
	virtual void setEyeRCornerR(CvPoint * p)=0;
	virtual void setEyeLPupil(CvPoint * p)=0;
	virtual void setEyeRPupil(CvPoint * p)=0;

	virtual void setEyeBrowLCornerL(CvPoint * p)=0;
	virtual void setEyeBrowLCornerR(CvPoint * p)=0;
	virtual void setEyeBrowRCornerL(CvPoint * p)=0;
	virtual void setEyeBrowRCornerR(CvPoint * p)=0;

	virtual void setNoseCenter(CvPoint * p)=0;

	virtual void setMouthCornerR(CvPoint * p)=0;
	virtual void setMouthCornerL(CvPoint * p)=0;
	virtual void setMouthLowerCorner(CvPoint * p)=0;

	virtual bool hasEyeLCornerL()=0;
	virtual bool hasEyeLCornerR()=0;
	virtual bool hasEyeRCornerL()=0;
	virtual bool hasEyeRCornerR()=0;
	virtual bool hasEyeLPupil()=0;
	virtual bool hasEyeRPupil()=0;

	virtual bool hasEyeBrowLCornerL()=0;
	virtual bool hasEyeBrowLCornerR()=0;
	virtual bool hasEyeBrowRCornerL()=0;
	virtual bool hasEyeBrowRCornerR()=0;

	virtual bool hasNoseCenter()=0;

	virtual bool hasMouthCornerR()=0;
	virtual bool hasMouthCornerL()=0;
	virtual bool hasMouthLowerCorner()=0;

	virtual bool isComplete()=0;

};

#endif /* IFACEPOINTS_H_ */
