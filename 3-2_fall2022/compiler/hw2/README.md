# [과제 2] 수식 계산을 위한 간단한 RD(Recursive-descent) Parser 구현

> 목표

- Recursive-descent parsing 방법을 이용하여 간단한 수식의 값 계산하는 프로그램 작성

<br>

> 조건

- 수식은 양의 정수와 실수, 소괄호, 덧셈 기호, 곱셈 기호로만 이루어져 있음
- 수식 내에 공백이 존재하는 경우, 이는 무시함
- get_token() 함수는 정수 이외에 실수도 구분 가능해야함
- [주어진 프로그램의 구조](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw2/receiveCode.c)를 그대로 유지하면서 실수 처리 기능도 추가해야함

<br>

> source

- [RD Parser](https://github.com/junghyun21/soongsilUniv/blob/main/3-2_fall2022/compiler/hw2/rd_parser.c)
