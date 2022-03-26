#include "utils.h"

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
  printf("Number of ocurrences: %d\n", occurrences(p1, p2));
  
  return EXIT_SUCCESS;
}
