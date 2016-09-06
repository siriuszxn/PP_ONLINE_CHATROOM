/*********************************************************
-  Copyright (C): 2016
-  File name    : server_thread.c
-  Author       : - Zhao -
-  Date         : 2016年01月29日 星期五 17时22分05秒
-  Description  : 服务器的线程的处理函数
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

void server_read_msg(void *arg)
{
    int ret;                  //用来接受返回值
    int from_fd;              //聊天记录文件描述符
     
    int fd = *((int *)arg);   

    struct _Message *msg = (struct _Message *)malloc(sizeof(struct _Message));
    if (msg == NULL)
    {
	printf("server_msg_read msg malloc error!\n");
	exit(1);
    }

    int n_read;
    int n_write;

    /* 打开数据库 */
    if (SQLITE_OK != sqlite3_open("PP_user.db", &db))
    {
	fprintf(stderr, "Cannot open database:%s\n", sqlite3_errmsg(db));
	sqlite3_close(db);
	exit(1);
    }
    /* 打开聊天记录文件,如果不存在则创建它,且每次可以自动在后面添加 */
    /*if ((from_fd = open("MsgEx.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
    {
	fprintf(stderr, "Open %s Error:%s\n", "MsgEx.txt", strerror(errno));
	exit(1);
    }*/

    while (1)
    {
	memset(msg, 0, sizeof(struct _Message));
	printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
	n_read = read(fd, msg, sizeof(struct _Message));


        /* 打开聊天记录文件,如果不存在则创建它,且每次可以自动在后面添加 */
        if ((from_fd = open("MsgEx.txt", O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR)) == -1)
        {
	    fprintf(stderr, "Open %s Error:%s\n", "MsgEx.txt", strerror(errno));
	    exit(1);
        }

	//如果客户端ctrl+c退出，则服务器将该用户踢下线
	if (msg->action == BACK_LOGMENU)
	{
	    n_read = 0;
	}
	printf("n_read = %d\n",n_read);
	if (n_read == 0)
	{
	    struct online* exit_fd1 = head;
	    struct online* exit_fd2 = exit_fd1;
	    /* 定位要删除的节点 */
	    while (exit_fd1 != NULL)
	    {
		if (exit_fd1->online_fd == fd)
                {
                    if (exit_fd1 == head)
		    {
			head = exit_fd1->next;
		    }
		    else
		    {
			exit_fd2->next = exit_fd1->next;
		    }
		    free(exit_fd1);
		    exit_fd1 = NULL;
		    break;

		}
		exit_fd2 = exit_fd1;
	        exit_fd1 = exit_fd1->next;
            }

	    close(fd);
	    pthread_exit(NULL);
	}

	printf("server_read msg->action = %d\n", msg->action);
	switch(msg->action)
	{
	    /* 如果读到登录命令 */
	    case LOGIN:
	    {   
                struct online *login = head;
		int n_write;
		//通过客户传过来的结构体信息
		//到数据库中寻找ID,检查输入密码是否正确
		printf("____________85_____________\n");
		printf("msg->pp_id = %d\n", msg->pp_id);
		ret = check_passwd_inbase(db, msg->pp_id, msg->passwd);
		
		printf("ret = %d\n", ret);
		//ID号输入错误
		if (ret == USERIDERROR)
		{
                    msg->flag = USERIDERROR;

		    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("The USERIDERROR write to client error!\n");
			exit(1);
		    }
		}
		//密码输入错误
		else if (ret == USERPASSERR)
		{
		    msg->flag = USERPASSERR;
		    
		    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("The USERPASSERR write to client error!\n");
			exit(1);
		    }

		}
		else if (ret == SUCCESS)
		{
                    while (login != NULL && (login->online_id != msg->pp_id))
		    {
			login = login->next;
		    }
		    //如果登录的账户已经在线，则返回登录失败的信息，不能重复登录
		    if (login != NULL && (login->online_id == msg->pp_id))
		    {
			msg->flag = LOGINFAIL;
			n_write = write(fd, msg, sizeof(struct _Message));
			if (n_write == -1)
			{
			    printf("The loginfail write error!\n");
			    exit(1);
			}
			break;
		    }
		    /*
		       否则登录成功，为新用户分配节点并且加入链表
		                                                   */
		    //根据ID查找出用户昵称
                    find_logname_inbase(db, msg);
                    /* 为新节点分配空间 */
                    new_user = (struct online *)malloc(sizeof(struct online));
		    if (new_user == NULL)
                    {
                        printf("new_user malloc error!\n");
	                exit(1);
                    }
                    memset(new_user, 0, sizeof(struct online));
		    //然后将新的在线用户结点插入链表
		    new_user->online_flag = 1;
		    new_user->online_fd = fd;
		    new_user->online_id = msg->pp_id;
		    strcpy(new_user->online_name, msg->name);
		    new_user->next = head;
		    head = new_user;
                 
		    n_write = write(fd, msg, sizeof(struct _Message));
		    printf("insert ask n_write = %d\n",n_write);
		    if (n_write == -1)
		    {
			printf("The insert_user write to client error!\n");
			exit(1);
		    } 
		}
		break;
	    }
	    
	    /* 如果读到注册命令 */
	    case REGIST:
	    {
		while (1)
		{
		    /* 使用随机数函数获得随即PP号 */
                    msg->pp_id = rand_brith_id();
		    printf("msg->pp_id rand is %d\n", msg->pp_id);
		    //将id传入数据库查找是否有重复,-1代表有重复,0代表ID可用
		    ret = find_id_inbase(db, msg->pp_id);
		    printf("find_id_inbase ret = %d", ret);
                    if (0 == ret) 
		    {
			/* 判断随即pp号无重复,则把用户信息写入数据库 */
                        insert_user_to_ppbase(db, msg);
			break;
		    }
		}
		//服务器动作记录,表示返回信息为注册
		msg->flag = REGIST;
		/* 将结构体信息发回客户端 */
		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("the server REGIST write to client error!\n");
		    exit(1);
		}

		break;
	    }
	    
	    /* 如果读到查看在线好友命令 */
	    case DIS_ONLINE_USER:
	    {
		printf("--------------查看在线好友------------------\n");
		struct online *dis = head;
		/* 遍历在线好友链表实现，将在线好友的ID和姓名依次写回客户端 */
		while (dis != NULL)
		{
		    msg->to_id = dis->online_id;
		    strcpy(msg->to_name, dis->online_name);
		    msg->flag = DIS_ONLINE_USER;
                    
		    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("write dis_online_user error!\n");
			exit(1);
		    }
		    //sleep(1);
                    dis = dis->next;
		}
		msg->action = DIS_SUCCESS;
		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("DIS_USER_SUCESS_WRITE error!\n");
		    exit(1);
		}

		break;
	    }
	    
	    /* 如果读到私聊命令 */
	    case CHATONE:
	    {
		int i;
		int j;
		int check = 0;
		int bytes_write;
		int bytes_read;

		char *ptr;
		char timew[30] = {0};
		char chatbuffer[1024];
		
		time_t timewrite;
		time(&timewrite);
		strcpy(timew, asctime(gmtime(&timewrite)));

		struct online *chartone = head;
                printf("****************CHATONE******************\n");
		msg->flag = CHATONE;
		//找到发起聊天的用户的name
		while(chartone != NULL)
		{
		    if (chartone->online_fd == fd)
		    {
		        memset(msg->name, 0, sizeof(msg->name));
	                strcpy(msg->name, chartone->online_name);
			if (chartone->online_id == msg->to_id)
			{
			    msg->flag = CHATONETOSELF;
			    check = 1;
			}
			break;
		    }
		    chartone = chartone->next;
		}
		if (check == 1)
		{
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
		        printf("write chatonetoself error!\n");
		        exit(1);
		    }
		    break;
		}
		//如果私聊用户自己被禁言则
		if (chartone->online_flag == 0)
		{
		    msg->flag = SLENCE;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write chartone self slence error!\n");
			exit(1);
		    }
		    break;
		}

		chartone = head;
		//定位私聊用户
		while((chartone != NULL) && (msg->to_id != chartone->online_id))
		{
                    chartone = chartone->next;
		}
		//如果私聊用户不存在则返回信息给发起聊天的人
		if (chartone == NULL)
		{
		    msg->flag = CHATONEFAIL;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write dis_online_user error!\n");
			exit(1);
		    }
		    break;
		}
		//如果在在线链表中找到用户输入匹配ID,并且该用户没有被禁言
                if ((msg->to_id == chartone->online_id) && (chartone->online_flag == 1))
		{
		    //则把数据包转发给对方用户
		    memset(msg->to_name, 0, sizeof(msg->to_name));
	            strcpy(msg->to_name, chartone->online_name);

                    for (i = 0; i <= 10; i++)
		    {
			ptr = chatbuffer;
		        memset(chatbuffer, 0, 1024);
                        switch(i)
			{
			    case 0:
			    {
		                strcpy(chatbuffer, msg->name);
				break;
			    }
			    case 1:
			    {
		                strcpy(chatbuffer, "#");
				break;
			    }
			    case 2:
			    {
		                strcpy(chatbuffer, "CHATONE");
				break;
			    }
			    case 3:
			    {
		                strcpy(chatbuffer, "#");
				break;
			    }
			    case 4:
			    {
		                strcpy(chatbuffer, msg->to_name);
				break;
			    }
			    case 5:
			    {
		                strcpy(chatbuffer, "#");
				break;
			    }
			    case 6:
			    {
		                strcpy(chatbuffer, msg->msg);
				break;
			    }
			    case 7:
			    {
		                strcpy(chatbuffer, "#");
				break;
			    }
			    case 8:
			    {
		                strcpy(chatbuffer, timew);
				for (j = 0; chatbuffer[j] != '\n'; j++)
				{
				    ;
				}
				chatbuffer[j] = '\0';
				break;
			    }
			    case 9:
			    {
		                strcpy(chatbuffer, "$");
				break;
			    }
			    case 10:
			    {
				strcpy(chatbuffer, "\n");
				break;
			    }
			}
			bytes_read = strlen(chatbuffer);
		        while ((bytes_write = write(from_fd, chatbuffer, bytes_read)))
		        {
			    if ((bytes_write == -1) && (errno != EINTR))
			    {
			        break;
			    }
			    else if (bytes_write == strlen(msg->name))
		            {
			        //写完了所有字节,继续写下一个数据,数据之间已#分隔
			        break;
			    }
			    else if (bytes_write > 0)
			    {
                                ptr += bytes_write;
			        bytes_read -= bytes_write;
			    }
		        }
		    }
		    close(from_fd);
		    
                    n_write = write(chartone->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
		        printf("write dis_online_user error!\n");
		        exit(1);
		    }
		    break;
		}
	    }
	    
	    /* 如果读到群聊命令 */
	    case CHATALL:
	    {
		printf("---------------CHATALL---------------------\n");
		int i;
		int j;
		int check = 0;
		int bytes_write;
		int bytes_read;

		char *ptr;
		char timew[30] = {0};
		char chatbuffer[1024];
		
		time_t timewrite;
		time(&timewrite);
		strcpy(timew, asctime(gmtime(&timewrite)));
		
		struct online *chartall = head;
		msg->flag = CHATALL;
		
                //遍历链表，先找到自己判断自己有没有被禁言，如果被禁言则跳出case
	        while (chartall != NULL)
		{
		    if (chartall->online_fd == fd)
		    {
		        //找到发起聊天的用户的name
	                strcpy(msg->name, chartall->online_name);
			
			if (chartall->online_flag == 0)
			{
		            msg->flag = SLENCE;
                            n_write = write(fd, msg, sizeof(struct _Message));
		            if (n_write == -1)
		            {
			        printf("write slence error!\n");
			        exit(1);
		            }
			    check = 1;
			    break;
			}
		    }
		    chartall = chartall->next;
		}
		if (check == 1)
		{
		    break;
		}
		
                //循环将数据写入文件
                for (i = 0; i <= 10; i++)
		{
		    ptr = chatbuffer;
		    memset(chatbuffer, 0, 1024);
                    switch(i)
		    {
		        case 0:
		        {
		            strcpy(chatbuffer, msg->name);
		            break;
			}
	                case 1:
	   	        {
		            strcpy(chatbuffer, "#");
		            break;
			}
			case 2:
			{
		            strcpy(chatbuffer, "CHATALL");
		            break;
			}
			case 3:
			{
		            strcpy(chatbuffer, "#");
		            break;
			}
			case 4:
			{
		            strcpy(chatbuffer, "大家");
		            break;
			}
			case 5:
			{
		            strcpy(chatbuffer, "#");
		            break;
			}
	                case 6:
		        {
	                    strcpy(chatbuffer, msg->msg);
	         	    break;
			}
			case 7:
			{
		            strcpy(chatbuffer, "#");
			    break;
			}
			case 8:
			{
		            strcpy(chatbuffer, timew);
		            for (j = 0; chatbuffer[j] != '\n'; j++)
			    {
			        ;
			    }
			    chatbuffer[j] = '\0';
		            break;
			}
			case 9:
			{
		            strcpy(chatbuffer, "$");
	   		    break;
			}
			case 10:
			{
			    strcpy(chatbuffer, "\n");
			    break;
			}
	            }
	            bytes_read = strlen(chatbuffer);
		    while ((bytes_write = write(from_fd, chatbuffer, bytes_read)))
		    {
		        if ((bytes_write == -1) && (errno != EINTR))
		        {
	    	            break;
			}
			else if (bytes_write == strlen(msg->name))
		        {
	           	    //写完了所有字节,继续写下一个数据,数据之间已#分隔
		            break;
	   	        }
			else if (bytes_write > 0)
			{
                            ptr += bytes_write;
			    bytes_read -= bytes_write;
			}
		    }
		}
		close(from_fd);
		
		chartall = head;
		while (chartall != NULL)
		{
		    //如果是本人群发，则自己不发送
                    if (chartall->online_fd == fd)
		    {
                        chartall = chartall->next;
			continue;
		    }

		    //其他在线用户全部发送!
                    n_write = write(chartall->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			 printf("write chartall error!\n");
			 exit(1);
		    }

                    chartall = chartall->next;
		}
		break;
	    }
	    
	    /* 如果读到查找密保命令 */
	    case FIND_PASSPRO:
	    {
                printf("__________________查找密保问题___________________\n");
                //根据msg->PP_ID 到数据库中查找密保问题
		//然后将密保问题写回客户机
		msg->flag = FIND_PASSPRO;
		find_passpro_inbase(db, msg);
		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("write passpro error!\n");
		    exit(1);
		}
		break;
	    }

	    /* 如果读到修改密码命令 */
	    case RESET_PASSWD:
	    {
		struct online *resok1 = head;
		struct online *resok2 = resok1;
		
		printf("_________________修改密码___________________\n");
		//在数据库中比对密保问题回答是否正确
		//如果正确则修改密码，并将成功修改信息写客户机
		//如果密保问题回答不正确则返回信息给客户机
                find_passkey_inbase(db, msg);
		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("write passkey error!\n");
		    exit(1);
		}
		//如果该用户修改密码成功，则下线
		if (msg->flag == RESET_SUCCESS)
		{
		
		    /* 定位要删除的节点 */
		    while ((resok1 != NULL) && (resok1->online_id != msg->pp_id))
		    {
		        resok2 = resok1;
		        resok1 = resok1->next;
		    }
		    //修改密码的用户不在线
		    if (resok1 == NULL)
		    {
		        break;
		    }
		
                    //修改密码的用户在线则强制下线，踢出
		    if (resok1->online_id == msg->pp_id)
		    {
		        if (resok1 == head)
		        {
			    head = resok1->next;
		        }
		        else
		        {
                            resok2->next = resok1->next;
		        }
		        free(resok1);
		        resok1 = NULL;
		        break;
		    }
		}
                break;
	    }
	    
	    /* 如果读到禁言命令 */
	    case SLENCE:
	    {
		printf("------------禁言--------------\n");
		struct online *slence = head;
		while (slence != NULL && slence->online_id != msg->to_id)
		{
		    slence = slence->next;
		}
		if (slence == NULL)
		{
		    //发送禁言用户不存在/已下线消息给VIP用户
		    msg->flag = SLENCEFAIL;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write tickfail error!\n");
	                exit(1);
		    }
		    break;
		}
		//如果该用户已经被禁言则不能再次禁言
		if (slence->online_flag == 0)
		{
	            msg->flag = SLENCEALREADY;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write fermite error!\n");
	                exit(1);
		    }
                    break;
		}
		//如果当前在线的用户ID与输入的ID相同,则禁言它
		if (slence->online_id == msg->to_id)
	        {
		    slence->online_flag = 0;
		    //发送禁言消息给被禁言的用户
                    msg->flag = SLENCE;
                    n_write = write(slence->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
		        printf("write slence error!\n");
		        exit(1);
	   	    } 
		    //发送禁言成功消息给VIP用户
	            msg->flag = SLENCESUCCESS;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
		        printf("write slence error!\n");
		        exit(1);
	            } 
		}
		break;
	    }
	    
	    /* 如果读到解禁命令 */
	    case PERMITE:
	    {
		printf("----------------------解禁-------------------\n");
		struct online *permite = head;
                
		while (permite != NULL && permite->online_id != msg->to_id)
		{
		    permite = permite->next;
		}
	
		if (permite == NULL)
		{
		    printf("asdfasdf\n");
		    //发送解禁不存在给消息给解禁VIP
		    msg->flag = PERMITEFAIL;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write permintefail error!\n");
	                exit(1);
		    }
		    break;
		}
		//如果该用户已经解禁则不能再次解禁
		if (permite->online_flag == 1)
		{
		    msg->flag = PERMITEALREADY;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write fermite error!\n");
	                exit(1);
		    }
                    break;
		}
		//如果当前在线的用户ID与输入的ID相同,则解禁它
		if (permite->online_id == msg->to_id)
		{
		    //发送解禁消息给被解禁的用户
		    msg->flag = PERMITE;
		    permite->online_flag = 1;
                    n_write = write(permite->online_fd, msg, sizeof(struct _Message));
                    if (n_write == -1)
                    {
	                printf("write fermite error!\n");
                        exit(1);
		    }
		    //发送解禁成功的消息给解禁VIP用户
		    msg->flag = PERMITESUCCESS;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
	            {
	                printf("write fermite error!\n");
	                exit(1);
	            }
		}
		break;
	    }
	    
	    /* 如果读到踢人命令 */
	    case TICK:
	    {
		printf("____________________踢人_____________________\n");
		struct online *tick1 = head;
		struct online *tick2 = tick1;
		/* 定位要删除的节点 */
		while ((tick1 != NULL) && (tick1->online_id != msg->to_id))
		{
		    tick2 = tick1;
		    tick1 = tick1->next;
		}
		if (tick1 == NULL)
		{
		    
		    //发送踢人不存在给消息给踢人VIP
		    msg->flag = TICKFAIL;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write tickfail error!\n");
	                exit(1);
		    }
		    break;
		}
		
                /* 如果找到要删除的节点 */
		if (tick1->online_id == msg->to_id)
		{
                    //发送踢人消息给被踢的用户
		    msg->flag = TICKSUCCESS;
                    n_write = write(tick1->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write ticksuccess error!\n");
	                exit(1);
		    }
		    //发送踢人成功的消息给踢人VIP
		    msg->flag = TICKOK;
                    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
	                printf("write ticksuccess error!\n");
	                exit(1);
		    }
		    if (tick1 == head)
		    {
			head = tick1->next;
		    }
		    else
		    {
                        tick2->next = tick1->next;
		    }
		    free(tick1);
		    tick1 = NULL;
		    break;
		}
	    }

	    /* 如果读到注册会员 */
	    case VIPMEMBER:
	    {
		printf("_________________注册会员___________________\n");
                //首先,根据注册的fd找到ID号,和姓名
		struct online *vipmember = head;
		while(vipmember != NULL)
		{
		    if (vipmember->online_fd == fd)
		    {
			strcpy(msg->to_name, vipmember->online_name);
			msg->pp_id = vipmember->online_id;
			break;
		    }
		    vipmember = vipmember->next;
		}
		//通过ID号在数据库中将vip_flag 改为 1
		//设置msg->flag = VIPMENBER
		set_vipflag_inbase(db, msg);
		msg ->flag = VIPMEMBER;

		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("write vipmember error!\n");
		    exit(1);
		}

		break;
	    }

	    /* 如果读到设置个性签名 */
	    case SETSIGNER:
	    {
		printf("________________设置个性签名___________________\n");
                //首先,根据注册的fd找到ID号,和姓名
		struct online *setsigner = head;
		while(setsigner != NULL)
		{
		    if (setsigner->online_fd == fd)
		    {
			msg->pp_id = setsigner->online_id;
			break;
		    }
		    setsigner = setsigner->next;
		}
		//通过ID号更新数据库中的个性签名
		//设置msg->flag为SETSIGNER
		update_signer_inbase(db, msg);
		msg->flag = SETSIGNER;

		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
		    printf("write vipmember error!\n");
		    exit(1);
		}
		break;
	    }
	    /* 如果读到点赞 */
	    case DIANZAN:
	    {
		printf("________________点赞___________________\n");
                //首先,根据注册的fd找到ID号,和姓名
		struct online *dianzan = head;
		while (dianzan != NULL)
		{
		    if (dianzan->online_fd == fd)
		    {
			strcpy(msg->name, dianzan->online_name);
			break;
		    }
		    dianzan = dianzan->next;
		}
		dianzan = head;

		while (dianzan  != NULL && dianzan->online_id != msg->to_id)
		{
		    dianzan = dianzan->next;
		}
		if (dianzan == NULL)
		{
		    msg->flag = DIANZANFAIL;
		    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("write dianzan  error!\n");
		    }
		    break;
		}
		if (dianzan->online_id == msg->to_id)
		{
		    update_zan_inbase(db, msg);
		    msg->flag = DIANZAN;

		    n_write = write(dianzan->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("write dianzan error!\n");
			break;
		    }
		}
		break;
	    }

	    /* 如果读到文件传输 */
	    case SENDFILE:
	    {
                printf("____________________文件传输___________________\n");
		//如果读到文件传输，则先根据对方ID判断该用户是否在线
		//如果该用户在线的话，则将该msg转发给该用户
		struct online *sendfile = head;
		//根据fd获得发送方用户的姓名
		while ((sendfile != NULL) && (sendfile->online_fd != fd))
		{
		    sendfile = sendfile->next;
		}
		if (sendfile == NULL)
		{
		    printf("sendfile server error!\n");
		}
		if (sendfile->online_fd == fd)
		{
		    strcpy(msg->name, sendfile->online_name);
		    //如果是自己发个自己则不能发送
		    if (sendfile->online_id == msg->to_id)
		    {
                        msg->flag = SENDFILETOSELF;

		        n_write = write(fd, msg, sizeof(struct _Message));
		        if (n_write == -1)
		        {
			    printf("write to fd sendfileerror\n");
			    exit(1);
		        }
			break;
	            }
		}

		sendfile = head;
                //遍历在线用户链表找到接受方好友ID
		while ((sendfile != NULL) && (sendfile->online_id != msg->to_id))
		{
		    sendfile = sendfile->next;
		}
		//该用户不存在或者已经下线
		if (sendfile == NULL)
		{
		    msg->flag = SENDFILE_ERROR;

		    n_write = write(fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("write to fd sendfileerror\n");
			exit(1);
		    }
		    break;
		}
		//该用户在线，则将数据包直接转发给该用户
		if (sendfile->online_id == msg->to_id)
		{
                    msg->flag = SENDFILE;
                    printf("%s\n", msg->filemsg);
		    n_write = write(sendfile->online_fd, msg, sizeof(struct _Message));
		    if (n_write == -1)
		    {
			printf("write to fd sendfileerror\n");
			exit(1);
		    }
		}
		break;
	    }
	    /////////////////
	    /* 查看聊天记录 */
	    case DISJILU:
	    {
		int i = 0;
		int count = 0;
		int to_fd;
		int bytes_read;

		struct online *disjilu = head;
		//找到该用户的姓名
		while (disjilu != NULL)
		{
		    if (fd == disjilu->online_fd)
		    {
                        strcpy(msg->name, disjilu->online_name);
			break;
		    }
		    disjilu = disjilu->next;
		}

		if ((to_fd = open("MsgEx.txt", O_RDONLY)) == -1)
		{
		    fprintf(stderr, "Open %s Error:%s\n", "MsgEx.txt", strerror(errno));
		    exit(1);
		}

                while ((bytes_read = read(to_fd, msg->filemsg, 2048)))
		{
		    if ((bytes_read == -1) && (errno != EINTR))
		    {
			printf("查看聊天记录异常！\n");
			break;
		    }
		}
		while (msg->filemsg[i++] != '\0')
		{
		    count++;
		}
		msg->count = count;
		close(to_fd);
                msg->flag = DISJILU;

		n_write = write(fd, msg, sizeof(struct _Message));
		if (n_write == -1)
		{
                    printf("write disjilu error!\n");
		    exit(1);
		}

		break;
	    }
	    default:
	    {
		break;
	    }
	}
    }
}
