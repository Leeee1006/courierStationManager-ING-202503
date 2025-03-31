#include "common.h"
#include "list.h"
#include "log.h"
#include "manager.h"
#include "package.h"
#include "shelf.h"
#include "start.h"
#include "ticket.h"
#include "timeFormat.h"
#include "tools.h"
#include "user.h"

int main()
{
	initLogs();
	initTickets();
	initPackages();
	initUsers();
	startMenu();
	return 0;
}