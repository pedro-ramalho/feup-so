#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc < 2) {
    fprintf(stderr, "usage: %s file \n", argv[0]);
    return EXIT_FAILURE;
  }

  int total_bytes = 0, total_blocks = 0;

  for (int i = 1; i < argc; i++) {
    printf("file: %s\n", argv[i]);

    struct stat info;
    
    if (lstat(argv[i], &info) == -1) {
      fprintf(stderr, "fsize: Can't stat %s\n", argv[i]);
      return EXIT_FAILURE;
    }

    total_bytes += (int)info.st_size;
    total_blocks += (int)info.st_blocks;

    printf("\n");
    printf(">> last modification: %d\n", (int)info.st_mtime);    
    printf(">> owner: %d\n", (int)info.st_uid);
    printf("\n");
  }
  
  printf("\n");
  printf(">> total bytes: %d\n", total_bytes);
  printf(">> total blocks: %d\n", total_blocks);
  printf("\n");

  return EXIT_SUCCESS;
}