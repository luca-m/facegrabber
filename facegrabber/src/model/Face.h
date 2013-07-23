/*
 * Face.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef FACE_H_
#define FACE_H_

#include "IFaceRegion.h"

using namespace std;

namespace facegrabber {

class Face: public IFaceRegion {

private:
	/**
	 *
	 * @param from
	 * @param to
	 */
	void copy(CvRect *from, CvRect * to);

protected:
	CvRect face;
	CvRect eyeL;
	CvRect eyeR;
	CvRect eyeBL;
	CvRect eyeBR;
	CvRect nose;
	CvRect mouth;

public:
	/**
	 *
	 * @param face
	 * @param eyeL
	 * @param eyeR
	 * @param eyeBrowL
	 * @param eyeBrowR
	 * @param nose
	 * @param mouth
	 */
	Face(CvRect * face, CvRect * eyeL, CvRect * eyeR, CvRect * eyeBL,
			CvRect * eyeBR, CvRect * nose, CvRect * mouth);

	virtual ~Face();

	/**
	 *
	 * @param r
	 */
	void setFace(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setEyeL(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setEyeR(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setEyeBrowL(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setEyeBrowR(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setNose(CvRect * r);
	/**
	 *
	 * @param r
	 */
	void setMouth(CvRect * r);

	/**
	 *
	 * @return
	 */
	bool isComplete();

	/**
	 *
	 * @return
	 */
	bool hasFace();
	/**
	 *
	 * @return
	 */
	bool hasEyeL();
	/**
	 *
	 * @return
	 */
	bool hasEyeR();
	/**
	 *
	 * @return
	 */
	bool hasEyeBrowL();
	/**
	 *
	 * @return
	 */
	bool hasEyeBrowR();
	/**
	 *
	 * @return
	 */
	bool hasNose();
	/**
	 *
	 * @return
	 */
	bool hasMouth();
	/**
	 *
	 * @return
	 */
	CvRect * getFace();
	/**
	 *
	 * @return
	 */
	CvRect * getEyeL();
	/**
	 *
	 * @return
	 */
	CvRect * getEyeR();
	/**
	 *
	 * @return
	 */
	CvRect * getEyeBrowL();
	/**
	 *
	 * @return
	 */
	CvRect * getEyeBrowR();
	/**
	 *
	 * @return
	 */
	CvRect * getNose();
	/**
	 *
	 * @return
	 */
	CvRect * getMouth();
};

} /* namespace facedetect */
#endif /* FACE_H_ */
