#pragma once
#include "common.h"

#define MAX_SHELVES 10 // 最大货架数
#define INIT_LEVELS 5  // 最大货架层数

// 功能：实时看板
// 参数：爆仓预警阈值 (体积利用率)
void showWarehouse(double warningThreshold);