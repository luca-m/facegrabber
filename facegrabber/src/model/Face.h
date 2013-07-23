/*
 * Face.h
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#ifndef FACE_H_
#define FACE_H_

#include <map>
#include <string>
#include "IFaceRegion.h"

using namespace std;

namespace facedetect {

class Face: public facedetect::IFaceRegion {

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
};

} /* namespace facedetect */
#endif /* FACE_H_ */
