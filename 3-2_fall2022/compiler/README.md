# [과제 1] 간단한 수식을 위한 파서(Parser) 구현

> 목표

- 간단한 수식을 입력 받아 그 수식의 값을 출력하는 C 프로그램 작성

<br>

> 조건

- 수식은 0에서 9 사이의 정수와 소괄호, 덧셈 기호, 곱셈 기호로만 이루어져 있음
- 수식 내에 공백이 존재하는 경우, 이는 무시함
- scanf()는 사용 불가하며 오직 getchar()만 사용 가능함

<br>

> BNF 표기법

```
<expression> ::= <term> | <term> + <term>
<term> ::= <factor> | <factor> * <factor>
<factor> ::= <number> | ( <expression> )
<number> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 
```