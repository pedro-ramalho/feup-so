#include "utils.h"

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