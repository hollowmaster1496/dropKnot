/*Author: Haseeb Syed */

#include "opencv2/opencv.hpp"
#include <queue>
#include <stdio.h>
#include "EyeTracker.h"
#include <iostream>

using namespace cv;

CvHaarClassifierCascade *cascade;
CvMemStorage *storage;
EyeTracker tracker(5000);

/* This method monitors user's eyes over a 50 frame interval
*
*
*/
void monitor_eyes(IplImage *newframe,
				CvHaarClassifierCascade *cascade,
				CvMemStorage *storage) {

	CvSeq *eyes = cvHaarDetectObjects(newframe, cascade, storage,
									  1.10, 5, 0, //CV_HAAR_DO_CANNY_PRUNING 
									  cvSize(25, 25));

	/* Counts total squints per frame */
	int squint_count = eyes->total;
	//std::cout << "total: " << squint_count << std::endl;

	/* Draw rectangle over each squint */
	for (int i = 0; i < squint_count; i++)
	{
		CvRect *r = (CvRect *)cvGetSeqElem(eyes, i);

		cvCircle(newframe, CvPoint((r->x) + r->width/1.8, (r->y) + r->height/1.8),
									r->x/10, CV_RGB(250, 250, 250), 0.5, 8, 0);
	}

	
	/* find redness of eye */
	if (squint_count == 0)
	{
		tracker.find_shut_duration(tracker.EYES_OPEN);
		//place redness detecting code here
	}
	else
	{
		tracker.find_shut_duration(tracker.EYES_CLOSED);
	}
}

/* main function 
 *
 */
int main(int, char**)
{

	cvStartWindowThread();

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
		if (tracker.sleep_deprivation_degree >= 0.65)
		{
			std::cout << "sleep deprivation degree: " << tracker.sleep_deprivation_degree;
			break;
		}


		Mat frame;
		capture >> frame; // get a new frame from camera
		//cvtColor(frame, edges1, COLOR_RGB2GRAY);
		edges1 = frame;

		//GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		//Canny(edges1, edges1, 0, 30, 3);
		monitor_eyes(edges, cascade, storage);
		cvShowImage("edges", edges);
		//cvReleaseImage( )
		//imshow("edges", edges1);
		if (waitKey(30) >= 0) break;
	}

	// Cleanup
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);

	destroyWindow("edges");

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}