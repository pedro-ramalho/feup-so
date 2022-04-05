#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  printf("parent\n");

  for (int i = 0; i < 3; i++) {
    if (fork() == 0) {
      printf("child\n");
    }

     /* if (fork() == 0) {
      printf("child\n");
    } */
  }
  
  return EXIT_SUCCESS;
}