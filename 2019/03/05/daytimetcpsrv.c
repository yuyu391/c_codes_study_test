#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char **argv)
{
	int	listenfd, connfd;
	struct sockaddr_in	servaddr;
	char buff[1024+1];
    time_t ticks;

	if ( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		printf("socket error[%d]:%s \n", errno, strerror(errno));
		exit(1);
	}

	memset( &servaddr, 0x00, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(6013);

    if ( bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr) ) < 0 ) {
        printf("bind error[%d]:%s \n", errno, strerror(errno));
        exit(1);    
    }
    
    if ( listen(listenfd, 128 ) < 0 ) {
        printf("listen error[%d]:%s \n", errno, strerror(errno));
        exit(1);    
    }
    
    while (1) {
        connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);
        ticks = time((time_t *)0);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
    }
	return 0;
}
