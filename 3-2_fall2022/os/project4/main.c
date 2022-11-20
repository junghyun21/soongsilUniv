#include "input.h"
#include "replacement.h"
#include "page.h"
#include <stdio.h>
#include <string.h>

#define MAX_SELECT_ALGORITHM 3 // 최대 알고리즘 시뮬레이터 선택 개수
#define PAGE_STRING_CNT 1000 // 페이지 스트링 개수
#define PAGE_STRING_SIZE 2000 // 페이지 스트링의 크기
#define REFERENCE_PAGE_STREAM 30 // 논리 주소 메모리 크기(페이지 개수)

int main()
{
    FILE *fp;
    enum eAlgorithm algorithm;
    enum eString string;
    char page_string[PAGE_STRING_SIZE]; // ESC 알고리즘을 제외한 모든 알고리즘에서 사용하는 페이지 스트링
    char esc_page_string[PAGE_STRING_SIZE]; // ESC 알고리즘 수행 시, 페이지 스트링 내에 RW bit 필요
    int algorithms[MAX_SELECT_ALGORITHM]; // 사용자가 선택한 알고리즘이 저장될 공간
    int algorithms_cnt; // 사용자가 선택된 알고리즘의 개수
    int frame_cnt; // 사용자가 입력한 페이지 프레임의 개수

    // 입력받을 데이터(페이지 스트링)를 저장할 공간 초기화
    memset(page_string, 0, PAGE_STRING_SIZE);
    memset(esc_page_string, 0, PAGE_STRING_SIZE);

    // 사용자 UI
    algorithms_cnt = selectAlgorithm(algorithms);
    frame_cnt = inputPageCnt();
    string = (enum eString)selectPageString();

    // 입력받을 데이터 저장
    switch(string)
    {
        case RAND:
            string_random(page_string, esc_page_string);
            break;

        case USERFILE:
            string_userfile(page_string, esc_page_string);
            break;

        default:
            fprintf(stderr, "nonexist for eString\n");
            exit(1);
    }

    // 각각의 알고리즘 실행
    for(int i = 0; i < algorithms_cnt; ++i)
    {
        algorithm = (enum eAlgorithm)algorithms[i];

        switch(algorithm)
        {
            case OPTIMAL:
                replace_optimal(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case FIFO:
                replace_fifo(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case LIFO:
                replace_lifo(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case LRU:
                replace_lru(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case LFU:
                replace_lfu(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case SC:
                replace_sc(page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case ESC:
                replace_esc(esc_page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;

            case ALL:
                replace_all(page_string, esc_page_string, PAGE_STRING_CNT, frame_cnt, REFERENCE_PAGE_STREAM);
                break;
            
            default:
                fprintf(stderr, "nonexist for eAlgorithm\n");
                exit(1);
        }
    }

    printf("<< 프로그램을 종료합니다. >>\n");

    return 0;
}