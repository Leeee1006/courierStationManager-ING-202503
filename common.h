#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <windows.h>
#include <time.h>
#include <stdbool.h> 

#define PHONE           12  // 手机号长度
#define NAME            20  // 名称长度
#define PASSWORD        6  // 密码长度
#define ID_CODE         31  // 身份码长度
#define TRACKING_NUM    15  // 快递单号长度
#define ADDRESS         200 // 地址名长度
#define DESCR           400 // 描述长度

/* 用户类型 */
typedef enum UserType
{
	Regular,   // 普通用户
	VIP,       // VIP 用户
	Operator,  // 操作员用户
	Admin      // 管理员用户
} UserType;

/* 包裹类型 */
typedef enum PackageStandard
{
	PackageStandard, // 标准包裹
	Parcel,   // 贵重包裹
	Fragile   // 易碎包裹
} PackageType;

/* 寄件方式 */
typedef enum ShippingMethod
{
	ShippingStandard, // 标准
	Express,  // 快递
	Economic  // 经济
} ShippingMethod;

/* 包裹状态 */
typedef enum PackageState
{
	Ordered,      // 已下单
	Shipped,      // 已寄出
	Pending,      // 待收件
	Delivered,    // 已收件
	Refused,      // 拒收
	Canceled,     // 取消
	Misdelivered, // 误取
	DamagedLost   // 损坏丢失
} PackageState;

/* 工单类型 */
typedef enum TicketType
{
	Miscollection,               // 误取申请
	DamageLoss,                  // 损坏丢失
	ComplaintSuggestion,         // 投诉建议
} TicketType;

/* 货架层信息 */
typedef struct ShelfLevel
{
	double volumeCapacity;     // 货架层最大容积
	double occupiedVolume;     // 货架层已使用容积
	int packageNum;            // 当前货架层的包裹数
} ShelfLevel;

/* 时间信息 */
typedef struct PackageTime
{
	time_t ordered;   // 下单时间
	time_t shipped;   // 已寄出时间
	time_t canceled;  // 取消时间
	time_t pending;   // 入库时间
	time_t delivered; // 收件时间
	time_t refused;   // 拒收时间
} PackageTime;

/* 用户信息 */
typedef struct User
{
	long long   userId;               // 用户编号
	char        userName[NAME];       // 用户姓名
	UserType    userType;             // 用户类型
	int         discount;             // 折扣(0%-100%)
	char        phoneNumber[PHONE];   // 手机号
	char        identityCode[ID_CODE];// 身份码
	char        password[PASSWORD];   // 密码
	int couponCount;         // 优惠券数量
	int experience;          // 经验值
} User;

/* 包裹信息 */
typedef struct Package
{
	char            trackingNum[TRACKING_NUM];		// 快递单号(唯一标识)
	char            packageName[NAME];   // 包裹名称
	PackageType     packageType;         // 包裹类型
	ShippingMethod  shippingMethod;      // 寄件方式
	double          volume;              // 包裹体积
	double          weight;              // 包裹重量
	char            senderPhone[PHONE];			// 寄件人手机号
	char            senderAddress[ADDRESS];		// 寄件地址
	char            receiverPhone[PHONE];		// 收件人手机号
	char            receiverAddress[ADDRESS];	// 收件地址
	bool            isHomeDelivered;     // 是否送件到楼
	bool            isHomeSent;          // 是否取件到楼
	int             usedCouponNum;					// 使用优惠券的数量
	double          shippingFee;         // 运费
	char            pickupCode[ID_CODE]; // 取件码
	PackageState    packageState;        // 包裹状态
	PackageTime     time;                // 统一时间信息
} Package;

/* 工单信息 */
typedef struct Ticket
{
	long long       ticketId;            // 工单编号
	TicketType      ticketType;          // 工单类型
	char            description[DESCR];  // 描述
	time_t          createdTime;         // 创建时间
	char            userPhone[PHONE];    // 用户手机号
	char            pkgTrackingNum[TRACKING_NUM]; //包裹快递单号
	bool            isHandled;          // 是否被处理
} Ticket;

/* 日志信息 */
typedef struct Log
{
	char            description[DESCR];  // 描述
	time_t          createdTime;         // 创建时间
} Log;

/* 统计数据 */
typedef struct Statistics
{
	double  weeklyRevenue;               // 每周收入
	int     sendCount;                   // 寄件数量
	int     pickupCount;                 // 取件数量
	int     remainPackages;              // 剩余包裹数量
} Statistics;
