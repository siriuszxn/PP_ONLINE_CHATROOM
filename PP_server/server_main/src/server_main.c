/*********************************************************
-  Copyright (C): 2016
-  File name    : sever.c
-  Author       : - Zhao -
-  Date         : 2016年01月29日 星期五 16时34分40秒
-  Description  : 服务器端程序_TCP_SERVER
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

int main(int argc, char **argv)
{
    int ret;
    int sockfd;     //服务器套接字 
    int new_fd;     //连接后与客户端的新的套接字
    int sin_size;
    int opt = 1;
    pthread_t id;
    sqlite3 *db = NULL;

    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    
    /* 创建一个用户数据库用来存放客户信息 */
    if (SQLITE_OK != sqlite3_open("PP_user.db", &db))
    {
	fprintf(stderr, "Cannot open database:%s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	exit(1);
    }
    else
    {
	printf("Open database successfully...\n");
    }

    create_server_sql(db);

    /* 调用socket函数创建一个TCP套接口 */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
	fprintf(stderr, "Socket error:%s\n\a",strerror(errno));
	exit(1);
    }
    /* 填充服务器端的信息 */
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(portnumber);
    /* 让服务器退出后不用在等待30s*/
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if (bind(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)) == -1)
    {
	fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
	exit(1);
    }
    /* 设置最大监听数目 */
    if (listen(sockfd, 30) == -1)
    {
	fprintf(stderr, "Listen error:%s\n\a",strerror(errno));
	exit(1);
    }
    /* 主线程负责与客户端建立连接 */
    while (1)
    {
	sin_size = sizeof(struct sockaddr_in);
	/* 阻塞的等待客户端的连接 */
	if ((new_fd = accept(sockfd, (struct sockaddr *)(&client_addr), &sin_size)) == -1)
        {
	    fprintf(stderr,"Accept error:%s\n\a", strerror(errno));
	    exit(1);
	}
	fprintf(stderr, "Server get connection from %s\n", inet_ntoa(client_addr.sin_addr));
        
	/* 创建一个子线程,用于处理多客户端连接*/
	ret = pthread_create(&id, NULL, (void *)server_read_msg, (void *)&new_fd);
	if (ret)
	{
	    printf("create thread error!\n");
	    exit(1);
	}
    }
    close(sockfd);
    sqlite3_close(db);
    return 0;
}

