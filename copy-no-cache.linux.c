#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int disable_cache(int fd) {
  int flags = fcntl(fd, F_GETFL);
  if (flags == -1) {
    perror("fcntl: F_GETFL");
    return 1;
  }

  if (fcntl(fd, F_SETFL, flags|O_SYNC) == -1) {
    perror("fcntl: F_SETFL");
    return 1;
  }

  return 0;
}

uint64_t timestamp(void) {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return 1000000 * ts.tv_sec + ts.tv_nsec;
}
