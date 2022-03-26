#include <stdlib.h>
#include "utils.h"

int main(int argc, char* argv[]) {
  printf("*FILE CONTENT*\n\n");
  
  for (int i = 1; i < argc; i++) {
    char* fcontent = get_file_content(argv[1]);
    print_file_content(fcontent);  
  }

  return EXIT_SUCCESS;
}