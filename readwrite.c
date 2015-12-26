#include <unistd.h>
#define size 100
int main(void)
{
    int n;
    char buf[size];
    
    while(n = read(STDIN_FILENO,buf,size))
    {
        if(n != write(STDOUT_FILENO,buf,n))
            perror("write error");
    }
    if(n < 0) perror("read error");
    return 0;
}
