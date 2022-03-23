#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define   READING_MODE        "r"

#define   UPPERCASE_FLAG      "-u"
#define   LOWERCASE_FLAG      "-l"
#define   UNSPECIFIED_FLAG    "-nf"

#define   MAX_STR_SIZE        128

char* get_file_content(const char* str) {
  FILE* ptr;
  ptr = fopen(str, READING_MODE);

  if (ptr == NULL)
    return NULL;
  
  char* fcontent = (char*)malloc(MAX_STR_SIZE * sizeof(char));

  fseek(ptr, 0, SEEK_SET);

  fread(fcontent, MAX_STR_SIZE, sizeof(char), ptr);

  fclose(ptr);

  return fcontent;
}

void print_file_content(const char* fcontent) {
  printf("%s\n", fcontent);
}

void to_lower(char* str) {
  int str_size = strlen(str);

  for (int i = 0; i < str_size; i++) 
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] += 32;
}

void to_upper(char* str) {
  int str_size = strlen(str);

  for (int i = 0; i < str_size; i++)
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] -= 32;
}

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