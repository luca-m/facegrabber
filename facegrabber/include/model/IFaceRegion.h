/*
 * IFaceArea.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef IFACEREGION_H_
#define IFACEREGION_H_

#include <opencv2/opencv.hpp>

using namespace std;

namespace facegrabber {

class IFaceRegion {
public:
	virtual ~IFaceRegion(){}
	/**
	 *
	 * @return
	 */
	virtual CvRect * getFace()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeL()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeR()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeBrowL()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeBrowR()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getNose()=0;
	/**
	 *
	 * @return
	 */
	virtual CvRect * getMouth()=0;

	/**
	 *
	 * @param r
	 */
	virtual void setFace(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setEyeL(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setEyeR(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setEyeBrowL(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setEyeBrowR(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setNose(CvRect * r)=0;
	/**
	 *
	 * @param r
	 */
	virtual void setMouth(CvRect * r)=0;

	/**
	 *
	 * @return
	 */
	virtual bool isComplete()=0;

	/**
	 *
	 * @return
	 */
	virtual bool hasFace()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeL()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeR()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeBrowL()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeBrowR()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasNose()=0;
	/**
	 *
	 * @return
	 */
	virtual bool hasMouth()=0;

};

} /* namespace facegrabber */
#endif /* IFACEREGION_H_ */
