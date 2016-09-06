/*********************************************************
-  Copyright (C): 2016
-  File name    : input_check.c
-  Author       : - Zhao -
-  Date         : 2016年01月30日 星期六 11时24分39秒
-  Description  : 字符串解析函数
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

int input_check(char *cmd)
{
    char check[5];
    int i = 0;

    /* 入口参数检查 */
    for (i = 0; i < 3; i++)
    {
	check[i] = cmd[i];
    }
    check[i] = '\0';
    
    /* 当命令为点赞时 */
    if (strcmp(check, "ZAN") == 0)
    {
	return DIANZAN;
    }

    /* 当命令为登录时 */
    if (strcmp(check, "LOG") == 0)
    {
	return LOGIN;
    }
    
    /* 当命令为注册时 */
    if (strcmp(check, "REG") == 0)
    {
	return REGIST;
    }
    
    /* 当命令为查看在线好友时*/
    if (strcmp(check, "DIS") == 0)
    {
	return DIS_ONLINE_USER;
    }

    /* 当命令为私聊时*/
    if (strcmp(check, "PCH") == 0)
    {
	return CHATONE;
    }

    /* 当命令为群聊时 */
    if (strcmp(check, "ACH") == 0)
    {
	return CHATALL;
    }

    /* 当命令为忘记/修改密码时 */
    if (strcmp(check, "REM") == 0)
    {
        return RESET_PASSWD;
    }
    
    /* 当命令为帮助时 */
    if (strcmp(check, "HLP") == 0)
    {
	return HELP;
    }
    
    /* 当命令为返回登录界面时 */
    if (strcmp(check, "BCK") == 0)
    {
	return BACK_LOGMENU;
    }
    
    /* 当命令为禁言时 */
    if (strcmp(check, "NOS") == 0)
    {
	return SLENCE;
    }

    /* 当命令为解禁时 */
    if (strcmp(check, "CAS") == 0)
    {
	return PERMITE;
    }
    
    /* 当命令为踢人时 */
    if (strcmp(check, "OUT") == 0)
    {
	return TICK;
    }
    
    /* 当命令为这种个性签名时 */
    if (strcmp(check, "SET") == 0)
    {
	return SETSIGNER;
    }

    /* 当命令为注册会员时 */
    if (strcmp(check, "VIP") == 0)
    {
	return VIPMEMBER;
    }

    /* 当命令为发送表情时 */
    if (strcmp(check, "SBQ") == 0)
    {
	return SENDBQ;
    }

    /* 当命令为发送短语时 */
    if (strcmp(check, "SDY") == 0)
    {
	return SENDDY;
    }

    /* 当命令为传输文件时 */
    if (strcmp(check, "SFS") == 0)
    {
	return SENDFILE;
    }

    /* 当命令为查看聊天记录时 */
    if (strcmp(check, "SJL") == 0)
    {
	return DISJILU;
    }
    if (strcmp(check, "EXT") == 0)
    {
	system("clear");
	printf("\033[15;40H＊感谢使用PP_ONLINE聊天室、您的使用是对我们最大的支持\n");
	sleep(2);
	printf("\033[17;40H                      下次再见\n");
	sleep(2);
	system("clear");
	exit(0);
    }
    /* 以上命令都不是的时*/
    return WRONG_CMD;
}
