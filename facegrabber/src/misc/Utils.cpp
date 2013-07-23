/*
 * Utils.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: stk
 */

#include "Utils.h"

namespace facegrabber {

void show_histogram(char* window_title, IplImage* src,
		char* channel_name) {
	IplImage* img, *canvas;
	int bins = 256;
	int hist[bins];
	double scale;
	int i, j, channel, max = 0;

	CvScalar colors[] = { CV_RGB(0,0,255), CV_RGB(0,255,0), CV_RGB(255,0,0),
	CV_RGB(0,0,0) };

	channel = strcmp(channel_name, "blue") == 0 ? 0 :
				strcmp(channel_name, "green") == 0 ? 1 :
				strcmp(channel_name, "red") == 0 ? 2 :
				strcmp(channel_name, "gray") == 0 ? 3 : 0;

	if (src->nChannels == 3 && channel == 3) {
		img = cvCreateImage(cvGetSize(src), 8, 1);
		cvCvtColor(src, img, CV_BGR2GRAY);
	} else if (channel > src->nChannels)
		return;
	else
		img = cvCloneImage(src);

	canvas = cvCreateImage(cvSize(256, 125), IPL_DEPTH_8U, 3);
	cvSet(canvas, CV_RGB(255,255,255), NULL);

	/* Reset histogram */
	for (j = 0; j < bins - 1; hist[j] = 0, j++)
		;
	for (i = 0; i < img->height; i++) {
		uchar* ptr = (uchar*) (img->imageData + i * img->widthStep);
		for (j = 0; j < img->width; j += img->nChannels)
			hist[ptr[j + (channel == 3 ? 0 : channel)]]++;
	}
	/* Get histogram peak */
	for (i = 0; i < bins - 1; i++)
		max = hist[i] > max ? hist[i] : max;
	scale = max > canvas->height ? (double) canvas->height / max : 1.;
	/* Draw histogram */
	for (i = 0; i < bins - 1; i++) {
		CvPoint pt1 = cvPoint(i, canvas->height - (hist[i] * scale));
		CvPoint pt2 = cvPoint(i, canvas->height);
		cvLine(canvas, pt1, pt2, colors[channel], 1, 8, 0);
	}
	cvShowImage(window_title, canvas);
	cvReleaseImage(&img);
}
;

IplImage* getSubImg(IplImage* img, CvRect *roiRect) {
	cvSetImageROI(img, *roiRect);
	IplImage* subImg = cvCreateImage(cvSize(roiRect->width, roiRect->height),
			img->depth, img->nChannels);
	cvCopy(img, subImg, 0);
	cvResetImageROI(img);
	return subImg;
}
;

} /* namespace misc */

