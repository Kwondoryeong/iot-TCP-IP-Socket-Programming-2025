#include <stdio.h>
/* Little Endian - 작은주소에 작은값저장*/
void main(){
	int n = 0x1234567;//리틀엔디안
	// int n = 0x6745231;//빅엔디안 작은주소에큰값저장
	char *pn = (char*)&n;
	printf("1st: %p, %#x\n", &(*pn), *pn);		// 작은주소
	printf("2nd: %p, %#x\n", &(*(pn+1)), *(pn+1));
	printf("3rd: %p, %#x\n", &(*(pn+2)), *(pn+2));
	printf("4th: %p, %#x\n", &(*(pn+3)), *(pn+3));	// 큰주소
}
