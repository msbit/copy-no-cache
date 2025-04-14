CFLAGS := -Wall -Wextra
CFLAGS += -O2

copy-no-cache: copy-no-cache.o

clean:
	rm -f copy-no-cache copy-no-cache.o
