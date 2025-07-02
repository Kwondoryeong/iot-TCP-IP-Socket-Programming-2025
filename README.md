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

#### 루프백 주소
- `127.0.0.1` = 자신의 컴퓨터를 가리키는 IP 주소
- 외부 네트워크를 거치지 않고 내부적으로만 통신
- 네트워크 테스트나 로컬 서버 실행 시 사용
- `ping 127.0.0.1`: 네트워크 스택 자체 점검 가능

## 2일차

### 문자열 정보 처리
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

- [소스코드](./Socket/chapter2/order3.c) IP 주소 문자열을 정수로 변환


- [소스코드](./Socket/chapter2/order4.c) IP 주소 문자열을 구조체의 필드에 저장


- [소스코드](./Socket/chapter2/order5.c)정수형 IP주소를 구조체로 저장 한 후, 다시 문자열으로 출력

- argc (argument count)
    - 인자의 개수
    - 실행 시 전달되는 문자열의 총 개수(자기 자신 포함)

- argv (argument vector)
    - 문자열 배열(char *argv[] == char ** argv) 포인터배열 == 포인터를 포인터로 가리키는 구조
    - 각 인자(문자열)를 가리키는 포인터들의 배열
    - argv[0]은 프로그램 이름, argv[1]부터는 사용자가 넘긴 인자

#### VMwere 창 캡쳐하기 
- Alt + PrtSc : 현재 창만 캡쳐
- PrtSc : 전체화면 캡쳐

#### nano 단축키
- Alt + 6 : 복사
- Ctrl + u : 붙여넣기

### sockaddr_in 구조체 정의 (IPv4 전용)
```c
struct sockaddr_in {
    sa_family_t    sin_family;  // 주소 체계: AF_INET (IPv4)
    in_port_t      sin_port;    // 포트 번호 (network byte order)
    struct in_addr sin_addr;    // IPv4 주소를 저장하기 위해 사용되는 구조체
    char           sin_zero[8]; // 구조체 크기 맞춤용 padding (사용 안함)
};
```
- `sin_family`: 주소 체계를 나타내며 보통 AF_INET으로 설정한다.
- `sin_port`: 포트 번호. htons() 함수로 호스트 바이트 순서를 네트워크 바이트 순서로 변환해서 저장해야 한다.
- `sin_addr`: 실제 IP 주소(in_addr 구조체로 감싸져 있음). inet_pton()이나 inet_addr() 등을 통해 설정한다.
- `sin_zero`: 구조체 크기를 sockaddr과 맞추기 위한 더미 배열. 실제로는 사용되지 않는다
- 참고: 원래 sockaddr_in 구조체 자체는 IPv6 주소 또한 담을 수 있다. IPv4주소만 담을 수 있는 이유는 `in_addr` 구조체 때문이다.

### in_addr 구조체 정의
```c
struct in_addr {
    in_addr_t s_addr; // IPv4 주소 (32비트 정수, network byte order)
};
```
- s_addr는 IPv4 주소를 저장하는 32비트 필드이며, `in_addr_t`는 보통 `uint32_t`
- 이 값은 네트워크 바이트 순서로 저장되어야 하므로, 보통 `inet_addr()`, `inet_pton()` 등을 사용해 IP 문자열을 변환해서 넣는다.

### in_addr_t
in_addr_t는 다음과 같이 정의된 **타입 별칭(alias)**
```
typedef uint32_t in_addr_t;
```
→ in_addr_t는 32비트 부호 없는 정수형(`uint32_t`)을 의미

→ 주로 **IPv4 주소를 표현**하는 데 사용된다.

→ `struct in_addr`처럼 구조체로 감싸진 형태와는 다른 개념.

→ `in_addr_t`는 **데이터 자체**, `in_addr는` **그걸 감싼 껍데기 구조체** 라고 볼 수 있다

#### uint32
C 표준 헤더 <stdint.h>에 정의된 고정 크기 정수형
- u = unsigned
- int = 정수
- 32 = 32비트

→ 32비트 부호 없는 정수
→ 값 범위 0 ~ 4,294,967,295 $(2^{32}-1)$


### 서버, 클라이언트 소켓 통신 간단 구현
- [소스코드-서버](./chapter2/echo_server.c)
- [소스코드-클라이언트](./chapter2/echo_client.c)

### 서버 동작 함수
1. socket()
2. bind()
3. listen()
4. accept()
5. read/write()
6. close()

#### 1. socket()
소켓 생성 – 통신에 사용할 소켓(파일 디스크립터) 생성
```c
int socket(int domain, int type, int protocol);
```
- 매개변수
    - `domain`: 주소 체계 (AF_INET, AF_INET6, AF_UNIX)
    - `type`: 통신 방식 (SOCK_STREAM, SOCK_DGRAM)
    - `protocol`: 보통 0 (자동 선택)
- 리턴값
    - 성공: 소켓 파일 디스크립터 (0이상의 정수)
    - 실패: -1

#### 2. bind()
소켓에 IP주소 + 포트번호 할당 (주소 바인딩)
```c
int bind(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
```
- 매개변수
    - `sockfd`: `socket()`에서 받은 디스크립터
    - `addr`: `sockaddr_in` 구조체 주소 (AF_INET용)
    - `addrlen`: 구조체 크기 (`sizeof(struct sockaddr_in)`)
- 리턴값
    - 성공: 0
    - 실패: -1 (포트 중복 사용, 권한 문제(1024 이하 포트))

#### 3. listen()
연결 요청 대기 상태로 전환
```c
int listen(int sockfd, int backlog);
```
- 매개변수
    - `sockfd`: bind()된 소켓 디스크립터
    - `backlog`: 연결 요청 큐의 최대 길이
- 리턴값
    - 성공: 0
    - 실패: -1

#### 4. accept()
클라이언트 연결 수락, 새 소켓 반환
```c
int accept(int sockfd, struct sockaddr* addr, socklen_t* addrlen);
```
- 매개변수
    - `sockfd`: listen() 상태의 서버 소켓
    - `addr`: 연결한 클라이언트 주소 정보 저장
    - `addrlen`: 구조체 크기(입력 + 출력)
- 리턴값
    - 성공: 새로운 소켓 디스크립터(클라이언트 전용)
    - 실패: -1

**🧠📌서버는 이때 만들어진 새로운 스크립트로 `read()/write()` 수행, 원래 `sockfd`는 계속 `accept()`에 사용**

#### 5. read() / write()
데이터 송수신 (파일/소켓 공통 함수)
```c
ssize_t read(int fd, vojid* buf, size_t count);
ssize_t write(int fd, const void* buf, size_t count);
```
- 매개변수
    - `fd`: accept()에서 받은 소켓 디스크립터
    - `buf`: 데이터 버퍼
    - `count`: 읽거나 쓸 최대 바이트 수
- 리턴값
    - 성공: 읽거나 쓴 바이트 수
    - 실패: -1
    - 0: 상대방이 연결 종료

#### 6. recv() / send()
`read()` / `write()`와 사용법은 유사하지만,
**소켓 통신에 특화된 확장 기능을 제공하는 함수**로, POSIX 시스템(리눅스 등)에서 사용
```c
ssize_t recv(int sockfd, void *buf, size_t len, int flags);
ssize_t send(int sockfd, const void *buf, size_t len, int flags);
```
- 매개변수 
    - `sockfd`: accept() 또는 socket()에서 반환된 소켓 디스크립터.
    데이터를 송수신할 대상 소켓을 식별하는 데 사용됨.
    - `buf`: 
        - recv()의 경우: 수신한 데이터를 저장할 버퍼
        - send()의 경우: 전송할 데이터를 담고 있는 버퍼
    - `len`: buf의 크기. 최대 송수신 바이트 수를 지정
    - `flags`: 송수신 동작을 제어하는 옵션 플래그, 일반적으로 0
        - 사용 가능한 주요 옵션:
        - MSG_PEEK: 수신 버퍼를 비우지 않고 들여다보기
        - MSG_DONTWAIT: 논블로킹 모드로 동작
        - MSG_WAITALL: 지정한 길이만큼 다 받을 때까지 대기
- 리턴값 
    - 성공: 전송된 바이트 수
    - 실패: -1
    - recv()가 0 반환 → 상대가 연결 종료

✅ read() / write()보다 소켓 전용 기능이 있어 실무에서는 recv()/send()를 더 자주 사용
#### 7. close()
열린 소켓 또는 파일 디스크립터 닫기
```c
int close(int fd);
```
- 매개변수
    - fd: socket(), accept() 등으로 생성된 디스크립터
- 리턴값
    - 성공: 0
    - 실패: -1

**🧠📌 `client_fd`, `server_fd` 모두 통신 종료 시 닫아야 리소스 해제**
  
**서버 동작 순서 요약**
```
socket()  →  bind()  →  listen()  →  accept()  →  read()/write()  →  close()
   ↑           ↑           ↑            ↑               ↑               ↑
소켓 생성   주소 할당     대기 시작    클라이언트 연결     데이터 통신       자원 해제

```

### 클라이언트 동작 함수
1. socket()
2. connect()
3. read/write()
4. close()


socket(), read/write(), close()는 함수가 같으므로 [서버 동작 함수](#서버-동작-함수) 참고

### 2.connect()
서버에 연결 시도
```c
int connect(int sockfd, const struct sockaddr* addr, socklen_t addrlen);
```
- 매개변수
  - `sockfd`: socket()에서 얻은 소켓 디스크립터
  - `addr`: 연결할 서버의 주소 (sockaddr_in* 형 변환)
  - `addrlen`: 주소 구조체 크기
- 리턴값
  - 성공: 0
  - 실패: -1 (perror() 등으로 에러 확인)
  
**클라이언트 동작 순서 요약**
```
socket()  →  connect()  →  read()/write()  →  close()
   ↑            ↑               ↑               ↑
소켓 생성   서버에 연결 요청    데이터 통신        자원 해제

```

---
### 추가 적으로 궁금한 점 🤔
#### 파일 디스크립터(File Descriptor)
- 정수값 하나로 OS 내의 열린 리소스를 식별하는 번호
- 리눅스/유닉스 계열에 특화된 개념 
- 참고) 윈도우의 **file handle** 개념과 비슷

**🔸기본 파일 디스크립터 번호**
| 번호 | 이름       | 설명       |
|---| :------: | :-------:|
| 0  | `stdin`  | 표준 입력    |
| 1  | `stdout` | 표준 출력    |
| 2  | `stderr` | 표준 에러 출력 |
→ **모든 프로세스는 최소 0~2번까지 파일 디스크립터를 이미 열고 시작**

**🔸사용 이유**
- **모든 I/O를 추상화**해서 동일한 방식(`read()`, `write()`, `close()`)으로 다룰 수 있음
- 커널이 리소스를 효율적으로 관리할 수 있게 함


## 3일차

### 

#### 

응답으로 날라온 sequence(byte + 1)로 보냄


#### TCP에서 TIMEOUT이 발생하는 기준
1. connect() 타임아웃
    - 클라이언트가 서버에 연결을 시도할 때 서버가 응답하지 않으면 일정 시간 후 실패
2. recv() / read() 타임아웃
    - 데이터를 읽으려고 대기 중일 때 상대방이 보내지 않으면 무한 대기하거나 타임아웃 발생
3. send() / write() 타임아웃
    - 상대방 수신 버퍼가 꽉 찼을 때 데이터를 보낼 수 없어 일정 시간 후 실패


#### TCP 연결 종료 - 4-Way Handshake
- TCP에서 소켓을 끊기 위해서 4way handshake(4단계)로 구현 되어야함(데이터 손실 방지)

1. 클라이언트가 연결 종료 요청 (`FIN`)
2. 서버가 확인 응답 (`ACK`)
3. 서버도 종료 요청 (`FIN`)
4. 클라이언트가 확인 응답 (`ACK`)

<img src="./image/4way_handshake_흐름도.png" width="400" />

- h1이 끊는다고 보내면 h2가 응답을 보내고 먼저 끊음 h1이 
이 과정을 통해 양측은 데이터를 안전하게 모두 주고받은 뒤 **정상적으로 연결을 해제**합니다.


#### Half Close 기법
- 출력버퍼를 닫아도 입력버퍼를 닫으면 안됨 (상대방이 보낸 데이터가 남아 있을 수 있음)
- 입력버퍼에 데이터가 없으면 종료

    shutdown(clnt_fd, SHUT_WR);
    read(clnt_fd, buf, BUF_SIZE);



[소스코드](./Socket/chapter3/file_server.c)
[소스코드](./Socket/chapter3/file_client.c)
- 서버에 작성된 코드가 recieve.dat 파일로 넘어가 만들어짐

##  접속 흐름 요약 (DNS 동작 포함)

1. **사용자가 `www.naver.com` 입력**
   - 브라우저 주소창에 도메인 입력

2. **로컬 DNS 캐시 확인**
   - 내 PC나 브라우저에 IP 정보가 저장되어 있다면 바로 사용

3. **DNS 서버에 질의 요청**
   - 캐시에 없으면, 설정된 DNS 서버(보통 ISP[Internet Service Provider] 제공)에 질의

4. **DNS 서버가 IP 주소 조회**
   - 필요 시 Root DNS → TLD DNS → 권한 DNS 순으로 IP 주소 탐색

5. **IP 주소 응답**
   - DNS 서버가 `www.naver.com`에 해당하는 공인 IP 주소를 사용자에게 전달

6. **해당 IP 주소로 네이버 서버에 접속**
   - TCP 3-way handshake로 연결 후 HTTPS 요청
   - 응답받은 웹페이지를 브라우저에 출력


> 도메인 입력 → 캐시 확인 → DNS 질의 → IP 응답 → 서버 접속 → 페이지 출력

- [소스코드](./Socket/chapter3/gethostbyname.c) 도메인으로부터 IP주소를 획득하는 코드
- [소스코드](./Socket/chapter3/gethostbyaddr.c) IP주소로부터 도메인을 획득하는 코드

## 소켓 옵션 비교표 (`getsockopt` vs `setsockopt`)

| 옵션 이름             | 레벨           | 설명                                      | getsockopt | setsockopt |
|------------------------|----------------|-------------------------------------------|------------|------------|
| `SO_REUSEADDR`         | `SOL_SOCKET`   | 포트 번호 재사용 허용                    | ✅         | ✅         |
| `SO_REUSEPORT`         | `SOL_SOCKET`   | 포트 번호 다중 소켓 재사용 (리눅스 전용) | ✅         | ✅         |
| `SO_KEEPALIVE`         | `SOL_SOCKET`   | 연결 유지 상태 확인                      | ✅         | ✅         |
| `SO_RCVBUF`            | `SOL_SOCKET`   | 수신 버퍼 크기                           | ✅         | ✅         |
| `SO_SNDBUF`            | `SOL_SOCKET`   | 송신 버퍼 크기                           | ✅         | ✅         |
| `SO_LINGER`            | `SOL_SOCKET`   | 소켓 종료 시 대기 여부 설정              | ✅         | ✅         |
| `SO_BROADCAST`         | `SOL_SOCKET`   | UDP 브로드캐스트 허용                    | ✅         | ✅         |
| `SO_ERROR`             | `SOL_SOCKET`   | 마지막 에러 코드 확인 (읽기 전용)        | ✅         | ❌         |
| `SO_TYPE`              | `SOL_SOCKET`   | 소켓 타입 확인 (STREAM/DGRAM 등)         | ✅         | ❌         |
| `TCP_NODELAY`          | `IPPROTO_TCP`  | Nagle 알고리즘 사용 여부                 | ✅         | ✅         |
| `TCP_MAXSEG`           | `IPPROTO_TCP`  | TCP 최대 세그먼트 크기 설정              | ✅         | ✅         |
| `IP_TTL`               | `IPPROTO_IP`   | IP TTL(Time To Live) 설정                | ✅         | ✅         |
| `IP_MULTICAST_TTL`     | `IPPROTO_IP`   | 멀티캐스트 패킷 TTL 설정                 | ✅         | ✅         |
| `IP_MULTICAST_LOOP`    | `IPPROTO_IP`   | 멀티캐스트 루프백 허용 여부             | ✅         | ✅         |

---

#### 참고

- ✅: 사용 가능
- ❌: 사용 불가 (읽기 전용 또는 설정 불가)
- `getsockopt()`은 대부분의 옵션에서 현재 설정 값을 확인할 수 있음
- `setsockopt()`은 읽기 전용 옵션에는 사용할 수 없음


### 다중 접속 서버(I/O Multiplexing & Asyncronous I/O)

- **멀티프로세스 기반**: 클라이언트마다 별도 프로세스를 생성해 처리  
- **멀티플렉싱 기반**: `select`, `poll`, `epoll` 등으로 여러 소켓의 입출력을 하나의 프로세스로 관리  
- **멀티스레드 기반**: 클라이언트마다 별도 스레드를 생성해 병렬 처리

#### 멀티프로세서

- **프로세스**: 실행 중인 프로그램을 의미함
- **`fork()` 함수**를 호출하면 현재 프로세스를 복제하여 **자식 프로세스** 생성

- fork() 함수의 기본 원리
    - fork()는 부모 프로세스가 자신과 완전히 똑같은 프로세스를 복제하는 함수
    복제 이후에는 부모와 자식 모두 fork()의 반환값을 기준으로 서로를 구분 

#### fork()의 반환값 규칙
- 반환값 > 0: 부모 프로세스에서 실행(자식의 PID)
- 반환값 == 0: 자식 프로세스에서 실행
- 반환값 = -1: 자식 프로세스 생성 실패

```c
#include <unistd.h>

pid_t fork(void);
// 성공 시: 자식 프로세스는 0 반환, 부모 프로세스는 자식의 PID 반환(양수)
// 실패 시: -1 반환

pid = fork();

if (pid == 0) {
    puts("child process\n");
    // 자식 프로세스만 이 블록 실행
} else if (pid > 0) {
    puts("child process ID: %d\n", pid)
    // 부모 프로세스만 이 블록 실행(자식PID 출력)
}
```
[소스코드1](./Socket/chapter3/fork.c) [소스코드2](./Socket/chapter3/fork1.c) fork()이후 부모와 자식의 독립적 실행 확인

