/* server.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 19601

int main(void)
{
    struct sockaddr_in servaddr,cliaddr;  //ipv4 address struct -> sockaddr_in
    socklen_t cliaddr_len;
    int listenfd,connfd;
    char buf[MAXLINE];
    char str[INET_ADDRSTRLEN];
  //  char str[100];
    int i ,n;
    
    listenfd = socket(AF_INET,SOCK_STREAM,0);  //create the socket

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    Bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    listen(listenfd,20);

    printf("Accepting connections ... \n");
    while(1)
    {
        cliaddr_len = sizeof(cliaddr);
        connfd =Accept(listenfd,(struct sockaddr*)&cliaddr,&cliaddr_len);

        n = Read(connfd,buf,MAXLINE);
        printf("Received from %s at port %d .\n",inet_ntop(AF_INET,&cliaddr.sin_addr,str,sizeof(str)),ntohs(cliaddr.sin_port));

        for(i = 0;i < n;i++)
        {
            buf[i] = toupper(buf[i]);
        }
        Write(connfd,buf,n);
        Close(connfd);
    }
}
