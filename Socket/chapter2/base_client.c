#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(int argc, char** argv){
	int sock_fd;
	struct sockaddr_in server_addr;
	char buf[1024];
	int recv_len;

	if((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket failed");
		exit(EXIT_FALLURE);
	}
	

	return 0;
}
