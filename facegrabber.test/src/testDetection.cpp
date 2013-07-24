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

			CvRect * area = f.getFace();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);

				/*
				 int *bbox = (int*) malloc(4 * sizeof(int));
				 double *landmarks = (double*) malloc(
				 2 * model->data.options.M * sizeof(double));
				 IplImage * igray = cvCreateImage(
				 cvSize(image->width, image->height), IPL_DEPTH_8U, 1);
				 cvCvtColor(image, igray, CV_RGB2GRAY);
				 //cvEqualizeHist(igray,igray);
				 //cvSmooth(igray, igray, CV_GAUSSIAN, 7, 7, 2.6);
				 bbox[0] = area->x;
				 bbox[1] = area->y;
				 bbox[2] = area->x + area->width;
				 bbox[3] = area->y + area->height;
				 flandmark_detect(igray, bbox, model, landmarks);
				 // display landmarks
				 //cvRectangle(image, cvPoint(bbox[0], bbox[1]),
				 //		cvPoint(bbox[2], bbox[3]), CV_RGB(255,0,0));
				 //cvRectangle(image, cvPoint(model->bb[0], model->bb[1]),
				 //		cvPoint(model->bb[2], model->bb[3]), CV_RGB(0,0,255));
				 cvCircle(image, cvPoint((int) landmarks[0], (int) landmarks[1]),
				 3, CV_RGB(0, 0,255), CV_FILLED);

				 cvCircle(image, cvPoint(int(landmarks[2]), int(landmarks[3])),
				 3, CV_RGB(0,255,0), CV_FILLED);
				 cvCircle(image, cvPoint(int(landmarks[4]), int(landmarks[5])),
				 3, CV_RGB(255,0,0), CV_FILLED);

				 //for (int i = 2; i < 2 * model->data.options.M; i += 2) {
				 //	cvCircle(image,
				 //			cvPoint(int(landmarks[i]), int(landmarks[i + 1])),
				 //			3, CV_RGB(255,0,0), CV_FILLED);
				 //
				 //}
				 */
			}
			area = f.getEyeL();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(255, 127, 127), 1, 8, 0);
				IplImage * t = facegrabber::getSubImg(image, area);
				IplImage * tgray = cvCreateImage(cvSize(t->width, t->height),
				IPL_DEPTH_8U, 1);
				cvCvtColor(t, tgray, CV_RGB2GRAY);
				cvEqualizeHist(tgray, tgray);
				cvSmooth(tgray, tgray, CV_GAUSSIAN, 7, 7, 2.6);
				//cvDilate(tgray, tgray,
				//		cvCreateStructuringElementEx(3, 3, 0, 0,
				//				CV_SHAPE_ELLIPSE), 1);
				//cvThreshold(tgray, tgray, 5, 255, CV_THRESH_BINARY_INV);
				//cvErode(tgray, tgray,
				//		cvCreateStructuringElementEx(5, 5, 0, 0, CV_SHAPE_RECT),
				//		1);
				//cvDilate(tgray, tgray,
				//		cvCreateStructuringElementEx(5, 5, 0, 0, CV_SHAPE_RECT),
				//		1);
				//show_histogram("hist", tgray, "blue");
				//cvCanny( tgray, tgray, 5, 5*3, 3);
				//cvErode(tgray, tgray,
				//		cvCreateStructuringElementEx(3, 3, 0, 0,
				//				CV_SHAPE_ELLIPSE), 1);
				//cvDilate(tgray, tgray,
				//		cvCreateStructuringElementEx(3, 3, 0, 0,
				//				CV_SHAPE_ELLIPSE), 1);
				//cvCircle(image,
				//		cvPoint(cvRound(area->x + area->width/2),
				//				cvRound(area->y + area->height/2)), 3, CV_RGB(0,255,0),
				//		-1, 8, 0);
				CvMemStorage* storage = cvCreateMemStorage(0);
				CvSeq* circles = cvHoughCircles(tgray, storage,
						CV_HOUGH_GRADIENT, 1, tgray->height / 4, 10, 10 * 3,
						sqrt(tgray->width * tgray->height / 20 / 3.14),
						sqrt(tgray->width * tgray->height / 4 / 3.14));
				for (int i = 0; i < circles->total; i++) {
					float* p = (float*) cvGetSeqElem(circles, i);
					cvCircle(image,
							cvPoint(cvRound(area->x + p[0]),
									area->y + cvRound(p[1])), 3,
							CV_RGB(0,255,0), -1, 8, 0);
					cvCircle(image,
							cvPoint(cvRound(area->x + p[0]),
									cvRound(area->y + p[1])), cvRound(p[2]),
							CV_RGB(255,0,0), 1, 8, 0);
					cvCircle(tgray, cvPoint(cvRound(p[0]), cvRound(p[1])), 3,
					CV_RGB(0,0,255), -1, 8, 0);
				}
				/*
				 cvErode(tgray, tgray,
				 cvCreateStructuringElementEx(3, 3, 0, 0,
				 CV_SHAPE_RECT), 8);
				 cvThreshold(tgray, tgray, 127, 255,
				 CV_THRESH_BINARY | CV_THRESH_OTSU);
				 */
				//cvShowImage(win_detail_1, tgray);
			}
			area = f.getEyeBrowL();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}
			area = f.getEyeBrowR();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 255, 255), 1, 8, 0);
			}
			area = f.getEyeR();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}
			area = f.getMouth();
			if (area != 0) {
				cvRectangle(image, cvPoint(area->x, area->y),
						cvPoint(area->x + area->width, area->y + area->height),
						CV_RGB(127, 127, 127), 1, 8, 0);
			}
			area = f.getNose();
			if (area != 0) {
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

