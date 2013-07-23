/*
 * IFaceArea.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef IFACEAREA_H_
#define IFACEAREA_H_

#include <string>

using namespace std;

namespace facedetect {

class IFaceRegion {
public:

	virtual ~IFaceRegion();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getFace();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeL();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeR();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeBrowL();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getEyeBrowR();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getNose();
	/**
	 *
	 * @return
	 */
	virtual CvRect * getMouth();

	/**
	 *
	 * @param r
	 */
	virtual void setFace(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setEyeL(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setEyeR(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setEyeBrowL(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setEyeBrowR(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setNose(CvRect * r);
	/**
	 *
	 * @param r
	 */
	virtual void setMouth(CvRect * r);

	/**
	 *
	 * @return
	 */
	virtual bool isComplete();

	/**
	 *
	 * @return
	 */
	virtual bool hasFace();
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeL();
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeR();
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeBrowL();
	/**
	 *
	 * @return
	 */
	virtual bool hasEyeBrowR();
	/**
	 *
	 * @return
	 */
	virtual bool hasNose();
	/**
	 *
	 * @return
	 */
	virtual bool hasMouth();

};

} /* namespace facedetect */
#endif /* IFACEAREA_H_ */
