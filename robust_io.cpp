//
// Created by System Administrator on 9/27/15.
//

#include "robust_io.h"

roi* rio_readinitb(int fd){
    roi* ans;
    ans->fd = fd;
    ans->free_size = 0;
    ans->curr_p = ans->buf;
    return ans;
}



int rio_read(rio* stream, char* usrbuf, size_t bytes) {
    // 从当前buf里面读取bytes字节数据
    while (stream->free_size <=0){
        stream->free_size = read(stream->fd, stream->buf, sizeof(stream->buf));
        if (stream->free_size < 0){
            if (errno != EINTR) // ???
                return -1;
        }
        else if(stream->free_size ==0) // EOF
            return 0;
        else
            stream->curr_p += stream->buf; // reset stream->curr_p
    }
    int cnt = bytes;
    if (stream->free_size < cnt)
        cnt = stream->free_size;
    memcpy(usrbuf, stream->curr_p, cnt);
    stream->curr_p += cnt;
    stream->free_size -= cnt;
    return cnt;
}

int rio_readlineb(rio* stream, char* res){
    int len=0;
    int ans;
    while ((ans=rio_read(stream, res, 1)) == 1){
        switch (*res){
            case '\n':
                *res = '\0';
                return len;
                break;
            default:
                len += 1;
                res++;
                continue;
        }
    }
    return (ans==-1)?ans:len;
}