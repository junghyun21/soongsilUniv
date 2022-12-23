// input.txt 파일에서 각 줄의 마지막이 '\n'이 아니라, '\r\n'으로 되어 있어서 에러가 발생했던 것
// 기존 코드: token_parsing()에서 strtok를 통해 맨 처음에 마지막 줄의 '\n'을 제거해줌
// 현재 코드: token_parsing()에서 strtok를 통해 맨 처음에 마지막 줄의 '\r'과 '\n'을 제거해줌
// 심정: 코드 싹 다 갈아엎을게 아니였는데.. 따흑... 그래도 코드가 좀 더 깔끔해지기도 했고, 다 해결되어서 기쁘다!!!!!!!!!!

/*
 * 화일명 : my_assembler_00000000.c
 * 설  명 : 이 프로그램은 SIC/XE 머신을 위한 간단한 Assembler 프로그램의 메인루틴으로,
 * 입력된 파일의 코드 중, 명령어에 해당하는 OPCODE를 찾아 출력한다.
 * 파일 내에서 사용되는 문자열 "00000000"에는 자신의 학번을 기입한다.
 */

/*
 *
 * 프로그램의 헤더를 정의한다.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <ctype.h>

// 파일명의 "00000000"은 자신의 학번으로 변경할 것.
#include "my_assembler_20201662.h"

/* ------------------------------------------------------------ * 설명 : 사용자로 부터 어셈블리 파일을 받아서 명령어의 OPCODE를 찾아 출력한다.
 * 매계 : 실행 파일, 어셈블리 파일
 * 반환 : 성공 = 0, 실패 = < 0
 * 주의 : 현재 어셈블리 프로그램의 리스트 파일을 생성하는 루틴은 만들지 않았다.
 *           또한 중간파일을 생성하지 않는다.
 * ------------------------------------------------------------ */
int main(int args, char *arg[])
{
    if (init_my_assembler() < 0)
    {
        printf("init_my_assembler: fail to initialization of program.\n");
        return -1;
    }

    if (assem_pass1() < 0)
    {
        printf("assem_pass1: fail to initialization of pass 1.\n");
        return -1;
    }

    make_opcode_output("output_20201662.txt");

    /*
     * 추후 프로젝트에서 사용되는 부분
     *
    make_symtab_output("symtab_00000000");
    if (assem_pass2() < 0)
    {
        printf(" assem_pass2: 패스2 과정에서 실패하였습니다.  \n");
        return -1;
    }

    make_objectcode_output("output_00000000");
    */
    return 0;
}

/* ------------------------------------------------------------ * 설명 : 프로그램 초기화를 위한 자료구조 생성 및 파일을 읽는 함수이다.
 * 매계 : 없음
 * 반환 : 정상종료 = 0 , 에러 발생 = -1
 * 주의 : 각각의 명령어 테이블을 내부에 선언하지 않고 관리를 용이하게 하기 위해서
 *       파일 단위로 관리하여 프로그램 초기화를 통해 정보를 읽어 올 수 있도록
 *       구현하였다.
 * ------------------------------------------------------------ */

//
int init_my_assembler(void)
{
    int result;

    if ((result = init_inst_file("inst.data")) < 0)
        return -1;
    if ((result = init_input_file("input.txt")) < 0)
        return -1;
    
    return result;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 머신을 위한 기계 코드목록 파일을 읽어 기계어 목록 테이블(inst_table)을
 *        생성하는 함수이다.
 * 매계 : 기계어 목록 파일
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : 기계어 목록파일 형식은 자유롭게 구현한다. 예시는 다음과 같다.
 *
 *    ===============================================================================
 *           | 이름 | 형식 | 기계어 코드 | 오퍼랜드의 갯수 | NULL|
 *    ===============================================================================
 *
 * ----------------------------------------------------------------------------------
 */
int init_inst_file(char *inst_file)
{
    FILE *file = NULL;
    char *mode = "r";
    char buf[MAX_BUF] = "\0";
    char *ptr = NULL;
    
    // inst.data 파일 open -> 실패 시, 에러메세지 출력 후 -1 리턴
    if((file = fopen(inst_file, mode)) == NULL)
    {
        perror("fopen error");
        return -1;
    }

    // 파일이 끝날 때까지 데이터를 한 줄씩 읽어옴
    // 읽어온 데이터를 '\t'를 기준으로 나누어 각각 저장
    // fgets: 개행문자를 기준(개행문자까지)으로 데이터를 읽어옴 + 더 읽을 데이터가 없으면 NULL값 반환
    // inst_index: inst의 개수
    while(fgets(buf, sizeof(buf), file) != NULL)
    {
        inst_table[inst_index] = (inst*)malloc(sizeof(inst));
        
        ptr = strtok(buf, "\n");  // 개행문자 제거
        
        // "\t"을 기준으로 값 나누어 저장
        ptr = strtok(ptr, "\t");
        strcpy(inst_table[inst_index]->str, ptr);
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->op = strtol(ptr, NULL, 16); // 16진수로 변환
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->format = atoi(ptr);
        
        ptr = strtok(NULL, "\t");
        inst_table[inst_index]->ops = atoi(ptr);
        
        ++inst_index; // inst_table내의 원소 개수(명령어 개수) 증가
    }

    fclose(file);
    
    return 0;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 어셈블리 할 소스코드를 읽어 소스코드 테이블(input_data)를 생성하는 함수이다.
 * 매계 : 어셈블리할 소스파일명
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : 라인단위로 저장한다.
 *
 * ----------------------------------------------------------------------------------
 */
int init_input_file(char *input_file)
{
    FILE *file = NULL;
    char *mode = "r";
    char buf[MAX_BUF] = "\0";
    
    if((file = fopen(input_file, mode)) == NULL)
    {
        perror("fopen error");
        return -1;
    }
    
    // input_file의 내의 데이터를 한 줄씩 읽어와서 input_data에 저장함
    while(fgets(buf, sizeof(buf), file) != NULL)
    {
        input_data[line_num] = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
        strcpy(input_data[line_num++], buf);
    }

    fclose(file);
    
    return 0;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 소스 코드를 읽어와 토큰단위로 분석하고 토큰 테이블을 작성하는 함수이다.
 *        패스 1로 부터 호출된다.
 * 매계 : 파싱을 원하는 문자열
 * 반환 : 정상종료 = 0 , 에러 < 0
 * 주의 : my_assembler 프로그램에서는 라인단위로 토큰 및 오브젝트 관리를 하고 있다.
 * ----------------------------------------------------------------------------------
 */
int token_parsing(char *str)
{
    char *ptr = NULL;
    int cnt_tab = 0; // tab의 개수
    int idx = 0;
    int len_operand = 0;
    
    token_table[token_line] = (token*)malloc(sizeof(token));
    
    // 초기화
    token_table[token_line]->label = NULL;
    token_table[token_line]->operator = NULL;
    for(int i = 0; i < MAX_OPERAND; ++i)
    {
        token_table[token_line]->operand[i] = NULL;
    }
    strcpy(token_table[token_line]->comment, "");
    
    // strtok는 연속된 구분자를 만났을 때, 빈 문자열을 반환하지 않음
    // 연속된 구분자도 구분해야하는 경우가 있어서 코드 새로 작성함
    // ex. RSUB ... -> ...이 command가 아닌 operand에 저장됨
    // 맥에서 개행은 \r\n으로 쓰임
    while(str[idx] != '\r' && str[idx] != '\n')
    {
        char buf[MAX_BUF] = "\0";
        int i = 0;
        
        // 구분자 나오기 전까지 buf에 값 저장
        while(TRUE)
        {
            if(str[idx] == '\t' || str[idx] == '\r')
            {
                ++idx;
                break;
            }
            
            buf[i++] = str[idx++];
        }
        
        // 각 token들 저장
        // buf가 빈문자열이면 초기화 값인 NULL 저장 -> 즉 따로 값 저장하지 않음
        // buf가 빈문자열이 아닐 때, 아래 코드들 실행
        if(strcmp(buf, ""))
        {
            // label
            if(cnt_tab == LABEL)
            {
                token_table[token_line]->label = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
                strcpy(token_table[token_line]->label, buf);
                
                // label 위치에 "."이 있는 경우 -> 주석인 경우
                // 주석 표시(.)만 있거나 or 주석 표시 뒤에 comment가 붙거나 -> 2가지 경우
                if(!strcmp(token_table[token_line]->label, "."))
                {
                    cnt_tab = COMMENT;
                    continue;
                }
            }
            // operator
            else if(cnt_tab == OPERATOR)
            {
                token_table[token_line]->operator = (char*)malloc(sizeof(char) * (strlen(buf) + 1));
                strcpy(token_table[token_line]->operator, buf);
            }
            // operand
            else if(cnt_tab == OPERAND)
            {
                int i = 0;
                // operand를 ',' 기준으로 나누어서 저장
                ptr = strtok(buf, ",");
                
                while(ptr != NULL && i < MAX_OPERAND)
                {
                    ++len_operand;

                    token_table[token_line]->operand[i] = (char*)malloc(sizeof(char) * (strlen(ptr) + 1));
                    strcpy(token_table[token_line]->operand[i++], ptr);

                    ptr = strtok(NULL, ",");
                }
            }
            // command
            else if(cnt_tab == COMMENT)
            {
                strcpy(token_table[token_line]->comment, buf);
            }
            // token이 입력 가능한 값보다 많이 입력되었을 때 -> error
            else
            {
                return -1;
            }
        }
        
        ++cnt_tab;
    }
    
    ++token_line;
    
    return len_operand;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 입력 문자열이 기계어 코드인지를 검사하는 함수이다.
 * 매계 : 토큰 단위로 구분된 문자열
 * 반환 : 정상종료 = 기계어 테이블 인덱스, 에러 < 0
 * 주의 :
 *
 * ----------------------------------------------------------------------------------
 */
int search_opcode(char *str)
{
    int idx = 0;
    
    if(str[0] == '+')
    {
        str = strtok(str, "+");
    }
    
    // 입력 문자열에 해당하는 opcode가 있으면 해당 opcode가 위치한 테이블의 인덱스 리턴
    while(idx < inst_index)
    {
        if(!strcmp(str, inst_table[idx]->str))
        {
            break;
        }
        
        idx++;
    }
    
    return idx;
}

/* ----------------------------------------------------------------------------------
* 설명 : 어셈블리 코드를 위한 패스1과정을 수행하는 함수이다.
*           패스1에서는..
*           1. 프로그램 소스를 스캔하여 해당하는 토큰단위로 분리하여 프로그램 라인별 토큰
*           테이블을 생성한다.
*
* 매계 : 없음
* 반환 : 정상 종료 = 0 , 에러 = < 0
* 주의 : 현재 초기 버전에서는 에러에 대한 검사를 하지 않고 넘어간 상태이다.
*      따라서 에러에 대한 검사 루틴을 추가해야 한다.
*
* -----------------------------------------------------------------------------------
*/
static int assem_pass1(void)
{
    // 원래 pass 1에서는 명령어의 길이를 알기 위해 OPTAB 검사 (->OPTAB의 opcode를 참고하여 location counter 계산)
    // pass 2에서는 명령어 포멧(opcode를 번역 및 주소 복사) 정함
    // 아래는 각각의 opcode값 확인하기 위한 코드
    int opcode_index = -1;
    
    for(int i = 0; i < line_num; ++i)
    {
        // input_data[i]를 의미별로 잘라서 저장
        if(token_parsing(input_data[i]) < 0)
        {
            return -1;
        }
        
        // 입력된 명령어에 해당되는 opcode를 맵핑시켜줌
        // token_table[i]->operator == NULL -> operator가 입력되지 않았다
        if(token_table[i]->operator != NULL)
        {
            opcode_index = search_opcode(token_table[i]->operator);
            
            // 에러를 리턴했을 때
            if(opcode_index < 0)
            {
                return -1;
            }
            // 리턴된 값은 token_table[i]->operator에 해당되는 opcode
            else if(opcode_index < inst_index)
            {
                opcode[i] = inst_table[opcode_index]->op;
            }
            // inst_table 을 다 뒤졌는데도 해당되는 opcode가 없는 경우
            // ex. 지시어, 주석 같은 경우 opcode 존재 x -> 아무것도 출력하지 않으면 됨
            else
            {
                opcode[i] = -1;
            }
        }
        else
        {
            opcode[i] = -1;
        }

    }
    
    return 0;
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 명령어 옆에 OPCODE가 기록된 표(과제 3번) 이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*        또한 과제 3번에서만 쓰이는 함수이므로 이후의 프로젝트에서는 사용되지 않는다.
* -----------------------------------------------------------------------------------
*/
void make_opcode_output(char *file_name)
{
    FILE *file = NULL;
    char buf[25];
    char empty = '\0';
    
    // 파일 이름이 NULL이면 화면에 출력
    if(file_name == NULL)
    {
        file = stdout; // 화면에 출력
    }
    else
    {
        if((file = fopen(file_name, "w")) < 0)
        {
            fprintf(stderr, "open error for %s\n", file_name);
        }
    }

    for(int i = 0; i < token_line; ++i)
    {
        buf[0] = '\0';
        
        // label
        if(token_table[i]->label != NULL)
        {
            fprintf(file, "%-7s", token_table[i]->label); // label 출력
            
            // 주석일 때 -> comment만 출력하고 넘어감
            if(!strcmp(token_table[i]->label, "."))
            {
                fprintf(file, "%-25s\n", token_table[i]->comment);
                continue;
            }
        }
        // NULL인 경우 따로 분리하지 않으면 (null)이 출력됨
        else
        {
            fprintf(file, "%-8c", empty);
        }

        // operator
        if(token_table[i]->operator != NULL)
        {
            fprintf(file, "%-7s", token_table[i]->operator); // operator 출력
        }
        else
        {
            fprintf(file, "%-8c", empty);
        }
        
        // operand
        for(int j = 0; j < MAX_OPERAND; ++j)
        {
            if(token_table[i]->operand[j] == NULL)
            {
                break;
            }
            
            strcat(buf, token_table[i]->operand[j]);
        }
        fprintf(file, "%-25s", buf); // operand 출력

        // opcode
        if(opcode[i] >= 0)
        {
            fprintf(file, "%02X", opcode[i]);
        }
    
        fprintf(file, "\n");
    }
    
    // 파일을 생성하여 파일에 출력이 끝난 후, 파일 닫기
    if(file_name != NULL)
    {
        fclose(file);
    }
    
    return;
}

///* ----------------------------------------------------------------------------------
//* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
//*        여기서 출력되는 내용은 SYMBOL별 주소값이 저장된 TABLE이다.
//* 매계 : 생성할 오브젝트 파일명
//* 반환 : 없음
//* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
//*        화면에 출력해준다.
//*
//* -----------------------------------------------------------------------------------
//*/
//void make_symtab_output(char *file_name)
//{
//    /* add your code here */
//}
//
///* ----------------------------------------------------------------------------------
//* 설명 : 어셈블리 코드를 기계어 코드로 바꾸기 위한 패스2 과정을 수행하는 함수이다.
//*           패스 2에서는 프로그램을 기계어로 바꾸는 작업은 라인 단위로 수행된다.
//*           다음과 같은 작업이 수행되어 진다.
//*           1. 실제로 해당 어셈블리 명령어를 기계어로 바꾸는 작업을 수행한다.
//* 매계 : 없음
//* 반환 : 정상종료 = 0, 에러발생 = < 0
//* 주의 :
//* -----------------------------------------------------------------------------------
//*/
//static int assem_pass2(void)
//{
//
//    /* add your code here */
//}
//
///* ----------------------------------------------------------------------------------
//* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
//*        여기서 출력되는 내용은 object code (프로젝트 1번) 이다.
//* 매계 : 생성할 오브젝트 파일명
//* 반환 : 없음
//* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
//*        화면에 출력해준다.
//*
//* -----------------------------------------------------------------------------------
//*/
//void make_objectcode_output(char *file_name)
//{
//    /* add your code here */
//}
