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
        printf("init_my_assembler: 프로그램 초기화에 실패 했습니다.\n");
        return -1;
    }

    if (assem_pass1() < 0)
    {
        printf("assem_pass1: 패스1 과정에서 실패하였습니다.\n");
        return -1;
    }

    // make_opcode_output(NULL);

    // make_symtab_output("symtab_20201662");
    make_symtab_output(NULL);
//    make_literaltab_output("literaltab_20201662");
//    if (assem_pass2() < 0)
//    {
//        printf(" assem_pass2: 패스2 과정에서 실패하였습니다.  \n");
//        return -1;
//    }
//
//    make_objectcode_output("output_20201662");
    
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
        
        ptr = strtok(buf, "\r\n");  // 개행문자 제거
        
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
    int cnt_tab = 0;
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
    token_table[token_line]->nixbpe = 0x00; // 00000000
    
    
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
    
    // token_table[token_line]->nixbpe에 값 저장
    
//    // n = 1, i = 1 (simple addressing in SIC/XE)
//    token_table[token_line]->nixbpe |= N;
//    token_table[token_line]->nixbpe |= I;
//
//    // 파싱된 값들 통해 n,i,e 값 작성
//    // x는 assem_pass1에서 확인 -> inst_table내의 ops값과 operand 개수 비교, 맞지 않는 경우 -> 1. 에러거나, 2. x이거나(== x=1)
//    // b, p는 location conter 다 끝나고 opcode 생성할 때 (왜냐하면 각 주소값들을 알아야 함)
//    // operand: @->indirect(n=1, i=0), #->immediate(n=0, i=1)
//    // operator: +->4형식(e=1)
//
//    // operator가 '+'로 시작하면 4형식 -> e = 1
//    if(token_table[token_line]->operator != NULL && token_table[token_line]->operator[0] == '+')
//    {
//        token_table[token_line]->nixbpe |= E;
//    }
//
//    idx = 0;
//    // n = 1, i = 1인 상태
//    while(token_table[token_line]->operand[idx] != NULL && idx < MAX_OPERAND)
//    {
//        // operand가 @로 시작하면 indirect addressing -> n = 1, i = 0
//        if(token_table[token_line]->operand[idx][0] == '@')
//        {
//            token_table[token_line]->nixbpe &= ~I;
//        }
//
//        // operand가 #로 시작하면 immediate addressing -> n = 0, i = 1
//        if(token_table[token_line]->operand[idx][0] == '#')
//        {
//            token_table[token_line]->nixbpe &= ~N;
//        }
//
//        ++idx;
//    }
    
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
    
    // 입력 문자열(명령어)에 해당하는 opcode가 있으면 해당 opcode가 위치한 테이블의 인덱스 리턴
    while(idx < inst_index)
    {
        if(!strcmp(str, inst_table[idx]->str))
        {
            break;
        }
        
        ++idx;
    }
    
    return idx;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 입력 label이 SYMTAB에 이미 존재하는지 검사하는 함수이다.
 * 매계 : label, 검사를 시작할 인덱스
 * 반환 : 이미 존재할 때 = 해당 인덱스 리턴, 존재하지 않을 때 = -1 리턴
 * 주의 :
 *
 * ----------------------------------------------------------------------------------
 */
int search_symtab(char* label, int sym_start)
{
    for(int i = sym_start; i < sym_line; ++i)
    {
        if(!strcmp(label, sym_table[i].symbol))
        {
            return i;
        }
    }
    
    return -1;
}

/* ----------------------------------------------------------------------------------
 * 설명 : 입력 literal이 LITTAB에 이미 존재하는지를 검사하는 함수이다.
 * 매계 : literal, 검사를 시작할 인덱스
 * 반환 : 이미 존재할 때 = 해당 인덱스 리턴, 존재하지 않을 때 = -1 리턴
 * 주의 :
 *
 * ----------------------------------------------------------------------------------
 */
int search_littab(char* literal, int literal_start)
{
    
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
    int index;
    int start_addr = 0;
    int sym_start = 0;
    int literal_start = 0;
    
    // input_data에 받아온 값들을 한 줄씩 parsing
    for(int i = 0; i < line_num; ++i)
    {
        if(token_parsing(input_data[i]) > MAX_OPERAND)
        {
            fprintf(stdout, "token_parsing() call error\n");
            return -1;
        }
    }
    
    // pass 1
    // 1. opcode를 조사하여 명령어 길이 파악
    // 2. 명령어 or 어셈블러 지시어의 길이 따라 location counter 크기 결정
    // 3. program block을 만나면 location counter 0으로 초기화
    // 4. 새로운 label 만나면 SYMTAB에 label과 현재 location counter 저장
    // 5. 새로운 literal 만나면 LITTAB에 literal 저장
    // 6. LTORG나 프로그램 끝을 만나면 현재 location counter에 literal의 바이트 수를 계산하여 저장
    
    // 시작주소: START라는 어셈블러 지시어 뒤에 오는 값이 시작주소임
    if(!strcmp(token_table[0]->operator, "START"))
    {
        start_addr = atoi(token_table[0]->operand[0]);
        locctr = start_addr;
        
        // section의 header 이름 저장
        strcpy(section_table[count_section].header, token_table[0]->label);
    }
    
    for(int i = 0; i < token_line; ++i)
    {
        // token_table[i]->operator == NULL -> operator나 어셈블러 지시어가 입력되지 않음
        if(token_table[i]->operator == NULL)
        {
            continue;
        }
        
        // CSECT: 새로운 section임을 나타냄
        if(!strcmp(token_table[i]->operator, "CSECT"))
        {
            // 기존 section의 길이 저장
            section_table[count_section].length = locctr - start_addr;
            
            // 새로운 section이 시작되었으므로, section의 개수 증가
            ++count_section;
            
            // section의 header 이름 저장
            strcpy(section_table[count_section].header, token_table[i]->label);
            
            start_addr = 0;
            locctr = start_addr;
            
            // SYMTAB에서 동일한 label이 없는 경우에만 label 저장
            // <but> 다른 section인 경우, 동일한 label 사용해도 상관 없음
            // -> 테이블 내에 동일한 label이 존재하는지 확인할 때, 동일 section 내에서만 검사하기 위함
            // litearl도 SYMTAB와 같은 원리
            sym_start = sym_line;
            literal_start = literal_line;
        }
        
        // SYMTAB 작성
        // token_table[i]->label == NULL -> label이 존재하지 않음
        if(token_table[i]->label != NULL)
        {
            // token_table[i]->label == "." -> 주석이므로 object program을 만들 때 필요 없음
            if(!strcmp(token_table[i]->label, "."))
            {
                continue;
            }
            // opeartor가 EQU이고 operand가 *인 경우 -> 주소에 현재 locctr 값 저장
            // opeartor가 EQU이고 operand가 *가 아닌 경우 -> 주소에 절대주소 값 저장
            // 아래는 후자의 경우임
            //
            else if(!strcmp(token_table[i]->operator, "EQU") && strcmp(token_table[i]->operator, "*"))
            {
                // 전체 SYMTAB을 훑어야하므로, 검사를 시작할 인덱스(두번째 인자)는 0
                //
                if(search_symtab(token_table[i]->label, 0) < 0)
                {
                    
                }
            }
            else
            {
                // 동일한 section의 SYMTAB에 동일한 label이 존재하는지 확인
                // 존재하면(search_symtab() >= 0) label은 테이블에 저장하지 않음
                if(search_symtab(token_table[i]->label, sym_start) < 0)
                {
                    // SYMTAB에 존재하지 않는 label인 경우에만 저장
                    strcpy(sym_table[sym_line].symbol, token_table[i]->label);
                    sym_table[sym_line].addr = locctr;
                    
                    ++sym_line;
                }
            }
        }
        
        // LITTAB 작성 -> literal 이름 저장
        for(int j = 0; j < MAX_OPERAND; ++j)
        {
            // token_table[i]->operand[j] == NULL -> 그 뒤로 더 이상 operand 존재하지 않음
            if(token_table[i]->operand[j] == NULL)
            {
                break;
            }
            
            isExist = FALSE;
            
            // literal은 맨 앞에 '='이 붙음
            if(token_table[i]->operand[j][0] == '=')
            {
                // ptr: literal의 사이즈를 알기 위함 ex. C, X, ...
                // str: literal의 이름을 알기 위함 ex. =C'EOF' -> str = EOF
                char *ptr, *str;
                ptr = strtok(token_table[i]->operand[j], "=");
                ptr = strtok(NULL, "'");
                str = strtok(NULL, "'");
                
                // 동일한 section의 LITTAB에 동일한 literal이 존재하는지 확인
                // 존재하면 litearl은 테이블에 저장하지 않음
                for(int k = literal_start; k < literal_line; ++k)
                {
                    if(!strcmp(sym_table[j].symbol, str))
                    {
                        isExist = TRUE;
                        break;
                    }
                }
                
                // LITTAB에 존재하지 않는 literal인 경우에만 저장
                if(!isExist)
                {
                    literal_table[literal_line].literal = (char*)malloc(sizeof(char) * (strlen(str) + 1));
                    strcpy(literal_table[literal_line].literal, str);
                    
                    // literal의 크기
                    if(ptr[0] == 'C')
                    {
                        literal_table[literal_line].len = (int)strlen(str);
                    }
                    else if(ptr[0] == 'X')
                    {
                        literal_table[literal_line].len = 1;
                    }
                    else
                    {
                        fprintf(stdout, "literal error\n");
                        return -1;
                    }
                    
                    ++literal_line;
                }
            }
        }
        
        // LITTAB 작성 -> literal 주소 저장
        if(!strcmp(token_table[i]->operator, "LTORG"))
        {
            // 주소가 저장 안된 literal들의 주소를 LITTAB에 저장
            while(literal_addr < literal_line)
            {
                literal_table[literal_addr].addr = locctr;
                locctr += literal_table[literal_addr].len;
                
                ++literal_addr;
            }
        }
        else if(!strcmp(token_table[i]->operator, "END"))
        {
            // 주소가 저장 안된 literal들의 주소를 LITTAB에 저장
            while(literal_addr < literal_line)
            {
                literal_table[literal_addr].addr = locctr;
                locctr += literal_table[literal_addr].len;
                
                ++literal_addr;
            }
            
            // 마지막 section의 크기 저장
            section_table[count_section].length = locctr - start_addr;
        }
        // '어셈블러 지시어' 따라 lacation counter 크기 결정
        // location counter가 증가하는 경우 -> WORD, BYTE, RESW, RESB
        else if(!strcmp(token_table[i]->operator, "WORD"))
        {
            
            
        }
        else if(!strcmp(token_table[i]->operator, "BYTE"))
        {
            
        }
        else if(!strcmp(token_table[i]->operator, "RESW"))
        {
            
        }
        else if(!strcmp(token_table[i]->operator, "RESB"))
        {
            
        }
        // '명령어'의 크기 따라 location counter 크기 결정되거나
        // 명령어도 아니고, location counter가 증가하는 어셈블러 지시어도 아닌 경우
        // -> 이 경우에는 아무것도 진행하지 않음
        else
        {
            // 해당하는 inst_table의 인덱스 리턴받음
            index = search_opcode(token_table[i]->operator);
            
            if(index < 0)
            {
                fprintf(stdout, "search_opcode() error\n");
                return -1;
            }
            // operator에 해당하는 값이 명령어일 때
            else if(index < inst_index)
            {
                // 1형식일 때
                if(inst_table[index]->format == 1)
                {
                    locctr += 1;
                }
                // 2형식일 때
                else if(inst_table[index]->format == 2)
                {
                    locctr += 2;
                }
                // 3,4형식일 때
                else
                {
                    // 4형식일 때
                    if(token_table[i]->operator[0] == '+')
                    {
                        locctr += 4;
                    }
                    // 3형식일 때
                    else
                    {
                        locctr += 3;
                    }
                }
            }
            
            // 명령어도 아니고, location counter가 증가하는 어셈블러 지시어도 아닌 경우
            // -> location counter가 증가하지 않는 어셈블러 지시어인 경우
            // ex. EQU, EXTDEF, EXTREF, ...
        }
        
        printf("locctr: %d\n", locctr);
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
//void make_opcode_output(char *file_name)
//{
//    FILE *file = NULL;
//        char buf[25];
//        char empty = '\0';
//
//        // 파일 이름이 NULL이면 화면에 출력
//        if(file_name == NULL)
//        {
//            file = stdout; // 화면에 출력
//        }
//        else
//        {
//            if((file = fopen(file_name, "w")) < 0)
//            {
//                fprintf(stderr, "open error for %s\n", file_name);
//            }
//        }
//
//        for(int i = 0; i < token_line; ++i)
//        {
//            buf[0] = '\0';
//
//            // label
//            if(token_table[i]->label != NULL)
//            {
//                fprintf(file, "%-7s", token_table[i]->label); // label 출력
//
//                // 주석일 때 -> comment만 출력하고 넘어감
//                if(!strcmp(token_table[i]->label, "."))
//                {
//                    fprintf(file, "%-25s\n", token_table[i]->comment);
//                    continue;
//                }
//            }
//            // NULL인 경우 따로 분리하지 않으면 (null)이 출력됨
//            else
//            {
//                fprintf(file, "%-8c", empty);
//            }
//
//            // operator
//            if(token_table[i]->operator != NULL)
//            {
//                fprintf(file, "%-7s", token_table[i]->operator); // operator 출력
//            }
//            else
//            {
//                fprintf(file, "%-8c", empty);
//            }
//
//            // operand
//            for(int j = 0; j < MAX_OPERAND; ++j)
//            {
//                if(token_table[i]->operand[j] == NULL)
//                {
//                    break;
//                }
//
//                strcat(buf, token_table[i]->operand[j]);
//            }
//            fprintf(file, "%-25s", buf); // operand 출력
//
//            // opcode
//            if(opcode[i] >= 0)
//            {
//                fprintf(file, "%02X", opcode[i]);
//            }
//
//            fprintf(file, "\n");
//        }
//
//        // 파일을 생성하여 파일에 출력이 끝난 후, 파일 닫기
//        if(file_name != NULL)
//        {
//            fclose(file);
//        }
//
//        return;
//}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 SYMBOL별 주소값이 저장된 TABLE이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*
* -----------------------------------------------------------------------------------
*/
void make_symtab_output(char *file_name)
{

        
    return;
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 LITERAL별 주소값이 저장된 TABLE이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*
* -----------------------------------------------------------------------------------
*/
void make_literaltab_output(char* filen_ame)
{
    /* add your code here */
}

/* ----------------------------------------------------------------------------------
* 설명 : 어셈블리 코드를 기계어 코드로 바꾸기 위한 패스2 과정을 수행하는 함수이다.
*           패스 2에서는 프로그램을 기계어로 바꾸는 작업은 라인 단위로 수행된다.
*           다음과 같은 작업이 수행되어 진다.
*           1. 실제로 해당 어셈블리 명령어를 기계어로 바꾸는 작업을 수행한다.
* 매계 : 없음
* 반환 : 정상종료 = 0, 에러발생 = < 0
* 주의 :
* -----------------------------------------------------------------------------------
*/
static int assem_pass2(void)
{

    /* add your code here */
    
    return 0;
}

/* ----------------------------------------------------------------------------------
* 설명 : 입력된 문자열의 이름을 가진 파일에 프로그램의 결과를 저장하는 함수이다.
*        여기서 출력되는 내용은 object code (프로젝트 1번) 이다.
* 매계 : 생성할 오브젝트 파일명
* 반환 : 없음
* 주의 : 만약 인자로 NULL값이 들어온다면 프로그램의 결과를 표준출력으로 보내어
*        화면에 출력해준다.
*
* -----------------------------------------------------------------------------------
*/
void make_objectcode_output(char *file_name)
{
    /* add your code here */
}

