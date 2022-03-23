#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define   READING_MODE        "r"
#define   CR_MODE             "a+" 

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

void write_to_file(const char* dest_file, const char* data) {
  FILE* ptr;
  ptr = fopen(dest_file, CR_MODE);

  fputs(data, ptr);
  fclose(ptr);  
}

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