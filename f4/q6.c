#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>

void display_file_info(const char* filepath) {
  struct stat info;
  lstat(filepath, &info);
  printf("%ld ", info.st_size);
  printf("%d ", info.st_mode);
  printf("%ld\n", info.st_mtime);
}

int main(int argc, char** argv) {
  struct dirent *p;
  DIR *q;

  if (argc != 2) {
    fprintf(stderr, "usage: %s dirname\n", argv[0]);
    return EXIT_FAILURE;
  }

  q = opendir(argv[1]);

  if (q == NULL) {
    printf("%s ", argv[1]);
    display_file_info(argv[1]);
  } 
  else {
    p = readdir(q);

    while (p != NULL) {
      printf("%s ", p->d_name);
      display_file_info(p->d_name);
      p = readdir(q);
    }
    
    closedir(q);
  }
 
  return EXIT_SUCCESS;
}