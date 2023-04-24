#include "TimeUtility.h"

string TimeUtility::time_format(int time) {
	string time_string = "";
	int hour = time / 60;
	time_string += (hour < 10 ? "0" : "") + to_string(hour);
	time_string += ":";
	int minutes = time % 60;
	time_string += (minutes < 10 ? "0" : "") + to_string(minutes);
	return time_string;
}