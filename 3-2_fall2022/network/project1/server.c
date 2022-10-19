#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_MESSAGE 1024

void *thread_recv(void *arg); // 클라이언트로부터 데이터를 수신받는 함수
void error_handling(char *message); // 에러 발생 시, 에러 문구 출력 후 프로그램 종료시키는 함수

static void *treturn;
static pthread_t thread;
static bool thread_exit = false;

// 클라이언트의 정보 -> 멀티스레드를 위해 전역변수로 설정
static struct sockaddr_in clnt_addr;
int clnt_sock;

int main(int argc, char **argv)
{
    /*
        - unix/linux 시스템에서는 socket의 통신 대상을 지정하기 위해 주소(address) 사용
        - 주소를 저장하기 위해 구조체 sockaddr 사용
        - 기본형태: sockaddr, AF_INET인 경우(IPv4 영역에서의 통신) 형태: sockaddr_in
            -> 주소체계(address family) 값에 따라 구조체 sockaddr를 형변환하여 사용
            -> 구조체 sockaddr를 그대로 사용하는 경우 IP 주소와 Port 번호가 조합되어 있어 읽고 쓰기 불편하기 때문

        struct sockaddr {
            unsigned short  sa_family; // 주소 체계     
            char    sa_data[14]; // 실제 주소 저장 = IP address + port number
        }; // 총 16byte

        struct sockaddr_in {
            short    sin_family;          // 주소 체계: AF_INET (IPv4)
            u_short  sin_port;            // 2byte port number -> 0 ~ 65535,  network byte order 따름
            struct   in_addr  sin_addr;   // 4byte host의 IP 주소
            char     sin_zero[8];         // 전체 크기를 16byte로 맞추기 위한 dummy -> 0으로 채워져야함 (padding bytes)
        };

        struct  in_addr {
            u_long  s_addr;     // 32bit의 IP 주소를 저장 할 구조체, network byte order 따름
        };
    */
    struct sockaddr_in serv_addr;
    socklen_t clnt_addr_size; // socklen_t: 소켓 관련 매개변수의 길이 및 크기 값 정의

    int serv_sock; // server

    char message[MAX_MESSAGE]; // 전송할 데이터를 저장하는 공간
    char clnt_ip[20]; // 클라이언트의 ip를 저장하는 공간

    // 실행 시, $ server <Port> 형태로 입력해야함
    if(argc != 2)
    {
        printf("Usage: %s <Port>\n", argv[0]);
        exit(1);
    }

    /*
        - 함수 원형: int socket(int domain, int type, int protocol)
        - socket를 생성하는 함수로 sys/socket.h 내부에 존재
        - domain: 통신할 영역 지정 -> IPv4를 사용할 예정으로 AF_INET 사용
        - type: socket의 타입 지정 -> TCP를 사용할 예정으로 SOCK_STREAM 사용
        - protocol: socket에서 사용할 프로토콜 지정 -> type에서 미리 지정할 예정으로 0 사용
        - return 값: 성공하면 생성한 socket을 가리키는 socket descriptor, 실패하면 -1
    */
    serv_sock = socket(PF_INET, SOCK_STREAM, 0); // TCP 연결 지향형 및 IPv4 도메인을 위한 '소켓 생성'
    if(serv_sock < 0)
        error_handling("server: socket error");

    memset(&serv_addr, 0, sizeof(serv_addr)); // 서버의 주소(address), 즉 서버의 통신 대상을 지정하기 위한 공간 초기화 및

    // 서버의 IP 주소와 서버 프로세스를 켜놓을 port 지정
    // htons(): 2byte 데이터에 대해 바이트 순서를 빅 엔디안 순서로 변환 
    // htonl(): 4byte 데이터에 대해 바이트 순서를 빅 엔디안 순서로 변환 
    // -> TCP/IP는 빅 엔디안 방식을 사용
    serv_addr.sin_family = AF_INET; // 주소 체계: AF_INET (IPv4)
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); // ip 주소 -> INADDR_ANY


    /*
        - 함수 원형: int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen)
        - socket과 server의 정보를 묶어주는 함수로 sys/socket.h 내부에 존재
        - bind가 필요한 이유: 
            외부의 컴퓨터가 IP주소를 기반으로 서버에 연결하려고 요청
            통신을 위해서는 socket descriptor의 번호를 알아야함
            IP 주소를 안다고 이를 아는 것이 아니므로, socket과 server의 정보를 묶어줌
        - sockfd: socket descriptor(생성한 socket을 가리킴)
        - myaddr: 서버의 IP 주소
        - addrlen: myaddr의 크기(길이)
        - return 값: 성공하면 0, 실패하면 -1
    */
    if(bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) // socket에 '주소(address) 할당'
        error_handling("server: bind error");

    /*
        - 함수 원형: int listen(int sockfd, int backlog)
        - 외부 컴퓨터로부터의 서버 요청을 수락할 수 있는 대기 상태에 들어가게 하는 함수로 sys/socket.h 내부에 존재
        - sockfd: socket descriptor(생성한 socket을 가리킴)) 
        - backlog: 연결 대기열의 크기, 즉 연결요청 대기 큐(Queue)의 크기 정보 지정
                   -> 1이면 클라이언트의 연결요청을 1개까지 대기 가능
        - return 값: 성공하면 0, 실패하면 -1
    */
    if(listen(serv_sock, 1) < 0) // 외부 컴퓨터로부터 서버 '연결 요청 대기 상태'
        error_handling("server: listen error");

    clnt_addr_size = sizeof(clnt_addr); // accept()에서 세번째 인자로 사용하기 위함
    while(true)
    {
        printf("======= [Port] : %d ========\n", atoi(argv[1]));
        printf("server: TCP server is ready to receive\n\n");
        /*
            - 함수 원형: int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
            - 서버 socket에 클라이언트를 연결, 즉 들어온 순서대로 연결 요청을 수락하는 함수로 sys/socket.h 내부에 존재
            - accept() 호출 -> 자동으로 소켓이 생성 및 해당 소켓과 연결 요청을 한 클라이언트 소켓의 연결
            - sockfd: 서버의 socket descriptor
            - addr: 클라이언트의 정보를 담을 구조체
            - addrlen: addr의 길이(크기)
            - return 값: 성공하면 생성된 socket을 가리키는 socket descriptor, 실패하면 -1
        */
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size); // 연결 요청을 한 클라이언트 소켓의 '연결 허용'
        if(clnt_sock < 0)
            error_handling("accept error");

        // inet_ntop(): 네트워크 바이트 정렬 방식(빅엔디안)의 IPv4 주소를 문자열(리틀엔디안) 주소로 변환
        // inet_ntoa(): 네트워크 바이트 정렬 방식(빅엔디안)의 IPv4 주소를 표준 점선 소수점 형식의 문자열(리틀엔디안) 주소로 변환
        // ntohs(): 2byte 데이터에 대해 바이트 순서를 리틀 엔디안 순서로 변환 
        inet_ntop(AF_INET, &clnt_addr.sin_addr.s_addr, clnt_ip, sizeof(clnt_ip));
        printf("server: %s client connect\n", clnt_ip);
        printf("%s(%d)님이 들어오셨습니다.\n\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port));

        thread_exit = false;
        pthread_create(&thread, NULL, thread_recv, NULL); // 클라이언트로부터 데이터 받는 스레드 생성

        // 서버가 데이터를 전송하는 스레드
        while(!thread_exit)
        {
            fgets(message, MAX_MESSAGE, stdin); // 전송할 데이터 입력 받음
   
            // 리눅스에서는 socket을 파일처럼 다룸 -> 데이터 전송 시 write() 사용
            if(write(clnt_sock, message, sizeof(message)) < 0)
                printf("message send failed\n\n");
        }

        // 현재 접속된 클라이언트와의 연결 해제 및 새로운 클라이언트의 요청 대기
        pthread_detach(thread);

        close(clnt_sock);
        printf("server: %s client closed\n\n", clnt_ip);
    }

    close(serv_sock); // 서버 종료

    return 0;
}

void *thread_recv(void *arg)
{
    char message[MAX_MESSAGE] = "\0";
    int len;

    // thread_exit == true 가 아닌 동안 클라이언트로부터 데이터 수신 -> 멀티스레드로 실행되는 중
    while(!thread_exit)
    {
        // 리눅스에서는 socket을 파일처럼 다룸 -> 데이터 수신 시 read() 사용
        if((len = read(clnt_sock, message, sizeof(message))) < 0)
        {
            // thread_exit가 read 도중에 바뀌어도 문제생기지 않도록
            if(!thread_exit)
                printf("message receive failed\n\n");
            else
                break;
        }
        else
        {
            message[len] = '\0';
            if(!strcmp(message, "quit")) // 클라이언트가 quit 입력 시, 연결 종료
            {
                thread_exit = true;
                break;
            }
            
            // 클라이언트가 전송한 정보 출력
            printf("[접속자: %s(%d)]: %s\n", inet_ntoa(clnt_addr.sin_addr), ntohs(clnt_addr.sin_port), message);
        }
    }

    pthread_exit(NULL);
}

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}