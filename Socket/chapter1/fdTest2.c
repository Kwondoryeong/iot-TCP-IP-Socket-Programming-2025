#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>

int main(){

	int fd;
	fd = open("a.txt", O_CREAT | O_RDONLY);
	if(fd < 0){ // 예외처리코드
		perror("could not open a.txt"); //에러 뜨면 에러 출력
		exit(1);
	}
	else{
		printf("open success!!\n");
		printf("file descripter: %d\n", fd);
	}

	close(fd)	// unistd.h
	return 0;

}
/*
#include<fcntl.h>

int open(const char* name, int flags)
flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_RRUNC, O_AAENO)
*/
