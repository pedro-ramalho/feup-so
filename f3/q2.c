#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  This function does not allow for input strings with a length 
  over 8 characters. Therefore, calling it with the string "abcdefghi"
  produces an error, called stack smashing.

  To fix this problem we would have to allocate enough memory
  in order to fit every character inside of the string 'content'.
  Down below is a possible fix:

  int f(char* content) {
    int size = strlen(content);
    char* str = (char*)malloc(size * sizeof(char));
    (void)strcpy(str, content);
    return result;
  }

*/

int f(char* content) {
  char str[8];
  int result = 2;
  (void)strcpy(str, content);
  return result;
}

int main(int argc, char* argv[]) {
  if (argc == 2)
    printf("result = %d\n", f(argv[1]));

  return EXIT_SUCCESS;
}