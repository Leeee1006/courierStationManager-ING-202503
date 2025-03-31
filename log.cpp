#include "log.h"

//日志链表指针
List* g_logs = NULL;

List* getLogs()
{
	return g_logs;
}

void initLogs()
{
	g_logs = list_init(sizeof(Log), LOG_FILE, sizeof(LOG_FILE));
}

void showLogs()
{
	printf_s("*************** 日志信息 ***************\n");
	if (g_logs->elementCount == 0)
	{
		printf_s("* 暂无日志\n");
		system("pause");
		system("cls");
		return;
	}
	for (ListNode* node = g_logs->head->next; node != NULL; node = node->next)
	{
		Log* log = (Log*)node->data;
		printf_s("| 日志描述：%s\n", log->description);
		printf_s("| 创建时间：%s\n", formatTime(log->createdTime));
		printf_s("+--------------------------------------+\n");
	}
	system("pause");
	system("cls");
	return;
}