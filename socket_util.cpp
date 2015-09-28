//
// Created by System Administrator on 9/27/15.
//


#include <netinet/in.h>
#include "socket_util.h"


int Open_listenfd(int port) {
    int socket_fd;
    int optval = 1;
    struct sockaddr_in server_addr;
    if ( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        return -1;

    // 设置socket属性，常用套接字，可复用，
    if ( setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int)) < 0 )
        return -1;

    // 设置server套接字地址：类型｜地址：端口
    bzero((char*)&server_addr, sizeof(server_addr)); // 初始化为0
    server_addr.sin_addr = AF_INET;                  // 地址类型
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 可监听任意地址
    server_addr.sin_port = htonl((unsigned int)port);// 端口

    bind(socket_fd, &server_addr, sizeof(server_addr));

    if (listen(socket_fd, 1024) < 0)
        return -1;

    return socket_fd;
}