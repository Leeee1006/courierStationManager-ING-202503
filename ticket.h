#pragma once
#include "common.h"
#include "user.h"
#include "manager.h"
#include "timeFormat.h"

#define TICKET_FILE "resource/tickets.dat" // 工单文件

// 功能：获取工单链表
// 返回：工单链表指针
List* getTickets();

void initTickets();

// 功能：显示工单
// 参数：工单类型
void showTickets(int ticketType);

// 功能：查找工单
// 参数1：工单编号 (不限：-1)
// 参数2：工单类型 (不限：-1)
// 参数3：是否被处理 (不限：-1)
// 返回：目标工单指针
Ticket * findTicket(long long ticketId, int ticketType, int isHandled);

// 功能：生成工单编号 (等于创建时间)
long long generateTicketId();