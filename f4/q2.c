#include <sys/types.h>
#include <sys/stat.h>

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    (void)fprintf(stderr, "usage: %s perms file\n", argv[0]);
    return EXIT_FAILURE;
  }

  int perms = atoi(argv[1]);

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
      (void)printf(stderr, "%s: illegal permission value\n", argv[0]);
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
      (void)printf(stderr, "%s: illegall permission value\n", argv[0]);
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
      (void)fprintf(stderr, "%s: illegal permission value\n", argv[0]);
      return EXIT_FAILURE;
  }

  chmod(argv[2], newperms);
  
  return EXIT_SUCCESS;
}