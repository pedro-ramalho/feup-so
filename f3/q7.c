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

int main(int argc, char* argv[]) {
  char* needle = argv[1];
  char* file_name = argv[2];

  char* fcontent = get_file_content(file_name);
  char* token;
  token = strtok(fcontent, "\n"); // split file content

  int line = 1, col = 1;

  while (token != NULL) {
    char* ret = strstr(token, needle);
    char* aux = token;

    if (ret != NULL) 
      while (aux != ret) {
        aux += sizeof(char);
        col++;
      }

    printf("[%d:%d]\n", line, col);
    token = strtok(NULL, "\n");

    col = 1;
    line++;      
  }  

  return EXIT_SUCCESS;
}