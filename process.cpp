//
// Created by System Administrator on 9/27/15.
//

#include <sys/stat.h>
#include "process.h"

#ifndef MAXARG
#define MAXARG 100
#endif

int parse_uri(char* uri, char* filename, char** cgi_args) {
    char* ptr = uri;
    if (!strstr(uri, 'cgi/bin')) { // static web request
        strcpy(cgi_args, "");
        strcpy(filename, '.');
        strcat(filename, uri);
        if (uri[strlen(uri)-1]=='/') // home page
           strcat(filename, "/home.html");
        return 1;
    }
    else {                        // dynamic web request
        ptr = index(uri, '?');
        if (ptr){
            strcpy(cgi_args, ptr+1);
            *ptr='\0';
        }
        else{
            strcpy(cgi_args, "");
        }
        strcpy(filename, '.');
        strcat(filename, uri);
    }
    return 2;
}

int serve_static(char* filename, size_t bytes) {

}

int serve_dynamic(char* filename, char* cgi_args) {

}

int process(int conn_fd){
    char line[MAXLINE], filename[MAXLINE], cgi_args[MAXLINE];
    char* cmd, uri, http_version;
    int method = 1; // 1 for 'GET'; 2 for 'POST'
    struct stat sbuf;

    // 读socket
    rio* stream = rio_readinitb(fd);
    if ((ans=rio_readlineb(stream, line)) <= 0){
        return ans;
    }
    sscanf(line, '%s %s %s', cmd, uri, http_version);
    if (!strcasecmp(cmd, 'GET'))
        method = 1;
    else if (!strcmpi(cmd, 'POST'))
        method = 2;
    else
        client_error(conn_fd, cmd, "501", "Forbidden", "un-implemented yes!\n");

    // 解析uri
    if ( method != parse_uri(uri, filename, cgi_args) )
        client_error(conn_fd, cmd, "", "not match uri\n");

    // 执行
    if (stat(filename, &sbuf)<0)
        clienterror(conn_fd, filename, "404", "Not Found", "");
    if (method==1) { // static
        if (S_ISREG(sbuf.st_mode || S_IRUSR(sbuf.st_mode)))
            clienterror(conn_fd, filename, "403", "Forbidden", "un-accessble");
        serve_static(method, filename, sbuf.st_size);
    }
    else if(method==2) {
        if (S_ISREG(sbuf.st_mode || S_IXUSR(sbuf.st_mode)))
            clienterror(conn_fd, filename, "403", "Forbidden", "un-accessble");
        serve_dynamic(method, filename, cgi_args);
    }
}

