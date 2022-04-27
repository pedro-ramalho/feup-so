#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define READ_END 0
#define WRITE_END 1
#define LINESIZE 256

#define READING_MODE "r"
#define MAX_STR_SIZE 256

char* get_file_content(const char* file) {
  FILE* ptr;
  ptr = fopen(file, READING_MODE);

  if (ptr == NULL)
    return NULL;
  
  char* fcontent = (char*)malloc(MAX_STR_SIZE * sizeof(char));

  fseek(ptr, 0, SEEK_SET);

  fread(fcontent, MAX_STR_SIZE, sizeof(char), ptr);

  fclose(ptr);

  return fcontent;
}

int main(int argc, char *argv[]) {
  int nbytes, fd[2];
  pid_t pid;
  char line[LINESIZE];

  if (pipe(fd) < 0) {
    perror("pipe error");
    exit(EXIT_FAILURE);
  }

  if ((pid = fork()) < 0) {
    perror("fork error");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0) {
    /* parent */
    close(fd[READ_END]);
    
    printf("Parent process with pid %d\n", getpid());
    printf("Messaging the child process (pid %d): \n", pid);

    const char* file_content = get_file_content(argv[1]);

    snprintf(line, LINESIZE, file_content, getpid());

    if ((nbytes = write(fd[WRITE_END], line, strlen(line))) < 0) {
      fprintf(stderr, "Unable to write to pipe: %s\n", strerror(errno));
    }

    close(fd[WRITE_END]);

    /* wait for child and exit */
    if (waitpid(pid, NULL, 0) < 0) {
      fprintf(stderr, "Cannot wait for child: %s\n", strerror(errno));
    }
    
    exit(EXIT_SUCCESS);
  }
  else {
    /* child */
    close(fd[WRITE_END]);

    printf("Child process with pid %d\n", getpid());
    printf("Receiving message from parent (pid %d): \n", getpid());

    if ((nbytes = read(fd[READ_END], line, LINESIZE)) < 0) {
      fprintf(stderr, "Unable to read from pipe: %s\n", strerror(errno));
    }

    close(fd[READ_END]);

    /* write message from parent and exit */
    write(STDOUT_FILENO, line, nbytes);
    
    exit(EXIT_SUCCESS);
  }

  return 0;
}