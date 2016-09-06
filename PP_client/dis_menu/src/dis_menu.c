/*********************************************************
-  Copyright (C): 2016
-  File name    : dis_menu.c
-  Author       : - Zhao -
-  Date         : 2016年01月25日 星期一 20时36分09秒
-  update Time  : 2016年02月21日 星期日 12时58分58秒
-  Description  : 界面程序
-  版本         : 版本2
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

#define SIZE 200000
#define LOGSLEEP 150000
#define LOGSLEEP2 7000

void loading_dis()
{
    system("clear");
    printf("\033[12;50H＊\n");
    usleep(SIZE);
    printf("\033[12;52H用\n");
    usleep(SIZE);
    printf("\033[12;54H心\n");
    usleep(SIZE);
    printf("\033[12;56H去\n");
    usleep(SIZE);
    printf("\033[12;58H做\n");
    usleep(SIZE);
    printf("\033[12;60H! \n");
    usleep(SIZE);
    printf("\033[12;50H  \n");
    usleep(SIZE);
    printf("\033[12;52H  \n");
    usleep(SIZE);
    printf("\033[12;54H  \n");
    usleep(SIZE);
    printf("\033[12;56H  \n");
    usleep(SIZE);
    printf("\033[12;58H  \n");
    usleep(SIZE);
    printf("\033[12;60H  \n");
    usleep(SIZE);
    printf("\033[14;62H代\n");
    usleep(SIZE);
    printf("\033[14;64H码\n");
    usleep(SIZE);
    printf("\033[14;66H因\n");
    usleep(SIZE);
    printf("\033[14;68H你\n");
    usleep(SIZE);
    printf("\033[14;70H而\n");
    usleep(SIZE);
    printf("\033[14;72H精\n");
    usleep(SIZE);
    printf("\033[14;74H彩\n");
    usleep(SIZE);
    printf("\033[14;76H＊\n");
    usleep(SIZE);
    printf("\033[14;62H  \n");
    usleep(SIZE);
    printf("\033[14;64H  \n");
    usleep(SIZE);
    printf("\033[14;66H  \n");
    usleep(SIZE);
    printf("\033[14;68H  \n");
    usleep(SIZE);
    printf("\033[14;70H  \n");
    usleep(SIZE);
    printf("\033[14;72H  \n");
    usleep(SIZE);
    printf("\033[14;74H  \n");
    usleep(SIZE);
    printf("\033[14;76H  \n");
    usleep(SIZE);
    printf("\033[12;50H＊用心去做!\n");
    printf("\033[14;62H代码因你而精彩＊\n");
    printf("\033[16;50H____________________________\n");
    printf("\033[17;49H｜＊                        ｜\n");
    printf("\033[18;50H^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n");
    printf("\033[19;50H PP_ONLINE  Linux网络聊天室\n");
    printf("\033[20;65HLoading...%%8 \n");
    sleep(1);
    printf("\033[17;53H＊＊＊\n");
    printf("\033[20;76H37\n");
    sleep(1);
    printf("\033[17;59H＊＊＊＊＊＊\n");
    printf("\033[20;76H80\n");
    sleep(1);
    printf("\033[17;71H＊＊＊\n");
    printf("\033[20;76H100\n");
    sleep(1);
}
/* 登录界面 */
void log_dis()
{
    system("clear");
    printf("\033[6;42H __\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ____________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ______________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H ________________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[6;42H __________________________________________________\n");
    usleep(LOGSLEEP);
    printf("\033[7;42H  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  \n");
    usleep(LOGSLEEP);
    printf("\033[7;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[8;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[10;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[11;42H＊__\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊__________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊____________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊______________________________________________\n");
    usleep(LOGSLEEP2);
    printf("\033[11;42H＊________________________________________________＊\n");
    usleep(LOGSLEEP);
    printf("\033[12;42H  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n");
    usleep(LOGSLEEP);
    printf("\033[12;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[19;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜                                                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[21;42H＊————————————————————————————————————————————————＊\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜   ________                                     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜      ｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜______｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜(^**^)｜                                    ｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;42H｜   ________       ___________________________   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;42H｜  ｜      ｜     ｜                         ｜  ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;42H｜  ｜(^**^)｜      ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;42H｜  ｜______｜      ___________________________   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;42H｜                 ｜                         ｜  ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;42H｜                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;42H｜               PP_ONLINE  聊天室                ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;57HID号\n");
    usleep(LOGSLEEP);
    printf("\033[17;57H密码\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊登录(LOG)                                     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊登录(LOG)                         ＊退出(EXT) ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊登录(LOG) ＊注册(REG)             ＊退出(EXT) ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;42H｜＊登录(LOG) ＊注册(REG) ＊忘密(REM) ＊退出(EXT) ｜\n");
}
void log_dis2()
{
    system("clear");
    printf("\033[6;42H __________________________________________________\n");
    printf("\033[7;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[8;42H｜                                                ｜\n");
    printf("\033[9;42H｜               PP_ONLINE  聊天室                ｜\n");
    printf("\033[10;42H｜                                                ｜\n");
    printf("\033[11;42H＊________________________________________________＊\n");
    printf("\033[12;42H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    printf("\033[13;42H｜   ________       ___________________________   ｜\n");
    printf("\033[14;42H｜  ｜      ｜ ID号｜                         ｜  ｜\n");
    printf("\033[15;42H｜  ｜(^**^)｜      ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    printf("\033[16;42H｜  ｜______｜      ___________________________   ｜\n");
    printf("\033[17;42H｜             密码｜                         ｜  ｜\n");
    printf("\033[18;42H｜                  ^^^^^^^^^^^^^^^^^^^^^^^^^^^   ｜\n");
    printf("\033[19;42H｜                                                ｜\n");
    printf("\033[20;42H｜＊登录(LOG) ＊注册(REG) ＊忘密(REM) ＊退出(EXT) ｜\n");
    printf("\033[21;42H＊————————————————————————————————————————————————＊\n");
}

/* 帮助界面 */
void help_dis()
{
    printf("\033[5;14H           ＊ 谢谢使用PP_ONLINE聊天室＊      \n");
    usleep(SIZE);
    printf("\033[6;14H                  写给用户的话               \n");
    usleep(SIZE);
    printf("\033[7;14H   在这里：                                  \n");
    usleep(SIZE);
    printf("\033[8;14H       你可以和好友说悄悄话、你的空间由你做主\n");
    usleep(SIZE);
    printf("\033[9;14H       你可以和大家群聊、爆料、吐嘈、扯八卦  \n");
    usleep(SIZE);
    printf("\033[10;14H       你可以发送表情、短语、传输文件，轻松聊\n");
    usleep(SIZE);
    printf("\033[11;14H       你还可以加入PP_ONLINE会员             \n");
    usleep(SIZE);
    printf("\033[12;14H       独享禁言、解禁、踢人等隐藏功能        \n");
    usleep(SIZE);
    printf("\033[13;14H                  开发人员信息               \n");
    usleep(SIZE);
    printf("\033[14;14H                     赵溪楠                  \n");
    usleep(SIZE);
    printf("\033[15;14H                 PP_ONLINE V3.0              \n");
    sleep(6);
    printf("\033[5;14H                                             \n");
    printf("\033[6;14H                                             \n");
    printf("\033[7;14H                                             \n");
    printf("\033[8;14H                                             \n");
    printf("\033[9;14H                                             \n");
    printf("\033[10;14H                                             \n");
    printf("\033[11;14H                                             \n");
    printf("\033[12;14H                                             \n");
    printf("\033[13;14H                                             \n");
    printf("\033[14;14H                                             \n");
    printf("\033[15;14H                                             \n");
}
/* 注册界面 */
void reg_dis()
{
    system("clear");
    printf("\033[5;38H __________________________________________________________\n");
    usleep(LOGSLEEP);
    printf("\033[6;38H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[7;38H｜＊                  欢迎注册PP_ONLINE                 ＊｜\n");
    usleep(LOGSLEEP);
    printf("\033[8;38H｜                                                        ｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;38H｜                ____________________________            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[10;38H｜      昵  称 : ｜                          ｜           ｜\n");
    usleep(LOGSLEEP);
    printf("\033[11;38H｜                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[12;38H｜                ____________________________            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;38H｜      密  码 : ｜                          ｜           ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;38H｜                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;38H｜                ____________________________            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;38H｜     再输密码: ｜                          ｜           ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;38H｜                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;38H｜                ____________________________            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[19;38H｜     密保问题: ｜                          ｜           ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;38H｜                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[21;38H｜                ____________________________            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[22;38H｜     密保答案: ｜                          ｜           ｜\n");
    usleep(LOGSLEEP);
    printf("\033[23;38H｜                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^            ｜\n");
    usleep(LOGSLEEP);
    printf("\033[24;38H｜                                                        ｜\n");
    usleep(LOGSLEEP);
    printf("\033[25;38H｜                                                        ｜\n");
    usleep(LOGSLEEP);
    printf("\033[26;38H｜                                                        ｜\n");
    usleep(LOGSLEEP);
    printf("\033[27;38H＊________________________________________________________＊\n\n");
    usleep(LOGSLEEP);
}

/* 修改/忘记密码界面 */
void rem_passwd()
{
    system("clear");
    printf("\033[7;45H ____________________________________________\n");
    usleep(LOGSLEEP);
    printf("\033[8;45H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[9;45H｜^^^^^^^^        PP_ONLINE         ^^^^^^^^｜\n");
    usleep(LOGSLEEP);
    printf("\033[10;45H｜               安全服务中心               ｜\n");
    usleep(LOGSLEEP);
    printf("\033[11;45H｜                                          ｜\n");
    usleep(LOGSLEEP);
    printf("\033[12;45H｜     请输入你的PP号                       ｜\n");
    usleep(LOGSLEEP);
    printf("\033[13;45H｜     _______________________________      ｜\n");
    usleep(LOGSLEEP);
    printf("\033[14;45H｜    ｜                             ｜     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[15;45H｜     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^      ｜\n");
    usleep(LOGSLEEP);
    printf("\033[16;45H｜     请回答密保问题                       ｜\n");
    usleep(LOGSLEEP);
    printf("\033[17;45H｜                                          ｜\n");
    usleep(LOGSLEEP);
    printf("\033[18;45H｜                                          ｜\n");
    usleep(LOGSLEEP);
    printf("\033[19;45H｜     _______________________________      ｜\n");
    usleep(LOGSLEEP);
    printf("\033[20;45H｜    ｜                             ｜     ｜\n");
    usleep(LOGSLEEP);
    printf("\033[21;45H｜     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^      ｜\n");
    usleep(LOGSLEEP);
    printf("\033[22;45H｜                                          ｜\n");
    usleep(LOGSLEEP);
    printf("\033[23;45H｜                                          ｜\n");
    usleep(LOGSLEEP);
    printf("\033[24;45H｜        设置(REM)        返回(BCK)        ｜\n");
    usleep(LOGSLEEP);
    printf("\033[25;45H＊__________________________________________＊\n");
}
/* 普通用户界面V2.0 做改变 */
void user_dis()
{
    time_t timep;
    time(&timep);
    system("clear");
    printf("\033[2;12H _____________________________________________________________________________________________________________\n");
    printf("\033[3;12H｜                                                   ｜                ｜  _______                           ｜\n");
    printf("\033[4;12H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜   PP_NEWS……    ｜ ｜     ｜   NAME:                  ｜\n");
    printf("\033[5;12H｜                                                   ｜                ｜ ｜(^_^)｜                          ｜\n");
    printf("\033[6;12H｜                                                   ｜    今日天气    ｜ ｜_____｜   PPID:        赞:       ｜\n");
    printf("\033[7;12H｜                                                   ｜                ｜                                    ｜\n");
    printf("\033[8;12H｜                                                   ｜   南京:晴      ｜ 个性签名: 这个人很懒,什么都没留下  ｜\n");
   printf("\033[9;12H｜                                                   ｜ 10～24度(微风) ＊－－－－－－－－－－－－－－－－－－＊\n");
   printf("\033[10;12H｜                                                   ｜                ｜                                    ｜\n");
   printf("\033[11;12H｜                                                   ｜ 适宜:出游、散步｜                                    ｜\n");
   printf("\033[12;12H｜                                                   ｜    ________    ｜                                    ｜\n");
   printf("\033[13;12H｜                                                   ｜   /________\\   ｜                                    ｜\n");
   printf("\033[14;12H｜                                                   ｜   |        |   ｜                                    ｜\n");
   printf("\033[15;12H｜                                                   ｜   |   加   |   ｜                                    ｜\n");
   printf("\033[16;12H｜___________________________________________________｜   |   多   |   ｜                                    ｜\n");
   printf("\033[17;12H＊                                                   ＊   |   宝   |   ｜                                    ｜\n");
   printf("\033[18;12H｜  隐藏功能:仅PP会员(超级用户)可见.VIP专用          ｜   |________|   ｜                                    ｜\n");
   printf("\033[19;12H＊___________________________________________________＊   \\________/   ＊____________________________________＊\n");
   printf("\033[20;12H｜                                                   ｜                ｜                                    ｜\n");
   printf("\033[21;12H｜   ＊群聊(ACH)     ＊私聊(PCH)     ＊点赞(ZAN)     ｜  金罐加多宝    ｜＊刷出在线好友(DIS)  ＊PP简介(HLP)  ｜\n");
   printf("\033[22;12H｜                                                   ｜     畅饮人生…… ｜                                    ｜\n");
   printf("\033[23;12H｜   ＊发送表情(SBQ)            ＊发送短语(SDY)      ｜                ｜＊修改密码(REM)      ＊切换帐号(BCK)｜\n");
   printf("\033[24;12H｜                                                   ｜    (^_^)       ｜                                    ｜\n");
   printf("\033[25;12H｜   ＊文件传输(SFS)            ＊查看聊天记录(SJL)  ｜                ｜＊设置个性签名(SET)  ＊注册会员(VIP)｜\n");
   printf("\033[26;12H＊___________________________________________________＊________________＊____________________________________＊\n\n");
   printf("\033[3;23HTIME: %s\n",asctime(gmtime(&timep)));
}
/* 超级用户登录界面 */
void superuser_dis()
{
    time_t timep;
    time(&timep);
    system("clear");
    printf("\033[2;12H _____________________________________________________________________________________________________________\n");
    printf("\033[3;12H｜                                                   ｜                ｜  _______                           ｜\n");
    printf("\033[4;12H｜^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^｜   PP_NEWS……    ｜ ｜     ｜   NAME:                  ｜\n");
    printf("\033[5;12H｜                                                   ｜                ｜ ｜(^_^)｜                          ｜\n");
    printf("\033[6;12H｜                                                   ｜    今日天气    ｜ ｜_____｜   PPID:        赞:       ｜\n");
    printf("\033[7;12H｜                                                   ｜                ｜                                    ｜\n");
    printf("\033[8;12H｜                                                   ｜   南京:晴      ｜ 个性签名: 这个人很懒,什么都没留下  ｜\n");
    printf("\033[9;12H｜                                                   ｜ 10～24度(微风) ＊－－－－－－－－－－－－－－－－－－＊\n");
    printf("\033[10;12H｜                                                   ｜                ｜                                    ｜\n");
    printf("\033[11;12H｜                                                   ｜ 适宜:出游、散步｜                                    ｜\n");
    printf("\033[12;12H｜                                                   ｜    ________    ｜                                    ｜\n");
    printf("\033[13;12H｜                                                   ｜   /________\\   ｜                                    ｜\n");
    printf("\033[14;12H｜                                                   ｜   |        |   ｜                                    ｜\n");
    printf("\033[15;12H｜                                                   ｜   |   加   |   ｜                                    ｜\n");
    printf("\033[16;12H｜___________________________________________________｜   |   多   |   ｜                                    ｜\n");
    printf("\033[17;12H＊                                                   ＊   |   宝   |   ｜                                    ｜\n");
    printf("\033[18;12H｜   ＊禁言(NOS)     ＊解禁(CAS)     ＊踢人(OUT)     ｜   |________|   ｜                                    ｜\n");
    printf("\033[19;12H＊___________________________________________________＊   \\________/   ＊____________________________________＊\n");
    printf("\033[20;12H｜                                                   ｜                ｜                                    ｜\n");
    printf("\033[21;12H｜   ＊群聊(ACH)     ＊私聊(PCH)     ＊点赞(ZAN)     ｜  金罐加多宝    ｜＊刷出在线好友(DIS)  ＊帮助(HLP)    ｜\n");
    printf("\033[22;12H｜                                                   ｜     畅饮人生…… ｜                                    ｜\n");
    printf("\033[23;12H｜   ＊发送表情(SBQ)            ＊发送短语(SDY)      ｜                ｜＊修改密码(REM)      ＊切换帐号(BCK)｜\n");
    printf("\033[24;12H｜                                                   ｜    (^_^)       ｜                                    ｜\n");
    printf("\033[25;12H｜   ＊文件传输(SFS)            ＊查看聊天记录(SJL)  ｜                ｜＊设置个性签名(SET)  ＊注册会员(VIP)｜\n");
    printf("\033[26;12H＊___________________________________________________＊________________＊____________________________________＊\n\n");
    printf("\033[3;23HTIME: %s\n",asctime(gmtime(&timep)));
}
/* 清屏小窗口*/
void clear_min()
{
    printf("\033[5;14H                                                   \n");
    printf("\033[6;14H                                                   \n");
    printf("\033[7;14H                                                   \n");
    printf("\033[8;14H                                                   \n");
    printf("\033[9;14H                                                   \n");
    printf("\033[10;14H                                                   \n");
    printf("\033[11;14H                                                   \n");
    printf("\033[12;14H                                                   \n");
    printf("\033[13;14H                                                   \n");
    printf("\033[14;14H                                                   \n");
    printf("\033[15;14H                                                   \n");
}


