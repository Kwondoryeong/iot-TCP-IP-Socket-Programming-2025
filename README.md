# iot-TCP-IP-Socket-Programming-2025

## TCP/IP 1일차

### VMware 및 Ubuntu

#### VMware 설치
1. Broadcom회원가입: https://www.broadcom.com/ - Support Portal - Register
2. 접속: https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion
3. DOWNLOAD FUSION OR WORKSTATION 클릭
4. My Downloads의 Free Software Downloads available **HERE** 클릭
5. 하단의 Vmware WorkStation Pro 클릭
6. VMware Workstation Pro 17.0 for Windows 클릭 
7. relese 버전 선택(17.6.3)
8. 동의 버튼 체크(하이퍼링크 클릭 후 체크 가능) - 다운로드
9. 관리자 권한으로 installer 실행
10. Add VMware Workstation console tools into system PATH 체크 설치


#### Ubuntu 설치
1. VMware Workstation Pro 실행
2. Create a New Virtual Machine 클릭 - Custom(advanced)
3. Installer disc Image file(iso): Browse에서 ubuntu.iso 파일 선택 - 기본 설정 후 Next


#### 소켓통신(이더넷, 인터넷 통신) 방식 2가지
- TCP방식: 파일, 메세지 
- UDP방식: 방송관련
- 실시간 데이터 송수신 구현
- 클라이언트(Client): 정보를 요청하는 쪽
- 서버(Server): 클라이언트의 요청을 받아서 응답하는 쪽

#### IP와 PORT
- 클라이언트가 서버에 접속하기 위해 IP주소로 서버를 찾아감 > 정보를 가지고 있는 응용프로그램을 찾기 위해 PORT 필요
- HTTP(HyperText Transfer Protocol) : 웹 데이터를 주고 받기 위한 통신 규약
- HTTPS(HyperText Transfer Protocol Secure) : SSL/TLS 암호화로 데이터를 주고 받아 도청, 위조 방지

### 소켓(Socket)
1. 소켓의 개념
    - 소켓: 네트워크 통신의 끝단(endpoint)
    - 클라이언트와 서버는 **소켓을 통해 연결**되고 데이터를 주고 받음

#### 서버 소켓 함수 호출 순서
1. socket(): 소켓 생성
2. bind(): 소켓 연결(주소 할당 - IP주소와 포트 소켓에 할당) 
3. listen(): 연결 요청 대기(서버)
4. accept(): 클라 연결 허용(서버) & 새로운 소켓 반환: 반환된 소켓으로 실제 데이터 송수신에 사용
5. recv()/send(): 데이터 송/수신
6. close(): 소켓 종료

#### 클라이언트 소켓 함수 호출 순서
1. socket(): 소켓 생성
2. connect(): 서버에 연결 요청
3. send()/recv(): 데이터 송수신
4. close(): 소켓 종료

### ubuntu
- ubuntu 커맨드 창 단축키 : ctrl + alt + t
```bash
sudo apt install net-tools      // 네트워크 관련 도구 설치
sudo apt install openssh-server // SSH 서버(원격 접속 기능) 설치
ifconfig    
> inet 192.xxx.xxx.xxx 
```
- putty에서 inet의 ip 입력 > port: 22 > telnet > ubuntu로 save - load - open

- ID, Password 입력
- change settings 후 session에 save 후 apply

```sh
// putty에서 입력 
sudo apt upgrade
sudo apt update

mkdir Work
mkdir Socket

sudo nano /etc/nanorc
set autoindent
set historylog
set linenumbers
set locking
set stateflags
set tabsize 3
```

#### 명령어 
- `uname`: 시스템 정보 출력 (운영체제 확인)
- `ls`: 현재 디렉터리의 파일 및 폴더 목록 보기
- `pwd`: 현재 디렉터리의 경로 출력
- `cd`: 디렉터리 이동
- `cd ..`: 상위 디렉터리로 이동
- `mkdir`: 새 디렉터리(폴더) 생성
- `rmdir`: 비어 있는 디렉터리(폴더) 삭제 
    - r : 파일 있어도 강제 삭제(순환 삭제)
    - f : 강제 삭제(에러 무시)
    - i : 삭제 전 확인
    - rf : 경고 없이 폴더 및 모든 내용 삭제 하므로 위험
- `rm`: 파일 또는 디렉터리 삭제
- `touch`: 새 파일 생성 또는 기존 파일의 수정
시간을 갱신
- `nano`: 터미널 기반 텍스트 편집기로 파일 내용 편집
- `cat`: 파일 내용 출력 (읽기 전용)
- `cp`: 파일이나 디렉터리 복사(깊은 복사)
    - r : cp -r dir1/ dir2/ - dir1의 모든 파일과 하위 폴더를 재귀적으로 복사
    - cp test.txt test1.txt : text.txt 파일을 text1.txt에 복사
- `mv`: 파일이나 디렉터리 이동 또는 이름 변경
    ```bash
    // 현재 디렉터리(./)에 있는 test.txt 파일을 상위 디렉터리(../)로 이동
    mv ./test.txt ../
    ```
- `gcc`: C 언어 컴파일러 (소스 코드를 실행 파일로 컴파일)
    - duplicate session 사용하여 코드 확인하며 수정
    - `-o`: 출력 파일 이름 지정 (예: `gcc main.c -o main`)
    - `./실행파일명`: 컴파일된 실행 파일 실행 (예: `./main`)
    ```bash
    sudo apt install gcc
    gcc main.c  // a.out이라는 실행 파일 만들어짐
    gcc main.c -o main // main이라는 실행 파일 만들어짐
    ./main      // 현재 폴더에 있는 main 실행
    ```
#### 단축키 
    - 저장: ctrl + s 
    - 나가기: ctrl + x


#### 나중에 파일 첨부할 것

```c
#include<stdio.h>
#include<unistd.h>

int main(){
    int fd1, fd2, fd3;

    // fd1 = socket(PF_INET, SOCK_STREAM, 0);
    // fd2 = open("test.dat", O_CREATE|O_WRONLY);
    // fd3 = socket(PF_INET, SOCK_DGRAM, 0);

    fd1 = fileno(stdin)  // 표준입력
    fd2 = fileno(stdout) // 표준출력
    fd3 = fileno(stderr) // 표준에러

    printf("fd 1: %d\n", fd1);
    printf("fd 2: %d\n", fd2);
    printf("fd 3: %d\n", fd3);

    close(fd1);
    close(fd2);
    close(fd3);

    return 0;
}

#include<stdio.h>

int main(){
    int fd;
    fd = opent("a.txt", O_CREAT | O_RDONLY);
    if(fd < ){
        perror("could not open a.txt")
        exit(1);
    }
    else{
        printf("open success!!");
        printf("file descripter : %d\n", fd);
    }
    
    return 0;
}

#include<fcntl.h>

int open(const char* name, int flags)
flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_RRUNC, O_APPEND

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
    int fd;
    char str[] = "Hello socket!!";
    fd = open("hello.txt", O_CREAT | O_WRONLY);
    if(fd < 0){
        perror("could not open hello.txt");
        exit(1);
    }
    if(write(fd, str, strlen(str) + 1) < 0){
        perror("Failed to write to file");
        exit(1);
    }
    close(fd);

    return 0;
}
/*
#include<unistd>
ssize_t write(int fd, const void* buf, size_t nbytes);
*/
```

#### open() 함수에서 사용하는 주요 플래그
- `#include<fcntl.h>`: 헤더 추가필요
- `O_RDONLY`: 읽기 전용으로 파일 열기
- `O_WRONLY`: 쓰기 전용으로 파일 열기
- `O_RDWR`: 읽기 및 쓰기 모두 가능하게 파일 열기
- `O_CREAT`: 파일이 없으면 새로 생성 (권한 필요)
- `O_TRUNC`: 파일을 열 때 기존 내용 제거
- `O_APPEND`: 파일 끝에 데이터를 추가 (이어쓰기 모드)

#### 플래그는 `|` 연산자로 조합하여 사용함  
- 예: `O_WRONLY | O_CREAT | O_TRUNC`

```bash
// 권한
chmod 774 hello.txt
sudo cat hello.txt

ssize_t raed(int fd, void* buf, size_t count);

```

### read() 함수

```c
ssize_t read(int fd, void* buf, size_t count);

```
- fd: 읽고자 하는 파일 디스크립터 번호 (open() 또는 socket() 등을 통해 얻음)
- buf: 읽은 데이터를 저장할 메모리 주소 (버퍼)
- count: 최대 읽을 바이트 수 (버퍼 크기)

- 추가 설명
    - `ssize_t`는 음수도 표현 가능한 정수형으로, 오류(-1) 처리를 위해 사용됨 (size_t : 양수만)
    - 파일 디스크립터(fd)는 리눅스에서 열린 파일을 식별하는 정수 값

#### 엔디안(Endian)

멀티바이트 데이터(예: int형 4바이트)를 메모리에 저장할 때, 바이트 순서를 결정하는 방식

| 구분 | 저장 방식 | 예: `0x12345678` 저장 시 (낮은 주소부터) |
|------|-----------|------------------------------------------|
| 리틀 엔디안 (Little Endian) | 가장 작은 바이트(LSB)를 **낮은 주소**에 저장 | `78 56 34 12` |
| 빅 엔디안 (Big Endian)     | 가장 큰 바이트(MSB)를 **낮은 주소**에 저장 | `12 34 56 78` |

- 대부분의 PC/Intel/ARM 시스템: **리틀 엔디안**
- 네트워크, 일부 특수 장치: **빅 엔디안**

- 프로토콜은 항상 빅 엔디안을 사용하기 때문에 바이트 순서를 미리 맞춰야 상대방이 제대로 해석할 수 있음
    - htons(port) : 호스트 바이트 순서 -> 네트워크 바이트 순서(=빅 엔디안)로 변환
    - htonl(ip) : 호스트바이트 순서 -> 네트워크 바이트 순서(=빅 엔디안)로 변환

[리틀엔디안 첨부1](./Socket/chapter1/order.c)
[리틀엔디안 첨부2](./Socket/chapter1/order1.c)

#### 엔디안 관련 함수 (htons, htonl 등)

네트워크에서는 **빅 엔디안(=네트워크 바이트 오더)** 를 사용하므로,  
리틀 엔디안 시스템에서는 바이트 순서를 바꿔야 할 때 아래 함수를 사용함.

| 함수 | 의미 | 대상 | 설명 |
|------|------|------|------|
| `htons()` | Host TO Network Short | 16비트 | 호스트 바이트 순서 → 네트워크 바이트 순서 (2바이트) |
| `htonl()` | Host TO Network Long  | 32비트 | 호스트 바이트 순서 → 네트워크 바이트 순서 (4바이트) |
| `ntohs()` | Network TO Host Short | 16비트 | 네트워크 바이트 순서 → 호스트 바이트 순서 (2바이트) |
| `ntohl()` | Network TO Host Long  | 32비트 | 네트워크 바이트 순서 → 호스트 바이트 순서 (4바이트) |

- `h`: host (내 컴퓨터의 엔디안 순서)
- `n`: network (빅 엔디안)

- 대부분의 PC는 리틀 엔디안이므로 실제로는 바이트 순서가 바뀜
- 네트워크 전송 전에 항상 `htons`, `htonl` 등을 사용하는 것이 좋음

#### IPv4 클래스 기반 주소 체계
    - 클래스 A: 네트워크 ID(1바이트) + 호스트 ID(3바이트) → IP 범위: 1.0.0.0 ~ 127.255.255.255
    - 클래스 B: 네트워크 ID(2바이트) + 호스트 ID(2바이트) → IP 범위: 128.0.0.0 ~ 191.255.255.255
    - 클래스 C: 네트워크 ID(3바이트) + 호스트 ID(1바이트) → IP 범위: 192.0.0.0 ~ 223.255.255.255
    - 클래스 D: 멀티캐스트 전용 (네트워크/호스트 구분 없음) → IP 범위: 224.0.0.0 ~ 239.255.255.255

- 네트워크 ID: 어떤 네트워크에 속하는지 구분
- 호스트 ID: 해당 네트워크 안의 개별 장치(IP)
- 현재는 클래스 기반이 아닌 **CIDR(사이더) 방식**(`192.168.0.0/24`)이 주로 사용

- 프로토콜 체계
    - PF_INET: IPv4 인터넷 프로토콜 체계
    - PF_INET6: IPv6

- 소켓의 타입(전송방식)
    - TCP(연결지향형 소켓) - SOCK_STREAM
    - UDP(비연결지향형 소켓) - SOCK_DGRAM


### 문자열 정보처리

```c
#include  <arpa/inet.h>
// 문자열 형태의 IP주소를 32비트 정수형으로 변환하는 함수
in_addr_t inet_addr(const char* string);
// 성공 시 빅엔디안으로 변환된 32비트 정수 값, 실패 시 INADDR_NONE(-1) 반환

#include  <arpa/inet.h>
/* 문자열을 정수 IP로 변환 */
int inet_aton(const char* string, struct in_addr* addr);
// 성공 시 true(1), 실패 시 false(0) 반환

#include  <arpa/inet.h>
/* 정수 IP를 문자열 주소로 변환 */
Char* inet_ntoa(struct in_addr adr);
// 성공 시 변환된 문자열의 주소, 실패 시 -1 반환

```

- IP 주소 문자열을 정수로 변환
[C언어](./Socket/chapter2/order3.c)

- IP 주소 문자열을 구조체의 필드에 저장
[C언어](./Socket/chapter2/order4.c)

- 정수형 IP주소를 구조체로 저장 한 후, 다시 문자열으로 출력
[C언어](./Socket/chapter2/order5.c)

#### 루프백 주소
- `127.0.0.1` = 자신의 컴퓨터를 가리키는 IP 주소
- 외부 네트워크를 거치지 않고 내부적으로만 통신
- 네트워크 테스트나 로컬 서버 실행 시 사용
- `ping 127.0.0.1`: 네트워크 스택 자체 점검 가능


