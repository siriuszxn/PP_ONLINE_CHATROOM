/*********************************************************
-  Copyright (C): 2016
-  File name    : client_main.c
-  Author       : - Zhao -
-  Date         : 2016年01月29日 星期五 18时40分20秒
-  Description  : 客户端TCP_client
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

int main(int argc, char **argv)
{
    int ret;           //保存线程的返回值
    int sockfd;
    int n_write;
    
    char buffer[50];   //定义一个缓冲区
    pthread_t id;      //线程ID
    Message msg;       //定义一个Message结构体

    struct sockaddr_in server_addr; //定义服务器的结构体
    
    /* main函数入口参数检查 */
    if (argc != 2)
    {
	fprintf(stderr, "Usage:%s hostname \a\n", argv[0]);
	exit(1);
    }
    /* 调用socket函数创建一个TCP协议套接口 */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
	fprintf(stderr, "Socket Error:$%s\a\n", strerror(errno));
	exit(1);
    }
    /* 填充服务器端的信息 */
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portnumber);
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    /* 连接服务器 */
    if (connect(sockfd, (struct sockaddr *)(&server_addr),sizeof(struct sockaddr)) == -1)
    {
	fprintf(stderr,"Connect Error:%s\a\n", strerror(errno));
	exit(1);
    }

    //创建一个子线程去不停的读取服务器发回的信息
    ret = pthread_create(&id, NULL, (void *)client_read_msg, (void *)&sockfd);
     
    if (ret != 0)
    {
	printf("Create pthread error!\n");
	exit(1);
    }

    /* 登录界面显示 */
    loading_dis();
    log_dis();

    //主线程去不停的获取用户输入
    while (1)
    {
	sleep(1);
	usleep(50000);
        msg.activity = 0;
	memset(buffer, 0, sizeof(buffer));
	printf("\033[28;71H                                      \n");
	printf("\033[28;45H＊Please input your choice:");
	scanf("%s", buffer);
        printf("\033[30;45H                                             ");
	fflush(stdout);
	//pthread_join(id, NULL);
	msg.action = input_check(buffer); //字符串解析将相应的动作状态返回到action中
	
	/* 如果输入出错则提示并要求用户重新输入 */
	if (msg.action == WRONG_CMD)
	{
	    printf("\033[30;45H＊客官您手抖了,再来一次!(^_^)");
	    printf("\033[28;45H                                   \n");
	    printf("\033[29;0H                                                    \n");
	    continue;
	}
	
	/* 根据字符串解析出来的action，将信息打包封装 */
	if (pack_msg(msg.action, &msg, sockfd, sizeof(msg)) != 0)
	{
	    continue;
	}
	
	/* 当动作命令为帮助时,显示帮助界面8s, 再跳回主界面 */
	if (msg.action == HELP)
	{
	    clear_min();
	    help_dis();   //软件使用说明及注意事项和开发人员信息
	    continue;
	}
	
	/* 当动作为退出时,关闭客户端进程 */
	if (msg.action == EXIT)
	{
            exit(0);
	}

	/* 当动作为文件读出异常 */
	if (msg.action == SENDFILE_ERROR)
	{
	    continue;
	}

	/* 当动作为返回登录界面时 */
	if (msg.action == BACK_LOGMENU)
	{
            continue;
	}
	/* 当动作为修改密码时 */
	if (msg.action == RESET_PASSWD)
	{
	    continue;
	}
	
	/* 当动作为VIP注册推出时 */
	if (msg.action == VIPEXIT)
	{
	    continue;
	}
	
	/* 像服务器发送数据包*/
	n_write = write(sockfd, &msg, sizeof(msg));
        if (n_write == -1)
	{
	    printf("the client_main write to server error\n");
	}
	/* 注册结束后清空数据包*/
	if (msg.action == REGIST)
	{
	    bzero(&msg.name, sizeof(msg.name));
	    bzero(&msg.pp_id, sizeof(msg.pp_id));
	    bzero(&msg.to_name, sizeof(msg.to_name));
	    bzero(&msg.to_id, sizeof(msg.to_id));
	    bzero(&msg.passwd, sizeof(msg.passwd));
	    bzero(&msg.passpro, sizeof(msg.passpro));
	    bzero(&msg.passkey, sizeof(msg.passkey));
            bzero(&msg.msg, sizeof(msg.msg));
	}
	sleep(1);
    }
    close(sockfd);
    exit(0);
}
