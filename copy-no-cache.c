#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int process(const char *infilename, const char *outfilename);
int disable_cache(int fd);
uint64_t timestamp(void);

int main(int argc, char **argv) {
  for (int i = 1; i < argc; i++) {
    process(argv[i], "/dev/null");
  }

  return 0;
}

int process(const char *infilename, const char *outfilename) {
  int ret = 0;

  int infd = open(infilename, O_RDONLY);
  if (infd == -1) {
    perror("open");
    ret = 1;
    goto defer_none;
  }

  int outfd = open(outfilename, O_WRONLY);
  if (outfd == -1) {
    perror("open");
    ret = 1;
    goto defer_infd;
  }

  if (disable_cache(infd) == 1) {
    ret = 1;
    goto defer_outfd;
  }

  char *buffer = calloc(1024 * 1024, sizeof(char));
  if (buffer == NULL) {
    perror("malloc");
    ret = 1;
    goto defer_outfd;
  }

  uint64_t before = timestamp();
  ssize_t totalcount = 0;
  for (;;) {
    ssize_t r = read(infd, buffer, 1024 * 1024);
    if (r == 0) {
      break;
    }
    if (r == -1) {
      ret = 1;
      goto defer_malloc;
    }

    totalcount += r;
    for (ssize_t w = 0; w < r; w += write(outfd, buffer, 1024 * 1024))
      ;
  }
  uint64_t after = timestamp();
  uint64_t delta = (after - before) / 1000000;
  printf("%s -> %s ", infilename, outfilename);
  if (delta == 0) {
    printf("∞ ");
  } else {
    printf("%llu ", totalcount / delta);
  }
  puts("bytes/ms");

defer_malloc:
  free(buffer);

defer_outfd:
  close(outfd);

defer_infd:
  close(infd);

defer_none:
  return ret;
}
