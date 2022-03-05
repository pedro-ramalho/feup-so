#include <stdio.h>

int main() {
    int i;
    int primes[] = {2, 3, 5, 7, 11};
    printf("size of primes = %ld\n", sizeof(primes));
    printf("size of int = %ld\n", sizeof(int));
    printf("*primes = %d\n", *primes);
    for (i = 0; i < sizeof(primes)/sizeof(int); i++) {
        printf("%d <--> %d\n", primes[i], *(primes + i));
    }
    return 0;
}