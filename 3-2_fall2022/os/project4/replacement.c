#include "replacement.h"
#include "page.h"
#include <stdio.h>
#include <stdlib.h> // exit()
#include <string.h>
#include <stdbool.h>

#define start_UI(algorithm)\
            printf("===================================================================\n");\
            printf("================ Page Replacement Algorithm: %s ================\n", algorithm);\
            printf("===================================================================\n");\
            output_page_string(page_string);

#define start_Frame()\
            printf("[Frame]\n");\
            printf("%-6s | %-10s | %-5s \n", "string", "page fault", "frame");\
            printf("--------------------------------------------------------------\n");

#define end_UI(page_fault_cnt)\
            printf("[Result]\n");\
            printf(">> Page Fault 횟수: %d\n", page_fault_cnt);

/*
    [Optimal Algorithm] 가장 오랜 시간동안 쓰이지 않을 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_optimal(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable_Optimal pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int use_frame[frame_cnt + 1]; // 해당 프레임에 저장되어 있는 페이지가 몇 회 이후에 사용되는지 저장하는 공간
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int useLast;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_Optimal.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    memset(use_frame, 0, sizeof(use_frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("Optimal"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                memset(use_frame, 0, sizeof(use_frame));

                // 현재 물리 메모리를 살펴봄
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    // 각각의 물리 메모리에 올라가있는 페이지들이 다음에 또 언제 참조되는지 확인 및 저장
                    for(int k = i; k < string_cnt; ++k)
                    {
                        ++use_frame[j];

                        if(page_string_no_space[k] == frame[j])
                        {
                            break;
                        }
                    }       
                }

                useLast = use_frame[1];
                replacement_frame = 1;
                // 가장 나중에 사용되는 값을 선택 -> 만약 동일한 값이 존재한다면 낮은 인덱스의 프레임의 값 교체
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(useLast < use_frame[j])
                    {
                        useLast = use_frame[j];
                        replacement_frame = j;
                    }
                }

                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }
            
        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [FIFO Algorithm] 가장 먼저 들어온 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_fifo(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int first;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_FIFO.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].input_time = -1;
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("FIFO"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].input_time = i;
                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                first = pageTable[frame[1]].input_time;
                replacement_frame = 1;
                // 페이지가 프레임에 올라간 시점(input_time)이 더 적을 수록 오래 머문 것
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(first > pageTable[frame[j]].input_time)
                    {
                        first = pageTable[frame[j]].input_time;
                        replacement_frame = j;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].input_time = -1;
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].input_time = i;
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }

        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [LIFO Algorithm] 가장 나중에 들어온 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_lifo(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int last;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_LIFO.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].input_time = -1;
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("LIFO"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].input_time = i;
                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                last = pageTable[frame[1]].input_time;
                replacement_frame = 1;
                // 페이지가 프레임에 올라간 시점(input_time)이 더 높을 수록 최근에 메모리에 올라간 것
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(last < pageTable[frame[j]].input_time)
                    {
                        last = pageTable[frame[j]].input_time;
                        replacement_frame = j;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].input_time = -1;
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].input_time = i;
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }

        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [LRU Algorithm] 가장 오래동안 사용되지 않은 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_lru(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable_LRU pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int old_time;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_LRU.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].ref_time = -1;
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("LRU"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        pageTable[page_string_no_space[i]].ref_time = i;

        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                old_time = pageTable[frame[1]].ref_time;
                replacement_frame = 1;
                // 페이지가 사용된 시점(old_time)이 더 낮을 수록 오랫동안 사용하지 않은 페이지
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(old_time > pageTable[frame[j]].ref_time)
                    {
                        old_time = pageTable[frame[j]].ref_time;
                        replacement_frame = j;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].ref_time = -1;
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }

        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [LFU Algorithm] 참조 횟수가 낮은 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_lfu(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable_LFU pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int least_cnt;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_LFU.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].ref_cnt = 0;
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("LFU"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        ++pageTable[page_string_no_space[i]].ref_cnt;

        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                least_cnt = pageTable[frame[1]].ref_cnt;
                replacement_frame = 1;
                // 참조 횟수(ref_cnt)가 낮을 수록 참조를 하지 않은 페이지
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(least_cnt > pageTable[frame[j]].ref_cnt)
                    {
                        least_cnt = pageTable[frame[j]].ref_cnt;
                        replacement_frame = j;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }

        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [SC Algorithm] 
    오래되고 사용하지 않는 page 교체
    R bit가 0인 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_sc(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable_SC pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int page_string_no_space[string_cnt]; // page_string에서 공백을 제외하고 숫자만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int cur;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_SC.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
        pageTable[i].r_bit = 0x00;
    }
    separate_page_space(page_string, page_string_no_space); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    
    start_UI("SC"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[page_string_no_space[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[page_string_no_space[i]].frame = j;
                        pageTable[page_string_no_space[i]].vi = 'v';
                        pageTable[page_string_no_space[i]].r_bit = 0x01;

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                            cur = 1;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                while(true)
                {
                    // 마지막 프레임까지 다 확인했으면 다시 첫번째 프레임으로 돌아가서 검사
                    if(cur > frame_cnt)
                    {
                        cur = 1;
                    }

                    // r-bit가 0이면 해당 페이지 교체
                    if(pageTable[frame[cur]].r_bit == 0x00)
                    {
                        replacement_frame = cur;
                        ++cur;

                        break;
                    }
                    else
                    {
                        pageTable[frame[cur]].r_bit = 0x00;
                        ++cur;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i'; 

                frame[replacement_frame] = page_string_no_space[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[page_string_no_space[i]].frame = replacement_frame;
                pageTable[page_string_no_space[i]].vi = 'v';
                pageTable[page_string_no_space[i]].r_bit = 0x01;
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
            pageTable[page_string_no_space[i]].r_bit = 0x01;
        }

        output_frame(fp, page_string_no_space[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    [ESC Algorithm]
    최근 사용하지 않았거나 수정하지 않은 페이지를 교체
    R bit와 W bit를 비교하여 page를 교체
    - 매개변수
        page_string: page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_esc(char *page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    FILE *fp; // 결과 값을 저장할 파일
    PageTable_ESC pageTable[ref_page_stream + 1]; // page table -> 논리적 메모리(참조 페이지 스트림) 개수와 동일
    int esc_page_string_page[string_cnt]; // esc_page_string에서 비트를 제외하고 숫자만 저장할 공간
    char esc_page_string_bit[string_cnt]; // esc_page_string에서 비트만 저장할 공간
    char page_fault[string_cnt]; // 각 페이지 스트링 값마다 page fault 발생 여부
    int frame[frame_cnt + 1]; // 페이지 스트링 값마다 물리적 메모리(프레임) 상태
    int page_fault_cnt; // page fault 발생 횟수
    bool isExist_free_frame; // 프리프레임 존재 여부 -> 존재하면 true

    int cur;
    int victim_r_bit;
    int victim_w_bit;
    int replacement_frame; // 교체할 프레임 -> victim
    int replacement_page; // invaild로 변경될 페이지

    fp = fopen("result_ESC.txt", "w");

    // 초기화
    for(int i = 0; i < ref_page_stream + 1; ++i)
    {
        pageTable[i].frame = 0;
        pageTable[i].vi = 'i';
        pageTable[i].r_bit = 0x00;
        pageTable[i].w_bit = 0x00;
    } 
    separte_page_bit(page_string, esc_page_string_page, esc_page_string_bit); // 알고리즘 수행 시 용이하도록 page_string 가공
    memset(page_fault, 0, sizeof(page_fault));
    memset(frame, 0, sizeof(frame));
    page_fault_cnt = 0;
    isExist_free_frame = true;
    victim_r_bit = 0x00;
    victim_w_bit = 0x00;
    
    start_UI("ESC"); // 알고리즘 수행 전, 해당 알고리즘의 이름 및 해당 알고리즘에서 사용되는 페이지 스트링 출력
    start_Frame(); // frame 출력 시작

    // 교체 알고리즘 시작
    for(int i = 0; i < string_cnt; ++i)
    {
        // page fault 발생 여부 확인
        // vaild-invaild bit가 i이면 현재 물리적 메모리에 페이지가 올라가지 않은 것 -> fault
        if(pageTable[esc_page_string_page[i]].vi == 'i')
        {
            page_fault[i] = 'Y';
            ++page_fault_cnt;

            // free frame 존재할 때 -> 교체 알고리즘 필요 없음
            if(isExist_free_frame)
            {
                // 낮은 인덱스의 프레임부터 확인하면서 빈 프레임 있으면 바로 사용
                for(int j = 1; j <= frame_cnt; ++j)
                {
                    if(frame[j] == 0)
                    {
                        frame[j] = esc_page_string_page[i]; // 프레임에 페이지 스트링의 값(페이지) 저장

                        pageTable[esc_page_string_page[i]].frame = j;
                        pageTable[esc_page_string_page[i]].vi = 'v';

                        // 방금 마지막 프레임에까지 값 저장했을 때 -> 다음 턴부터는 프리 프레임이 없음
                        if(frame_cnt == j)
                        {
                            isExist_free_frame = false;
                            cur = 1;
                        }

                        break;
                    }
                } 
            }
            // free frame 존재하지 않을 때 -> 교체 알고리즘 필요
            else
            {
                while(true)
                {
                    // 마지막 프레임까지 다 확인한 경우
                    // 다시 첫번째 프레임으로 돌아가서 검사 + victim_bit 변경
                    if(cur > frame_cnt)
                    {
                        cur = 1;

                        // victime_r_bit == 0x00인 경우
                        // -> 현재 w_bit는 0x00이거나 0x01
                        if(victim_r_bit == 0x00)
                        {
                            // (0, 0) -> (0, 1)
                            if(victim_w_bit == 0x00)
                            {
                                victim_r_bit = 0x00;
                                victim_w_bit = 0x01;
                            }
                            // (0, 1) -> (1, 0)
                            else
                            {
                                victim_r_bit = 0x01;
                                victim_w_bit = 0x00;
                            }
                        }
                        // victime_r_bit == 0x01인 경우
                        // -> 현재 w_bit는 0x00이거나 0x01
                        else
                        {
                            // (1, 0) -> (1, 1)
                            if(victim_w_bit == 0x00)
                            {
                                victim_r_bit = 0x01;
                                victim_w_bit = 0x01;
                            }
                            // (1, 1) -> (0, 0)
                            else
                            {
                                victim_r_bit = 0x00;
                                victim_w_bit = 0x00;
                            }
                        }
                    }
 
                    // 우선 순위 따라 victim으로 설정 (00 -> 01 -> 10 -> 11)
                    if(pageTable[frame[cur]].r_bit == victim_r_bit && pageTable[frame[cur]].w_bit == victim_w_bit )
                    {
                        replacement_frame = cur;
                        cur++;
                        break;
                    }
                    else
                    {
                        ++cur;
                    }
                }
                
                replacement_page = frame[replacement_frame]; // 교체될 페이지
                pageTable[replacement_page].frame = 0;
                pageTable[replacement_page].vi = 'i';
                pageTable[replacement_page].r_bit = 0x00;
                pageTable[replacement_page].w_bit = 0x00;

                frame[replacement_frame] = esc_page_string_page[i]; // 프레임에 페이지 스트링의 값(페이지) 저장
                pageTable[esc_page_string_page[i]].frame = replacement_frame;
                pageTable[esc_page_string_page[i]].vi = 'v';
            }
        }   
        // vaild-invaild bit가 v이면 현재 물리적 메모리에 페이지가 올라가있는 것 -> hit
        else
        {
            page_fault[i] = 'N';
        }

        // r, w bit 값 설정
        if(esc_page_string_bit[i] == 'r')
        {
            pageTable[esc_page_string_page[i]].r_bit = 0x01; // r-bit = 1
        }
        else
        {
            pageTable[esc_page_string_page[i]].w_bit = 0x01; // w-bit = 1
        }

        output_frame(fp, esc_page_string_page[i], page_fault[i], frame, frame_cnt); // 프레임 하나씩 출력 및 파일 저장

    }

    end_UI(page_fault_cnt); // 알고리즘 수행 후, 해당 알고리즘에서 발생한 page fault 출력
    
    fprintf(fp, ">> Page Fault 횟수: %d\n", page_fault_cnt);
    fclose(fp);

    return;
}

/*
    모든 교체 알고리즘을 실행시키는 함수
    - 매개변수
        page_string: ESC 알고리즘 외의 알고리즘들에서 사용되는 page reference string
        esc_page_string: ESC 알고리즘에서 사용되는 page reference string
        string_cnt: 페이지 스트링 내 페이지 개수
        frame_cnt: page frame의 개수
        ref_page_stream: 논리적 주소 메모리의 크기(페이지의 개수)
*/
void replace_all(char *page_string, char *esc_page_string, int string_cnt, int frame_cnt, int ref_page_stream)
{
    printf("[ALL]\n");

    replace_optimal(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_fifo(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_lifo(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_lru(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_lfu(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_sc(page_string, string_cnt, frame_cnt, ref_page_stream);
    replace_esc(esc_page_string, string_cnt, frame_cnt, ref_page_stream);

    return;
}