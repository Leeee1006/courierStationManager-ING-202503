#pragma once
#include "common.h"
#include "list.h"
#include "package.h"
#include "log.h"
#include "ticket.h"
#include "timeFormat.h"
#include "manager.h"

#define USER_FILE "resource/users.dat"   // 用户文件
#define DEFAULT_SENDER_ADDRESS "吉大大学城" // 默认寄件地址
#define UPGRADE_FEE 300.0       // 会员升级花费
#define COUPON_VALUE 5.0        // 优惠券面额
#define EXP_COEF 1				// 经验值系数
#define EXP_OF_PER_COUPON 10	// 兑换每张优惠券消耗的经验值

List* getUsers();

void initUsers();

// 功能：查找用户；
// 参数1：编号 (不限：-1)；
// 参数2：姓名 (不限：NULL)；
// 参数3：手机号 (不限：NULL)；
// 参数4：密码 (不限：NULL)；
// 返回：目标用户指针 (查无：NULL)；
User* findUser(long long userId, const char* userName, const char* phone, const char* password);

// 功能：删除用户；
// 参数1：编号 (不限：-1)；
// 参数2：姓名 (不限：NULL)；
// 参数3：手机号 (不限：NULL)；
// 参数4：密码 (不限：NULL)；
void deleteUser(long long userId, const char* userName, const char* phone, const char* password);

// 功能：显示所有用户
void showUsers();

// 功能：生成用户编号
// 返回：用户编号
long long generateUserId();

// 功能：生成身份码
// 参数：手机号
// 返回：身份码字符串
char* generateIdentityCode(const char* phone);

// 功能：用户菜单
// 参数：当前用户
void userMenu(User* currentUser);

// ************************************

// 功能：包裹信息菜单
void packageInfoMenu();

// 功能：取件信息菜单
void receivingInfoMenu();

// 功能：已签收包裹信息菜单
void packageDeliveredMenu();

// 功能：待取件包裹信息菜单，用户可以拒收
void packagePendingMenu();

// 功能：拒收包裹
void refusePackage();

// 功能：已拒收包裹信息菜单
void packageRefusedMenu();

// ************************************

// 功能：寄件信息菜单
void sendingInfoMenu();

// 功能：已寄出包裹信息菜单
void packageShippedMenu();

// 功能：已下单包裹信息菜单
void packageOrderedMenu();

// 功能：取消包裹
void cancelPackage();

// 功能：已取消包裹信息菜单
void PackageCanceledMenu();

// ************************************

// 功能：取件菜单
void pickupPackageMenu();

// 功能：取件
void pickupPackage();

// 功能：寄件
void sendPackage();

// ************************************

// 功能：个人中心
void personalCenter();

// 功能：显示用户信息
void showUserInfo(User* user);

// 功能：显示身份码
void showIdentityCode();

// 功能：会员升级
void userUpgrade();

// 功能：发送工单
void sendTicket();

// 功能：兑换优惠券
void exchangeCoupons();