#pragma once
#include "common.h"

// 校验密码是否合法
bool isValidPassword(const char* password, int flag);

// 校验用户名是否合法
bool isValidUserName(const char* userName);

// 判断是否为中文字符
bool isChineseChar(const unsigned char* str);

// 判断字符串是否为中文字符串
bool isChineseString(const char * str, int flag);

// 校验手机号是否合法
bool isValidPhoneNumber(const char* phoneNumber);

// 安全内存分配
void* safeMalloc(size_t size, const char* context);

// 安全文件操作
FILE* safeFopen(const char* fileName, const char* mode);