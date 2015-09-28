//
// Created by System Administrator on 9/27/15.
//

#ifndef TINY_WEB_ROBUST_IO_H
#define TINY_WEB_ROBUST_IO_H

#endif //TINY_WEB_ROBUST_IO_H

#ifndef MAXBUFSZ
#define MAXBUFSZ 1024
#endif

#ifndef MAXLINE
#define MAXLINE 100
#endif

struct rio {
    int fd;         // 文件描述符
    char buf[MAXBUFSZ];      // 缓冲区
    char* curr_p; // 当前缓冲区指针位置
    int free_size;  // 未读大小
};

int rio_readinitb(int fd);

int rio_read(rio* stream, char* usrbuf, size_t bytes);

int rio_readlineb(rio* stream, char* res);