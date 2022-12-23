import time

def calculateGCD(a, b, numbers, idx, N):
    i = 1
    while True:
        if i > a or i > b:  
            break

        if a % i == 0 and b % i == 0:
            gcd = i

        i += 1

    if gcd == 1 or idx == N - 1:
        return gcd

    idx += 1
    if N > idx:
        return calculateGCD(gcd, numbers[idx], numbers, idx, N)


def bubble_sort(numbers, N):
    for i in range(0, N):
        for j in range(0, N - 1):
            if numbers[j] > numbers[j + 1]:
                temp = numbers[j]
                numbers[j] = numbers[j + 1]
                numbers[j + 1] = temp


def printPrimeNum(numbers, N):
    for i in range(0, N - 1):
        min = numbers[i]
        max = numbers[i + 1]
        if min == max:
            continue
        size = max - min + 1

        isPrime = [True for i in range(size)]
        
        cnt = size
        j = 2
        while(True):
            if j * j > max:
                break

            for k in range(0, size):
                if isPrime[k]:
                    if (k + min) % j == 0:
                        isPrime[k] = False
                        cnt -= 1

            j += 1

        print("Number of prime numbers between {}, {}: {}".format(min, max, cnt))


if __name__ == '__main__':
    while True:
        # input N
        while True:
            print("Input the number of numbers to process: ", end= "")

            try:
                N = int(input())
            except:
                continue

            if N < 2 or N > 30:
                continue

            break


        # input numbers
        while True:
            print("Input the numbers to be processed: ")

            try:
                numbers = list(map(int, input().split()))
            except:
                continue
            
            isInteger = True

            for i in range(N):
                if numbers[i] <= 0 or numbers[i] > 100000:
                    isInteger = False
                    break

            if isInteger:
                break


        # check start time
        start_time = time.time()
    

        # calculate GCD & print GCD
        gcd = calculateGCD(numbers[0], numbers[1], numbers, 1, N)
        print("GCD of input numbers is {}".format(gcd))


        # sort numbers & print number of prime number
        bubble_sort(numbers, N)
        printPrimeNum(numbers, N)

        # check end time 
        end_time = time.time()


        # print total execution time 
        total_time = end_time - start_time
        print("Total execution time using Python is {} seconds!".format(total_time))


        # terminate condition
        while True:
            print("continue?(y/n): ", end = "")
            isExecute = input()

            if isExecute == 'y' or isExecute == 'n':
                break

        if isExecute == 'n':
            break