CFLAGS := -Wall -Wextra
CFLAGS += -O2

main: main.o

clean:
	rm -f main main.o
