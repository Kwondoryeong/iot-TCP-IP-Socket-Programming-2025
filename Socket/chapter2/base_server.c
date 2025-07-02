#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    const char* message = "Hello world!!\n";

    // 소켓 생성
    if ((server_fd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(1);
    }

    // 서버 주소 초기화 및 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);       // 모든 IP로부터 연결 허용
    server_addr.sin_port = htons(atoi(argv[1]));           // 포트번호 설정

    // 바인딩
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind failed");
        close(server_fd);
        exit(1);
    }

    // 연결 대기
    if (listen(server_fd, 5) == -1) {
        perror("listen failed");
        close(server_fd);
        exit(1);
    }

    client_addr_len = sizeof(client_addr);

    // 연결 수락
    if ((client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len)) == -1) {
        perror("accept failed");
        close(server_fd);
        exit(1);
    }

    // 메시지 전송
    if (write(client_fd, message, strlen(message)) == -1) {
        perror("write failed");
    }

    // 종료
    close(client_fd);
    close(server_fd);

    return 0;
}
