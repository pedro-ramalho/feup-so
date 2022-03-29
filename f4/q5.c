#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFFER_SIZE 1024

int main() {
  char buffer[BUFFER_SIZE];

  getcwd(buffer, BUFFER_SIZE);
  printf("%s\n", buffer);

  return EXIT_SUCCESS;
}