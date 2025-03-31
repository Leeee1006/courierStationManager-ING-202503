#include"user.h"

// 用户链表指针
List* g_users = NULL;
// 当前用户指针
User* g_currentUser = NULL;

List* getUsers()
{
	return g_users;
}

void initUsers()
{
	g_users = list_init(sizeof(User), USER_FILE, sizeof(USER_FILE));
}

User* findUser(long long userId, const char* userName, const char* phone, const char* password)
{
	for (ListNode* node = g_users->head->next; node != NULL; node = node->next)
	{
		User* user = (User*)node->data;
		if ((userId == -1 || user->userId == userId) &&
			(userName == NULL || strcmp(user->userName, userName) == 0) &&
			(phone == NULL || strcmp(user->phoneNumber, phone) == 0) &&
			(password == NULL || strcmp(user->password, password) == 0))
		{
			return user;
		}
	}
	return NULL;
}

void deleteUser(long long userId, const char* userName, const char* phone, const char* password)
{
	for (ListNode* cur = g_users->head; cur != g_users->tail; )
	{
		User* user = (User*)cur->next->data;
		if ((userId == -1 || user->userId == userId) &&
			(userName == NULL || strcmp(user->userName, userName) == 0) &&
			(phone == NULL || strcmp(user->phoneNumber, phone) == 0) &&
			(password == NULL || strcmp(user->password, password) == 0))
		{
			if (cur->next == g_users->tail)
			{
				g_users->tail = cur;
			}
			ListNode* temp = cur->next;
			cur->next = temp->next;
			if (temp->data != NULL)
			{
				free(temp->data);
			}
			free(temp);
			g_users->elementCount--;
		}
		else
		{
			cur = cur->next;
		}
	}
}

void showUsers()
{
	printf_s("*************** 用户全览 ***************\n");
	for (ListNode* node = g_users->head->next; node != NULL; node = node->next)
	{
		User* user = (User*)node->data;
		showUserInfo(user);
	}
	system("pause");
	system("cls");
}

long long generateUserId()
{
	return time(NULL);
}

char* generateIdentityCode(const char* phone)
{
	static char identityCode[ID_CODE] = "";
	identityCode[0] = '0';
	identityCode[1] = 'A';
	identityCode[2] = 'a';
	for (int i = 1; i < 10; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			identityCode[3 * i + j] = (phone[i] + 131 * (identityCode[3 * (i - 1) + j])) % 94 + 33;
		}
	}
	identityCode[30] = '\0';
	return identityCode;
}

void userMenu(User* currentUser)
{
	if (currentUser == NULL)
	{
		return;
	}
	g_currentUser = currentUser;
	while (1)
	{
		printf_s("* 欢迎你，%s！\n", g_currentUser->userName);
		printf_s("************** 用户主菜单 **************\n");//width=40
		printf_s("*              1.查询包裹              *\n");
		printf_s("*              2.我要取件              *\n");
		printf_s("*              3.我要寄件              *\n");
		printf_s("*              4.个人中心              *\n");
		printf_s("*              0.退出登录              *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//查询包裹
		case 1:
			system("cls");
			packageInfoMenu();
			break;
			//我要取件
		case 2:
			system("cls");
			pickupPackageMenu();
			break;
			//我要寄件
		case 3:
			system("cls");
			sendPackage();
			break;
			//个人中心
		case 4:
			system("cls");
			personalCenter();
			break;
			//返回
		case 0:
			system("cls");
			return;
			//输入错误
		default:
			printf("输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void packageInfoMenu()
{
	while (1)
	{
		printf("* 欢迎你，%s！\n", g_currentUser->userName);
		printf("*************** 查询包裹 ***************\n");//width=40
		printf("*                1.取件                *\n");
		printf("*                2.寄件                *\n");
		printf("*                0.返回                *\n");
		printf("****************************************\n");
		printf("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//查询取件
		case 1:
			system("cls");
			receivingInfoMenu();
			break;
			//查询寄件
		case 2:
			system("cls");
			sendingInfoMenu();
			break;
			//返回
		case 0:
			system("cls");
			return;
			//输入错误
		default:
			printf("输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void receivingInfoMenu()
{
	while (1)
	{
		printf_s("* 欢迎你，%s！\n", g_currentUser->userName);
		printf_s("*************** 查询取件 ***************\n");//width=40
		printf_s("*               1.已签收               *\n");
		printf_s("*               2.待取件               *\n");
		printf_s("*               3.已拒收               *\n");
		printf_s("*               0.返回                 *\n");
		printf_s("****************************************\n");
		printf_s("请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//查询已签收包裹
		case 1:
			system("cls");
			packageDeliveredMenu();
			break;
			//查询待取件包裹
		case 2:
			system("cls");
			packagePendingMenu();
			break;
			//查询已拒收包裹
		case 3:
			system("cls");
			packageRefusedMenu();
			break;
			//返回
		case 0:
			system("cls");
			return;
			//输入错误
		default:
			printf("输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void packageDeliveredMenu()
{
	printf("* 欢迎你，%s！\n", g_currentUser->userName);
	// 包裹不存在
	if (!findPackage(NULL, NULL, NULL, g_currentUser->phoneNumber, Delivered))
	{
		printf_s("* 暂无已签收的包裹\n");
		system("pause");
		system("cls");
		return;
	}
	//显示所有已签收包裹信息
	showPackageDelivered(g_currentUser->phoneNumber);
	system("pause");
	system("cls");
}

void packagePendingMenu()
{
	while (1)
	{
		printf("* 欢迎你，%s！\n", g_currentUser->userName);
		// 包裹不存在
		if (!findPackage(NULL, NULL, NULL, g_currentUser->phoneNumber, Pending))
		{
			printf_s("* 暂无待取件的包裹\n");
			system("pause");
			system("cls");
			return;
		}
		//显示所有待取件包裹信息
		showPackagePending(g_currentUser->phoneNumber);
		// 拒收选项
		printf("* 请输入您的选择(1.我要拒收；0.返回)：");
		int refuseOption = -1;
		scanf_s("%d", &refuseOption);
		rewind(stdin);
		switch (refuseOption)
		{
		case 1:
			//请求拒收包裹
			refusePackage();
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			//输入错误
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void refusePackage()
{
	Package package = {};
	printf_s("* 请输入需要拒收的包裹快递单号：");
	scanf_s("%s", package.trackingNum, TRACKING_NUM);
	rewind(stdin);
	//查找包裹
	Package* foundPackage = findPackage(package.trackingNum, NULL, NULL, g_currentUser->phoneNumber, Pending);
	//包裹未找到
	if (foundPackage == NULL)
	{
		printf_s("* 包裹不存在，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	printf_s("* 请输入您的选择 (1.确认拒收；0.返回)：");
	int refuseOption = 0;
	scanf_s("%d", &refuseOption);
	rewind(stdin);
	// 确认拒收
	if (refuseOption == 1)
	{
		package.packageState = Refused;
		//记录拒收时间
		package.time.refused = time(NULL);
		//保存包裹
		list_save(getPackages());
		//添加日志
		Log tempLog = {};
		sprintf_s(tempLog.description, DESCR, "用户%s拒收了包裹%s", g_currentUser->phoneNumber, package.trackingNum);
		tempLog.createdTime = time(NULL);
		list_add(getLogs(), &tempLog);
		//保存日志
		list_save(getLogs());
		printf("* 拒收成功！\n");
		system("pause");
		system("cls");
	}
	// 返回
	else if (refuseOption == 2)
	{
		system("cls");
	}
	//输入错误
	else
	{
		printf("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
}

void packageRefusedMenu()
{
	printf("* 欢迎你，%s！\n", g_currentUser->userName);
	// 包裹不存在
	if (!findPackage(NULL, NULL, NULL, g_currentUser->phoneNumber, Refused))
	{
		printf_s("* 暂无已拒收的包裹\n");
		system("pause");
		system("cls");
		return;
	}
	//显示所有已拒收包裹信息
	showPackageRefused(g_currentUser->phoneNumber);
	system("pause");
	system("cls");
}

void sendingInfoMenu()
{
	while (1)
	{
		printf("* 欢迎你，%s！\n", g_currentUser->userName);
		printf("*************** 查询寄件 ***************\n");//width=40
		printf("*               1.已寄出               *\n");
		printf("*               2.待寄出               *\n");
		printf("*               3.已取消               *\n");
		printf("*               0.返回                 *\n");
		printf("****************************************\n");
		printf("* 请输入您的选择：");

		int menuOption = -1;
		scanf_s("%d", &menuOption);
		//清空输入缓冲区
		rewind(stdin);

		switch (menuOption)
		{
			//返回
		case 0:
			system("cls");
			return;
			//查询已寄出包裹
		case 1:
			system("cls");
			packageShippedMenu();
			break;
			//查询待寄出包裹
		case 2:
			system("cls");
			packageOrderedMenu();
			break;
			//查询已取消包裹
		case 3:
			system("cls");
			PackageCanceledMenu();
			break;
			//输入错误
		default:
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void packageShippedMenu()
{
	printf("* 欢迎你，%s！\n", g_currentUser->userName);
	// 包裹不存在
	if (!findPackage(NULL, NULL, g_currentUser->phoneNumber, NULL, Shipped))
	{
		printf_s("* 暂无已寄出的包裹\n");
		system("pause");
		system("cls");
		return;
	}
	//显示所有已寄出包裹信息
	showPackageShipped(g_currentUser->phoneNumber);
	system("pause");
	system("cls");
}

void packageOrderedMenu()
{
	while (1)
	{
		printf_s("* 欢迎你，%s！\n", g_currentUser->userName);
		// 包裹不存在
		if (!findPackage(NULL, NULL, g_currentUser->phoneNumber, NULL, Ordered))
		{
			printf_s("* 暂无已下单的包裹\n");
			system("pause");
			system("cls");
			return;
		}
		//显示所有待寄出包裹信息
		showPackageOrdered(g_currentUser->phoneNumber);
		// 包裹不存在
		if (!isPackageExist(Ordered))
		{
			system("pause");
			system("cls");
			return;
		}
		printf_s("* 请输入您的选择 (1.我要取消；0.返回)：");
		int cancelOption = -1;
		scanf_s("%d", &cancelOption);
		rewind(stdin);
		switch (cancelOption)
		{
		case 1:
			//请求取消包裹
			cancelPackage();
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			//输入错误
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void cancelPackage()
{
	Package package = {};
	printf_s("* 请输入需要取消的包裹快递单号：");
	scanf_s("%s", package.trackingNum, TRACKING_NUM);
	rewind(stdin);
	// 查找已下单包裹
	Package* foundPackage = findPackage(package.trackingNum, NULL, g_currentUser->phoneNumber, NULL, Ordered);
	// 包裹未找到
	if (foundPackage == NULL)
	{
		printf_s("* 包裹不存在，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	printf("* 请输入您的选择 (1.确认取消；0.返回)：");
	int cancelOption = -1;
	scanf_s("%d", &cancelOption);
	rewind(stdin);
	// 确认取消
	if (cancelOption == 1)
	{
		foundPackage->packageState = Canceled;
		// 记录取消时间
		foundPackage->time.canceled = time(NULL);
		// 保存包裹
		list_save(getPackages());
		// 添加日志
		Log tempLog = {};
		sprintf_s(tempLog.description, DESCR, "用户%s取消了包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
		tempLog.createdTime = time(NULL);
		list_add(getLogs(), &tempLog);
		// 保存日志
		list_save(getLogs());
		printf_s("* 取消成功！\n");
		system("pause");
		system("cls");
	}
	// 返回
	else if (cancelOption == 0)
	{
		system("cls");
	}
	// 输入错误
	else
	{
		printf_s("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
}

void PackageCanceledMenu()
{
	printf("* 欢迎你，%s！\n", g_currentUser->userName);
	// 包裹不存在
	if (!findPackage(NULL, NULL, g_currentUser->phoneNumber, NULL, Canceled))
	{
		printf_s("* 暂无已取消的包裹\n");
		system("pause");
		system("cls");
		return;
	}
	// 显示所有已取消包裹信息
	showPackageCanceled(g_currentUser->phoneNumber);
	system("pause");
	system("cls");
}

void pickupPackageMenu()
{
	while (1)
	{
		printf_s("* 欢迎你，%s！\n", g_currentUser->userName);
		// 包裹不存在
		if (!findPackage(NULL, NULL, g_currentUser->phoneNumber, NULL, Pending))
		{
			printf_s("* 暂无待取件的包裹\n");
			system("pause");
			system("cls");
			return;
		}
		showPackagePending(g_currentUser->phoneNumber);
		printf_s("* 请输入您的选择(1.我要取件；0.返回)：");
		int PickupOption = -1;
		scanf_s("%d", &PickupOption);
		rewind(stdin);
		switch (PickupOption)
		{
			//返回
		case 0:
			system("cls");
			return;
		case 1:
			//请求取件
			pickupPackage();
			break;
		default:
			//输入错误
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void pickupPackage()
{
	Package package = {};
	printf_s("* 请输入需要取件的包裹快递单号：");
	scanf_s("%s", package.trackingNum, TRACKING_NUM);
	rewind(stdin);
	//查找待取件包裹
	Package* foundPackage = findPackage(package.trackingNum, NULL, NULL, g_currentUser->phoneNumber, Pending);
	//包裹未找到
	if (foundPackage == NULL)
	{
		printf("* 包裹不存在，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	//更改包裹状态为已签收
	foundPackage->packageState = Delivered;
	//记录签收时间
	foundPackage->time.delivered = time(NULL);
	//保存包裹
	list_save(getPackages());
	//添加日志
	Log tempLog = {};
	sprintf_s(tempLog.description, DESCR, "用户%s签收了包裹%s", g_currentUser->phoneNumber, foundPackage->trackingNum);
	tempLog.createdTime = time(NULL);
	list_add(getLogs(), &tempLog);
	//保存日志
	list_save(getLogs());
	printf("* 取件成功！\n");
	system("pause");
	system("cls");
}

void sendPackage()
{
	Package package = {};
	printf_s("* 欢迎你，%s！\n", g_currentUser->userName);
	printf_s("*************** 我要寄件 ***************\n");
	printf_s("* 请填写寄件信息：\n");
	//填写包裹名称
	printf_s("* 包裹名称：");
	scanf_s("%s", package.packageName, NAME);
	rewind(stdin);
	//自动填充寄件地址
	printf_s("* 寄件地址：");
	strcpy_s(package.senderAddress, ADDRESS, "吉大大学城");
	printf_s("%s\n", package.senderAddress);
	//填写取件地址
	printf_s("* 取件地址：");
	scanf_s("%s", package.receiverAddress, ADDRESS);
	rewind(stdin);
	//地址格式错误

	//取件地址与寄件地址相同
	if (strcmp(package.receiverAddress, package.senderAddress) == 0)
	{
		printf_s("* 取件地址不能与寄件地址相同，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	// 自动填充寄件人手机号
	printf_s("* 寄件人手机号：");
	strcpy_s(package.senderPhone, PHONE, g_currentUser->phoneNumber);
	printf_s("%s\n", package.senderPhone);
	// 填写取件人手机号
	printf_s("* 取件人手机号：");
	scanf_s("%s", package.receiverPhone, PHONE);
	rewind(stdin);
	// 手机号格式错误
	if (!isValidPhoneNumber(package.receiverPhone))
	{
		printf("* 手机号格式错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	// 取件人手机号与寄件人手机号相同
	if (strcmp(package.receiverPhone, g_currentUser->phoneNumber) == 0)
	{
		printf("* 取件人手机号不能与寄件人手机号相同，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	//填写重量
	printf_s("* 包裹重量/千克：");
	package.weight = -1.0;
	scanf_s("%lf", &package.weight);
	rewind(stdin);
	//重量非法
	if (package.weight <= 0.0 || package.weight > 100.0)
	{
		printf_s("* 重量非法，合法区间：(0, 100]\n");
		system("pause");
		system("cls");
		return;
	}
	//填写体积
	printf_s("* 包裹体积/立方厘米：");
	package.volume = -1.0;
	scanf_s("%lf", &package.volume);
	rewind(stdin);
	//体积非法
	if (package.volume <= 0.0 || package.volume > 10000.0)
	{
		printf("* 体积非法，合法区间：(0, 10000]\n");
		system("pause");
		system("cls");
		return;
	}
	//选择寄件方式
	printf("* 寄件方式(0.普通；1.紧急；2.轻缓)：");
	int shippingMethodOption = -1;
	scanf_s("%d", &shippingMethodOption);
	rewind(stdin);
	switch (shippingMethodOption)
	{
		//普通
	case 0:
		package.shippingMethod = ShippingStandard;
		break;
		//快递
	case 1:
		package.shippingMethod = Express;
		break;
		//经济
	case 2:
		package.shippingMethod = Economic;
		break;
		//输入错误
	default:
		printf("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	//选择包裹类型
	printf_s("* 包裹类型(0.普通：1.易碎；2.贵重)：");
	int packageTypeOption = -1;
	scanf_s("%d", &packageTypeOption);
	rewind(stdin);
	switch (packageTypeOption)
	{
		//普通
	case 0:
		package.packageType = PackageStandard;
		break;
		//易碎
	case 1:
		package.packageType = Fragile;
		break;
		//贵重
	case 2:
		package.packageType = Parcel;
		break;
		//输入错误
	default:
		printf("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	//是否取件到楼
	printf_s("* 是否取件到楼 (1.是；0.否): ");
	int homeSentOption = -1;
	scanf_s("%d", &homeSentOption);
	rewind(stdin);
	switch (homeSentOption)
	{
		//取件到楼
	case 1:
		package.isHomeSent = true;
		break;
		//快递点自寄
	case 0:
		package.isHomeSent = false;
		break;
		//输入错误
	default:
		printf_s("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	//是否送件到楼
	printf("* 是否送件到楼 (1.是；0.否): ");
	int homeDeliveredOption = -1;
	scanf_s("%d", &homeDeliveredOption);
	rewind(stdin);
	switch (homeDeliveredOption)
	{
		//送件到楼
	case 1:
		package.isHomeDelivered = true;
		break;
		//快递点取件
	case 0:
		package.isHomeDelivered = false;
		break;
		//输入错误
	default:
		printf("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	// 未使用优惠券前的运费
	package.usedCouponNum = 0;
	package.shippingFee = calculateShippingFee(&package, g_currentUser);
	//提示会员优惠
	if (g_currentUser->userType == VIP)
	{
		printf_s("* 已享%.1lf折会员专属优惠\n", 1.0 * g_currentUser->discount / 10);
	}
	printf_s("* 目前费用：%.2lf\n", package.shippingFee);
	//使用优惠券的数量
	printf_s("* 优惠券面额：%.2lf\n", COUPON_VALUE);
	printf_s("* 剩余优惠券：%d\n", g_currentUser->couponCount);
	if (g_currentUser->couponCount > 0) {
		package.usedCouponNum = -1;
		printf_s("* 使用优惠券的数量：");
		scanf_s("%d", &package.usedCouponNum);
		rewind(stdin);
		if (package.usedCouponNum < 0)
		{
			printf_s("* 优惠券数量须不小于 0 张！\n");
			system("pause");
			system("cls");
			return;
		}
		if (package.usedCouponNum > g_currentUser->couponCount)
		{
			printf("* 优惠券数量不足！\n");
			system("pause");
			system("cls");
			return;
		}
	}
	// 重新结算运费
	package.shippingFee = calculateShippingFee(&package, g_currentUser);
	//是否下单
	printf_s("* 下单需要支付%.2lf元\n", package.shippingFee);
	printf_s("* 是否下单 (1.下单；0.取消): ");
	int orderOption = -1;
	scanf_s("%d", &orderOption);
	rewind(stdin);
	//确认下单
	if (orderOption == 1)
	{
		//使用优惠券
		g_currentUser->couponCount -= package.usedCouponNum;
		//用户经验值增加
		g_currentUser->experience += ((int)log(package.shippingFee) + 1) * EXP_COEF;
		//生成快递单号
		strcpy_s(package.trackingNum, TRACKING_NUM, generateTrackingNumber());
		//添加待寄出包裹
		package.pickupCode[0] = '\0';
		package.packageState = Ordered;
		package.time = { time(NULL),-1,-1,-1,-1,-1 };
		list_add(getPackages(), &package);
		//保存包裹
		list_save(getPackages());
		//添加日志
		Log tempLog = {};
		sprintf_s(tempLog.description, DESCR, "用户%s下单了包裹%s", g_currentUser->phoneNumber, package.trackingNum);
		tempLog.createdTime = time(NULL);
		list_add(getLogs(), &tempLog);
		// 保存日志
		list_save(getLogs());
		//驿站盈利10%(未完成)

		printf_s("* 下单成功! \n");
		printf_s("* 快递单号为: %s\n",package.trackingNum);
		system("pause");
		system("cls");
	}
	// 取消
	else if (orderOption == 0)
	{
		system("cls");
	}
	//输入错误
	else
	{
		printf_s("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
}

void personalCenter()
{
	while (1)
	{
		//显示所有用户信息
		showUserInfo(g_currentUser);
		printf_s("*************** 个人中心 ***************\n");//width=40
		printf_s("*              1.身份码                *\n");
		printf_s("*              2.会员升级              *\n");
		printf_s("*              3.发送工单              *\n");
		printf_s("*              4.优惠福利              *\n");
		printf_s("*              0.返回                  *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			//打开身份码
		case 1:
			system("cls");
			showIdentityCode();
			break;
			//会员升级
		case 2:
			system("cls");
			userUpgrade();
			break;
			//发送工单
		case 3:
			system("cls");
			sendTicket();
			break;
			//兑换优惠券
		case 4:
			system("cls");
			exchangeCoupons();
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			//输入错误
			printf("输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void showUserInfo(User* user)
{
	printf("*************** 用户信息 ***************\n");
	printf("| 用户名：%s\n", user->userName);
	printf("| 类型：%s\n", (user->userType == VIP) ? "尊敬的会员" : "普通用户");
	printf("| 折扣：%.1lf折\n", 1.0 * user->discount / 10);
	printf("| 手机号：%s\n", user->phoneNumber);
	printf("| 优惠券数量：%d\n", user->couponCount);
	printf("| 经验值：%d\n", user->experience);
	printf("+--------------------------------------+\n");
}

void showIdentityCode()
{
	//显示所有用户信息
	showUserInfo(g_currentUser);
	printf("**************** 身份码 ****************\n");
	printf("* 您的身份码是：%s\n", g_currentUser->identityCode);
	system("pause");
	system("cls");
}

void userUpgrade()
{
	//显示所有用户信息
	showUserInfo(g_currentUser);
	printf("*************** 会员升级 ***************\n");
	if (g_currentUser->userType == Regular)
	{
		printf("* 您是否愿意花费%.2lf元充值会员？\n", UPGRADE_FEE);
		printf("* 请输入您的选择(1.充值；0.返回)：");
		int upgradeOption = -1;
		scanf_s("%d", &upgradeOption);
		rewind(stdin);
		switch (upgradeOption)
		{
			//充值
		case 1:
			g_currentUser->userType = VIP;
			g_currentUser->discount = 80;
			list_save(g_users);
			printf("* 充值成功！\n");
			system("pause");
			system("cls");
			break;
			//返回
		case 0:
			system("cls");
			return;
		default:
			printf("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
	else
	{
		printf("* 您已是尊贵的会员！\n");
		system("pause");
		system("cls");
	}
}

void sendTicket()
{
	//显示所有用户信息
	showUserInfo(g_currentUser);
	printf("*************** 发送工单 ***************\n");
	Ticket tempTicket = {};
	//填写工单类型
	printf_s("* 请输入工单类型 (1.误取申请；2.损坏丢失；3.投诉建议)：");
	int ticketTypeOption = -1;
	scanf_s("%d", &ticketTypeOption);
	rewind(stdin);
	//工单内容
	switch (ticketTypeOption)
	{
	case 1:
		tempTicket.ticketType = Miscollection;
		break;
	case 2:
		tempTicket.ticketType = DamageLoss;
		break;
	case 3:
		tempTicket.ticketType = ComplaintSuggestion;
		break;
	default:
		printf_s("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
		return;
	}
	if (tempTicket.ticketType == ComplaintSuggestion)
	{
		// 自动将快递单号置空
		tempTicket.pkgTrackingNum[0] = '\0';
	}
	else
	{
		printf_s("* 请输入状态是\"已签收\"包裹快递单号：");
		scanf_s("%s", tempTicket.pkgTrackingNum, TRACKING_NUM);
		if (findPackage(tempTicket.pkgTrackingNum, NULL, NULL, NULL, Delivered) == NULL)
		{
			printf_s("* 该快递单号的\"已签收\"包裹不存在！\n");
			system("pause");
			system("cls");
			return;
		}
	}
	printf_s("* 请输入工单描述(按下 Enter 键后输入完成)：\n");
	printf_s("\n");
	fgets(tempTicket.description, sizeof(tempTicket.description),stdin);
	tempTicket.description[strcspn(tempTicket.description, "\n")] = '\0';
	rewind(stdin);
	printf_s("\n");
	printf("* 是否发送该工单 (1.发送；0.返回)：");
	int sendOption = -1;
	scanf_s("%d", &sendOption);
	rewind(stdin);
	// 发送
	if (sendOption == 1)
	{
		tempTicket.ticketId = generateTicketId();
		tempTicket.createdTime = time(NULL);
		strcpy_s(tempTicket.userPhone, PHONE, g_currentUser->phoneNumber);
		// 添加工单
		list_add(getTickets(), &tempTicket);
		// 保存工单
		list_save(getTickets());
		// 添加日志
		Log tempLog = {};
		sprintf_s(tempLog.description, DESCR, "用户%s发送了工单%.20lld", g_currentUser->phoneNumber, generateTicketId());
		tempLog.createdTime = time(NULL);
		// 保存日志
		list_save(getLogs());
		printf("* 工单发送成功！\n");
		system("pause");
		system("cls");
	}
	// 返回
	else if (sendOption == 0)
	{
		system("cls");
	}
	// 输入错误
	else
	{
		printf("* 输入错误，请重新输入！\n");
		system("pause");
		system("cls");
	}
}

void exchangeCoupons()
{
	while (1)
	{
		//显示所有用户信息
		showUserInfo(g_currentUser);
		printf_s("*************** 优惠福利 ***************\n");
		printf_s("* 优惠券面额：%.2lf\n", COUPON_VALUE);
		printf_s("* 经验值消耗：%d 点每张优惠券\n", EXP_OF_PER_COUPON);
		printf_s("* 是否兑换优惠券 (1.兑换；0.返回)：");
		int exchangeCouponOption = -1;
		scanf_s("%d", &exchangeCouponOption);
		rewind(stdin);
		// 兑换优惠券
		if (exchangeCouponOption == 1)
		{
			printf_s("* 请输入您需要兑换的优惠券数量：");
			int exchangeCouponNum = -1;
			scanf_s("%d", &exchangeCouponNum);
			rewind(stdin);
			if (exchangeCouponNum <= 0)
			{
				printf_s("* 兑换的优惠券数量须大于 0 张！\n");
				system("pause");
				system("cls");
			}
			else if (exchangeCouponNum * EXP_OF_PER_COUPON > g_currentUser->experience)
			{
				printf_s("* 经验值不足！\n");
				system("pause");
				system("cls");
			}
			else
			{
				g_currentUser->couponCount += exchangeCouponNum;
				g_currentUser->experience -= exchangeCouponNum * EXP_OF_PER_COUPON;
				printf_s("* 兑换成功！\n");
				// 保存用户
				list_save(g_users);
				system("pause");
				system("cls");
			}
		}
		// 返回
		else if (exchangeCouponOption == 0)
		{
			system("cls");
			break;
		}
		//输入错误
		else
		{
			printf_s("* 输入错误！\n");
			system("pause");
			system("cls");
		}
	}
}