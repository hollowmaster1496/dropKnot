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
void monitorEyes() {

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