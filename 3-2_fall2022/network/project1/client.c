#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
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

int clnt_sock;

int main(int argc, char **argv)
{
    struct sockaddr_in serv_addr;
    char message[MAX_MESSAGE] = "\0";

    // 실행 시, $ client <IP> <Port> 형태로 입력해야함
    if(argc != 3)
    {
        printf("Usage: %s <IP> <Port>\n", argv[0]);
        exit(1);
    }

    // TCP 연결 지향형 및 IPv4 도메인을 위한 '소켓 생성'
    clnt_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(clnt_sock < 0)
        error_handling("client: socket error");

    memset(&serv_addr, 0, sizeof(serv_addr)); // 인자로 받은 서버 주소를 저장하기 위한 공간 초기화
    serv_addr.sin_family = AF_INET; // 주소 체계: AF_INET (IPv4)
    serv_addr.sin_port = htons(atoi(argv[2])); // 인자로 받은 port 번호 저장
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]); // 인자로 받은 ip 주소 저장

    /*
        - 함수 원형: int connect(int sockfd, struct sockaddr* serv_addr, socklen_t addrlen)
        - 서버에 연결을 요청하는 함수로 sys/socket.h 내부에 존재
        - sockfd: serv_addr에 해당하는 서버와 데이터를 주고 받을 client socket을 가리키는 socket descriptor 
        - serv_addr: 서버의 주소 정보
        - addrlen: serv_addr의 크기(길이)
        - return 값: 성공하면 0, 실패하면 -1
    */
    if(connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error_handling("client: connect error");
    
    printf("=================================================\n");
    printf("client: %s server connect\n", argv[1]);
    printf("%s 방에 입장하셨습니다. 방에서 나가려면 quit를 입력하세요.\n\n", argv[1]);

    pthread_create(&thread, NULL, thread_recv, NULL); // 서버로부터 데이터 받는 스레드 생성

    // 클라이언트가 데이터를 전송하는 스레드
    while(!thread_exit)
    {        
        fgets(message, MAX_MESSAGE, stdin); // 전송할 데이터 입력 받음

        message[strlen(message) - 1] = '\0';
        if(!strcmp(message, "quit")) // 클라이언트가 quit 입력 시, 연결 종료
            thread_exit = true;

        // 리눅스에서는 socket을 파일처럼 다룸 -> 데이터 전송 시 write() 사용
        if(write(clnt_sock, message, sizeof(message)) < 0)
            printf("message send failed\n\n");
    }
    pthread_detach(thread);

    close(clnt_sock);
    printf("client: %s server closed\n\n", argv[1]);

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
            if(!strcmp(message, ""))
                continue;
            // 서버가 전송한 정보 출력
            printf("[관리자(서버)]: %s\n", message);
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