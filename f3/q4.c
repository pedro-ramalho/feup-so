#include "utils.h"

int flag_print_fc(const char flag[2], const char* file_name) {
  char* fcontent = get_file_content(file_name);

  if (fcontent == NULL)
    return 0;

  if (strcmp(flag, LOWERCASE_FLAG) == 0)
    to_lower(fcontent);
  if (strcmp(flag, UPPERCASE_FLAG) == 0) 
    to_upper(fcontent);

  print_file_content(fcontent);

  return 1;
}

int main(int argc, char* argv[]) {
  if (argc == 2)  // no flag specified
    if (!flag_print_fc(UNSPECIFIED_FLAG, argv[1]))
      return EXIT_FAILURE;

  if (argc == 3)  // flag specified
    if (!flag_print_fc(argv[1], argv[2])) 
      return EXIT_FAILURE;
  
  return EXIT_SUCCESS;
}