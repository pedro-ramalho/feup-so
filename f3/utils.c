#include "utils.h"

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

void print_file_content(const char* fcontent) {
  printf("%s\n", fcontent);
}

void write_to_file(const char* dest_file, const char* data) {
  FILE* ptr;
  ptr = fopen(dest_file, CRWR_MODE);

  fputs(data, ptr);
  fclose(ptr); 
}


int contains(char* s1, char* s2) {
  return strstr(s2, s1) != NULL;
}

int occurrences(char* s1, char* s2) {
  int num_ocurrences = 1;

  while (strstr(s2, s1) != NULL) {
    s2 += sizeof(s1);
    num_ocurrences++;
  }

  return num_ocurrences;
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


char* get_file_content(const char* file) {
  FILE* ptr;
  ptr = fopen(file, READING_MODE);

  if (ptr == NULL)
    return NULL;
  
  char* fcontent = (char*)malloc(MAX_STR_SIZE * sizeof(char));

  fseek(ptr, 0, SEEK_SET);

  fread(fcontent, MAX_STR_SIZE, sizeof(char), ptr);

  fclose(ptr);

  return fcontent;
}