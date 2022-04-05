#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  /* fork a child process */
  fork();
  printf("first: %d\n", getpid());
  /* fork another process */
  fork();
  printf("second: %d\n", getpid());
  /* and fork another */
  fork();
  printf("third: %d\n", getpid());

  return EXIT_SUCCESS;
}
