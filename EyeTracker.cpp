/* Author: Haseeb Syed */

#include "EyeTracker.h"

EyeTracker::EyeTracker(int cache_size) {
	_cache_size = cache_size;
	_average_open_state = 1;		
}

EyeTracker::~EyeTracker() {
	//just in case anything needs to be deallocated
}


int EyeTracker::detect_fatigue_level(cv::Mat frame) {
	return 0;
}


void EyeTracker::find_shut_duration(int item) {
	if (eyes_state_cache.size() == 5000)
	{
		int tmp = eyes_state_cache.front();
		eyes_state_cache.pop();
		_average_open_state -= tmp;
	}
	eyes_state_cache.push(item);
	_average_open_state += item;

	sleep_deprivation_degree = (double)_average_open_state / (eyes_state_cache.size());
}


