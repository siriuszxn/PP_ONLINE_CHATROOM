/*********************************************************
-  Copyright (C): 2016
-  File name    :rand_brith_id.c
-  Author       :- Zhao -
-  Date         :2016年01月30日 星期六 21时49分31秒
-  Description  :
*  *******************************************************/
#include "../../../include/PP_ONLINE.h"

int rand_brith_id()
{
    int i;
    int j;
    srand((unsigned)time(NULL));

    for (i = 0; i < 10; i++)
    {
	j = (((double)rand() / (double)999999) * 999999 + 100001);
    }
    j = j % 1000000;
    
    return j;
}
