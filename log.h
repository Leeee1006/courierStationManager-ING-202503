#pragma once
#include "common.h"
#include "list.h"
#include "timeFormat.h"

#define LOG_FILE "resource/logs.dat" // 日志文件

List* getLogs();

void initLogs();

// 功能：显示所有日志信息
void showLogs();