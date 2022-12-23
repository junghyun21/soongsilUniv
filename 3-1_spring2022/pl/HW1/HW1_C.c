#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int calculateGCD(int a, int b, int *numbers, int idx, int N); // GCD(the greatest common denominator)
void bubble_sort(int *numbers, int N); // sort numbers 
void printPrimeNum(int *numbers, int N); // print count of prime number

int main()
{
    while(true){
        int N; // number of N (2 <= N <= 30)
        int *numbers; // input numbers
        int *temp;
        int gcd;
        int cnt_prime; // number of prime number
        clock_t start_time; // after completion of input
        clock_t end_time; // after completion of output
        double total_time;
        bool isInteger;
        char isExecute = '\0'; 
        
        /* input N */
        while(true){
            printf("Input the number of numbers to process: ");
            scanf("%d", &N);

            if(N >= 2 && N <= 30){
                break;
            }

            while(getchar() != '\n');
        }

        /* dynamic assignment of space to store numbers*/
        numbers = (int *)malloc(sizeof(int) * N);
        temp = (int *)malloc(sizeof(int) * N);
        if(numbers == NULL || temp == NULL){
            fprintf(stderr, "malloc error\n");
            exit(1);
        }

        /* input numbers */
        while(true){
            isInteger = true;

            printf("Input the numbers to be processed:\n");

            for(int i = 0; i < N; ++i){
                scanf("%d", &temp[i]);
            }

            while(getchar() != '\n');

            for(int i = 0; i < N; ++i){
                if(temp[i] <= 0 || temp[i] > 100000){
                    isInteger = false;
                    break;
                }

                numbers[i] = temp[i];
            }

            if(isInteger){
                break;
            }
        }

        /* check start time */
        start_time = clock();

        /* calculate GCD & print GCD*/
        gcd = calculateGCD(numbers[0], numbers[1], numbers, 1, N);
        printf("GCD of input numbers is %d\n", gcd);

        /* sort numbers & print number of prime number */
        bubble_sort(numbers, N);
        printPrimeNum(numbers, N);

        /* check end time */
        end_time = clock();

        /* print total execution time */
        total_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        printf("Total execution time using C is %lf seconds!\n", total_time);

        free(numbers);

        /* terminate condition */
        do{
            printf("continue?(y/n): ");
            scanf("%c", &isExecute);
        }while(isExecute != 'y' && isExecute != 'n');

        if(isExecute == 'n'){
            break;
        }

    }

    return 0;
}

// GCD(the greatest common denominator)
// a, b: factor for calcutation of GCD
// numbers: input numbers
// idx: index number of b
// N: number of numbers
int calculateGCD(int a, int b, int *numbers, int idx, int N)
{
    int gcd;

    for(int i = 1; i <= a && i <= b; ++i){
        if(a % i == 0 && b % i == 0){
            gcd = i;
        }
    }

    if(gcd == 1 || idx == N - 1){
        return gcd;
    }

    if(N > ++idx){
        return calculateGCD(gcd, numbers[idx], numbers, idx, N);
    }
    
}

// sort numbers through bubble sort
// numbers: array to be sorted
// N: number of numbers
void bubble_sort(int *numbers, int N)
{
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

// print count of prime number
// numbers: sorting array
// N: number of numbers
void printPrimeNum(int *numbers, int N)
{
    bool *isPrime;
    int min;
    int max;
    int size;
    int cnt;

    for(int i = 0; i < N - 1; ++i){
        min = numbers[i];
        max = numbers[i + 1];
        if(min == max){ // overlapping numbers will be treated as one
            continue;
        }
        size = max - min + 1;

        isPrime = (bool *)malloc(sizeof(bool) * size); // if A is a prime number, it's true (min <= A <= max)
        for(int j = 0; j < size; ++j){
            isPrime[j] = true; // initialization array
        }

        cnt = size;
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

        free(isPrime);

        printf("Number of prime numbers between %d, %d: %d\n", min, max, cnt);

    } 

    return;
}