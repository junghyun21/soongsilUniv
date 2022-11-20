#include "input.h"
#include "replacement.h"
#include "page.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SPACE ' '
#define ENTER '\n'

#define MAX_SELECT_ALGORITHM 3 // 최대 알고리즘 시뮬레이터 선택 개수
#define MIN_PAGE_FRAME 3 // 최소 페이지 프레임 개수
#define MAX_PAGE_FRAME 10 // 최대 페이지 프레임 개수

/*
    page replacement 알고리즘 시뮬레이터를 선택하는 함수
    - 매개변수
        int *algorithms: 최대 3개의 알고리즘 시뮬레이터의 종류를 저장할 공간
    - 리턴값
        algorithms_cnt: 선택된 알고리즘 시뮬레이터의 개수
*/
int selectAlgorithm(int *algorithms)
{
    int algorithms_cnt;
    int temp;

    printf("[1] Page Replacement 알고리즘 시뮬레이터를 선택하시오. (최대 3개)\n");
    printf("    (1) Optimal  (2) FIFO  (3) LIFO  (4) LRU  (5) SC  (6) ESC  (8) ALL\n");

    while(true)
    {
        printf("    >> ");

        memset(algorithms, 0, sizeof(int) * MAX_SELECT_ALGORITHM); // 선택한 알고리즘 목록 초기화
        algorithms_cnt = 0;

        while(algorithms_cnt < MAX_SELECT_ALGORITHM)
        {
            while((temp = getchar()) == SPACE); // 공백 무시

            temp -= '0'; // temp는 int형이기 때문에 char형일때의 값으로 바꾸어서 비교해야함
            if(temp >= OPTIMAL && temp <= ESC)
            {   
                algorithms[algorithms_cnt++] = temp;

                temp = getchar();
                if(temp == ENTER)
                {
                    return algorithms_cnt;
                }
                else if(temp == SPACE)
                {
                    ;
                }
                else
                {
                    errorInput(SELECTALGO, NONEXIST); // 잘못된 값이 들어온 경우
                    break;
                }
            }
            else if(temp == ALL)
            {
                if(algorithms_cnt == 0)
                {
                    algorithms[algorithms_cnt++] = temp;

                    if(getchar() == ENTER)
                    {
                        return algorithms_cnt;
                    }
                }
                
                errorInput(SELECTALGO, ONLYALL); // ALL가 단독으로 입력되지 않은 경우
                break;
            }
            else
            {
                errorInput(SELECTALGO, NONEXIST); // 잘못된 값이 들어온 경우
                break;
            }

        }

        if(algorithms_cnt == MAX_SELECT_ALGORITHM)
        {
            errorInput(SELECTALGO, CNT); // 선택한 시뮬레이터 개수가 잘못된 경우
        }

        while(getchar() != ENTER); // 버퍼 비우기
    }

}

/*
    page frame 개수를 입력받는 함수
    - 리턴값
        frame_cnt: 입력된 page frame의 개수
*/
int inputPageCnt()
{
    int frame_cnt;

    printf("[2] 페이지 프레임의 개수를 입력하시오. (최소 3, 최대 10)\n");

    frame_cnt = 0; // 문자가 입력되었을 때, frame_cnt에는 아무것도 저장되지 못하기 때문에
    while(true)
    {
        printf("    >> ");
        scanf("%d", &frame_cnt);

        if(frame_cnt >= MIN_PAGE_FRAME && frame_cnt <= MAX_PAGE_FRAME)
        {
            return frame_cnt;
        }

        errorInput(PAGECNT, CNT); // 입력한 프레임 개수가 잘못되었을 때

        while(getchar() != ENTER); // 버퍼 비우기
    }
}

/*
    데이터를 입력 받을 방식을 선택하는 함수
    - 리턴값
        string: 선택한 입력받을 데이터(페이지 스트링)
*/
int selectPageString()
{
    int string;

    printf("[3] 데이터 입력 방식을 선택하시오.\n");
    printf("    (1) 랜덤하게 생성  (2) 사용자 생성 파일 오픈\n");

    string = 0; // 문자가 입력되었을 때, string에는 아무것도 저장되지 못하기 때문에
    while(true)
    {
        printf("    >> ");
        scanf("%d", &string);

        if(string == RAND || string == USERFILE)
        {
            return string;
        }

        errorInput(PAGESTRING, NONEXIST); // 잘못된 값이 들어온 경우
        
        while(getchar() != ENTER); // 버퍼 비우기
    }
}

static void errorInput(enum eCaller caller, enum eError errno)
{
    if(caller == SELECTALGO)
    {
        switch(errno)
        {
            case NONEXIST:
                printf("** 위의 번호 중 최대 3개를 골라 스페이스로 구분하여 알고리즘을 선택해야 합니다. **\n");
                printf("** 그 외의 문자들은 모두 입력할 수 없습니다. **\n\n");
                break;

            case CNT:
                printf("** ALL을 제외한 최대 3개의 알고리즘을 선택해야 합니다. **\n\n");
                break;

            case ONLYALL:
                printf("** (8) ALL 은 다른 알고리즘과 동시에 선택될 수 없습니다. **\n\n");
                break;
       
            default:
                break;
        }
    }
    else if(caller == PAGECNT)
    {
        switch(errno)
        {
            case CNT:
                printf("** 페이지 프레임의 개수는 3개에서 10개 사이 값으로만 설정할 수 있습니다. **\n\n");
                break;
            
            default:
                break;
        }
    }
    else if(caller == PAGESTRING)
    {
        switch(errno)
        {
            case NONEXIST:
                printf("** 위의 번호 중 하나를 선택해야 합니다. **\n\n");
                break;

            default:
                break;
        }
    }

    return;
}