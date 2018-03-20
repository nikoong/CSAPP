#include <stdio.h>
#include "csapp.h"
/* Recommended max cache and object sizes */
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

/* You won't lose style points for including this long line in your code */
static const char *requestline_format = "GET %s HTTP/1.0\r\n";
static const char *user_agent_header = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";
static const char *host_header_format = "Host: %s：%s\r\n";
static const char *connection_header = "Connection: close\r\n";
static const char *proxy_connection_header = "Proxy-Connection: close\r\n";
static const char *blank_line = "\r\n";

void doit(int fd);
void parse_uri(char* uri, char* hostname, char* path, char* port);
void build_request_header(char* request_header, char* hostname, 
              char* path, char* port, rio_t* pclient_rio);
void clienterror(int fd, char *cause, char *errnum, 
         char *shortmsg, char *longmsg);


int main(int argc,char **argv)
{
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    /* Check command line args */
    if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
    }

    listenfd = Open_listenfd(argv[1]);
    while (1) {
    clientlen = sizeof(clientaddr);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen); 
        Getnameinfo((SA *) &clientaddr, clientlen, hostname, MAXLINE, 
                    port, MAXLINE, 0);
        printf("Accepted connection from (%s, %s)\n", hostname, port);
    doit(connfd);                                             
    Close(connfd);                                            
    }
}


void doit(int fd) 
{
    int serverfd;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char hostname[MAXLINE], path[MAXLINE], port[MAXLINE], 
         request_header[MAXLINE];
    rio_t rio, server_rio;

    /* Read request line and headers */
    Rio_readinitb(&rio, fd);
    if (!Rio_readlineb(&rio, buf, MAXLINE))  
        return;
    printf("%s", buf);
    sscanf(buf, "%s %s %s", method, uri, version);       
    if (strcasecmp(method, "GET")) {                     
        clienterror(fd, method, "501", "Not Implemented",
                    "Tiny does not implement this method");
        return;
    }                                                    
                            
    /* Parse URI from GET request */
    parse_uri(uri, hostname, path, port);

    /* Build the request header*/
    build_request_header(request_header, hostname, path, port, &rio);

    /*Connect to server*/
    serverfd = Open_clientfd(hostname, port);

    if(serverfd<0){
        printf("connection failed\n");
        return;
    }

    /*Write the http header to server*/
    Rio_readinitb(&server_rio, serverfd);
    Rio_writen(serverfd, request_header, strlen(request_header));

    /*receive message from end server and send to the client*/
    size_t n;
    while( (n=Rio_readlineb(&server_rio,buf,MAXLINE))!=0 )
    {
        printf("proxy received %zu bytes,then send\n",n);
        Rio_writen(fd, buf, n);
    }
    Close(serverfd);
}


/*
 * parse_uri - parse the uri, get hostname, path and port information 
 */
void parse_uri(char* uri, char* hostname, char* path, char* port)
{
    char buf[MAXLINE];
    /*position to "//", the first"/", ":" */ 
    char* pstart, *ppath, *pport;

    strcpy(buf, uri);

    pstart = strstr(buf, "//") + 2;
    ppath = strchr(pstart, '/');
    if(!ppath){
        strcpy(path, "/");
    }else{
        strcpy(path, ppath);
        *ppath = 0;
    }

    pport = strchr(pstart, ':');
    if(!pport){
        strcpy(port, "80");
        strcpy(hostname, pstart);
    }else{
        strcpy(port, pport+1);
        *pport = 0;
        strcpy(hostname, pstart);
    }

}




/*
 * build_request_header - build request_header with the Host, 
 * User-Agent, Connection, and Proxy-Connection headers.
 * It is possible that web browsers will attach their own Host headers to their HTTP requests. 
 * If that isthe case, the proxy will use the same Host header as the browser.
 */
void build_request_header(char* request_header, char* hostname, 
              char* path, char* port, rio_t* client_rio)
{
    char buf[MAXLINE], host_header[MAXLINE], other_header[MAXLINE];
    strcpy(host_header, "\0");
    sprintf(request_header, requestline_format, path);
    
    /*check host header and get other request header for client rio then change it */
    while(Rio_readlineb(client_rio, buf, MAXLINE) >0){
        if(strcmp(buf, blank_line)==0) break;//EOF
        if(strncasecmp("Host:", buf, strlen("Host:"))){
            strcpy(host_header, buf);
            continue;
        }
        //when this line is not  proxy_connection header or connection header or user-agent:
        if( !strncasecmp("Connection:", buf, strlen("Connection:")) 
            && !strncasecmp("Proxy-Connection:", buf, strlen("Proxy-Connection:"))
            && !strncasecmp("User-Agent:", buf, strlen("User-Agent:")) )
        {
            strcat(other_header, buf);
        }
    }
    if(strlen(host_header) == 0){
        sprintf(host_header, host_header_format, hostname, port);
    }
    strcat(request_header, host_header);
    strcat(request_header, user_agent_header);
    strcat(request_header, other_header);
    strcat(request_header, connection_header);
    strcat(request_header, proxy_connection_header);
    strcat(request_header, blank_line);
}

/*
 * clienterror - returns an error message to the client
 */
void clienterror(int fd, char *cause, char *errnum, 
         char *shortmsg, char *longmsg) 
{
    char buf[MAXLINE], body[MAXBUF];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""ffffff"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    Rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
}
