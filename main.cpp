/*Author: Haseeb Syed */

#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "EyeTracker.h"
//#include <iostream>

using namespace cv;

CvHaarClassifierCascade *cascade;
CvMemStorage *storage;


/* This method monitors user's eyes over a 50 frame interval
*
*
*/
void monitor_eyes(IplImage *newframe,
	CvHaarClassifierCascade *cascade,
	CvMemStorage *storage) {

	CvSeq *eyes = cvHaarDetectObjects(newframe, cascade, storage,
		1.15, 5,
		0, //CV_HAAR_DO_CANNY_PRUNING 
		cvSize(30, 30));
	// Looking for better detection?! Try these parameters: 
	// 1.15, 5, 0, cvSize(30 x 30)

	for (int i = 0; i < (eyes ? eyes->total : 0); i++)
	{
		CvRect *r = (CvRect *)cvGetSeqElem(eyes, i);

		cvRectangle(newframe,
			cvPoint(r->x, r->y),
			cvPoint(r->x + r->width, r->y + r->height),
			CV_RGB(0, 255, 0), 2, 8, 0);
	}
}

/* main function 
 *
 */
int main(int, char**)
{
	// load "closed eyes" classifier as cascade
	std::string RootCascade = "Cascade/";
	std::string Extension = ".xml";
	std::string filename = RootCascade + "closed_eye_classifier" + Extension;
	cascade = (CvHaarClassifierCascade*)cvLoad(filename.c_str());

	// Create Memory Storage Buffer
	storage = cvCreateMemStorage(0); 

	// Open default camera
	VideoCapture capture(0); 
	if (!capture.isOpened())  
		return -1;

	// Check for proper initialization
	if (!cascade || !storage)
	{
		printf("Initialization Failed: %s\n",
			(!cascade) ? " Cascade file not found !\n" :
			(!storage) ? " Memmory not allocated or not enough memory !\n" :
			" The input file can not be found!\n");
		system("pause");

		return 0;
	}

	IplImage edges1;
	IplImage* edges = &edges1;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		capture >> frame; // get a new frame from camera
		//cvtColor(frame, edges1, COLOR_RGB2GRAY);
		edges1 = frame;

		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges, edges, 0, 30, 3);
		monitor_eyes(edges, cascade, storage);
		cvShowImage("edges", edges);
		//cvReleaseImage( )
		//imshow("edges", edges1);
		if (waitKey(30) >= 0) break;
	}

	// Cleanup
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}




