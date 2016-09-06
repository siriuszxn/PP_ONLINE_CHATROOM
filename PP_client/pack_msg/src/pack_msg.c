/*********************************************************
-  Copyright (C): 2016
-  File name    : pack_msg.c
-  Author       : - Zhao -
-  Date         : 2016年01月30日 星期六 13时22分29秒
-  Description  : 将数据打包
-  input        : 动作action，指向msg的数据结构指针＊msg,
-  output       : 
-  return       : 成功返回0
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

int pack_msg(int action, Message *msg, int sockfd, int msgbytes)
{
    int i;                       
    int n_write;                //实际写入的字节数
    
    char buffer[BUFFSIZE];      //缓冲区
    memset(buffer, 0, BUFFSIZE);

    /* 根据action动作选项选择执行 */
    switch(action)
    {
	/* 当命令为登录 */
	case LOGIN: 
	{
	    printf("\033[14;63H");
	    scanf("%d", &msg->pp_id);

	    /* 获取输入密码 */
	    while (1)
	    {
		memset(buffer, 0, BUFFSIZE);
                printf("\033[25;45H                                            \n");
                printf("\033[17;63H");
	        scanf("%s", buffer);
	
                for (i = 0; buffer[i] != '\0'; i++)
		{
                    msg->passwd[i] = buffer[i];
		}
	        msg->passwd[i] = '\0';

	        break;
	    }
	    break;
	}
	
	/* 当命令为注册时 */
	case REGIST:
	{
	    memset(buffer, 0, BUFFSIZE);
            reg_dis();  //跳到注册界面
            /* 循环，直到用户输入正确的用户名，错误则重新输入 */
	    while (1)
	    {
		printf("\033[10;57H                         \n");
		printf("\033[25;59H                           \n");
                printf("\033[10;57H");
		fgets(buffer, BUFFSIZE, stdin);
		for (i = 0; buffer[i] != '\n'; i++)
		{
		    msg->name[i]= buffer[i];
		}
		if (strlen(buffer) == 1)
		{
		    printf("\033[25;59H＊用户名不可以为空哦!\n");
		    continue;
		}
		if (i >= 20)
		{
		    printf("\033[25;59H＊您输入的用户名过长!\n");
                    continue;
		}
		msg->name[i] = '\0';
		printf("\033[10;85HOK^_^\n");
		break;
	    }
	    char temp[20]; /* 临时变量,用来比较两次密码是否相同 */
	    memset(temp, 0, sizeof(temp));
	    memset(buffer, 0, sizeof(buffer));
	    /* 循环体，检查两次密码输入是否正确 */
            while ((strcmp(msg->passwd, temp) != 0) || (strlen(msg->passwd) == 0))
            {
                while (1)
		{
		    printf("\033[13;57H                      \n");
		    printf("\033[13;57H");
                    fgets(buffer, BUFFSIZE, stdin);
		    printf("\033[25;59H                           \n");
		    for (i = 0; buffer[i] != '\n'; i++)
		    {
			msg->passwd[i] = buffer[i];
		    }
		    if (strlen(buffer) == 1)
		    {
                        printf("\033[25;59H＊密码不能为空哦!\n");
			continue;
		    }
		    if (i >= 20)
		    {
			printf("\033[25;59H＊您输入的密码过长!\n");
			continue;
		    }
		    msg->passwd[i] = '\0';
		    strcpy(temp, msg->passwd);
		    printf("\033[13;85HOK^_^\n");
		    printf("\033[16;57H                    \n");
		    printf("\033[16;57H");

		    memset(buffer, 0, BUFFSIZE);
		    fgets(buffer, BUFFSIZE, stdin);
		    
		    printf("\033[25;59H                        \n");
		    for (i = 0; buffer[i] != '\n'; i++)
		    {
			msg->passwd[i] = buffer[i];
		    }
		    msg->passwd[i] = '\0';
		    if (strcmp(msg->passwd, temp) != 0)
		    {
			printf("\033[25;59H＊两次输入不一致\n");
			printf("\033[16;57H                \n");
		        printf("\033[13;85H      \n");
			continue;
		    }
		    else
		    {
			printf("\033[25;59H＊两次密码比对正确!\n");
		        printf("\033[16;85HOK^_^\n");
		        break;
		    }
		}
	    }
	    /* 循环，输入密保问题，保证格式正确 */
	    memset(buffer, 0, BUFFSIZE);
	    while (1)
	    {
		printf("\033[19;57H                          \n");
                printf("\033[19;57H");
		fgets(buffer, BUFFSIZE, stdin);
		printf("\033[25;59H                          \n");
		for (i = 0; buffer[i] != '\n'; i++)
		{
		    msg->passpro[i]= buffer[i];
		}
		if (strlen(buffer) == 1)
		{
		    printf("\033[25;59H＊密保问题不可以为空哦!\n");
		    continue;
		}
		if (i >= 50)
		{
		    printf("\033[25;59H＊您输入的密保问题过长!\n");
                    continue;
		}
		msg->passpro[i] = '\0';
		printf("\033[19;85HOK^_^\n");
		break;
	    }
	    /* 循环,并且确保密保答案输入正确 */
	    memset(buffer, 0, BUFFSIZE);
	    while (1)
	    {
		printf("\033[22;57H                          \n");
                printf("\033[22;57H");
		fgets(buffer, BUFFSIZE, stdin);
		printf("\033[25;59H                         \n");
		for (i = 0; buffer[i] != '\n'; i++)
		{
		    msg->passkey[i]= buffer[i];
		}
		if (strlen(buffer) == 1)
		{
		    printf("\033[25;59H＊密保答案不可以为空哦!\n");
		    continue;
		}
		if (i >= 20)
		{
		    printf("\033[25;59H＊您输入的密保答案过长!\n");
                    continue;
		}
		msg->passkey[i] = '\0';
		printf("\033[22;85HOK^_^\n");
	        printf("\033[25;50H＊恭喜您注册成功!,正在生成PP号\n");
		printf("\033[26;56H               loading......\n");
		sleep(2);
		log_dis2();
		break;
	    }
            break;
	}
	
	/* 当命令为查看在线好友时 */
	case DIS_ONLINE_USER:
	{
	    msg->action = DIS_ONLINE_USER;
            break;
	}
	
	/* 当命令为私聊时 */
	case CHATONE:
	{
	    msg->to_id = 0;
            msg->action = CHATONE;
	    clear_min();

	    printf("\033[5;15H＊请输入聊天好友ID:");
	    scanf("%d", &msg->to_id);
	    
	    printf("\033[7;15H＊你对%d悄悄说:", msg->to_id);
            scanf("%s", msg->msg); 
	   
	    break;
	}
	
	/* 当命令为群聊时 */
	case CHATALL:
	{
	    msg->action = CHATALL;
	    clear_min();

	    printf("\033[6;15H＊你对大家说:");
	    scanf("%s", msg->msg);
	    break;
	}
	
	/* 当命令为修改密码时 */
	case RESET_PASSWD:
	{
	    memset(buffer, 0, sizeof(buffer));
	    //跳转到安全中心界面
	    rem_passwd();
            //获取需要修改密码的PP号
	    printf("\033[14;53H");
	    scanf("%d", &msg->pp_id);
	    msg->action = FIND_PASSPRO;
	    //根据PP号去数据库中查找该用户的密保问题
            n_write = write(sockfd, msg, msgbytes);
	    //printf("RESET——PASSWD find_passpro write = %d", n_write);
	    if (n_write == -1)
	    {
	        printf("reset_passwd write ppid error!\n");
	        exit(1);
    	    }
            sleep(1);
	    while(1)
	    {
	        //获取密保问题的答案
	        printf("\033[20;53H");
	        scanf("%s", msg->passkey);
		printf("\033[22;51H                           \n");
		if (strlen(msg->passkey) == 1)
		{
		    printf("\033[22;52H＊密保答案不可以为空哦!\n");
		    continue;
	        }
		break;
	    }
	    //获取新设置的PP号密码
            while (1)
	    {
	        printf("\033[16;47H                               \n");
	        printf("\033[18;47H                               \n");
	        printf("\033[18;52H请设置新密码\n");
		printf("\033[20;53H                            \n");
	        memset(buffer, 0, BUFFSIZE);
		printf("\033[20;53H");
                fgets(buffer, BUFFSIZE, stdin);
	        for (i = 0; buffer[i] != '\n'; i++)
	        {
     		    msg->passwd[i] = buffer[i];
		}
		if (strlen(buffer) == 1)
		{
		    continue;
                }
                if (i >= 20)
	        {
	   	    printf("\033[22;51H＊您输入的密码过长!\n");
	    	    continue;
		}
                msg->passwd[i] = '\0';
	        break;
	    }
	    msg->action = RESET_PASSWD;
	    //将密保问题和密保答案发送到服务器修改
            n_write = write(sockfd, msg, msgbytes);
	    if (n_write == -1)
	    {
	        printf("reset_passwd write ppid error!\n");
	        exit(1);
    	    }
	    break;
	}
	
	/* 当命令为禁言时 */
	case SLENCE:
	{
	    clear_min();
	    printf("\033[5;15H＊请输入您想要禁言的好友ID:");
	    scanf("%d", &msg->to_id);
	    break;
	}
	
	/* 当命令为解禁时 */
	case PERMITE:
	{
            clear_min();
	    printf("\033[5;15H＊请输入您想要解禁的好友ID:");
	    scanf("%d", &msg->to_id);
	   
	    break;
	}
	
	/* 当命令为踢人时 */
	case TICK:
	{
            clear_min();
	    printf("\033[5;15H＊请输入您想要踢出的好友ID:");
	    scanf("%d", &msg->to_id);
	    break;
	}
	
	/*  当命令为切换用户时 */
	case BACK_LOGMENU:
	{
            n_write = write(sockfd, msg, msgbytes);
	    if (n_write == -1)
	    {
	        printf("reset_passwd write ppid error!\n");
	        exit(1);
    	    }
	    log_dis2();
	    break;
	}
	/* 当命令为设置个性签名时 */
	case SETSIGNER:
	{
	    clear_min();

	    printf("\033[6;14H               ＊秀出你的个性＊            \n");
	    printf("\033[7;14H                                           \n");
	    printf("\033[8;14H             你的个性签名由你做主          \n");
	    printf("\033[9;14H                                           \n");
	    printf("\033[10;14H           Please input your signer        \n");
	    printf("\033[11;14H         _____________________________     \n");
	    printf("\033[12;14H        ｜                           ｜    \n");
	    printf("\033[13;14H         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^     \n");
	    printf("\033[14;14H                                           \n");
	    
	    while (1)
	    {
                printf("\033[12;24H");
		fgets(buffer, BUFFSIZE, stdin);
		for (i = 0; buffer[i] != '\n'; i++)
		{
		    msg->signer[i]= buffer[i];
		}
		if (strlen(buffer) == 1)
		{
		    continue;
		}
		msg->signer[i] = '\0';
		break;
	    }
	    break;
	}
	
	/* 当命令为注册会员时 */
	case VIPMEMBER:
	{
	    int randnum = 0;
	    int fernum = 0;
	    int momnum = 0;
	    clear_min();

	    printf("\033[5;14H             欢迎订制PP_ONLINE会员         \n");
	    printf("\033[6;14H                                           \n");
	    printf("\033[7;14H          聊天因你而精彩，资费15元/月      \n");
	    printf("\033[8;14H                                           \n");
	    printf("\033[9;14H       请输入“根据系统提示”按月订制会员    \n");
	    printf("\033[10;14H                     输入“12345”退出订制   \n");
	    printf("\033[11;14H       支付密码:                           \n");
	    printf("\033[12;14H         _____________________________     \n");
	    printf("\033[13;14H        ｜                           ｜    \n");
	    printf("\033[14;14H         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^     \n");
	    printf("\033[15;14H                                           \n");
	    
	    while (1)
	    {
	        printf("\033[11;14H       支付密码:                           \n");
		printf("\033[13;24H            \n");
                printf("\033[11;31H5s\n");
	        sleep(1);
	        printf("\033[11;31H4s\n");
	        sleep(1);
	        printf("\033[11;31H3s\n");
	        sleep(1);
	        printf("\033[11;31H2s\n");
	        sleep(1);
	        printf("\033[11;31H1s\n");
	        sleep(1);
	        randnum = rand_brith_id();
	        printf("\033[11;31H%d\n", randnum);
	        printf("\033[13;24H");
	        scanf("%d", &fernum);
	        //退出注册
                if (fernum == 12345)
	        {
		    printf("\033[15;14H       ＊很遗憾，会员与您失之交臂！\n");
		    sleep(1);
		    clear_min();
		    msg->action = VIPEXIT;
		    break;
	        }
	        else
	        {
		    //支付密码输入正确
		    if (randnum == fernum)
	  	    {
		        printf("\033[11;21H订制月数:        \n");
			printf("\033[13;24H                 \n");
		        printf("\033[13;24H");
		        scanf("%d", &momnum);
		        if (momnum <= 0 || momnum >12)
		        {
			    printf("\033[15;14H       ＊您所订制的月份超出限制\n");
			    momnum = 0;
			    fernum = 0;
			    sleep(1);
			    printf("\033[15;14H                                  \n");
			    continue;
		        }
		        else
		        {
		            printf("\033[15;14H       ＊恭喜您已成为VIP、付款￥ %d\n", momnum * 15);
		            msg->vip_flag = 1;
			    sleep(1);
			    break;
		        }
		    }
		    else
		    {
		        printf("\033[15;14H       ＊支付密码输入错误，请重试！\n");
		        sleep(1);
		        printf("\033[15;14H                                       \n");
		        continue;
		    }
	        }
	    }
	    break;
	}
	
	/* 当命令为发送表情时*/
        case SENDBQ:
	{
	    int num;
	    clear_min();

	    printf("\033[5;14H       PP_ONLINE表情包、聊得就是表情      \n");
	    printf("\033[6;14H                                          \n");
	    printf("\033[7;14H                                          \n");
	    printf("\033[8;14H                                          \n");
            printf("\033[9;14H                                          \n");
            printf("\033[10;14H                                          \n");
	    printf("\033[11;14H    1、 (-_-!)    2、(~>_<~)    3、($_$)  \n"); 
	    printf("\033[12;14H    4、 (T^T)     5、(+_+)      6、(-_-#) \n");
	    printf("\033[13;14H    7、 (～o～)   8、(n_n)      9、(ToT)  \n");
	    printf("\033[14;14H    10、(*^_^*)  11、(＊o＊)   12、(^w^)  \n");
	     
            printf("\033[7;14H       请输入私发PP号(输入12345可群发)    \n");
	    printf("\033[8;14H       好友ID:");
            scanf("%d", &msg->to_id);
	    if (msg->to_id == 12345)
	    {
	        //群聊
   	        msg->action = CHATALL;
	    }
	    else
	    {
    	        //私聊
	        msg->action = CHATONE;
	    }
	    fflush(stdin);
	    while(1)
	    {
	        printf("\033[9;14H       表情编号:");
	        scanf("%d",&num);
    	        if (num >= 1 && num <=12)
     	        {
	            switch(num)
		    {
			case 1: strcpy(msg->msg, "(-_-!)"); break;
			case 2: strcpy(msg->msg, "(->_<-)"); break;
			case 3: strcpy(msg->msg, "($_$)"); break;
			case 4: strcpy(msg->msg, "(T^T)"); break;
			case 5: strcpy(msg->msg, "(+_+)"); break;
			case 6: strcpy(msg->msg, "(-_-#)"); break;
			case 7: strcpy(msg->msg, "(～o～)"); break;
			case 8: strcpy(msg->msg, "(n_n)"); break;
			case 9: strcpy(msg->msg, "(ToT)"); break;
			case 10: strcpy(msg->msg, "(*^_^*)"); break;
			case 11: strcpy(msg->msg, "(＊_＊)"); break;
			case 12: strcpy(msg->msg, "(^w^)"); break;

		    }
		    msg->activity = 1;
		    sleep(1);
		    clear_min();
	            break;
         	}
	        else
	        {
	            printf("\033[15;14H        ＊表情编号不再范围内，请重试      \n");
		    fflush(stdout);
		    continue;
		}
	    }
	    break;
	}

	/* 当命令为发送短语时 */
	case SENDDY:
	{
	    int num;
	    clear_min();

	    printf("\033[5;14H       PP_ONLINE表情包、聊得就是表情      \n");
	    printf("\033[6;14H                                          \n");
	    printf("\033[7;14H                                          \n");
	    printf("\033[8;14H                                          \n");
            printf("\033[9;14H                                          \n");
            printf("\033[10;14H       1、外面侯着,老夫在上课            \n");
	    printf("\033[11;14H       2、我有四个兄弟,叫东北F4          \n"); 
	    printf("\033[12;14H       3、快点啊，等的我花都谢了         \n");
	    printf("\033[13;14H       4、您所呼叫的用户已牛逼,sorry...  \n");
	    printf("\033[14;14H       5、哟,是哪个妖风把您给上线了      \n");
	    printf("\033[15;14H       6、看我小眼神行事，哈哈           \n");
	     
            printf("\033[7;14H       请输入私发PP号(输入12345可群发)    \n");
	    printf("\033[8;14H       好友ID:");
            scanf("%d", &msg->to_id);
	    if (msg->to_id == 12345)
	    {
	        //群聊
   	        msg->action = CHATALL;
	    }
	    else
	    {
    	        //私聊
	        msg->action = CHATONE;
	    }
	    fflush(stdin);
	    while(1)
	    {
	        printf("\033[9;14H       短语编号:");
	        scanf("%d",&num);
    	        if (num >= 1 && num <= 6)
     	        {
	            
                    switch(num)
		    {
			case 1: strcpy(msg->msg, "外面侯着,老夫在上课"); break;
	                case 2: strcpy(msg->msg, "我有四个兄弟,叫东北F4"); break;
	                case 3: strcpy(msg->msg, "快点啊，等的我花都谢了"); break;
	                case 4: strcpy(msg->msg, "您所呼叫的用户已牛逼,sorry..."); break;
	                case 5: strcpy(msg->msg, "哟,是哪个妖风把您给上线了"); break;
	                case 6: strcpy(msg->msg, "看我小眼神行事,哈哈"); break;
		    }
		    msg->activity = 2;
		    sleep(1);
		    clear_min();
	            break;
         	}
	        else
	        {
	            printf("\033[15;14H        ＊短语编号不再范围内，请重试      \n");
		    fflush(stdout);
		    continue;
		}
	    }
	    break;
	}

	/* 当命令为发送文件 */
	case SENDFILE:
	{
	    int i = 0;
	    int sum = 0;
	    int flag = 0;
	    int count = 0;
	    int from_fd;
	    int bytes_read;

	    char check[30] = {0};
	    char *ptr = check;
	    //获取要传送的好友ID
	    //获取想要让对方得到的文件名bb
	    //打开本地文件aa
	    //将文件中的内容写到结构体数组中
	    //然后发送给服务器
	    //服务器再把该内容转发给对方，对方收到信号之后，再本地创建一个bb文件并把文件内容写入
	    clear_min();

	    printf("\033[5;14H                   ＊文件传输＊              \n");
	    printf("\033[6;14H                                          \n");
	    printf("\033[7;14H    请输入接受文件对方ID: ");
	    scanf("%d", &msg->to_id);
            while (1)
	    {
	        printf("\033[9;14H    请输入要传输的文件名: ");
	        scanf("%s", msg->filename);
	        if ((from_fd = open(msg->filename, O_RDONLY)) == -1)
	        {
                    printf("\033[11;14H       ＊%s文件不存在!\n", msg->filename);
		    sleep(1);
		    flag = 1;
		    clear_min();
		    break;
	        }
		while (1)
		{
		    printf("\033[11;14H    是否要重命名该文件(yes/no): ");
		    scanf("%s", check);
		    printf("\033[13;14H                                     \n");
		    if (strcmp(check, "yes") == 0)
		    {
			//循环获取直到用户输入正确的文件名
			while (1)
			{
			    memset(check, 0, 30);
			    ptr = check;
			    printf("\033[13;14H    新的文件名(*.txt):");
			    scanf("%s", check);
			    printf("\033[15;14H                                      \n");
			    sum = 0;
			    while (*ptr != '.')
			    {
				sum++;
				if (sum == 29)
				{
				    printf("\033[15;14H该文件不可用，请注意格式.txt\n");
				    break;
				}
				ptr++;
			    }
			    if (sum == 29)
			    {
				sum = 0;
				continue;
			    }
			    if (strcmp(ptr, ".txt") == 0)
			    {
		                strcpy(msg->filename, check);
				break;
			    }
			    else
			    {
				printf("\033[15;14H该文件不可用，请注意格式.txt\n");
			    }
			}
			break;
		    }
	  	    else if (strcmp(check, "no") == 0)
		    {
                        break;
		    }
		    else
	  	    {
		        printf("\033[13;14H   您输入的指令有误,请重试!\n");
	 	    }
		}
		break;
	    }
	    if (flag == 1)
	    {
		break;
	    }
	    //从from_fd中读取直到遇到，到msg->filemsg中
	    while ((bytes_read = read(from_fd, msg->filemsg, 1024)))
	    {
	        /* 一个致命的错误发生了 */
	        if ((bytes_read == -1) && (errno != EINTR))
	        {
	            printf("\033[11;14H       ＊文件读出异常中断！\n");
		    msg->action = SENDFILE_ERROR;
	            break;
   	        }
	    }
	    while (msg->filemsg[i++] != '\0')
	    {
		count++;
	    }
	    msg->count = count;
	    printf("\033[15;14H     ＊文件%s已经成功发送!\n", msg->filename);

	    sleep(1);
	    clear_min();
	    close(from_fd);

	    break;
	}

	/* 当命令为查看聊天记录时 */
	case DISJILU:
	{
	    msg->action = DISJILU;
	    break;
	}
        
	/* 当命令为点赞时 */
	case DIANZAN:
	{
            clear_min();

	    printf("\033[6;14H    ＊请输入你想点赞的好友ID：");
	    scanf("%d", &msg->to_id);
	    break;
	}

	default:
	{
	    break;
	}
    }
    return 0;
}

