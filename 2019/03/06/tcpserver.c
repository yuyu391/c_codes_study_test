#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <time.h>

int main(int argc, char **argv)
{
	time_t ticks;
	ticks = time((time_t *)NULL);		
	ticks = time(NULL);		
	printf("%.24s\r\n", ctime(&ticks));


	return 0;
}
