#include "shelf.h"

static ShelfLevel g_warehouse[MAX_SHELVES][INIT_LEVELS] = { { {2, 1.8, 3} } };

void showWarehouse(double warningThreshold)
{
	printf_s("*************** 实时看板 ***************\n");
	printf_s("* 当前爆仓阈值：%.2lf %%\n", warningThreshold);
	for (int shelfId = 0; shelfId < MAX_SHELVES; shelfId++)
	{
		printf_s("* 货架编号：%d\n", shelfId);
		printf_s("+--------------------------------------+\n");
		for (int levelId = INIT_LEVELS - 1; levelId >= 0; levelId--)
		{
			printf_s("| 第 %d 层\n", levelId);
			printf_s("| 体积容量：%.2lf\n", g_warehouse[shelfId][levelId].volumeCapacity);
			printf_s("| 占用体积：%.2lf\n", g_warehouse[shelfId][levelId].occupiedVolume);
			if (g_warehouse[shelfId][levelId].occupiedVolume > 0)
			{
				double occupancyRate = 100.0 * g_warehouse[shelfId][levelId].occupiedVolume / g_warehouse[shelfId][levelId].volumeCapacity;
				printf_s("| 占用率：%.2lf%%", occupancyRate);
				if (occupancyRate > warningThreshold)
				{
					printf_s(" 超过阈值！");
				}
				printf_s("\n");
			}
			printf_s("| 包裹数量：%d\n", g_warehouse[shelfId][levelId].packageNum);
			printf_s("+--------------------------------------+\n");
		}
	}
	system("pause");
	system("cls");
}