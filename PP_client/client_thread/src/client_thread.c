/*********************************************************
-  Copyright (C): 2016
-  File name    : client_thread.c
-  Author       : - Zhao -
-  Date         : 2016年01月30日 星期六 00时53分13秒
-  Description  : 客户端线程处理函数，不断的读取服务器的输入
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

void client_read_msg(void *arg)
{
    int fd = *((int *)arg); 
    int n_read;
   
    int count = 0;
    
    struct _Message *msg = (struct _Message *)malloc(sizeof(struct _Message));
    
    while (1)
    {
        memset(msg, 0, sizeof(struct _Message));
	//阻塞式不停的从服务器读取传回的数据
	n_read = read(fd, msg, sizeof(struct _Message));
	if (n_read == 0)
	{
            close(fd);
	    pthread_exit(NULL);
	}

        //根据msg->flag执行相应的操作
	switch(msg->flag)
	{
	    /* 当服务器返回普通用户登录成功动作 */
	    case LOGIN:
	    {
                printf("\033[25;45H                                                   \n");
		printf("\033[25;45H＊恭喜您已成功登录!\n");
		sleep(1);
		user_dis();
		printf("\033[4;103H %s\n", msg->name);
		printf("\033[6;103H %d\n", msg->pp_id);
		printf("\033[6;114H%d\n", msg->zan);
		//如果该用户设置过个性签名,则登录时显示该用户设置的个性签名
		if (strcmp("admin", msg->signer) != 0)
		{
		    printf("\033[8;95H                       \n");
                    printf("\033[8;95H %s\n", msg->signer);
		}
		break;
	    }
	    
	    /* 当服务器返回超级用户登录成功动作 */
	    case LOGINSUPER:
	    {
                printf("\033[25;45H                                                     \n");
		printf("\033[25;45H＊超级用户已成功登录!\n");
		sleep(1);
		superuser_dis();
		printf("\033[4;103H %s(VIP)\n", msg->name);
		printf("\033[6;103H %d\n", msg->pp_id);
		printf("\033[6;114H%d\n", msg->zan);
		//如果该用户设置过个性签名,则登录时显示该用户设置的个性签名
		if (strcmp("admin", msg->signer) != 0)
		{
		    printf("\033[8;95H                       \n");
                    printf("\033[8;95H %s\n", msg->signer);
		}
		break;
	    }
	    
	    /* 当服务器返回登录出错的动作时 */
	    case LOGINFAIL:
	    {
		printf("\033[25;45H                                                     \n");
		printf("\033[25;45H＊您的帐号已经在别的地方登录！\n");
		printf("\033[14;63H                     \n");
		printf("\033[17;63H                     \n");
		break;
	    }

	    /* 当服务器返回登录ID出错动作 */
            case USERIDERROR:
	    {
		printf("\033[25;45H                                                     \n");
		printf("\033[25;45H＊您输入的ID号有错误!\n");
		printf("\033[14;63H                     \n");
		printf("\033[17;63H                     \n");
		break;
	    }
	    
	    /* 当服务器返回登录密码出错动作 */
	    case USERPASSERR:
	    {
		printf("\033[25;45H                                                     \n");
		printf("\033[25;45H＊您输入的密码错误!\n");
		printf("\033[14;63H                     \n");
		printf("\033[17;63H                     \n");
		break;
	    }
	    
	    /* 当服务器返回注册动作 */
	    case REGIST:
	    {
		printf("\033[25;45H                                                     \n");
                printf("\033[25;45H＊welcome to PP_ONLINE,you ppid is %d\n", msg->pp_id);
		break;
	    }
	    
	    /* 当服务器返回查看在线好友信息 */
	    case DIS_ONLINE_USER:
	    {
		/* 如果重新执行查询命令则清除显示好友区域 */
		if (count == 0)
		{
		    printf("\033[10;86H                                   \n");
		    printf("\033[11;86H                                   \n");
		    printf("\033[12;86H                                   \n");
		    printf("\033[13;86H                                   \n");
		    printf("\033[14;86H                                   \n");
		    printf("\033[15;86H                                   \n");
		    printf("\033[16;86H                                   \n");
	 	    printf("\033[17;86H                                   \n");
		}

		count++;
		/* 收到查看好友结束命令则清0计数 */
		if (msg->action == DIS_SUCCESS)
		{
		    count = 0;
		}

		printf("\033[10;86H＊在线好友如下:\n");
		if (count == 1)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[11;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[11;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[11;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[11;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 2)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[12;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[12;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[12;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[12;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 3)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[13;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[13;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[13;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[13;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 4)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[14;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[14;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[14;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[14;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 5)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[15;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[15;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[15;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[15;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 6)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[16;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[16;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[16;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[16;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 7)
		{
		    if (msg->pp_id == msg->to_id)
		    {
		        printf("\033[17;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[17;102H＊PPID:%d(自己)\n", msg->to_id);
		    }
		    else
		    {
		        printf("\033[17;86H＊NAME:%s\n", msg->to_name);
		        printf("\033[17;102H＊PPID:%d\n", msg->to_id);
		    }
		}
		else if (count == 8)
		{
		    count = 0;
                    printf("\033[18;86H＊您的好友已达上限!\n");
		}
		break;
	    }
	    
	    /* 当服务器返回私聊信息时 */
	    case CHATONE:
	    {
		clear_min();

		if (msg->activity == 1)
		{
		    printf("\033[6;15H＊%s 对你发送表情:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    msg->activity = 0;
		    fflush(stdout);
		    
		    break;
		}
		else if (msg->activity == 2)
                {

		    printf("\033[6;15H＊%s 对你发送短语:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    msg->activity = 0;
		    fflush(stdout);
		    
                    break;
		}
		else
		{
		    printf("\033[5;15H＊%s 悄悄对你说:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    fflush(stdout);
		    break;
		}
	    }
	    
	    /* 当服务器返回私聊用户不存在信息时 */
	    case CHATONEFAIL:
	    {
		clear_min();
		printf("\033[5;15H＊您想要私聊的用户不存在/已下线\n");
		break;
	    }

	    /* 当服务器返回群聊信息时 */
	    case CHATALL:
	    {
		clear_min();
		if (msg->activity == 1)
		{
		    printf("\033[6;15H＊%s 发送表情:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    msg->activity = 0;
		    fflush(stdout);
		    break;
		}
		else if (msg->activity == 2)
		{
		    printf("\033[6;15H＊%s 发送短语:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    msg->activity = 0;
		    fflush(stdout);
                    break;
		}
		else
		{
		    printf("\033[5;15H＊%s 对大家说:%s", msg->name, msg->msg);
		    printf("\033[28;72H");
		    fflush(stdout);
		    break;
		}
	    }
	    
	    /* 当服务器返回禁言信息时 */
	    case SLENCE:
	    {
		clear_min();
		printf("\033[5;15H＊您已被禁言，不能发言!");
		printf("\033[28;72H");
		fflush(stdout);

		break;
	    }
	    
	    /* 当服务器返回禁言成功消息给VIP时 */
	    case SLENCESUCCESS:
	    {
		clear_min();
		printf("\033[6;15H该用户已经成功被禁言！\n");
		printf("\033[29;0H\n");
		break;
	    }
	    
	    /* 当服务器返回已经禁言的信息时 */
	    case SLENCEALREADY:
	    {
		clear_min();
		printf("\033[5;15H＊该用户已经被禁言过了!\n");
		printf("\033[29;0H\n");
		break;
	    }
	    
	    /* 当服务器返回禁言用户不在线时 */
	    case SLENCEFAIL:
	    {
		clear_min();
		printf("\033[6;15H＊您想禁言的用户不存在/已下线，谢谢\n");
		printf("\033[29;0H\n");
		break;
	    }
	    
	    /* 当服务器返回解禁信息时 */
	    case PERMITE:
	    {
		clear_min();
		printf("\033[5;15H＊您已被解禁，可以发言了哦!");
		printf("\033[28;72H");
		fflush(stdout);
		break;
	    }
	    
	    /* 当服务器返回解禁成功消息给VIP时 */
	    case PERMITESUCCESS:
	    {
		clear_min();
		printf("\033[6;15H＊该用户已经成功被解禁！\n");
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回已经解禁的信息时 */
	    case PERMITEALREADY:
	    {
		clear_min();
		printf("\033[5;15H(^_^)该用户已经被解禁过了!\n");
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回解禁用户不存在时 */
	    case PERMITEFAIL:
	    {
		clear_min();
		printf("\033[6;15H＊您想解禁的用户不存在/已下线，谢谢\n");
		break;
	    }
	    
	    /* 当服务器返回踢人成功信息时 */
	    case TICKSUCCESS:
	    {
		clear_min();
		printf("\033[5;15H＊(*_*)很抱歉,您被管理员踢下线了\n");
		printf("\033[6;20H＊请重新登录!\n");
		printf("\033[30;45H\n");
		sleep(2);
		exit(0);
		break;
	    }

	    /* 当服务器返回踢人成功消息给VIP时 */
	    case TICKOK:
	    {
		clear_min();
		printf("\033[6;15H＊该用户已经成功被踢下线\n");
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回踢人失败信息时 */
	    case TICKFAIL:
	    {
		clear_min();
		printf("\033[6;15H＊你想要踢出的好友不存在/已下线,谢谢\n");
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回查找密保问题信息时 */
	    case FIND_PASSPRO:
	    {
		printf("\033[18;47H                          \n");
		printf("\033[18;52H%s?\n",msg->passpro);
		break;
	    }
	    /* 当服务器返回密保答案错误时 */
	    case PASSKEY_ERROR:
	    {
		printf("\033[20;52H                         \n");
		printf("\033[22;51H                         \n");
		printf("\033[22;51H＊密保答案错误，请重试\n");
		break;
	    }
	    /* 当服务器返回修改密码成功时*/
	    case RESET_SUCCESS:
	    {
		printf("\033[20;52H                         \n");
		printf("\033[22;51H                         \n");
		log_dis2();
		printf("\033[26;45H＊密码修改成功!");
		printf("\033[28;72H");
		fflush(stdout);
		break;
	    }
	    
	    /* 当服务器返回订制VIPok时 */
	    case VIPMEMBER:
	    {
		clear_min();
         
		printf("\033[4;103H %s(VIP)\n", msg->to_name);
		printf("\033[18;16H＊禁言(NOS)     ＊解禁(CAS)     ＊踢人(OUT)\n");
		printf("\033[29;0H\n");
		break;
	    }
	    
	    /* 当服务器返回设置个性签名时 */
	    case SETSIGNER:
	    {
                printf("\033[14;14H        ＊恭喜您,您的个性已成功到帐＊    \n");
		printf("\033[8;95H                        \n");
                printf("\033[8;95H %s\n", msg->signer);
                sleep(1);
	        
		clear_min();
		printf("\033[29;0H\n");
		break;
	    }
            
	    case DIANZANFAIL:
	    {
		clear_min();

		printf("\033[6;14H    ＊您要赞的好友不存在或已下线\n");
		break;
	    }
             
	    case DIANZAN:
	    {
                clear_min();
		printf("\033[6;14H    ＊好友%s对你点赞  +1 ", msg->name);
		printf("\033[6;114H     ");
		printf("\033[6;114H%d", msg->zan);
		printf("\033[28;72H");
		fflush(stdout);

		break;
	    }

	    /* 服务器返回私聊和自己时 */
	    case CHATONETOSELF:
	    {
		printf("\033[6;14H    ＊对不起，您不能和自己聊天!\n");
		sleep(1);
		clear_min();
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回发送文件失败时 */
	    case SENDFILE_ERROR:
	    {
		printf("\033[11;14H                                        \n");
		printf("\033[11;14H    ＊好友%d不存在或者已下线！\n", msg->to_id);
		sleep(1);

		clear_min();
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回发送文件给自己时 */
	    case SENDFILETOSELF:
	    {
		printf("\033[11;14H    ＊不可以发送文件给自己\n");
		sleep(1);
		clear_min();
		printf("\033[29;0H\n");
		break;
	    }

	    /* 当服务器返回发送文件时 */
	    case SENDFILE:
	    {	
		file_recv(msg);
		break;
	    }
	    /* 查看聊天记录 */
	    case DISJILU:
	    {
		int j = 0;
		int count = 0;
		char *ptr = msg->filemsg;
		char *sub = msg->filemsg;
		char *pna = msg->name;
		char *src;
		char name[20];
		char action[20];
		char to_name[20];
		char msg[300];
		char time[50];
		char recvbuf[2048];
		//解析接收到的数据
		//然后显示
		clear_min();      
		printf("\033[5;14H                   ＊聊天记录＊         \n");
	        while(*sub != '\0')
		{
		    if (*sub == '$')
		    {
			*sub = '\0';
			strcpy(recvbuf, ptr);
			ptr = ptr + strlen(recvbuf) + 2;
                        //对一个聊天记录进行解析
			src = recvbuf;
			while (*src != '#')
			{
			    name[j++] = *src;
			    src++;
			}
			name[j] = '\0';
			j = 0;
			src++;
			while (*src != '#')
			{
			    action[j++] = *src;
			    src++;
			}
			action[j] = '\0';
			j = 0;
			src++;
			while (*src != '#')
			{
			    to_name[j++] = *src;
			    src++;
			}
			to_name[j] = '\0';
			j = 0;
			src++;
			while (*src != '#')
			{
			    msg[j++] = *src;
			    src++;
			}
			msg[j] = '\0';
			j = 0;
			src++;
			while (*src != '\0')
			{
			    time[j++] = *src;
			    src++;
			}
			time[j] = '\0';
			j = 0;
                        //如果这条聊天记录和该用户有关则显示
			if ((strcmp(pna, name) == 0) || (strcmp(pna, to_name) == 0))                                  
			{
			    count++;
			    if (strcmp(action, "CHATONE") == 0)
			    {
				switch(count)
				{
				    case 1: 
				    {
					printf("\033[6;14HTIME:%s", time);
					printf("\033[7;14H%s对%s悄悄说:%s", name, to_name, msg);
					break;
				    }
				    case 2:
				    {
					printf("\033[8;14HTIME:%s", time);
					printf("\033[9;14H%s对%s悄悄说:%s", name, to_name, msg);
					break;
				    }
				    case 3:
				    {
					printf("\033[10;14HTIME:%s", time);
					printf("\033[11;14H%s对%s悄悄说:%s", name, to_name, msg);
					break;
				    }
				    case 4: 
				    {
					printf("\033[12;14HTIME:%s", time);
					printf("\033[13;14H%s对%s悄悄说:%s", name, to_name, msg);
					break;
				    }
				    case 5: 
				    {
					printf("\033[14;14HTIME:%s", time);
					printf("\033[15;14H%s对%s悄悄说:%s", name, to_name, msg);
					break;
				    }
			            default: 
			            {
					count = 0;
					sleep(2);
					clear_min();
					break;
				    }
				}
				fflush(stdout);
			    }
			    else if (strcmp(action, "CHATALL") == 0)
			    {
				switch(count)
				{
				    case 1:
				    {
					printf("\033[6;14HTIME:%s", time);
					printf("\033[7;14H%s对大家说:%s", name, msg);
					break;
				    }
				    case 2: 
				    {
					printf("\033[8;14HTIME:%s", time);
					printf("\033[9;14H%s对大家说%s", name, msg);
					break;
				    }
				    case 3: 
				    {
					printf("\033[10;14HTIME:%s", time);
					printf("\033[11;14H%s对大家说%s", name, msg);
					break;
				    }
				    case 4: 
				    {
					printf("\033[12;14HTIME:%s", time);
					printf("\033[13;14H%s对大家说%s", name, msg);
					break;
				    }
				    case 5: 
				    {
					printf("\033[14;14HTIME:%s", time);
					printf("\033[15;14H%s对大家说%s", name, msg);
					break;
				    }
			            default: 
			            {
					count = 0;
					sleep(2);
					clear_min();
					break;
				    }
				}
				fflush(stdout);
			    }
			}
		    }
		    sub++;
		}
		printf("\033[28;72H");
		fflush(stdout);
		break;
	    }
	}
    }
}



   
