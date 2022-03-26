#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/* FILE OPENING MODES */

#define   READING_MODE        "r"
#define   CRWR_MODE           "a+" 


/* FLAGS FOR COMMANDS */

#define   UPPERCASE_FLAG      "-u"
#define   LOWERCASE_FLAG      "-l"
#define   NUMCHARS_FLAG       "-c"
#define   NUMWORDS_FLAG       "-w"
#define   NUMLINES_FLAG       "-l"
#define   UNSPECIFIED_FLAG    "-nf"


/* MAX SIZE OF AN INPUT STRING */
#define   MAX_STR_SIZE        128

void to_lower(char* str);
void to_upper(char* str);
void print_file_content(const char* fcontent); 
void write_to_file(const char* dest_file, const char* data);

int contains(char* s1, char* s2);
int occurrences(char* s1, char* s2);
int get_num_lines(const char* file);
int get_num_chars(const char* file);
int get_num_words(const char* file);
 
char* get_file_content(const char* str);
 