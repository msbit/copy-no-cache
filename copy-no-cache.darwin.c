#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

int disable_cache(int fd) {
  if (fcntl(fd, F_NOCACHE, 1) == -1) {
    perror("fcntl");
    return 1;
  }

  return 0;
}

uint64_t timestamp(void) {
  return clock_gettime_nsec_np(CLOCK_UPTIME_RAW);
}
