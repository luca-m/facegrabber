/*
 * testDetection.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include <stdio.h>

//#include "capture/CamCapture.cpp"
#include "capture/VideoCapture.cpp"
#include "detector/HaarLikeDetector.cpp"
#include "model/Face.cpp"
#include "misc/Utils.cpp"

using namespace facegrabber;

char face_conf[] = "resources/haarcascade_frontalface_alt.xml";
char eyeL_conf[] = "resources/haarcascade_lefteye_2splits.xml";
char eyeR_conf[] = "resources/haarcascade_righteye_2splits.xml";
char nose_conf[] = "resources/haarcascade_mcs_nose.xml";
char mouth_conf[] = "resources/haarcascade_mcs_mouth.xml";
const char win_title[] = "Picture Test";
const char win_detail_1[] = "Detail 1";
char lena[] = "data/lena.tif";
char video[] = "data/video.avi";

int main(int argv, char * args[]) {
	try {
		IplImage * image;
		facegrabber::VideoCapture & capture = *new facegrabber::VideoCapture(
				video);
		facegrabber::HaarLikeDetector & detector =
				*new facegrabber::HaarLikeDetector(face_conf, eyeL_conf,
						eyeR_conf, nose_conf, mouth_conf, false);
		//FLANDMARK_Model * model = flandmark_init("data/flandmark_model.dat");

		if (!capture.init()) {
			printf("ERR: Could not open the input device!");
			exit(-1);
		}
		cvNamedWindow(win_title, 1);
		cvNamedWindow(win_detail_1, 1);

		while ((image = capture.nextFrame())) {

			IFaceRegion & f = detector.detect(image);

			CvRect * area;
			if (f.hasFace()) {
				area = f.getFace();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f.hasEyeL()) {
				area = f.getEyeL();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(255, 127, 127), 1, 8, 0);
				IplImage * t = facegrabber::getSubImg(image, area);
				IplImage * tgray = cvCreateImage(cvSize(t->width, t->height),
				IPL_DEPTH_8U, 1);
				cvCvtColor(t, tgray, CV_RGB2GRAY);
				cvEqualizeHist(tgray, tgray);
				cvSmooth(tgray, tgray, CV_GAUSSIAN, 7, 7, 2.6);

			}

			if (f.hasEyeBrowL()) {
				area = f.getEyeBrowL();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}

			if (f.hasEyeBrowR()) {
				area = f.getEyeBrowR();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}

			if (f.hasEyeR()) {
				area = f.getEyeR();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f.hasMouth()) {
				area = f.getMouth();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}

			if (f.hasNose()) {
				area = f.getNose();
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}
			cvShowImage(win_title, image);
			//cv::Mat frame(image);
			//cv::imshow(win_title,frame);
			int c = cvWaitKey(50);
			if ((char) c == 'q') {
				break;
			}
		}
	} catch (int e) {
		printf("Exception #%d\n", e);
	}

}

