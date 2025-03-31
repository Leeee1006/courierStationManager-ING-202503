#pragma once
#include "common.h"
#include "list.h"	
#include "user.h"
#include "log.h"
#include "package.h"
#include "shelf.h"

#define DAYS 7  // 过去7天的历史数据
#define MAX_TRACKING_NUM 20 // 最大快递单号

void countPendingPackages(List* packages, time_t startDate, int* counts);

bool validateDate(int year, int month, int day);

bool inputDateSafe(time_t* result);

void linearRegression(const double x[], const double y[], int n, double* a, double* b);

void drawAsciiChart(const double x[], const double y[], const double yPred[], int n);
