# [과제 3] 간단한 수식을 위한 LR Parser 구현

> 목표

- 간단한 수식을 입력 받아 그 수식의 값을 출력하는 C 프로그램 작성

<br>

> 조건

- 수식은 양의 정수와 소괄호, 덧셈 기호, 곱셈 기호로만 이루어져 있음
- 수식 내에 공백이 존재하는 경우, 이는 무시함
- scanf()는 사용 불가하며 오직 getchar()만 사용 가능함

<br>

> LR 문법

![LR](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw3/LR.png)

<br>

> Action Table && GOTO Table

![actione table](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw3/table.png)


<br>

> source

- [LR Parser](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw3/lr_parser.c)