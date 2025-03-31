#include"manager.h"

static double g_warningThreshold = 0.0; // 爆仓预警阈值 (体积利用率)

void managerMenu()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		printf_s("**************** 主菜单 ****************\n");//width=40
		printf_s("*              1.智能库存              *\n");
		printf_s("*              2.用户管理              *\n");
		printf_s("*              3.信息维护              *\n");
		printf_s("*              4.数据分析              *\n");
		printf_s("*              0.退出登录              *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//智能库存
		case 1:
			system("cls");
			warehouseMenu();
			break;
			//用户管理
		case 2:
			system("cls");
			userManagementMenu();
			break;
			// 信息维护
		case 3:
			system("cls");
			infoMaintenanceMenu();
			break;
			//数据分析
		case 4:
			system("cls");
			printf("* 功能未创建\n");
			system("pause");
			system("cls");
			break;
			// 退出登录
		case 0:
			system("cls");
			return;
			// 输入错误
		default:
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void warehouseMenu()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		printf_s("*************** 智能库存 ***************\n");//width=40
		printf_s("*              1.实时看板              *\n");
		printf_s("*              2.爆仓预警              *\n");
		printf_s("*              3.包裹追踪              *\n");
		printf_s("*              4.包裹全览              *\n");
		printf_s("*              0.返回                  *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			// 实时看板
		case 1:
			system("cls");
			printf_s("* 管理员身份\n");
			showWarehouse(g_warningThreshold);
			break;
			// 爆仓预警设置
		case 2:
			system("cls");
			resetWarningThreshold();
			break;
			// 包裹追踪
		case 3:
			system("cls");
			trackPackageMenu();
			break;
			// 包裹全览
		case 4:
			system("cls");
			printf_s("* 管理员身份\n");
			showAllPackages();
			break;
			// 返回
		case 0:
			system("cls");
			return;
			//输入错误
		default:
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void userManagementMenu()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		printf_s("*************** 用户管理 ***************\n");//width=40
		printf_s("*              1.用户检索              *\n");
		printf_s("*              2.删除用户              *\n");
		printf_s("*              3.用户全览              *\n");
		printf_s("*              0.返回                  *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//用户检索
		case 1:
			system("cls");
			managerFindUser();
			break;
			// 删除用户
		case 2:
			system("cls");
			managerDeleteUser();
			break;
			// 用户全览
		case 3:
			system("cls");
			printf_s("* 管理员身份\n");
			showUsers();
			break;
			//返回
		case 0:
			system("cls");
			return;
			//输入错误
		default:
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void trackPackageMenu()
{
	printf_s("* 管理员身份\n");
	printf_s("*************** 包裹追踪 ***************\n");
	Package package = {};
	printf_s("* 请输入快递单号：");
	scanf_s("%s", package.trackingNum, TRACKING_NUM);
	rewind(stdin);
	Package* foundPackage = findPackage(package.trackingNum, NULL, NULL, NULL, -1);
	if (foundPackage == NULL)
	{
		printf_s("* 包裹不存在！\n");
		system("pause");
		system("cls");
		return;
	}
	printf_s("* 包裹状态为：");
	switch (foundPackage->packageState)
	{
	case Ordered:
		printf_s("已下单\n");
		printf_s("* 下单时间：%s\n", formatTime(foundPackage->time.ordered));
		break;
	case Canceled:
		printf_s("已取消\n");
		printf_s("* 取消时间：%s\n", formatTime(foundPackage->time.canceled));
		break;
	case Shipped:
		printf_s("已寄出\n");
		printf_s("* 寄出时间：%s\n", formatTime(foundPackage->time.shipped));
		break;
	case Pending:
		printf_s("待取件\n");
		printf_s("* 取件码：%s\n", foundPackage->pickupCode);
		printf_s("* 入库时间：%s\n", formatTime(foundPackage->time.pending));
		break;
	case Refused:
		printf_s("已拒收\n");
		printf_s("* 拒收时间：%s\n", formatTime(foundPackage->time.refused));
		break;
	case Delivered:
		printf_s("已签收\n");
		printf_s("* 收件人手机号：%s\n", foundPackage->receiverPhone);
		printf_s("* 签收时间：%s\n", formatTime(foundPackage->time.delivered));
		break;
	case Misdelivered:
		printf_s("误取\n");
		break;
	case DamagedLost:
		printf_s("损坏丢失\n");
		break;
	default:
		printf_s("信息错误\n");
		break;
	}
	system("pause");
	system("cls");
}

void resetWarningThreshold()
{
	printf_s("* 管理员身份\n");
	printf_s("*************** 爆仓预警 ***************\n");
	printf_s("* 当前爆仓阈值：%.2lf %%\n", g_warningThreshold);
	printf_s("* 是否重置爆仓阈值 (1.是；2.否)：");
	int resetOption = -1;
	scanf_s("%d", &resetOption);
	rewind(stdin);
	if (resetOption == 1)
	{
		printf_s("* 请输入新的阈值：");
		double newThreshold = 0.0;
		scanf_s("%lf", &newThreshold);
		rewind(stdin);
		if (newThreshold <= 0.0 || newThreshold > 100.0)
		{
			printf_s("* 阈值非法，请重新输入！\n");
			system("pause");
			system("cls");
		}
		else
		{
			g_warningThreshold = newThreshold;
			printf_s("* 成功重置阈值！\n");
			system("pause");
			system("cls");
		}
	}
	else if (resetOption == 2)
	{
		printf_s("* 成功保持原来阈值！\n");
		system("pause");
		system("cls");
	}
	else
	{
		printf_s("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
}

void managerFindUser()
{
	printf_s("* 管理员身份\n");
	printf_s("*************** 用户检索 ***************\n");
	User user = {};
	printf_s("* 请输入您要查询用户的手机号：");
	scanf_s("%s", &user.phoneNumber, PHONE);
	rewind(stdin);
	//手机号格式错误
	if (!isValidPhoneNumber(user.phoneNumber))
	{
		printf_s("* 手机号格式错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
	User* foundUser = findUser(-1, NULL, user.phoneNumber, NULL);
	//用户不存在
	if (foundUser == NULL)
	{
		printf_s("* 用户不存在！\n");
		system("pause");
		system("cls");
	}
	//用户存在
	else
	{
		showUserInfo(foundUser);
		system("pause");
		system("cls");
	}
}

void managerDeleteUser()
{
	User tempUser = {};
	printf_s("* 管理员身份\n");
	printf_s("*************** 删除用户 ***************\n");
	printf_s("* 请输入您要删除的用户的手机号：");
	scanf_s("%s", tempUser.phoneNumber, PHONE);
	rewind(stdin);
	if (!isValidPhoneNumber(tempUser.phoneNumber))
	{
		printf_s("* 手机号格式错误！\n");
		system("pause");
		system("cls");
		return;
	}
	User* foundUser = findUser(-1, NULL, tempUser.phoneNumber, NULL);
	//用户不存在
	if (foundUser == NULL)
	{
		printf_s("* 用户不存在\n");
		system("pause");
		system("cls");
		return;
	}
	if (findPackage(NULL, NULL, foundUser->phoneNumber, NULL, Ordered) != NULL)
	{
		printf_s("* 该用户有未寄出的包裹！\n");
	}
	if (findPackage(NULL, NULL, NULL, foundUser->phoneNumber, Pending) != NULL)
	{
		printf_s("* 该用户有未领取的包裹！\n");
	}
	printf_s("* 是否继续删除该用户及其相关的包裹 (1,是；2.否)？");
	int deleteOption = -1;
	scanf_s("%d", &deleteOption);
	rewind(stdin);
	switch (deleteOption)
	{
		// 删除
	case 1:
		// 删除寄件
		deletePackage(NULL, NULL, foundUser->phoneNumber, DEFAULT_SENDER_ADDRESS, NULL, NULL, -1);
		// 删除取件
		deletePackage(NULL, NULL, NULL, NULL, foundUser->phoneNumber, DEFAULT_SENDER_ADDRESS, -1);
		// 删除用户
		deleteUser(-1, NULL, foundUser->phoneNumber, NULL);
		// 保存用户
		list_save(getUsers());
		printf_s("* 删除成功! \n");
		system("pause");
		system("cls");
		break;
		// 不删除
	case 2:
		system("cls");
		break;
	default:
		printf_s("* 输入错误，请重新输入! \n");
		system("pause");
		system("cls");
		break;
	}
}

void infoMaintenanceMenu()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		printf_s("*************** 信息维护 ***************\n");//width=40
		printf_s("*              1.工单处理              *\n");
		printf_s("*              2.日志信息              *\n");
		printf_s("*              0.返回                  *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			// 工单处理
		case 1:
			system("cls");
			AddressTicketMenu();
			break;
			// 日志信息
		case 2:
			system("cls");
			printf_s("* 管理员身份\n");
			showLogs();
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void AddressTicketMenu()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		printf_s("*************** 工单处理 ***************\n");//width=40
		printf_s("*              1.误取处理              *\n");
		printf_s("*              2.损坏丢失              *\n");
		printf_s("*              3.投诉建议              *\n");
		printf_s("*              0.返回                  *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//误取处理
		case 1:
			system("cls");
			AddressMisdelivery();
			break;
			//损坏丢失
		case 2:
			system("cls");
			AddressDamageLoss();
			break;
			//投诉建议
		case 3:
			system("cls");
			AddressComplaintSuggestion();
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void AddressMisdelivery()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		if (!findTicket(-1, Miscollection, -1))
		{
			printf_s("* 暂无误取申请工单\n");
			system("pause");
			system("cls");
			return;
		}
		printf_s("*************** 误取处理 ***************\n");
		showTickets(Miscollection);
		printf_s("* 是否处理工单并将包裹状态改为误取 (1.处理; 0.返回): ");
		int addressOption = -1;
		scanf_s("%d", &addressOption);
		rewind(stdin);
		if (addressOption == 1)
		{
			Ticket tempTicket = {};
			printf_s("* 请输入需要处理的工单编号：");
			scanf_s("%lld", &tempTicket.ticketId);
			rewind(stdin);
			Ticket* foundTicket = findTicket(tempTicket.ticketId, Miscollection, false);
			if (foundTicket == NULL)
			{
				printf_s("* 工单不存在或已处理！\n");
				system("pause");
				system("cls");
			}
			else
			{
				foundTicket->isHandled = true;
				Package* foundPackage = findPackage(foundTicket->pkgTrackingNum, NULL, NULL, NULL, -1);
				if (foundPackage != NULL)
				{
					foundPackage->packageState = Misdelivered;
				}
				// 保存工单
				list_save(getTickets());
				printf_s("* 处理成功！\n");
				system("pause");
				system("cls");
			}
		}
		// 返回
		else if (addressOption == 0)
		{
			system("cls");
			return;
		}
		// 输入错误
		else
		{
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}

void AddressDamageLoss()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		if (!findTicket(-1, DamageLoss, -1))
		{
			printf_s("* 暂无损坏丢失工单\n");
			system("pause");
			system("cls");
			return;
		}
		printf_s("************* 损坏丢失处理 *************\n");
		showTickets(DamageLoss);
		printf_s("* 是否处理工单并将包裹状态改为损坏丢失 (1.处理; 0.返回): ");
		int addressOption = -1;
		scanf_s("%d", &addressOption);
		rewind(stdin);
		// 处理
		if (addressOption == 1)
		{
			Ticket tempTicket = {};
			printf_s("* 请输入需要处理的工单编号：");
			scanf_s("%lld", &tempTicket.ticketId);
			rewind(stdin);
			Ticket* foundTicket = findTicket(tempTicket.ticketId, DamageLoss, false);
			if (foundTicket == NULL)
			{
				printf_s("* 工单不存在或已处理！\n");
				system("pause");
				system("cls");
			}
			else
			{
				foundTicket->isHandled = true;
				Package* foundPackage = findPackage(foundTicket->pkgTrackingNum, NULL, NULL, NULL, -1);
				if (foundPackage != NULL)
				{
					foundPackage->packageState = DamagedLost;
				}
				// 保存工单
				list_save(getTickets());
				printf_s("* 处理成功！\n");
				system("pause");
				system("cls");
			}
		}
		// 返回
		else if (addressOption == 0)
		{
			system("cls");
			return;
		}
		// 输入错误
		else
		{
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}

void AddressComplaintSuggestion()
{
	while (1)
	{
		printf_s("* 管理员身份\n");
		if (!findTicket(-1, ComplaintSuggestion, -1))
		{
			printf_s("* 暂无投诉建议工单\n");
			system("pause");
			system("cls");
			return;
		}
		printf_s("************* 投诉建议处理 *************\n");
		showTickets(ComplaintSuggestion);
		printf_s("* 是否处理工单 (1.处理; 0.返回): ");
		int addressOption = -1;
		scanf_s("%d", &addressOption);
		rewind(stdin);
		// 处理
		if (addressOption == 1)
		{
			Ticket tempTicket = {};
			printf_s("* 请输入需要处理的工单编号：");
			scanf_s("%lld", &tempTicket.ticketId);
			rewind(stdin);
			Ticket* foundTicket = findTicket(tempTicket.ticketId, ComplaintSuggestion, false);
			if (foundTicket == NULL)
			{
				printf_s("* 工单不存在或已处理！\n");
				system("pause");
				system("cls");
			}
			else
			{
				foundTicket->isHandled = true;
				// 保存工单
				list_save(getTickets());
				printf_s("* 处理成功！\n");
				system("pause");
				system("cls");
			}
		}
		// 返回
		else if (addressOption == 0)
		{
			system("cls");
			return;
		}
		// 输入错误
		else
		{
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
		}
	}
}
