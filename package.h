#pragma once
#include "common.h"
#include "list.h"
#include "user.h"
#include "log.h"
#include "shelf.h"
#include "timeFormat.h"

#define PACKAGE_FILE "resource/packages.dat" // 包裹文件

List* getPackages();

void initPackages();

// 功能：查找包裹
// 参数1：快递单号 (不限：NULL) 
// 参数2：包裹名称 (不限：NULL) 
// 参数3：寄件人手机号 (不限：NULL)
// 参数4：收件人手机号 (不限：NULL)
// 参数5：包裹状态 (不限：-1)
// 返回：目标包裹指针 (查无：NULL)
Package* findPackage(char* trackingNum, char* name, char* senderPhone, char* receiverPhone, int packageState);

// 功能: 删除包裹
// 参数1: 快递单号 (不限: NULL) 
// 参数2: 包裹名称 (不限: NULL) 
// 参数3: 寄件人手机号 (不限: NULL)
// 参数4: 寄件地址 (不限: NULL)
// 参数5: 收件人手机号 (不限: NULL)
// 参数6: 收件地址 (不限: NULL)
// 参数7: 包裹状态 (不限: -1)
void deletePackage(char* trackingNum, char* name, char* senderPhone, const char* senderAddress, char* receiverPhone, const char* receiverAddress, int packageState);

// 功能：判断包裹是否存在
// 参数：包裹状态
// 返回：包裹是否存在
bool isPackageExist(PackageState packageState);

// 功能：计算运费
// 参数：包裹指针
// 返回：运费
double calculateShippingFee(Package* package, User* user);

// 功能：生成快递单号
// 返回：快递单号字符串
char* generateTrackingNumber();

// 功能：显示已下单包裹
// 参数：包裹链表，寄件人手机号
void showPackageOrdered(char* senderPhone);

// 功能：显示已取消包裹
// 参数：包裹链表指针，寄件人手机号
void showPackageCanceled(char* senderPhone);

// 功能：显示已寄出包裹
// 参数：包裹链表指针，寄件人手机号
void showPackageShipped(char* senderPhone);

// 功能：显示待取件包裹
// 参数：包裹链表指针，收件人手机号
void showPackagePending(char* receiverPhone);

// 功能：显示已拒收包裹
// 参数：包裹链表指针，收件人手机号
void showPackageRefused(char* receiverPhone);

// 功能：显示已签收包裹
// 参数：包裹链表指针，收件人手机号
void showPackageDelivered(char* receiverPhone);

// 功能：显示所有包裹
void showAllPackages();
