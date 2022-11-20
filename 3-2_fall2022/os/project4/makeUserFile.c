#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PAGE_STRING 1000 // 페이지 개수
#define REFERENCE_PAGE_STREAM 30
#define RW 2

int main()
{
    FILE *fp1 = fopen("user_page_string", "w");
    FILE *fp2 = fopen("user_page_string_ESC", "w"); // R W 비트가 함께 표시되어야 함
    char page;
    char bit;
    int temp;
    int random = -1;

    srand(time(NULL));
    for(int i = 0; i < PAGE_STRING; ++i)
    {
        // page_string은 연속된 숫자를 가질 수 없음
        if(random != (temp = (rand() % REFERENCE_PAGE_STREAM) + 1))
        {
            random = temp;

            page = (char)random; // 1 ~ 30 사이의 숫자 랜덤으로 저장
            if((rand() % RW) == 0) // 0 or 1 -> rw 비트 랜덤으로 저장하기 위함
            {
                bit = 'r';
            }
            else
            {
                bit = 'w';
            }

            fprintf(fp1, "%c ", page); // ESC가 아닌 경우: 페이지 번호 + 공백
            fprintf(fp2, "%c%c", page, bit); // ESC인 경우: 페이지 번호 + RW bit
        }
        else
        {
            --i;
            continue;
        }
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}