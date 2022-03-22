#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STR_SIZE 64

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

int main() {
  char* p1 = (char*)malloc(MAX_STR_SIZE * sizeof(char));
  char* p2 = (char*)malloc(MAX_STR_SIZE * sizeof(char));

  printf("Insert the first string:\n");
  fgets(p1, MAX_STR_SIZE, stdin);

  p1[strcspn(p1, "\n")] = 0;

  printf("\n");

  printf("Insert the second string:\n");
  fgets(p2, MAX_STR_SIZE, stdin);

  p1[strcspn(p2, "\n")] = 0;

  printf("\n");
  printf("num of ocurrences: %d\n", occurrences(p1, p2));
  
  return EXIT_SUCCESS;
}
