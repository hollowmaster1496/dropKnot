/* Author: Haseeb Syed */

#include "EyeTracker.h"

EyeTracker::EyeTracker(int cache_size) {
	_cache_size = cache_size;

	for (int i = 0; i < cache_size; i++)
	{
		eyes_state_cache[i] = 1;	//assume eyes open for first 50 frames
	}

	_average_open_state = 1;		
}

EyeTracker::~EyeTracker() {
	//just in case anything needs to be deallocated
}

/* This method monitors user's eyes over 50 frames
*
*
*/
int EyeTracker::detect_fatigue_level(cv::Mat frame) {
	return 0;
}

/* This method calculates a running average of 
*	subject's squint/blinks.
*
*/
double EyeTracker::find_shut_duration(int item) {
	if (eyes_state_cache.size == 50)
	{
		int tmp = eyes_state_cache.front();
		eyes_state_cache.pop();
		_average_open_state -= tmp;
	}
	eyes_state_cache.push(item);
	_average_open_state += item;

	return (double)_average_open_state / (eyes_state_cache.size);
	return 
	
}