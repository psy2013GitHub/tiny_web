#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "netinet/in.h"
#include "socket_util.h"
#include "process.h"

using namespace std;

int main(int argc, char** argv) {

    int listen_fd;
    int conn_fd;
    struct sockaddr_in client_addr;
    int client_len;

    if (argc != 2){
        printf("usage: ./tiny_web <port>");
        return -1;
    }

    int port = atoi(argv[1]);

    if ((listen_fd = Open_listenfd(port)) < 0) // 建立可复用监听socket
        return -1;
    while (1){
        client_len = sizeof(client_addr);
        conn_fd = accept(listen_fd, (sockaddr *)&client_addr, &client_len); // accept 负责填写客户端socket地址
        if (conn_fd < 0)
            continue;
        process(conn_fd);
        close(conn_fd);
    }


    return 0;
}