#pragma once
#include <string.h>
#include <time.h>
#include "common.h"

// 功能：格式化时间，"yyyy-MM-dd hh:mm:ss"
// 参数：时间/秒
// 返回：格式化时间字符串
char* formatTime(time_t time);

// 功能：数字化时间，"yyyyMMddhhmmss"
// 参数：时间/秒
// 返回：数字化时间字符串
char* digitalTime(time_t time);
