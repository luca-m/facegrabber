/*
 * testDetection.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include <stdlib.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>

#include "../src/capture/VidCapture.h"
#include "../src/detector/HaarLikeDetector.h"
#include "../src/locator/FlandmarkLocator.h"
#include "../src/model/FaceRegion.h"
#include "../src/model/FacePoints.h"

#include "../src/misc/Utils.h"

using namespace std;
using namespace facegrabber;

const char win_detection[] = "Detection";
const char win_localization[] = "Localization";

char face_conf[] = "resources/haarcascade_frontalface_alt.xml";
char eyeL_conf[] = "resources/haarcascade_lefteye_2splits.xml";
char eyeR_conf[] = "resources/haarcascade_righteye_2splits.xml";
char nose_conf[] = "resources/haarcascade_mcs_nose.xml";
char mouth_conf[] = "resources/haarcascade_mcs_mouth.xml";
char fm_model[] = "resources/flandmark_model.dat";

char lena[] = "data/lena.tif";
char video[] = "data/seq_300frames.avi";// "data/video.avi";//

int main(int argv, char * args[]) {
	try {

		VidCapture capture(video);
		HaarLikeDetector detector(face_conf, eyeL_conf, eyeR_conf, nose_conf,
				mouth_conf, true,false);
		FlandmarkLocator locator(fm_model);
		IplImage * image = 0, *image2 = 0;

		if (!capture.isReady()) {
			cout << "ERR: Could not open the input device!";
			exit(-1);
		}
		cvNamedWindow(win_detection, 1);
		cvNamedWindow(win_localization, 1);

		while ((image = capture.nextFrame())) {
			if (image2 != 0) {
				cvReleaseImage(&image2);
			}
			image2 = getImgCopy(image);
			IFaceRegion * f = detector.detect(image);

			CvRect * area;
			if (f->hasFace()) {
				area = f->getFace();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f->hasEyeL()) {
				area = f->getEyeL();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(255, 127, 127), 1, 8, 0);
				//IplImage * t = getSubImg(image, area);
				//IplImage * tgray = cvCreateImage(cvSize(t->width, t->height),
				//IPL_DEPTH_8U, 1);
				//cvCvtColor(t, tgray, CV_RGB2GRAY);
				//cvEqualizeHist(tgray, tgray);
				//cvSmooth(tgray, tgray, CV_GAUSSIAN, 7, 7, 2.6);

			}

			if (f->hasEyeBrowL()) {
				area = f->getEyeBrowL();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}

			if (f->hasEyeBrowR()) {
				area = f->getEyeBrowR();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}

			if (f->hasEyeR()) {
				area = f->getEyeR();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f->hasMouth()) {
				area = f->getMouth();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f->hasNose()) {
				area = f->getNose();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			IFacePoints * points = locator.locate(image2, f);

			if (points->hasEyeLCornerL()) {
				cvCircle(image2, *points->getEyeLCornerL(), 3, CV_RGB(0, 0,255),
				CV_FILLED);
			}
			if (points->hasEyeLCornerR()) {
				cvCircle(image2, *points->getEyeLCornerR(), 3, CV_RGB(0, 0,127),
				CV_FILLED);
			}
			if (points->hasEyeRCornerL()) {
				cvCircle(image2, *points->getEyeRCornerL(), 3, CV_RGB(0, 0,255),
				CV_FILLED);
			}
			if (points->hasEyeRCornerR()) {
				cvCircle(image2, *points->getEyeRCornerR(), 3, CV_RGB(0, 127,127),
				CV_FILLED);
			}
			if (points->hasMouthCornerL()) {
				cvCircle(image2, *points->getMouthCornerL(), 3, CV_RGB(0, 0,255),
				CV_FILLED);
			}
			if (points->hasMouthCornerR()) {
				cvCircle(image2, *points->getMouthCornerR(), 3, CV_RGB(0, 0,127),
				CV_FILLED);
			}
			if (points->hasNoseCenter()) {
				cvCircle(image2, *points->getNoseCenter(), 3, CV_RGB(255, 0,0),
				CV_FILLED);
			}



			cvShowImage(win_detection, image);
			cvShowImage(win_localization, image2);
			//cvShowImage(win_detail_1, image);
			//cv::Mat frame(image);
			//cv::imshow(win_detail_1,frame);

			int c = cvWaitKey(1);
			if ((char) c == 'q') {
				break;
			}
		}
	} catch (int e) {
		cout << "Exception #" << e;
	}

}

