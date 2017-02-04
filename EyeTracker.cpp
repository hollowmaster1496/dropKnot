#include "EyeTracker.h"

EyeTracker::EyeTracker(int cache_size) {
	_cache_size = cache_size;
	EyeTracker::eyes_state_cache = std::vector<int>(cache_size);

	for (int i = 0; i < cache_size; i++)
	{
		eyes_state_cache[i] = 1;	//assume eyes open for first 50 frames
	}

	_average_open_state = 1;		
}

EyeTracker::~EyeTracker() {
	//just in case anything needs to be deallocated
}

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

/* This method monitors user's eyes over 50 frames
*
*
*/
int findEyeFatigue(cv::Mat frame) {
	return 0;
}

/* This method monitors user's eyes over 50 frames
*
*
*/
int findEyeShutDuration() {
	//_average_open_state
	return 0;
}