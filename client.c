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

int main(int argc,char *argv[])
{
    struct sockaddr_in servaddr;
    char buf[MAXLINE];
    int sockfd,n;
    char *str;

    if(argc != 2)
    {
        fputs("usage:./client message\n",stderr);
        exit(1);
    }
    str = argv[1];
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    inet_pton(AF_INET,"127.0.0.1",&servaddr.sin_addr);
    servaddr.sin_port = htons(SERV_PORT);
    
    Connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));

    Write(sockfd,str,strlen(str));

    n = Read(sockfd,buf,MAXLINE);  //read the message from sockfd to the buf array

    printf("Response from server:\n");
   // printf("%s\n",buf);
    Write(STDOUT_FILENO,buf,n);  // print the buf to the screen
    printf("\n");
    Close(sockfd);
    return 0;
}
