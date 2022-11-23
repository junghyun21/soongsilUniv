#include "page.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define PAGE_STRING_CNT 1000 // 페이지 스트링 개수
#define PAGE_STRING_SIZE 2000 // 페이지 스트링의 크기
#define REFERENCE_PAGE_STREAM 30 // 논리 주소 메모리 크기(페이지 개수)
#define RW 2
#define SPACE ' '

/*
    랜덤 함수를 사용하여 매 프로그램이 수행될 때 마다 프로그램 내부에서 페이지 스트링을 생성하는 방법
    - 매개변수
        page_string: 랜덤으로 생성한 페이지 스트링을 저장할 공간
        esc_page_string: ESC 알고리즘 수행 시 사용할 페이지 스트링을 저장할 공간
*/
void string_random(char *page_string, char *esc_page_string)
{
    char page;
    char bit;
    int temp;
    int random = -1;
    int idx = 0;

    srand(time(NULL));

    while(idx < PAGE_STRING_SIZE)
    {
        // page_string 은 연속된 숫자를 가질 수 없음
        if(random != (temp = (rand() % REFERENCE_PAGE_STREAM) + 1))
        {
            random = temp;

            page = (char)random; // 1 ~ 30 사이의 숫자 랜덤으로 저장

            page_string[idx] = page; 
            esc_page_string[idx] = page;

            ++idx;
        }
        else
        {
            continue;
        }
        
        page_string[idx] = SPACE;
        if(rand() % RW == 0) // 0 or 1 -> rw 비트 랜덤으로 저장하기 위함
        {
            esc_page_string[idx] = 'r';
        }
        else
        {
            esc_page_string[idx] = 'w';
        }
        
        ++idx;
    }

    return;
}

/*
    미리 생성해둔 파일에서 페이지 스트링 값을 가져오는 함수
    - 매개변수
        page_string: 파일에서 불러온 페이지 스트링을 저장할 공간
        esc_page_string: ESC 알고리즘 수행 시 사용할 페이지 스트링을 저장할 공간
*/
void string_userfile(char *page_string, char *esc_page_string)
{
    FILE *fp_page_string;
    FILE *fp_esc_page_string;
    char *fname = "./user_page_string";
    char *fname_esc = "./user_page_string_ESC";
    char *mode = "r";
    
    // 미리 생성하여 저장해둔 ESC 외의 다른 알고리즘을 위한 input 데이터 파일 오픈
    if((fp_page_string = fopen(fname, mode)) == NULL)
    {
        fprintf(stderr, "fopen error for %s\n", fname);
        exit(1);
    }

    // 미리 생성하여 저장해둔 ESC를 위한 input 데이터 파일 오픈
    if((fp_esc_page_string = fopen(fname_esc, mode)) == NULL)
    {
        fprintf(stderr, "fopen error for %s\n", fname_esc);
        exit(1);
    }

    fread(page_string, PAGE_STRING_SIZE, 1, fp_page_string);
    fread(esc_page_string, PAGE_STRING_SIZE, 1, fp_esc_page_string);

    fclose(fp_page_string);
    fclose(fp_esc_page_string);

    return;
}

/*
    ESC 알고리즘을 제외한 다른 알고리즘 수행 시,
    page string을 좀 더 쉽게 다루기 위해 공백 제거 및 int형 변환을 수행하는 함수
    - 매개변수
        page_string: 공백이 포함되어 있는 char 형태의 page string
        page_string_no_space: 공백이 제거된 int 형태의 page string을 저장할 공간
*/
void separate_page_space(char *page_string, int *page_string_no_space)
{
    for(int i = 0, idx = 0; i < PAGE_STRING_SIZE && idx < PAGE_STRING_CNT; ++i)
    {
        if(page_string[i] != SPACE)
        {
            page_string_no_space[idx++] = page_string[i];
        }
    }

    return;
}

/*
    ESC 알고리즘 수행 시,
    page string을 좀 더 쉽게 다루기 위해 page와 bit 분리 및 page를 int형으로 변환하는 함수
    - 매개변수
        esc_page_string: page와 bit가 함께 입력되어 있는 page string
        esc_page_string_page: page만 int 형태로 따로 저장할 공간
        esc_page_string_bit: bit만 char 형태로 따로 저장할 공간

*/
void separte_page_bit(char *esc_page_string, int *esc_page_string_page, char *esc_page_string_bit)
{
    for(int i = 0, idx = 0; i < PAGE_STRING_SIZE && idx < PAGE_STRING_CNT; ++i)
    {
        // esc_page_string은 page + bit + page + bit + ... 순서이므로, bit가 나온 후, 인덱스 증가
        if(esc_page_string[i] == 'r' || esc_page_string[i] == 'w')
        {
            esc_page_string_bit[idx++] = esc_page_string[i]; // char형 그대로 저장
        }
        else
        {
            esc_page_string_page[idx] = esc_page_string[i]; // char형 -> int형
        }

    }

    return;
}

/*
    현재 사용될 페이지 스트링의 값들을 출력하는 함수
    - 매개변수
        string: 출력할 페이지 스트링
*/
void output_page_string(char* page_string)
{
    printf("[Page String]\n");
    
    for(int i = 0; i < PAGE_STRING_SIZE; ++i)
    {
        if(page_string[i] == 'r' || page_string[i] == 'w' || page_string[i] == SPACE ) 
        {
            printf("%c", page_string[i]);
        }
        else
        {
            printf("%d", page_string[i]);
        }
    }

    putchar('\n');

    return;
}

/*
    알고리즘이 수행될 때 페이지 프레임 개수별로 실제 페이지가 교체된 내용 출력 및 파일로 저장
    한 프레임 당 하나씩 출력 및 파일로 저장
    - 매개변수
        string: 해당 알고리즘에서 사용된 페이지 스트링
        page_fault: page fault 발생 여부
        frame: 물리적 주소 내부
        frame_cnt: 페이지 프레임의 개수
*/
void output_frame(FILE *fp, int processed_page_string, char page_fault, int *frame, int frame_cnt)
{
    printf("%-6d | %-10c | ", processed_page_string, page_fault);
    fprintf(fp, "%-6d | %-10c | ", processed_page_string, page_fault);

    for(int i = 1; i <= frame_cnt; ++i)
    {
        printf("%-4d", frame[i]);
        fprintf(fp, "%-4d", frame[i]);
    }
    printf("\n");
    fprintf(fp, "\n");

    return;
}
