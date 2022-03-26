#include "utils.h"

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