#include "utils.h"

int main(int argc, char* argv[]) {
  char* fcontent = get_file_content(argv[1]);

  if (fcontent == NULL) {
    printf("%s does not exist!\n", argv[1]);
    return EXIT_FAILURE;
  }

  write_to_file(argv[2], fcontent);

  printf("%s CONTENT:\n", argv[1]);
  print_file_content(get_file_content(argv[1]));

  printf("\n");

  printf("%s CONTENT:\n", argv[2]);
  print_file_content(get_file_content(argv[2]));

  return EXIT_SUCCESS;
}