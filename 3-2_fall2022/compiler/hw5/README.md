# [과제 5] yacc와 lex를 이용한 간단한 C parser 구현

> 목표

- C 문법을 따르는 Parser 작성

<br>

> 조건

- Lex scanner, Yacc parser를 이용하여 구현
- Lex는 입력 문자열에 대한 일차적인 검색, Yacc는 실제적인 분석
- Yacc는 입력에 대한 token이 필요하면, lex에서 제공하는 yylex()를 호출하여 문법 체크
- comma와 shift 연산자는 제외함

<br>

> 순서

```
vi yacc.y // C 문법 작성
vi lex.l // 토큰 분석기 작성
yacc -d yacc.y // y.tab.c 생성됨 -> 이 테이블이 있어야 lex 돌릴 수 있음
lex lex.l // lex.yy.c 생성됨
gcc main.c y.tab.c lex.yyc
```

<br>

> shift/reduce 해결 방법

- selection_statement에서 발생
- else가 어떤 if에 붙는지 모호한 문제가 발생하기 때문에 conflicts 발생
- %nonassoc와 %prec를 통해 해결
    
    ```
    selection_statement
            : IF_SYM LP expression RP statement              
            | IF_SYM LP expression RP statement ELSE_SYM statement
            | SWITCH_SYM LP expression RP statement
            ;
    ```

    ```
    %token ...

    // Precedences go increasing, so "then" < "else"
    %nonassoc "then"
    %nonassoc ELSE_SYM

    %%

    .
    .
    .

    selection_statement
            : IF_SYM LP expression RP statement                %prec "then"
            | IF_SYM LP expression RP statement ELSE_SYM statement
            | SWITCH_SYM LP expression RP statement
            ;
    ```


<br>

> source

- [yacc](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw5/yacc.y)
- [lex](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw5/lex.l)