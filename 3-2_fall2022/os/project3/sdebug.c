#include "types.h"
#include "stat.h"
#include "user.h"

#define PNUM 5 // process 개수
#define PRINT_CYCLE 10000000 // 실행 중인 process가 정보를 출력하는 주기 
#define TOTAL_COUNTER 500000000 // process가 소모할 수 있는 시간

void sdebug_func(void)
{
    int n, pid;
    int weight = 1;
    long start_ticks, end_ticks, ticks, counter;

    printf(1, "start sdebug command\n");

    for(n = 0; n < PNUM; ++n)
    {
        pid = fork(); // 새로운 process 생성

        // process 생성이 실패한 경우
        if(pid < 0)
        {
            printf(1, "fork failed\n");
            exit();
        }

        // 자식 processs인 경우
        if(pid == 0)
        {
            weightset(weight++); // 현재 생성된 프로세스에게 가중치 부여

            start_ticks = uptime(); // uptime(): 시작 이후로 clock_tick이 발생한 횟수
            counter = start_ticks * 10;

            int first = 1; // 프로세스의 정보 출력은 프로세스 별로 한 번씩만 수행

            // 프로세스가 생성된 이후부터 소모할 수 있는 시간
            while(TOTAL_COUNTER >= counter)
            {
                
                end_ticks = uptime();
                counter = (end_ticks - start_ticks) * 10;

                counter = ticks * 10;

                if(PRINT_CYCLE == counter)
                {
                    if(first)
                    {
                        end_ticks = uptime();

                        // 1ticks = 10ms
                        printf(1, "PID: %d, WEIGHT: %d, TIMES: %dms\n", pid, weight, (end_ticks - start_ticks) * 10);

                        first = 0;
                    }
                }
            }

            printf(1, "PID: %d terminated\n", pid);
            exit(); // 현재 프로세스 종료
        }

        // 부모 process인 경우(자식의 PID 리턴)    
        else
        {
            // wait(): 자식 process가 끝날때까지 기다림
            // 자식 process가 종료되면 자식의 PID 리턴, 자식이 없으면 -1 리턴
            for(int i = n; i >= 0; --i)
            {
                if(wait() < 0)
                {
                    printf(1, "wait stopped early\n");
                    exit();
                }
            }
            
            // 자식 프로세스가 더 이상 없어야하는데 아직 있는 경우
            if(wait() != -1)
            {
                printf(1, "wait got too many\n");
                exit();
            }
        }
    }

    printf(1, "end of sdebug command\n");
}

int main(void)
{
    sdebug_func();
    exit();
}