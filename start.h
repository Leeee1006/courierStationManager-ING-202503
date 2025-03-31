#pragma once
#include "common.h"
#include "tools.h"
#include "user.h"
#include "manager.h"

// 功能：开始菜单
// 参数：用户链表指针
void startMenu();

// 功能：用户注册
// 参数：用户链表指针
void userRegister();

// 功能：用户登录
// 参数：用户链表指针
// 返回：登录用户指针 (登录失败：NULL)
User* userLogin();

// 功能：管理员登录
void managerLogin();