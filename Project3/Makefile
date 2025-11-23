# Compiler and flags
CC	= gcc
CFLAGS	= -O3

# Targets
all: main.c

# Multi-threaded program
threadScheduler.run: main.c
	$(CC) $(CFLAGS) -pthread main.c -o threadScheduler.run

# Clean build artifacts
clean:
	rm -f threadScheduler.run

# Phony targets
.PHONY: all clean
