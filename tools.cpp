#include "tools.h"

bool isValidPassword(const char* password, int flag)
{
	//数字长度限定函数
	if (!password || strlen(password) != flag) return false;
	for (int i = 0; i < flag; i++)
	{
		if (!isdigit((unsigned char)password[i])) return false;
	}
	return true;
}

bool isValidUserName(const char* userName)
{
	if (!userName || *userName == '\0' || strlen(userName) < 4 || strlen(userName) > 8) // 限定姓名为 2 至 4 个汉字
	{
		return false;
	}

	return isChineseString(userName, 8);
}

bool isChineseChar(const unsigned char* str)
{
	if (!str || str[0] == '\0' || str[1] == '\0') return false; // 避免空指针和越界访问

	unsigned char high = str[0];
	unsigned char low = str[1];

	return (high >= 0xB0 && high <= 0xF7 && low >= 0xA1 && low <= 0xFE);
}

bool isChineseString(const char* str, int flag)
{
	int i = 0;
	while (str[i] != '\0')
	{
		// 如果当前字符是中文字符，跳过两个字节
		if (isChineseChar((unsigned char*)&str[i]))
		{
			i += 2; // 中文字符由两个字节组成
		}
		else
		{
			return false; // 如果遇到非中文字符，返回0
		}
	}
	if (i > flag || i == 0)
	{
		return false;
	}
	return true; // 如果整个字符串都是中文字符，返回1
}

bool isValidPhoneNumber(const char* phoneNumber)
{
	if (!phoneNumber || strlen(phoneNumber) != 11) return false;
	for (int i = 0; i < 11; i++)
	{
		if (!isdigit((unsigned char)phoneNumber[i])) return false;
	}
	return true;
}

// 安全内存分配
void* safeMalloc(size_t size, const char* context)
{
	void* ptr = malloc(size);
	if (!ptr)
	{
		perror(context);
		exit(EXIT_FAILURE);
	}
	return ptr;
}

// 安全文件操作
FILE* safeFopen(const char* fileName, const char* mode)
{
	FILE* fp;
	if (fopen_s(&fp, fileName, mode) || !fp)
	{
		perror(fileName);
		exit(EXIT_FAILURE);
	}
	return fp;
}