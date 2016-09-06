	        

#include "../../../include/PP_ONLINE.h"


void file_recv(struct _Message *msg)
{
    int to_fd;
    int bytes_read = msg->count;
    int bytes_write;
		
    char *ptr;
    clear_min();
		
    printf("\033[6;14H    好友%s向你发送文件%s\n", msg->name, msg->filename);
	
    //打开或创建文件
    if ((to_fd = open(msg->filename, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR)) == -1)
    {
        fprintf(stderr, "Open %s Error:%s", msg->filename, strerror(errno));
        exit(1);
    }
    //写文件
    ptr = msg->filemsg;
    while ((bytes_write = write(to_fd, ptr, bytes_read)))
    {
        /* 一个致命的错误发生了 */
        if ((bytes_write == -1) && (errno != EINTR))
	{
	    break;
	}
        else if (bytes_write == bytes_read)
        {
            /* 写完了所有读的字节 */
	    printf("\033[8;14H    文件%s成功接收完成!", msg->filename);
	    break;
        }
	else if (bytes_write > 0) 
	{
	    /* 只写了一部分 */
	    ptr += bytes_write;
	    bytes_read -= bytes_write;
        }
    }
    printf("\033[28;72H");
    fflush(stdout);
}           
	 
