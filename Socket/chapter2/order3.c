#include <stdio.h>
#include <arpa/inet.h>

void main(){
	char* addr = "192.168.0.1";
	// inet_addr함수는 .으로 구분된 형태를 ip주소로 변환
	unsigned int cv_addr = inet_addr(addr); 
	if(cv_addr == INADDR_NONE) perror("Error");
	printf("address: %#x\n", cv_addr);	

	printf("unsigned int: %lu\n", sizeof(unsigned int));
	printf("unsigned long: %ld\n", sizeof(unsigned long int));

}
