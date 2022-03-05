#include <stdio.h>

int main() {
    int i;
    char msg[] = "Hello World";
    for (int i = 0; i < sizeof(msg); i++)
        printf("%c <--> %c\n", msg[i], *(msg+i));
    
    return 0;
}