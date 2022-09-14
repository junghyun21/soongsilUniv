/*
    - 목표: 간단한 수식을 계산하는 RD Parser 구현
    - 조건: 1. 수식은 양의 정수와 실수, (, ), +, *으로만 이루어져 있음
           2. 공백이 들어온 경우, 이는 무시함
           3. get_token() 함수는 정수 이외에 실수도 구분 가능해야함
    - 고려사항: 1. 본 과제의 parser는 leftmost이며, 연산자의 우선 순위는 (), *, + 순서임
              2. 실수도 포함된 수식의 경우, 수식의 타입에 맞게 결과 출력해야함
    - BNF 표기법:
        <expression> ::= <term> | <term> + <term>
        <term> ::= <factor> | <factor> * <factor>
        <factor> ::= <number> | <number> . <number> | ( <expression> )
        <number> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

enum Token{NUMBER, PLUS, STAR, LP, RP, END};

double expression();
double term();
double factor();
void get_token();
void error(int errno);

bool isDouble;
double num;
enum Token token;

int main()
{
    double result;

    printf("expression > ");
    get_token();

    result = expression();

    if(token != END)
    {
        error(3);
    }
    else
    {
        if(isDouble)
        {
            printf("result: %f\n", result);
        }
        else
        {
            printf("result: %d\n", (int)result);
        }
    }

    return 0;
}

double expression()
{
    double result;
    result = term();
    while(token == PLUS)
    {
        get_token();
        result = result + term();
    }
    return result;
}

double term()
{
    double result;
    result = factor();
    while(token == STAR)
    {
        get_token();
        result = result * factor();
    }
    return result;
}

double factor()
{
    double result;
    if(token == NUMBER)
    {
        result = num;
        get_token();
    }
    else if(token == LP)
    {
        get_token();
        result = expression();
        if(token == RP) get_token();
        else error(2);
    }
    else error(1);
    return result;
}

void get_token()
{
    static char ch = ' ';
    int i = 10;
    
    while(ch == ' ' || ch == '\t') ch = getchar();

    if(isdigit(ch))
    {
        token = NUMBER;
        num = 0;
    
        do{
            num = num * i + atoi(&ch);
            while((ch = getchar()) == ' ' || ch == '\t');
        }while(isdigit(ch));

        if(ch == '.')
        {
            isDouble = true;

            while((ch = getchar()) == ' ' || ch == '\t');
            while(isdigit(ch))
            {
                num = num + atof(&ch) / i;
                i *= 10;

                while((ch = getchar()) == ' ' || ch == '\t');
            }
        }

        return;
    }
    else if(ch == '+')
    {
        token = PLUS;
    }
    else if(ch == '*')
    {
        token = STAR;
    }
    else if(ch == '(')
    {
        token = LP;
    }
    else if(ch == ')')
    {
        token = RP;
    }
    else if(ch == '\n')
    {
        token = END;
        return;
    }
    else
    {
        error(4);
    }

    while((ch = getchar()) == ' ' || ch == '\t');

    return;
}

void error(int errno)
{
    switch(errno)
    {
        case 1: printf("error: number or '(' expected\n"); break;
        case 2: printf("error: ')' expected\n"); break;
        case 3: printf("error: EOF expected\n"); break;
        case 4: printf("error: invalid formula\n"); break;
    }
    exit(1);
}