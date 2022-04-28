#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1

char *cmd1[] = {"ls", "-l", NULL};
char *cmd2[] = {"wc", "-l", NULL};

int main(int argc, char* argv[]) {
  int fd[2];
  pid_t pid;

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