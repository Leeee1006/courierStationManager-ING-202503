#include "ticket.h"

// 工单链表指针
List* g_tickets = NULL;

List* getTickets()
{
	return g_tickets;
}

void initTickets()
{
	g_tickets = list_init(sizeof(Ticket), TICKET_FILE, sizeof(TICKET_FILE));
}

void showTickets(int ticketType)
{
	for (ListNode* node = g_tickets->head->next; node != NULL; node = node->next)
	{
		Ticket* tkt = (Ticket*)node->data;
		if (ticketType == -1 || tkt->ticketType == ticketType)
		{
			printf_s("*************** 工单信息 ***************\n");
			printf_s("| 工单编号：%lld\n", tkt->ticketId);
			printf_s("| 工单类型：");
			switch (tkt->ticketType)
			{
			case Miscollection:
				printf_s("误取\n");
				break;
			case DamageLoss:
				printf_s("损坏丢失\n");
				break;
			case ComplaintSuggestion:
				printf_s("投诉建议\n");
				break;
			default:
				printf_s("信息错误\n");
				break;
			}
			printf_s("| 工单描述：\n\n%s\n\n", tkt->description);
			printf_s("| 创建时间：%s\n", formatTime(tkt->createdTime));
			printf_s("| 用户手机号：%s\n", tkt->userPhone);
			if (tkt->pkgTrackingNum[0] != '\0')
			{
				printf_s("| 包裹快递单号：%s\n", tkt->pkgTrackingNum);
			}
			printf_s("| 是否被处理：%s\n", tkt->isHandled ? "已处理" : "未处理");
			printf_s("+--------------------------------------+\n");
			printf_s("\n");
		}
	}
}

Ticket* findTicket(long long ticketId, int ticketType, int isHandled)
{
	for (ListNode* node = g_tickets->head->next; node != NULL; node = node->next)
	{
		Ticket* ticket = (Ticket*)node->data;
		if ((ticketId == -1 || ticket->ticketId == ticketId) &&
			(ticketType == -1 || ticket->ticketType == ticketType) &&
			(isHandled == -1 || ticket->isHandled == (bool)isHandled))
		{
			return ticket;
		}
	}
	return NULL;
}

long long generateTicketId()
{
	return time(NULL);
}
