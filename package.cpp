#include "package.h"

// 包裹链表指针
List* g_packages = NULL;

List* getPackages()
{
	return g_packages;
}

void initPackages()
{
	g_packages = list_init(sizeof(Package), PACKAGE_FILE, sizeof(PACKAGE_FILE));
}

Package* findPackage(char* trackingNum, char* packageName, char* senderPhone, char* receiverPhone, int packageState)
{
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if ((trackingNum == NULL || strcmp(pkg->trackingNum, trackingNum) == 0) &&
			(packageName == NULL || strcmp(pkg->packageName, packageName) == 0) &&
			(senderPhone == NULL || strcmp(pkg->senderPhone, senderPhone) == 0) &&
			(receiverPhone == NULL || strcmp(pkg->receiverPhone, receiverPhone) == 0) &&
			(packageState == -1 || pkg->packageState == packageState))
		{
			return pkg;
		}
	}
	return NULL;
}

void deletePackage(char* trackingNum, char* packageName, char* senderPhone, const char* senderAddress, char* receiverPhone, const char* receiverAddress, int packageState)
{
	for (ListNode* cur = g_packages->head; cur != g_packages->tail; )
	{
		Package* pkg = (Package*)cur->next->data;
		if ((trackingNum == NULL || strcmp(pkg->trackingNum, trackingNum) == 0) &&
			(packageName == NULL || strcmp(pkg->packageName, packageName) == 0) &&
			(senderPhone == NULL || strcmp(pkg->senderPhone, senderPhone) == 0) &&
			(senderAddress == NULL || strcmp(pkg->senderAddress, senderAddress) == 0) &&
			(receiverPhone == NULL || strcmp(pkg->receiverPhone, receiverPhone) == 0) &&
			(receiverAddress == NULL || strcmp(pkg->receiverAddress, receiverAddress)) &&
			(packageState == -1 || pkg->packageState == packageState))
		{
			if (cur->next == g_packages->tail)
			{
				g_packages->tail = cur;
			}
			ListNode* temp = cur->next;
			cur->next = temp->next;
			if (temp->data != NULL)
			{
				free(temp->data);
			}
			free(temp);
			g_packages->elementCount--;
		}
		else
		{
			cur = cur->next;
		}
	}
}

bool isPackageExist(PackageState packageState)
{
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (pkg->packageState == packageState)
		{
			return true;
		}
	}
	return false;
}

double calculateShippingFee(Package* package, User* user)
{
	double shippingFee = 0.0;
	//抛比系数
	const double VOLUMETRIC_WEIGHT_RATIO = 6000.0;
	//首重/(元/千克)
	const double FIRST_WEIGHT = 12.0;
	//续重/(元/千克)
	const double SUBSEQUENT_WEIGHT = 3.0;
	//体积重量/千克
	double volumetricWeight = package->volume / VOLUMETRIC_WEIGHT_RATIO;
	//实际重量/千克
	double actualWeight = fmax(package->weight, volumetricWeight);
	//基础运费
	shippingFee += FIRST_WEIGHT + SUBSEQUENT_WEIGHT * (fmax(actualWeight - 1.0, 0.0));
	//寄件方式加费
	switch (package->shippingMethod)
	{
		//普通
	case ShippingStandard:
		shippingFee += 0.0;
		break;
		//紧急
	case Express:
		shippingFee += 10.0;
		break;
		//轻缓
	case Economic:
		shippingFee += -10.0;
		break;
	}
	//包裹类型加费
	switch (package->packageType)
	{
		//普通
	case PackageStandard:
		shippingFee += 0.0;
		break;
		//易碎
	case Fragile:
		shippingFee += 10.0;
		break;
		//贵重
	case Parcel:
		shippingFee += 30.0;
		break;
	}
	// 上门取件加费 (与用户折扣有关)
	shippingFee += package->isHomeDelivered ? 5.0 * user->discount / 100.0 : 0.0;
	// 上门寄件加费 (与用户折扣有关)
	shippingFee += package->isHomeSent ? 5.0 * user->discount / 100.0 : 0.0;
	// 优惠券减免
	shippingFee -= 1.0 * package->usedCouponNum * COUPON_VALUE;
	// 会员折扣
	shippingFee *= 1.0 * user->discount / 100.0;
	// 避免运费负值
	shippingFee = fmax(shippingFee, 0.0);
	return shippingFee;
}

char* generateTrackingNumber()
{
	time_t temp = time(NULL);
	return digitalTime(temp);
}

void showPackageOrdered(char* senderPhone)
{
	printf_s("**************************************************** 已下单的包裹 ****************************************************\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	printf_s("|    快递单号    |    取件人   |                 收件地址                 |       下单时间      |      寄件金额      |\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Ordered)
		{
			//打印快递单号，取件人，收件地址，下单时间，寄件金额
			printf_s("| %14s | %11s | %40s | %19s | %18.8g |\n", pkg->trackingNum, pkg->receiverPhone, pkg->receiverAddress, formatTime(pkg->time.ordered), pkg->shippingFee);
			printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
		}
	}
}

void showPackageCanceled(char* senderPhone)
{
	printf_s("**************************************************** 已取消的包裹 ****************************************************\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	printf_s("|    快递单号    |    收件人   |                 收件地址                 |       取消时间      |      寄件金额      |\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Canceled)
		{
			//打印快递单号，取件人，收件地址，收件时间，寄件金额
			printf_s("| %14s | %11s | %40s | %19s | %18.8g |\n", pkg->trackingNum, pkg->receiverPhone, pkg->receiverAddress, formatTime(pkg->time.canceled), pkg->shippingFee);
			printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
		}
	}
}

void showPackageShipped(char* senderPhone)
{
	printf_s("**************************************************** 已寄出的包裹 ****************************************************\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	printf_s("|    快递单号    |    收件人   |                 收件地址                 |       寄出时间      |      寄件金额      |\n");
	printf_s("+----------------+-------------+------------------------------------------+---------------------+--------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->senderPhone, senderPhone) == 0 && pkg->packageState == Shipped)
		{
			//打印快递单号，取件人，收件地址，寄出时间，寄件金额
			printf_s("| %14s | %11s | %40s | %19s | %18.8g |\n", pkg->trackingNum, pkg->receiverPhone, pkg->receiverAddress, formatTime(pkg->time.shipped), pkg->shippingFee);
			printf_s("+--------------------+--------------------+----------------------------------------+--------------------+--------------------+\n");
		}
	}
}

void showPackagePending(char* receiverPhone)
{
	printf_s("******************** 待取件的包裹 *******************\n");
	printf_s("+----------------+------------+---------------------+\n");
	printf_s("|    快递单号    |   取件码   |       入库时间      |\n");
	printf_s("+----------------+------------+---------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Pending)
		{
			//打印快递单号，取件码，入库时间
			printf_s("| %14s | %10s | %19s |\n", pkg->trackingNum, pkg->pickupCode, formatTime(pkg->time.pending));
			printf_s("+----------------+------------+---------------------+\n");
		}
	}
}

void showPackageRefused(char* receiverPhone)
{
	printf_s("******************** 已拒收的包裹 *******************\n");
	printf_s("+----------------+------------+---------------------+\n");
	printf_s("|    快递单号    |   取件码   |       拒收时间      |\n");
	printf_s("+----------------+------------+---------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Refused)
		{
			//打印快递单号，取件码，拒收时间
			printf_s("|%19s |%19s |%19s |\n", pkg->trackingNum, pkg->pickupCode, formatTime(pkg->time.refused));
			printf_s("+----------------+------------+---------------------+\n");
		}
	}
}

void showPackageDelivered(char* receiverPhone)
{
	printf_s("******************** 已签收的包裹 *******************\n");
	printf_s("+----------------+------------+---------------------+\n");
	printf_s("|    快递单号    |   取件码   |       签收时间      |\n");
	printf_s("+----------------+------------+---------------------+\n");
	for (ListNode* node = g_packages->head->next; node != NULL; node = node->next)
	{
		Package* pkg = (Package*)node->data;
		if (strcmp(pkg->receiverPhone, receiverPhone) == 0 && pkg->packageState == Delivered)
		{
			//打印快递单号，取件码，签收时间
			printf_s("|%19s |%19s |%19s |\n", pkg->trackingNum, pkg->pickupCode, formatTime(pkg->time.delivered));
			printf_s("+----------------+------------+---------------------+\n");
		}
	}
}

void showAllPackages()
{
	printf_s("*************** 包裹全览 ***************\n");
	if (g_packages->elementCount == 0)
	{
		printf_s("* 暂无包裹\n");
		system("pause");
		system("cls");
		return;
	}
	for (ListNode* p = g_packages->head->next; p != NULL; p = p->next)
	{
		printf_s("*************** 包裹信息 ***************\n");
		Package* pkg = (Package*)p->data;
		printf_s("| 快递单号：%s\n", pkg->trackingNum);
		printf_s("| 包裹名称：%s\n", pkg->packageName);
		printf_s("| 包裹类型：");
		switch (pkg->packageType)
		{
		case PackageStandard:
			printf_s("标准\n");
			break;
		case Fragile:
			printf_s("易碎\n");
			break;
		case Parcel:
			printf_s("贵重\n");
			break;
		default:
			printf_s("信息错误\n");
			break;
		}
		printf_s("| 寄件方式：");
		switch (pkg->shippingMethod) {
		case ShippingStandard:
			printf_s("标准\n");
			break;
		case Express:
			printf_s("快递\n");
			break;
		case Economic:
			printf_s("经济\n");
			break;
		default:
			printf_s("信息错误\n");
			break;
		}
		printf_s("| 体积：%.2lf\n", pkg->volume);
		printf_s("| 重量：%.2lf\n", pkg->weight);
		printf_s("| 寄件地址：%s\n", pkg->senderAddress);
		printf_s("| 收件地址：%s\n", pkg->receiverAddress);
		printf_s("| 寄件人手机号：%s\n", pkg->senderPhone);
		printf_s("| 收件人手机号：%s\n", pkg->receiverPhone);
		printf_s("| 优惠券使用数量：%d\n", pkg->usedCouponNum);
		printf_s("| 运费：%.2lf\n", pkg->shippingFee);
		if (pkg->pickupCode[0] != '\0')
		{
			printf_s("| 取件码：%s\n", pkg->pickupCode);
		}
		printf_s("| 包裹状态：");
		switch (pkg->packageState)
		{
		case Ordered:
			printf_s("已下单\n");
			break;
		case Canceled:
			printf_s("已取消\n");
			break;
		case Shipped:
			printf_s("已寄出\n");
			break;
		case Pending:
			printf_s("待取件\n");
			break;
		case Refused:
			printf_s("已拒收\n");
			break;
		case Delivered:
			printf_s("已签收\n");
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
		printf_s("+--------------------------------------+\n");
	}
	system("pause");
	system("cls");
	return;
}