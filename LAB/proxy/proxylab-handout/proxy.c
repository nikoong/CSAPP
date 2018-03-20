#include <stdio.h>

/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

int main(int argc,char **argv)
{
    int listenfd,connfd;
    socklen_t  clientlen;
    char hostname[MAXLINE],port[MAXLINE];

    struct sockaddr_storage clientaddr;/*generic sockaddr struct which is 28 Bytes.The same use as sockaddr*/

    if(argc != 2){
        fprintf(stderr,"usage :%s <port> \n",argv[0]);
        exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd,(SA *)&clientaddr,&clientlen);

        /*print accepted message*/
        Getnameinfo((SA*)&clientaddr,clientlen,hostname,MAXLINE,port,MAXLINE,0);
        printf("Accepted connection from (%s %s).\n",hostname,port);

        /*sequential handle the client transaction*/
        doit(connfd);

        Close(connfd);
    }
    return 0;
}
