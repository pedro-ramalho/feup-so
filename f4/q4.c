#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void set_perms(int given_perms, const char* file) {
  int perms = atoi(given_perms);

  int operms = perms % 10; //owner perms
  perms /= 10;

  int gperms = perms % 10; //group perms
  perms /= 10;

  int uperms = perms; //user perms

  mode_t newperms = (mode_t) 0;

  switch (uperms) {
    case 0: break;
    case 1: newperms |= S_IXUSR; break;
    case 2: newperms |= S_IWUSR; break;
    case 3: newperms |= S_IWUSR | S_IXUSR; break;
    case 4: newperms |= S_IRUSR; break;
    case 5: newperms |= S_IRUSR | S_IXUSR; break;
    case 6: newperms |= S_IRUSR | S_IWUSR; break;
    case 7: newperms |= S_IRUSR | S_IWUSR | S_IXUSR; break;
    default:
      return EXIT_FAILURE;
  }

  switch (gperms) {
    case 0: break;
    case 1: newperms |= S_IXGRP; break;
    case 2: newperms |= S_IWGRP; break;
    case 3: newperms |= S_IWGRP | S_IXGRP; break;
    case 4: newperms |= S_IRGRP; break;
    case 5: newperms |= S_IRGRP | S_IWGRP; break;
    case 6: newperms |= S_IRGRP | S_IWGRP; break;
    case 7: newperms |= S_IRGRP | S_IWGRP | S_IXGRP; break;
    default:
      return EXIT_FAILURE;
  }

  switch (operms) {
    case 0: break;
    case 1: newperms |= S_IXOTH; break;
    case 2: newperms |= S_IWOTH; break;
    case 3: newperms |= S_IWOTH | S_IWOTH; break;
    case 4: newperms |= S_IROTH; break;
    case 5: newperms |= S_IROTH | S_IXOTH; break;
    case 6: newperms |= S_IROTH | S_IWOTH; break;
    case 7: newperms |= S_IROTH | S_IWOTH | S_IXOTH; break;
    default:
      return EXIT_FAILURE;
  }

  chmod(file, newperms);

  return EXIT_SUCCESS;
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("usage: touch filename\n");
    return EXIT_FAILURE;
  }

  struct stat info;

  if (lstat(argv[1], &info) == -1) { //file does not exist, create it and set perms to 644
    int fd = open(argv[1], O_CREAT);
    set_perms(644, argv[1]);    
  }
  else //file exists, update modified date
    utime(argv[1], NULL);    
  
  return EXIT_SUCCESS;
}