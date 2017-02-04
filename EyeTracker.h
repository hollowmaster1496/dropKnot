#include <vector>
#include <opencv2/opencv.hpp>

#ifndef EYE_TRACKER_H
#define EYE_TRACKER_H

class EyeTracker
{
public:
	enum
	{
		EYES_OPEN,
		EYES_CLOSED
	};

	/* Constructor */
	EyeTracker(int);

	/* Destructor */
	~EyeTracker();


	/* This method monitors user's eyes over 50 a frame interval
	 *  and continuosly updates the _average_open_state member */
	void monitor_eyes();

	/* This method calculates the redness of the eyes and returns
	 *	an integer from a "tiredness" scale of 1 to 10  */
	int detect_fatigue_level();

	/* This method calculates how long during a 50 frame period the
	 *  the subject's eyes remained shut */
	int find_shut_duration();

private:
	std::vector<int> eyes_state_cache;	// stores eyes open state for past frames
	int _average_open_state;			// average number of times eyes remain open in eyes_state_cache[]
	int _cache_size = 50;				// total number of frames stored in cache at a time
};

#endif

