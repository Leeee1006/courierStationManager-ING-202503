#pragma once
#include"common.h"
#include"user.h"
#include"log.h"
#include"package.h"
#include"shelf.h"

#define MANAGER_PASSWORD 17843 // 管理员登录密码

// 功能：管理员主菜单
void managerMenu();

/**********************/

// 功能：智能库存菜单
void warehouseMenu();

// 功能：包裹追踪菜单
void trackPackageMenu();

// 功能：重置爆仓预警阈值
void resetWarningThreshold();

// ************************************

// 功能：用户管理菜单
void userManagementMenu();

// 功能：用户检索
void managerFindUser();

// 功能：删除用户
void managerDeleteUser();

// ************************************

// 功能：信息维护菜单
void infoMaintenanceMenu();

// 功能：处理工单菜单
void AddressTicketMenu();

// 功能：处理误取工单
void AddressMisdelivery();

// 功能：处理损坏丢失工单
void AddressDamageLoss();

// 功能：处理投诉建议工单
void AddressComplaintSuggestion();

