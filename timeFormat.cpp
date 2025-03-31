#include "timeFormat.h"

char* formatTime(time_t time)
{
	static const int FMT_TIME_SIZE = ((int)sizeof("yyyy-MM-dd hh:mm:ss"));
	static char timeString[FMT_TIME_SIZE] = "";
	time_t tempTime = time;
	struct tm timeInfo;
	localtime_s(&timeInfo,&tempTime);
	sprintf_s(timeString, FMT_TIME_SIZE, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d",
		timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
		timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
	return timeString;
}

char* digitalTime(time_t time)
{
	static const int DGT_TIME_SIZE = ((int)sizeof("yyyyMMddhhmmss"));
	static char timeString[DGT_TIME_SIZE] = "";
	time_t tempTime = time;
	struct tm timeInfo;
	localtime_s(&timeInfo, &tempTime);
	sprintf_s(timeString, DGT_TIME_SIZE, "%.4d%.2d%.2d%.2d%.2d%.2d",
		timeInfo.tm_year + 1900, timeInfo.tm_mon + 1, timeInfo.tm_mday,
		timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
	return timeString;
}