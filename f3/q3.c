#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define READING_MODE "r"
#define MAX_STR_SIZE 128

int print_file_content(char* str) {
  FILE* ptr;
  ptr = fopen(str, READING_MODE);

  if (ptr == NULL)
    return 0;
  
  char* fcontent = (char*)malloc(MAX_STR_SIZE * sizeof(char));

  fseek(ptr, 0, SEEK_SET); //move pointer to start of file
  
  fread(fcontent, MAX_STR_SIZE, sizeof(char), ptr);

  printf("%s\n", fcontent);

  fclose(ptr);

  free(fcontent);
  
  return 1;  
}

int main(int argc, char* argv[]) {
  printf("*FILE CONTENT*\n\n");

  for (int i = 1; i < argc; i++)
    if (!print_file_content(argv[i])) {
      printf("File '%s' does not exist!\n", argv[i]);
      return EXIT_FAILURE;
    }
  
  return EXIT_SUCCESS;
}