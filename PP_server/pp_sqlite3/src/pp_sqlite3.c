/*********************************************************
-  Copyright (C): 2016
-  File name    : pp_sqlite3.c
-  Author       : - Zhao -
-  Date         : 2016年01月30日 星期六 01时12分05秒
-  Description  : 服务器端的数据库操作文件
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

//创建数据库
void create_server_sql(sqlite3 *db)
{
    int ret = 0;
    char *sql = NULL;
    char *errmsg = NULL;

    /* 手动在堆上申请一段空间, 用来存储SQL命令 */
    sql = (char *)malloc(sizeof(char) * 256);
    if (sql == NULL)
    {
	printf("create_server_sql sql malloc error!\n");
	exit(1);
    }
    /* 创建了一个用户信息表 ppusertable */
    ret = sqlite3_exec(db, "create table if not exists ppusertable(pp_id integer primary key, name varchar(20), passwd varchar(20), passpro varchar(50), passkey varchar(50), vip_flag integer, signer varchar(25), zan integer);", NULL, NULL, &errmsg);
    if (ret != SQLITE_OK)
    {
	fprintf(stderr, "Create table err:%s\n", sqlite3_errmsg(db));
    }
    /* 首先在表中加入一个超级用户admin,id1000,昵称admin,密码admin,密保admin,密保答案admin */
    sprintf(sql, "insert into ppusertable values(100000, 'admin', 'admin', 'admin', 'admin', 1, 'admin', 0);");
    //printf("%s\n", sql);
    sqlite3_exec(db, sql, NULL, NULL, &errmsg);
	    
    /* 释放手动malloc分配 */
    free(sql);
    sql = NULL;
}

//查询ID是否重复
int find_id_inbase(sqlite3 *db, int newid)
{
    int ret = 0; 
    int row = 0;
    int column = 0;
    
    char *sql = NULL;
    char *errmsg = NULL;
    char **resultSet = NULL;
    
    /* 给sql在堆空间上开辟100个字节 */
    sql = (char *)malloc(sizeof(char) * 100);
    if (sql == NULL)
    {
	printf("find_id_in_ppbase sql malloc error!\n");
	exit(1);
    }

    sprintf(sql, "select * from ppusertable where pp_id = %d;", newid);
    printf("sql = %s", sql);
    if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
    {
	fprintf(stderr, "select err:%s\n", sqlite3_errmsg(db));
    }
    /* 如果查询到的行数为0，则说明ID没有重复，新ID可用 */
    if (row > 0)  
    {
	ret = -1;
    }
    /* 数据库中没有这个ID */
    if (row == 0)
    {
	ret = 0;
    }
    printf("###########ret = %d\n",ret);
    free(sql);
    sql = NULL;

    return ret;
}

/* 将好友信息加入服务器用户数据库 */
void insert_user_to_ppbase(sqlite3 *db, struct _Message *msg)
{
    char* sql = NULL;
    char* errmsg = NULL;
    
    sql = (char *)malloc(sizeof(char) * 200);
    if (sql == NULL)
    {
	printf("insert_user_to_ppbase sql malloc error!\n");
	exit(1);
    }

    sprintf(sql, "insert into ppusertable values(%d, '%s', '%s', '%s', '%s', 0, 'admin','0');", msg->pp_id, msg->name, msg->passwd, msg->passpro, msg->passkey);
    if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	printf("ADD ppuser information failed!\n");
    }
    else
    {
	printf("ADD ppuser successfully……\n");
    }
    /* 对于手动申请的堆空间,使用完后要释放! */
    free(sql);
    sql = NULL;
}
/* 登录信息在数据库中核对 */
int check_passwd_inbase(sqlite3 *db, int inputid, char *inputpasswd)
{
    printf("inputid = %d\n", inputid);
    int ret = find_id_inbase(db, inputid);
    int row = 0;
    int column = 0;

    char* sql = NULL;
    char* errmsg = NULL;
    char** resultSet = NULL;

    if (ret == 0)
    {
	return USERIDERROR;  //ID输入错误
    }
    //ret = -1说明数据库中有这个ID
    if (ret == -1)
    {
        sql = (char *)malloc(sizeof(char *) * 100);
	if (sql == NULL)
	{
	    printf("check passwd sql malloc error!\n");
	    exit(1);
	}
	sprintf(sql, "select passwd from ppusertable where pp_id = %d;",inputid); 
        //printf("check_passwd_sql = %s\n",sql);
	if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
	{
	    fprintf(stderr,"select passwd error!\n");
	    exit(1);
	}
	if (strcmp(inputpasswd, resultSet[1 * column + 0]) == 0)
	{
	    free(sql);
	    sql = NULL;
	    return SUCCESS;
	}
	else
	{
	    free(sql);
	    sql = NULL;
	    return USERPASSERR;
	}
    }
    return 0;
}
/* 通过ID得到数据库中用户昵称 */
void find_logname_inbase(sqlite3 *db, struct _Message *msg)
{
    int row = 0;
    int column = 0;

    char* sql = NULL;
    char* errmsg = NULL;
    char** resultSet = NULL;

    sql = (char *)malloc(sizeof(char *) * 200);
    if (sql == NULL)
    {
        printf("find_logname sql malloc error!\n");
	exit(1);
    }
    
    sprintf(sql, "select name from ppusertable where pp_id = %d;",msg->pp_id); 
    
    printf("find_logname sql = %s\n", sql);

    if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
    {
        fprintf(stderr,"select passwd error!\n");
	exit(1);
    }
    printf("row = %d\n", row);
    if (row > 0)
    {
	strcpy(msg->name, resultSet[1 * column + 0]);
        memset(sql, 0, sizeof(sql));
	sprintf(sql, "select vip_flag from ppusertable where pp_id = %d;", msg->pp_id);

	if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
	{
	    fprintf(stderr, "select vip_flag error!\n");
	    exit(1);
	}
	printf("LOGINSUPER  vip_flag =%d\n", *resultSet[1 * column + 0]);
	//如果查到该用户的vip_flag == 1,则为超级用户
        if (*resultSet[1 * column + 0] - '0'== 1)
	{
	    msg->flag = LOGINSUPER;
	}
	else
	{
	    msg->flag = LOGIN;
	}
        memset(sql, 0, sizeof(sql));
	sprintf(sql, "select signer from ppusertable where pp_id = %d;", msg->pp_id);
	if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
	{
	    fprintf(stderr, "select signer error!\n");
	    exit(1);
	}

	if (row > 0)
	{
	    strcpy(msg->signer, resultSet[1 * column + 0]);
	    printf("msg->signer = %s\n", msg->signer);
	}
	else
	{
	    printf("select signer inbase error!\n");
	    exit(1);
	}
        memset(sql, 0, sizeof(sql));
	sprintf(sql, "select zan from ppusertable where pp_id = %d;", msg->pp_id);

	if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
	{
	    fprintf(stderr, "select vip_flag error!\n");
	    exit(1);
	}
	printf("zan =%d\n", *resultSet[1 * column + 0] - '0');

        msg->zan = *resultSet[1 * column + 0] - '0';
	free(sql);
	sql = NULL;
    }
    else
    {
	printf("find_logname error!\n");
    }
}
/* 通过ID得到数据库中密保问题 */
void find_passpro_inbase(sqlite3 *db, struct _Message *msg)
{
    int row = 0;
    int column = 0;

    char* sql = NULL;
    char* errmsg = NULL;
    char** resultSet = NULL;

    sql = (char *)malloc(sizeof(char *) * 150);
    if (sql == NULL)
    {
        printf("check passwd sql malloc error!\n");
	exit(1);
    }
    sprintf(sql, "select passpro from ppusertable where pp_id = %d;",msg->pp_id); 
        
    if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
    {
        fprintf(stderr,"select passwd error!\n");
	exit(1);
    }
    if (row > 0)
    {
	strcpy(msg->passpro, resultSet[1 * column + 0]);
	free(sql);
	sql = NULL;
    }
    else
    {
	printf("find_passpro error!\n");
    }
}

/* 通过ID得到数据库密保答案。如果密保回答正确，则修改密码*/
void find_passkey_inbase(sqlite3 *db, struct _Message *msg)
{
    int row = 0;
    int column = 0;

    char* sql = NULL;
    char* errmsg = NULL;
    char** resultSet = NULL;

    sql = (char *)malloc(sizeof(char *) * 150);
    if (sql == NULL)
    {
        printf("check passwd sql malloc error!\n");
	exit(1);
    }
    sprintf(sql, "select passkey from ppusertable where pp_id = %d;",msg->pp_id); 
        
    if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
    {
        fprintf(stderr,"select passwd error!\n");
	exit(1);
    }
    if (row > 0)
    {
        //密保答案回答正确
	//可以修改密码
	if (strcmp(msg->passkey, resultSet[1 * column + 0]) == 0)
	{
	    msg->flag = RESET_SUCCESS;
	    memset(sql, 0, sizeof(sql));
	    sprintf(sql, "update ppusertable set passwd = '%s' where pp_id = %d;", msg->passwd, msg->pp_id);
            if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
            {
	        printf("updata passwd fail\n");
            }
            else
            {
	        printf("updata passwd success\n");
            }
	}
	else
	{
	    //密保答案错误
	    msg->flag = PASSKEY_ERROR;
	}
	free(sql);
	sql = NULL;
    }
    else
    {
	printf("find_passkey error!\n");
    }
}

/* 通过ID更新数据库中用户的vipflag */
void set_vipflag_inbase(sqlite3 *db, struct _Message *msg)
{
    char* sql = NULL;
    char* errmsg = NULL;

    sql = (char *)malloc(sizeof(char *) * 150);
    if (sql == NULL)
    {
        printf("check passwd sql malloc error!\n");
	exit(1);
    }

    sprintf(sql, "update ppusertable set vip_flag = %d where pp_id = %d;", msg->vip_flag, msg->pp_id);
    if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	printf("updata vipflag fail\n");
    }
    else
    {
        printf("updata vipflag success\n");
    }
    free(sql);
    sql = NULL;
}

/* 通过ID更新数据库中用户的zan*/
void update_zan_inbase(sqlite3 *db, struct _Message *msg)
{
    int zan = 0;
    
    int row = 0;
    int column = 0;
    
    char* sql = NULL;
    char* errmsg = NULL;
    char** resultSet = NULL;

    sql = (char *)malloc(sizeof(char *) * 150);
    if (sql == NULL)
    {
        printf("check passwd sql malloc error!\n");
	exit(1);
    }
    memset(sql, 0, sizeof(sql));
    sprintf(sql, "select zan from ppusertable where pp_id = %d;", msg->to_id);

    if (SQLITE_OK != sqlite3_get_table(db, sql, &resultSet, &row, &column, &errmsg))
    {
        fprintf(stderr, "select vip_flag error!\n");
        exit(1);
    }
    printf("zan =%d\n", *resultSet[1 * column + 0] - '0');
    //如果查到该用户的vip_flag == 1,则为超级用户
    zan = (*resultSet[1 * column + 0] - '0');
    zan = zan + 1;

    memset(sql, 0, sizeof(sql));
    sprintf(sql, "update ppusertable set zan = %d where pp_id = %d;", zan, msg->pp_id);
    if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	printf("updata zan fail\n");
    }
    else
    {
        printf("updata zan success\n");
    }
    msg->zan = zan;

    free(sql);
    sql = NULL;
}

/* 通过ID更新数据库中用户的个性签名*/
void update_signer_inbase(sqlite3 *db, struct _Message *msg)
{
    char* sql = NULL;
    char* errmsg = NULL;

    sql = (char *)malloc(sizeof(char *) * 150);
    if (sql == NULL)
    {
        printf("check passwd sql malloc error!\n");
	exit(1);
    }

    sprintf(sql, "update ppusertable set signer = '%s' where pp_id = %d;", msg->signer, msg->pp_id);
    if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, &errmsg))
    {
	printf("updata signer fail\n");
    }
    else
    {
        printf("updata signer success\n");
    }
    free(sql);
    sql = NULL;
}

