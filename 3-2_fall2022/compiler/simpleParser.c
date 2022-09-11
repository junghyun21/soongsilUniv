/*
    - 목표: 간단한 수식을 입력받아 그 수식의 값을 출력하는 C 프로그램 작성
    - 조건: 1. 수식은 0또는 한 자리 양의 정수와 (, ), +, *으로만 이루어져 있음
           2. 공백이 들어온 경우, 이는 무시함
           3. scanf()는 사용 불가하며 오직 getchar()만 사용 가능함
    - 고려사항: 본 과제의 parser는 leftmost이며, 연산자의 우선 순위는 (), *, + 순서임
    - BNF 표기법:
        <expression> ::= <term> <expr_res>
        <expr_res> ::= + <term> <expr_res> | λ
        <term> ::= <factor> <term_res>
        <term_res> ::= * <factor> <term_res> | λ
        <factor> ::= <number> | ( <expression> )
        <number> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
        -------------------------------------------------------
        <expression> ::= <term> | <term> + <term>
        <term> ::= <factor> | <factor> * <factor>
        <factor> ::= <number> | ( <expression> )
        <number> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
*/

#include <stdio.h>
#include <stdlib.h>

#define PLUS '+'
#define MULTI '*'
#define PARENTHESES_OPEN '('
#define PARENTHESES_CLOSE ')'
#define SPACE ' '

static char input;

int expression();
int term();
int factor();

int main()
{
    int result;
    
    printf("수식 입력 > ");
    while((input = getchar()) == SPACE);

    result = expression();

    printf("결과값 > %d\n", result);

    return 0;
}

int expression()
{
    int result; 

    result = term();

    while(input != '\n')
    {
        if(input == PLUS)
        {
            while((input = getchar()) == SPACE);
            result += term();
        }
        else if(input == PARENTHESES_CLOSE)
        {
            break;
        }
        else
        {
            printf("syntax error!\n");
            exit(1);
        }
    }

    return result;
}

int term()
{
    int result;

    result = factor();

    if(input == MULTI)
    {
        while((input = getchar()) == SPACE);
        result *= factor();
    }

    return result;
}

int factor()
{
    int result;

    // number
    if('0' <= input && input <= '9')
    {
        result = atoi(&input);
    }
    // ( <expression> )
    else if(input == PARENTHESES_OPEN)
    {
        while((input = getchar()) == SPACE);
        result = expression();

        if(input != PARENTHESES_CLOSE)
        {
            printf("syntax error\n");
            exit(1);
        }
    }
    else
    {
        printf("syntax error!\n");
        exit(1);
    }

    while((input = getchar()) == SPACE);

    return result;
}