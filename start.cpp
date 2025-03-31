#include "start.h"

void startMenu()
{
	while (1)
	{
		printf_s("* 欢迎使用驿站管理系统\n");
		printf_s("*************** 开始菜单 ***************\n");//width=40
		printf_s("*              1.用户注册              *\n");
		printf_s("*              2.用户登录              *\n");
		printf_s("*              3.管理员登录            *\n");
		printf_s("*              0.退出系统              *\n");
		printf_s("****************************************\n");
		printf_s("* 请输入您的选择：");
		int menuOption = -1;
		scanf_s("%d", &menuOption);
		rewind(stdin);
		switch (menuOption)
		{
			// 用户注册
		case 1:
			userRegister();
			break;
			// 用户登录
		case 2:
			userMenu(userLogin());
			break;
			// 管理员登录
		case 3:
			managerLogin();
			break;
			// 退出
		case 0:
			printf_s("* 欢迎下次使用！\n");
			return;
			// 输入错误
		default:
			printf_s("* 输入错误，请重新输入！\n");
			system("pause");
			system("cls");
			break;
		}
	}
}

void userRegister()
{
	User newUser = {};
	//设置手机号
	printf_s("* 请设置您的手机号：");
	scanf_s("%s", newUser.phoneNumber, PHONE);
	rewind(stdin);
	//手机号格式错误
	if (!isValidPhoneNumber(newUser.phoneNumber))
	{
		printf_s("* 手机号格式错误，请重新注册！\n");
		system("pause");
		system("cls");
		return;
	}
	//手机号重复
	if (findUser(-1, NULL, newUser.phoneNumber, NULL) != NULL)
	{
		printf_s("* 手机号已存在，请重新注册！\n");
		system("pause");
		system("cls");
		return;
	}
	//设置密码
	printf_s("* 请设置登录密码：");
	scanf_s("%s", newUser.password, PASSWORD);
	rewind(stdin);
	//密码格式错误
	if (!isValidPassword(newUser.password, PASSWORD - 1))
	{
		printf_s("* 密码格式错误，请重新注册！\n");
		system("pause");
		system("cls");
		return;
	}
	//设置用户名
	printf_s("* 请设置您的姓名：");
	scanf_s("%s", newUser.userName, NAME);
	rewind(stdin);
	//姓名格式错误
	if (!isValidUserName(newUser.userName))
	{
		printf_s("* 姓名格式错误，请重新注册！\n");
		system("pause");
		system("cls");
		return;
	}
	// 添加用户
	newUser.userId = generateUserId();
	newUser.userType = Regular;
	newUser.discount = 100;
	newUser.couponCount = 0;
	newUser.experience = 0;
	strcpy_s(newUser.identityCode, ID_CODE, generateIdentityCode(newUser.phoneNumber));
	list_add(getUsers(), &newUser);
	// 保存用户
	list_save(getUsers());
	printf_s("* 注册成功！\n");
	system("pause");
	system("cls");
}

User* userLogin()
{
	User user = {};
	//输入手机号
	printf_s("* 请输入您的手机号：");
	scanf_s("%s", user.phoneNumber, PHONE);
	rewind(stdin);
	//手机号格式错误
	if (!isValidPhoneNumber(user.phoneNumber))
	{
		printf_s("* 手机号格式错误，请重新登录！\n");
		system("pause");
		system("cls");
		return NULL;
	}
	//输入密码
	printf_s("* 请输入登录密码：");
	scanf_s("%s", user.password, PASSWORD);
	rewind(stdin);
	//密码格式错误
	if (!isValidPassword(user.password, PASSWORD - 1))
	{
		printf_s("* 密码格式错误，请重新登录！\n");
		system("pause");
		system("cls");
		return NULL;
	}
	// 登录失败
	User* foundUser = findUser(-1, NULL, user.phoneNumber, user.password);
	if (foundUser == NULL)
	{
		printf_s("* 手机号或密码错误，登录失败！\n");
		system("pause");
		system("cls");
		return NULL;
	}
	printf_s("* 登录成功！\n");
	system("pause");
	system("cls");
	return foundUser;
}

void managerLogin()
{
	printf_s("* 请输入管理员密码：");
	long long password = -1;
	scanf_s("%lld", &password);
	rewind(stdin);
	if (password == MANAGER_PASSWORD)
	{
		printf_s("* 登录成功！\n");
		system("pause");
		system("cls");
		managerMenu();
	}
	else 
	{
		printf_s("* 密码错误！\n");
		system("pause");
		system("cls");
	}
	return;
}