#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/***** MACROS *****/


/* Pipe macros used in the file descriptor */

#define READ_END 0
#define WRITE_END 1


/* Integers used to represent the size of arrays and buffers */

#define ARR_SIZE 20
#define BUFF_SIZE 1024


/* Strings used to parse other strings */

#define BLANK " "
#define PIPE_SYMBOL "|"



void build_arr(char* cmd_str, char** cmd_arr) {
  const char sep[1] = BLANK;
  char* token;
  int idx = 0;

  token = strtok(cmd_str, sep);

  while (token != NULL) {
    cmd_arr[idx] = (char*)malloc(strlen(token) * sizeof(char*));
    cmd_arr[idx] = token;
    idx++;

    token = strtok(NULL, sep);
  }
}

void split_cmds(char* cmd, char* cmdl, char* cmdr) {
  const char sep[1] = PIPE_SYMBOL;
  char* token;

  /* get the left-most command */
  token = strtok(cmd, sep);
  strcpy(cmdl, token);
  
  /* get the right-most command */
  token = strtok(NULL, sep);
  strcpy(cmdr, token);
} 

int main(int argc, char* argv[]) {
  int fd[2];
  pid_t pid;

  char** cmd1;
  char** cmd2;

  char* cmd;
  char* cmdl;
  char* cmdr;

  /* allocate enough memory */
  cmd = (char*)malloc(BUFF_SIZE);
  cmdl = (char*)malloc(BUFF_SIZE);
  cmdr = (char*)malloc(BUFF_SIZE);

  /* fetch the command input by the user */
  strcpy(cmd, argv[1]);

  /* split the command in two, using the pipe symbol as the separator */
  split_cmds(cmd, cmdl, cmdr);
  
  cmd1 = (char**)malloc(ARR_SIZE);
  cmd2 = (char**)malloc(ARR_SIZE);

  /* build an array for each command and null terminate it */
  build_arr(cmdl, cmd1);  
  build_arr(cmdr, cmd2);

  cmd1[ARR_SIZE - 1] = NULL;
  cmd2[ARR_SIZE - 1] = NULL;

  if (pipe(fd) < 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }

  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    close(fd[READ_END]);

    dup2(fd[WRITE_END], STDOUT_FILENO);

    close(fd[WRITE_END]);
    // parent writes to the pipe

    if (execvp(cmd1[0], cmd1) < 0) {
      fprintf(stderr, "execvp error %s\n", strerror(errno));
    }
  }
  else {
    close(fd[WRITE_END]);

    dup2(fd[READ_END], STDIN_FILENO);

    close(fd[READ_END]);
    
    if (execvp(cmd2[0], cmd2) < 0) {
      fprintf(stderr, "execvp error %s\n", strerror(errno));
    }
  }

  return 0;
}
