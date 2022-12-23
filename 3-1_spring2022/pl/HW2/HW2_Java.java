import java.util.Scanner;
import java.lang.String;

public class HW2_Java
{
    static String input; 
    static int idx;
    static int bracket;

    // <expr> -> <term> {+ <term> | - <term>}
    static public double expr()
    {
        double result;

        result = term();

        // '\0'은 input의 마지막 값을 의미 -> 더 이상 lexical 분석 할 필요가 없음
        while(idx < input.length())
        {
            // <expr> -> <term> + <term>
            if(input.charAt(idx) == '+')
            {
                ++idx;
                result += term(); // <term> 다음 lexeme 가리키는 중
            }
            // <expr> -> <term> - <term>
            else if(input.charAt(idx) == '-')
            {
                ++idx;
                result -= term(); // <term> 다음 lexeme 가리키는 중
            }
            // <factor> -> (<expr>) 였던 경우, 가르키고 있는 lexeme은 ')'인 상태로 리턴
            else if(bracket > 0 && input.charAt(idx) == ')')
            {
                --bracket;
                return result;
            }
            // +, -, )이 아닌 경우 => syntax error
            else
            {
                System.out.println("syntax error!!");
                System.exit(0);
            }
        }
    
        return result;
    }

    // <term> -> <factor> {* <factor> | / <factor>}
    static public double term()
    {
        double result;

        result = factor(); 

        while(idx < input.length() && (input.charAt(idx) == '*' || input.charAt(idx) == '/'))
        {

            // <term> -> <factor> * <factor>
            if(input.charAt(idx) == '*')
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
    static public double factor()
    {
        double result;
        
        // <factor> -> -(<number> | (<expr>))
        if(input.charAt(idx) == '-')
        {
            ++idx; // '-' 다음 lexeme 가리킴
   
            // <factor> -> -(<expr>)
            if(input.charAt(idx) == '(')
            {
                ++bracket; // '('의 개수 증가
                ++idx; // '(' 다음 lexeme 가리킴
                result = expr();
    
                // <expr> 다음 lexeme 가르키는 중 
                // ')'이 아니면 syntax error => 프로그램 종료
                // ')'이면 ')' 다음 lexeme 가르키는 중
                if(input.charAt(idx++) != ')')
                {
                    System.out.println("syntax error!!");
                    System.exit(0);

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
            if(input.charAt(idx) == '(')
            {
                ++bracket; // '('의 개수 증가
                ++idx; // '(' 다음 lexeme 가리킴
                result = expr();
    
                // <expr> 다음 lexeme 가르키는 중 
                // ')'이 아니면 syntax error => 프로그램 종료
                // ')'이면 ')' 다음 lexeme 가르키는 중
                if(input.charAt(idx++) != ')')
                {
                    System.out.println("syntax error!!");
                    System.exit(0);

                }
       
            }
            // <factor> -> <number>
            else
            {
                result = number(); // <number> 다음 lexeme 가르키는 중
            }
        }
    
        return result;
    }

    // <number> -> <digit>{<digit>}
    static public double number()
    {
        String str = "";
        double result;
        int cnt = 0; // digit의 개수를 알기 위함

        while('0' <= input.charAt(idx) && input.charAt(idx) <= '9')
        {
            str += input.charAt(idx);

            if(idx == input.length() - 1)
            {
                break;
            }
            
            ++idx;
            ++cnt;
        }

        // digit이 하나도 없으면 syntax error
        if(cnt == 0)
        {
            System.out.println("syntax error!!");
            System.exit(0);
        }

        result = Double.parseDouble(str);

        return result;
    }

    public static void main(String[] args)
    {
        double result;
        String str;

        Scanner scanner = new Scanner(System.in);

        while(true)
        {
            System.out.print(">>");

            str = scanner.nextLine(); // 공백 포함하여 값 수식 입력받음
            input = str.replaceAll(" ", ""); // 공백 제거

            idx = 0;

            result = expr();

            // result가 정수인 경우 -> 소수점 없이 출력
            if(result - (int)result == 0)
            {
                System.out.println((int)result);
            }
            // result가 실수인 경우 -> 소수점 있게 출력
            else
            {
                System.out.println(result);
            }
        }

    }

}