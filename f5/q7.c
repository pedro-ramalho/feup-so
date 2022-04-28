#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>


/* MACROS */

#define BUFF_SIZE 1024

/* parses a given command and inserts each flag into the array args */
void parse_command(char* cmd, char** args) {
  int idx = 0;

  const char sep[2] = " ";
  char* token;

  /* get the first token */
  token = strtok(cmd, sep);

  while (token != NULL) {
    /* allocate memory for the next token, null terminate it and add it to the array */
    args[idx] = (char*)malloc(strlen(token) * sizeof(char*));
    args[idx] = token;
    args[idx][strlen(token)] = '\0';
    
    idx++;

    token = strtok(NULL, sep);
  }
}

char* get_first_token(char* cmd) {
  char* cmd_copy = (char*)malloc(strlen(cmd) * sizeof(char*));
  strcpy(cmd_copy, cmd);
  
  return strtok(cmd_copy, " ");
}

int main(int argc, char* argv[]) {
  FILE *fp;

  fp = fopen("history/cmds.txt", "ab+");

  char buf[BUFF_SIZE];

  /* command to be input by the user */
  char* cmd;
  cmd = (char*)malloc(BUFF_SIZE);

  /* allocate an array of up to 20 strings, at most */
  char** args;
  args = (char**)malloc(20 * sizeof(char*));

  pid_t pid;

  /* infinite cycle, leave when user presses CTRL-C or CTRL-D */
  while (1) {

    /* give prompt, read command, null terminate it */
    fprintf(stdout, "$ ");
    if ((cmd = fgets(buf, sizeof(buf), stdin)) == NULL)
      break;

    cmd[strlen(buf) - 1] = '\0';

    if ((pid = fork()) == -1) {
      fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
      continue;
    }
    
    /* child process */
    if (pid == 0) {
      /* append written command to the text file */
      fprintf(fp, cmd);
      printf("cmd = %s\n", cmd);
      char* instr = get_first_token(cmd);

      parse_command(cmd, args);

      // myhistory 3
      // == tail -n 3 history/cmds.txt
      // args[0] = myhistory
      // args[1] = 3
      // args[0] = tail
      // args[2] = args[1]
      // args[1] = "-n"
      // args[3] = history/cmds.txt
      if (strcmp(instr, "myhistory") == 0) {
        char* new_instr = "tail";
        char num_lines[2];

        strcpy(num_lines, args[1]);

        for (int i = 0; i < 20; i++)
          args[i] = (char*)malloc(BUFF_SIZE);
        
        strcpy(args[0], "tail");
        strcpy(args[2], num_lines);
        strcpy(args[1], "-n");
        strcpy(args[3], "history/cmds.txt");

        args[0][BUFF_SIZE - 1] = '\0';
        args[1][BUFF_SIZE - 1] = '\0';
        args[2][BUFF_SIZE - 1] = '\0';
        args[3][BUFF_SIZE - 1] = '\0';

        execvp(new_instr, args);
      }

      execvp(instr, args);

      /* if this code runs then execvp failed */
      fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf, strerror(errno));
      exit(EXIT_FAILURE);
    }

    if ((pid = waitpid(pid, NULL, 0)) < 0)
      fprintf(stderr, "%s: waitpid error: %s\n", argv[0], strerror(errno));
  }

  return EXIT_SUCCESS;
}
