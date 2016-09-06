/*********************************************************
-  Copyright (C): 2016
-  File name    :PP_ONLINE.h
-  Author       :- Zhao -
-  Date         :2016年01月29日 星期五 20时56分45秒
-  Description  :
*  *******************************************************/
/* 条件编译 */
#ifndef PP_ONLINE_H_
#define PP_ONLINE_H_

/* 头文件 */
#include <stdio.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sqlite3.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
 
/* 宏定义 */
#define LOGIN           0    //宏定义登录action
#define REGIST          1    //宏定义注册action
#define FIND_PASSPRO    2    //宏定义找到密保问题action    
#define DIS_ONLINE_USER 3    //宏定义查看在线好友action
#define CHATONE         4    //宏定义私聊action
#define CHATALL         5    //宏定义群聊action
#define RESET_PASSWD    6    //宏定义修改密码action
#define HELP            7    //宏定义帮助action
#define BACK_LOGMENU    8    //宏定义返回登录界面action
#define SLENCE          9    //宏定义禁言action
#define PERMITE        10    //宏定义解禁action
#define TICK           11    //宏定义踢人action
#define EXIT           12    //宏定义退出action
#define SUCCESS        13    //宏定义成功
#define LOGINSUPER     15    //宏定义超级用户
#define SLENCEALREADY  16    //宏定义已经禁言
#define PERMITEALREADY 17    //宏定义已经解禁
#define DIS_SUCCESS    18    //宏定义查看好友结束
#define TICKFAIL       19    //宏定义踢人失败
#define PERMITESUCCESS 20    //宏定义解禁成功给VIP
#define SLENCESUCCESS  21    //宏定义禁言成功给VIP
#define TICKOK         22    //宏定义踢人返回给VIP
#define TICKSUCCESS    23    //宏定义踢人成功
#define PERMITEFAIL    24    //宏定义解禁的对象不存在
#define SLENCEFAIL     25    //宏定义禁言用户不存在
#define CHATONEFAIL    26    //宏定义私聊用户不存在
#define LOGINFAIL      27    //宏定义登录用户已在线
#define PASSKEY_ERROR  28    //宏定义密保答案回答错误
#define RESET_SUCCESS  29    //宏定义密码改动成功
#define SETSIGNER      30    //宏定义设置个性签名
#define VIPMEMBER      31    //宏定义注册会员
#define SENDBQ         32    //宏定义发送表情
#define SENDDY         33    //宏定义发送短语
#define SENDFILE       34    //宏定义发送文件
#define DISJILU        35    //宏定义查看聊天记录
#define VIPEXIT        36    //宏定义VIP注册退出
#define SENDFILE_ERROR 37    //宏定义发送文件失败，对方用户不在线
#define SENDFILETOSELF 38    //宏定义发送文件给自己
#define CHATONETOSELF  39    //宏定义私聊和自己
#define DIANZAN        40    //宏定义点赞
#define DIANZANFAIL    41    //宏定义点赞失败
#define WRONG_CMD      14    //宏定义输入指令出错action
#define USERIDERROR    -2    //宏定义ID出错
#define USERPASSERR    -3    //宏定义密码出错
#define BUFFSIZE       1024  //数据缓冲区大小
#define portnumber     8000  //端口号8000

/* 
   定义一个结构体,用来封装消息,供服务器客户端通信 
                                                  */
typedef struct _Message
{
    int count;               //文件字符数计数
    int action;              //服务器接受动作,传输选择协议
    int flag;                //客户端接受动作
    int vip_flag;            //超级用户标志位
    int activity;            //发送表情短语状态切换
    int zan;                 //点赞标志位
    int pp_id;               //存放PPid号
    int to_id;               //存放对方PPid号 
    
    char name[20];           //存放当前昵称
    char passwd[20];         //存放密码
    char signer[25];         //存放个性签名
    char passpro[50];        //存放密保问题
    char passkey[50];        //存放密保答案
    char to_name[20];        //存放对方昵称
    char msg[300];           //存放聊天的内容
    char filename[20];       //存放文件名
    char filemsg[2048];      //存放文件内容

}Message;

/* 
   定义一个结构体,用来记录当前在线好友
   功能:主要为用户在线链表
                                       */
struct online
{
    int  online_flag;        //禁言标志位
    int  online_fd;          //连接描述符   
    int  online_id;          //在线用户ID
    
    char online_name[20];    //在线用户姓名

    struct online *next;
};

/* 
   定义全局变量 
                */
struct online *head;
struct online *new_user;
pthread_mutex_t mutex;    //互斥锁
sqlite3* db;

/* 
   函数声明
           */

void log_dis(void);       //登录界面动态
void log_dis2(void);      //登录界面静态
void reg_dis(void);       //注册界面
void help_dis(void);      //帮助界面 
void user_dis(void);      //用户界面
void clear_min(void);     //请屏小窗口
void loading_dis(void);   //聊天室开机加载动画
void rem_passwd(void);    //修改密码界面
void superuser_dis(void); //超级用户界面
int  input_check(char *); //字符串解析动作
void file_recv(struct _Message *);      //文件读取线程
int  pack_msg(int, Message *, int, int);//客户端数据打包
void client_read_msg(void *);           //客户端读线程
void server_read_msg(void *);           //服务器读线程
int  rand_brith_id(void);               //6位的随机数产生函数,用来获取qq号
void create_server_sql(sqlite3 *);      //创建数据库
int  find_id_inbase(sqlite3 *, int);    //查询IDs是否重复
void insert_user_to_ppbase(sqlite3 *, struct _Message *); //将好友信息添加到数据库
int  check_passwd_inbase(sqlite3 *, int, char *);         //登录信息核对
void find_logname_inbase(sqlite3 *, struct _Message *);   //根据上线ID得到该用户昵称
void find_passpro_inbase(sqlite3 *, struct _Message *);   //根据ID得到该用户的密保问题
void find_passkey_inbase(sqlite3 *, struct _Message *);   //根据ID得到该用户的密保答案并判断与用户输入是否一致
void set_vipflag_inbase(sqlite3 *, struct _Message *);    //根据ID更新数据库中的VIP_flag
void update_signer_inbase(sqlite3 *, struct _Message *);  //根据ID更新数据库中的个性签名 
void update_zan_inbase(sqlite3 *, struct _Message *);     //根据ID更新数据库中的赞


#endif
