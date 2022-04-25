#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>

void parse_command(char* command, char array[1024]) {
  const char sep[] = " ";
  char *token;
  int i = 0;

  token = strtok(command, sep);

  while (token != NULL) {
    array[i] = *token;
    token = strtok(NULL, sep);
    i++;
  }
}

int main(int argc, char* argv[]) {
  char buf[1024];
  char parsed_command[1024];

  char *command;

  pid_t pid;

  for( ; ; ) {
    fprintf(stdout, "$ ");
    if ((command = fgets(buf, sizeof(buf), stdin)) == NULL)
      break;
    
    command[strlen(buf) - 1] = '\0';
    parse_command(command, parsed_command);

    if ((pid = fork()) == -1) {
      fprintf(stderr, "%s: can't fork command: %s\n", argv[0], strerror(errno));
      continue;
    }
    else if (pid == 0) {
      execlp(command, command, (char *)0);
      fprintf(stderr, "%s: couldn't exec %s: %s\n", argv[0], buf, strerror(errno));
      exit(EXIT_FAILURE);
    }

    if ((pid = waitpid(pid, NULL, 0)) < 0)
      fprintf(stderr, "%s: waitpid error: %s\n", argv[0], strerror(errno));
  }

  exit(EXIT_SUCCESS);
}
