import java.util.InputMismatchException;
import java.util.Scanner;

public class HW1_Java{
    public static int N_MIN = 2;
    public static int N_MAX = 30;
    public static int numbers_MIN = 0;
    public static int numbers_MAX = 100000;

    public static int calculateGCD(int a, int b, int[] numbers, int idx, int N){
        int gcd = 0;

        for(int i = 1; i <= a && i <= b; ++i){
            if(a % i == 0 && b % i == 0){
                gcd = i;
            }
        }
    
        if(gcd == 1 || idx == N - 1){
            return gcd;
        }
    
        if(N > ++idx){
            gcd = calculateGCD(gcd, numbers[idx], numbers, idx, N);
        }

        return gcd;
    }

    public static void bubble_sort(int[] numbers, int N){
        int temp;

        for(int i = 0; i < N; ++i){
            for(int j = 0; j < N - 1; ++j){
                if(numbers[j] > numbers[j + 1]){
                    temp = numbers[j];
                    numbers[j] = numbers[j + 1];
                    numbers[j + 1] = temp;
                }
            }
        }
    
        return;
    }
    
    public static void printPrimeNum(int[] numbers, int N){
        for(int i = 0; i < N - 1; ++i){
            int min = numbers[i];
            int max = numbers[i + 1];
            if(min == max){ // overlapping numbers will be treated as one
                continue;
            }
            int size = max - min + 1;
    
            boolean[] isPrime = new boolean[size]; // if A is a prime number, it's true (min <= A <= max)
            for(int j = 0; j < size; ++j){
                isPrime[j] = true; // initialization array
            }
    
            int cnt = size;
            for(int j = 2; j * j <= max; ++j){ // calculate count of prime number
                for(int k = 0; k < size; ++k){
                    if(isPrime[k]){ // if isPrime[k] is false(not prime number), it doesn't execute
                        if((k + min) % j == 0){
                            isPrime[k] = false;
                            --cnt;
                        }
                    }
                    
                }
            }
    
            System.out.printf("Number of prime numbers between %d, %d: %d\n", min, max, cnt);
    
        } 
    
        return;
    }

    public static void main(String[] args){
        Scanner scanner = new Scanner(System.in);

        while(true){

            /* input N */
            int N;
            
            while(true){
                System.out.print("Input the number of numbers to process: ");

                try{
                    N = scanner.nextInt();
                    scanner.nextLine();
                }
                catch (InputMismatchException e){
                    scanner.nextLine();
                    continue;
                }

                if(N < N_MIN || N > N_MAX){
                    System.out.print("Out of bound. ");
                    continue;
                }

                break;
            }

            /* input numbers */
            int[] numbers = new int[N];

            while(true){
                System.out.println("Input the numbers to be processed:");

                String input = scanner.nextLine();
                String[] inputs = input.split(" ");

                boolean isInteger = true;

                for(int i = 0; i < N; ++i){
                    try{
                        numbers[i] = Integer.parseInt(inputs[i]);
                    }
                    catch (NumberFormatException e){
                        System.out.println("write only integer");
                        isInteger = false;
                        break;
                    }
                    catch(ArrayIndexOutOfBoundsException e){
                        System.out.printf("wirte only %d numbers\n", N);
                        isInteger = false;
                        break;
                    }
                }

                if(!isInteger){
                    continue;
                }

                for(int i = 0; i < N; ++i){
                    if(numbers[i] <= numbers_MIN || numbers[i] > numbers_MAX){
                        isInteger = false;
                        break;
                    }
                }

                if(!isInteger){
                    continue;
                }

                break;
            }
            
            /* check start time */
            long start_time = System.currentTimeMillis();

            /* calculate GCD & print GCD*/
            int gcd = calculateGCD(numbers[0], numbers[1], numbers, 1, N);
            System.out.println("GCD of input numbers is " + gcd);

            /* sort numbers & print number of prime number */
            bubble_sort(numbers, N);
            printPrimeNum(numbers, N);

            /* check end time */
            long end_time = System.currentTimeMillis();

            /* print total execution time */
            double total_time = (double)(end_time - start_time) / 1000.0;
            System.out.println("Total execution time using Java is " + total_time + " seconds!");

            /* terminate condition */
            char isExecute;

            do{
                System.out.print("continue?(y/n): ");
                isExecute = scanner.next().charAt(0);
            }while(isExecute != 'y' && isExecute != 'n');

            if(isExecute == 'n'){
                break;
            }

        }

        scanner.close();
    }


}