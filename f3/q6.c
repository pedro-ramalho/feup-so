#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define   READING_MODE        "r"
#define   CR_MODE             "a+" 

#define   UPPERCASE_FLAG      "-u"
#define   LOWERCASE_FLAG      "-l"
#define   NUMCHARS_FLAG       "-c"
#define   NUMWORDS_FLAG       "-w"
#define   NUMLINES_FLAG       "-l"
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

int get_num_lines(const char* file) {
  int num_lines = 1;

  for (int i = 0; i < strlen(file); i++)
    if (file[i] == '\n')
      num_lines++;
  
  return num_lines;
}

int get_num_chars(const char* file) {
  int num_chars = 0;

  for (int i = 0; i < strlen(file); i++)
    if (file[i] != '\n' && file[i] != ' ')
      num_chars++;
  
  return num_chars;
}

int get_num_words(const char* file) {
  int num_words = 1;

  for (int i = 0; i < strlen(file); i++)
    if (file[i] == ' ' || file[i] == '\n')
      num_words++;

  return num_words; 
}

int main(int argc, char* argv[]) {
  char* fcontent;

  if (argc == 2) {  //unspecified flag
    fcontent = get_file_content(argv[1]);
    printf("Number of characters: %d\n", get_num_chars(fcontent));    
  }
  if (argc == 3) {
    fcontent = get_file_content(argv[2]);
    if (strcmp(NUMCHARS_FLAG, argv[1]) == 0)
      printf("Number of characters: %d\n", get_num_chars(fcontent));
    
    if (strcmp(NUMWORDS_FLAG, argv[1]) == 0)
      printf("Number of words: %d\n", get_num_words(fcontent));
    
    if (strcmp(NUMLINES_FLAG, argv[1]) == 0)
      printf("Number of lines: %d\n", get_num_lines(fcontent));
  }
 
  return EXIT_SUCCESS;
}