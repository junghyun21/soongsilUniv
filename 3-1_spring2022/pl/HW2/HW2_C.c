#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_INPUT 1024

double expr();
double term();
double factor();
double number();

char str[MAX_INPUT];
char input[MAX_INPUT];
int idx;
int bracket;

int main()
{
    double result;

    while(true)
    {
        int cnt = 0;
        idx = 0;

        printf(">>");
        scanf("%[^\n]s", str);
        
        while(getchar() != '\n'); // 버퍼 내 개행문자 제거

        while(str[idx] != '\0') // 공백문자 제거
        {
            if(str[idx] != ' ')
            {
                input[cnt] = str[idx];
                ++cnt;
            }

            ++idx;
        }

        input[cnt] = '\0';

        idx = 0;

        result = expr();

        // result가 정수인 경우 -> 소수점 없이 출력
        if(result - (int)result == 0)
        {
            printf("%d\n", (int)result);
        }
        // result가 실수인 경우 -> 소수점 있게 출력
        else
        {
            printf("%f\n", result);
        }
    }

    return 0;
}

// <expr> -> <term> {+ <term> | - <term>}
double expr()
{
    double result;

    result = term(); // <term> 다음 lexeme 가리키는 중

    // '\0'은 input의 마지막 값을 의미 -> 더 이상 lexical 분석 할 필요가 없음
    while(input[idx] != '\0')
    {
        // <expr> -> <term> + <term>
        if(input[idx] == '+')
        {
            ++idx;
            result += term(); // <term> 다음 lexeme 가리키는 중
        }
        // <expr> -> <term> - <term>
        else if(input[idx] == '-')
        {
            ++idx;
            result -= term(); // <term> 다음 lexeme 가리키는 중
        }
        // <factor> -> (<expr>) 였던 경우, 가리키고 있는 lexeme은 ')'인 상태로 리턴
        else if(bracket > 0 && input[idx] == ')')
        {
            --bracket;
            return result;
        }
        // +, -, )이 아닌 경우 => syntax error
        else
        {
            printf("syntax error!!\n");
            exit(0);
        }
    }

    return result;
}

// <term> -> <factor> {* <factor> | / <factor>}
double term()
{
    double result;

    result = factor(); // <factor> 다음 lexeme 가르키는 중

    while(input[idx] == '*' || input[idx] == '/')
    {
        // <term> -> <factor> * <factor>
        if(input[idx] == '*')
        {
            ++idx;
            result *= factor(); // <factor> 다음 lexeme 가르키는 중
        }
        // <term> -> <factor> / <factor>
        else
        {
            ++idx;
            result /= factor(); // <factor> 다음 lexeme 가르키는 중
        }
    }

    return result;
}

// <factor> -> [-](<number> | (<expr>))
double factor()
{
    double result;

    // <factor> -> -(<number> | (<expr>))
    if(input[idx] == '-')
    {
        ++idx; // '-' 다음 lexeme 가리킴
        
        // <factor> -> -(<expr>)
        if(input[idx] == '(')
        {
            ++bracket; // '('의 개수 증가
            ++idx; // '(' 다음 lexeme 가리킴
            result = expr();

            // <expr> 다음 lexeme 가르키는 중 
            // ')'이 아니면 syntax error => 프로그램 종료
            // ')'이면 ')' 다음 lexeme 가르키는 중
            if(input[idx++] != ')')
            {
                printf("syntax error!!\n");
                exit(0);
            }
        }
        // <factor> -> - <number>
        else
        {
            result = number(); // <number> 다음 lexeme 가르키는 중
        }

        result *= -1; // result 값을 음수로 만들기 위함
    }
    // <factor> -> (<number> | (<expr>))
    else
    {
        // <factor> -> (<expr>)
        if(input[idx] == '(')
        {
            ++bracket; // '('의 개수 증가
            ++idx; // '(' 다음 lexeme 가리킴
            result = expr();

            // <expr> 다음 lexeme 가르키는 중 
            // ')'이 아니면 syntax error => 프로그램 종료
            // ')'이면 ')' 다음 lexeme 가르키는 중
            if(input[idx++] != ')')
            {
                printf("syntax error!!\n");
                exit(0);
            }
        }
        // <factor> -> <number>
        else
        {
            result = number(); // <number> 다음 lexeme 가르키는 중
        }
    }

    // printf("");
    return result;
}

// <number> -> <digit>{<digit>}
double number()
{
    char str[MAX_INPUT];
    double result;
    int index = 0;
    int cnt = 0; // digit의 개수를 알기 위함

    while('0' <= input[idx] && input[idx] <= '9')
    {
        str[index++] = input[idx];

        ++idx; // 다음 lexeme 가르키는 중
        ++cnt;
    }

    // digit이 하나도 없으면 syntax error
    if(cnt == 0)
    {
        printf("syntax error!!\n");
        exit(0);
    }

    result = (double)atoi(str);

    return result;
}