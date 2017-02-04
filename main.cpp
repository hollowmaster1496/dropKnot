/*Author: Haseeb Syed */

#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "EyeTracker.cpp"
//#include <iostream>

using namespace cv;

CvHaarClassifierCascade *cascade;
CvMemStorage *storage;


/* main function 
 *
 */
int main(int, char**)
{
	// (2) Defining the path and Loading the Classifier in (C++ format)
	std::string RootCascade = "MyCascade/";
	std::string Extension = ".xml";
	std::string filename = RootCascade + "closed_eye_classifier" + Extension;
	cascade = (CvHaarClassifierCascade*)cvLoad(filename.c_str());

	// (3)  Creating Buffer
	storage = cvCreateMemStorage(0);

	VideoCapture capture(0); // open the default camera
	if (!capture.isOpened())  // check if we succeeded
		return -1;

	// (5) Check for proper initialization
	if (!cascade || !storage)
	{
		printf("Initialization Failed: %s\n",
			(!cascade) ? " Cascade file not found !\n" :
			(!storage) ? " Not memmory allocated or not enough memory !\n" :
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
		EyeTracker tracker(50);

		tracker.monitor_eyes(edges, cascade, storage);

		cvShowImage("edges", edges);
		//cvReleaseImage( )
		//imshow("edges", edges1);
		if (waitKey(30) >= 0) break;
	}

	//(8) Releasing the resources (Cascade and Buffer)
	cvReleaseHaarClassifierCascade(&cascade);
	cvReleaseMemStorage(&storage);

	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}




