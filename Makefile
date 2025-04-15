CFLAGS := -Wall -Wextra
CFLAGS += -O2

darwin: copy-no-cache.o copy-no-cache.darwin.o
	$(LINK.o) $(^) $(LOADLIBES) $(LDLIBS) -o copy-no-cache

linux: copy-no-cache.o copy-no-cache.linux.o
	$(LINK.o) $(^) $(LOADLIBES) $(LDLIBS) -o copy-no-cache

clean:
	rm -f copy-no-cache copy-no-cache.o copy-no-cache.darwin.o copy-no-cache.linux.o
