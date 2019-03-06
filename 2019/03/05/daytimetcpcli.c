#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netinet/in.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char **argv)
{
	int	sockfd,n;
	char	recvline[1024+1];
	struct sockaddr_in	servaddr;

	if ( argc !=2 ) {
		printf("usage: a.out <IP address>!\n");
		exit(1);
	}

	if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
		printf("socket error[%d]:%s \n", errno, strerror(errno));
		exit(1);
	}

	memset( &servaddr, 0x00, sizeof(servaddr) );
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(6013);
	if ( (inet_pton(AF_INET, argv[1], &servaddr.sin_addr)) <= 0 ) {
		printf("inet_pton error[%d]:%s \n", errno, strerror(errno));
		exit(1);
	}
	
	if ( connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
		printf("connect error[%d]:%s\n", errno, strerror(errno));
		exit(1);
	}	

	while ( (n = read(sockfd, recvline, 1024)) > 0 ) {
		recvline[n] = 0;
		if ( fputs(recvline, stdout) == EOF ) {
			printf("fputs error[%d]:%s \n", errno, strerror(errno));
			exit(1);
		}
	}
	
	if ( n < 0 ) {
		printf("read error[%d]:%s \n", errno, strerror(errno));
		exit(1);
	}
	return 0;
}
