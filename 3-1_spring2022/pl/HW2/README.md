# [PL] HW2

### 다음의 EBNF로 문법이 정의되는 수식을 위한 계산기 구현
    <expr> -> <term> {+ <term> | - <term>}
    <term> -> <factor> {* <factor> | / <factor>}
    <factor> -> [-] (<number> | (<expr>))
    <number> -> <digit> {<digit>}
    <digit> -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<br>

> ### 함수 호출 통한 우선순위 결정
- 각각의 LHS(좌항)을 하나의 함수로 해결함
- expr() 호출 -> term() 호출 -> factor() 호출 -> number() 호출 -> digit 결정
<br>
<br>
<br>
<br>
<br>

**2022.05.04** <br>
- HW2_C.c
    > factor() 내에서 printf() 유무에 따라 결과 값이 달라진다. -> 189 line
    > 
    > + printf()문이 있는 경우 -> 올바른 값(4782) 출력
    > <br> ![printf():O](./image_README/printf("factor()->").png)
    > 
    > + printf()문이 없는 경우 -> 잘못된 값(6337) 출력
    > <br> (다른 수식이 입력되었을 때에는 올바른 값 출력되기도 함)
    > <br> ![printf():X](./image_README/no_printf().png)
    >
    > <br> => 출력 유무 자체의 차이라고 생각해서 기존 printf()문을 printf("") 로 수정했는데, 오히려 printf()문이 없는 경우(6337)와 동일한 값이 출력됨 - *띠용?*
<br><br>

- HW2_Java.java
    > c언어 보고 그대로 베껴서 코드 옮기다 보니 엉망진창이 되어버렸다. - *머쓱*
    >
    > 전체적으로 다시 손을 봐야할 것 같다.
    >
    > 특히 String 타입에서 메모리를 벗어나는 값을 사용하는 부분(java.lang.OutOfMemoryError: heap space) 신경써서 고쳐야할듯