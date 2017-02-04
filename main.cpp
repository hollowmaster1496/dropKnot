/*Author: Haseeb Syed */

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

/* main function 
 *
 */
int main(int, char**)
{
	VideoCapture capture(0); // open the default camera
	if (!capture.isOpened())  // check if we succeeded
		return -1;

	Mat edges;
	namedWindow("edges", 1);
	for (;;)
	{
		Mat frame;
		capture >> frame; // get a new frame from camera
		cvtColor(frame, edges, COLOR_RGB2GRAY);
		GaussianBlur(edges, edges, Size(7, 7), 1.5, 1.5);
		Canny(edges, edges, 0, 30, 3);
		imshow("edges", edges);
		if (waitKey(30) >= 0) break;
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;
}




