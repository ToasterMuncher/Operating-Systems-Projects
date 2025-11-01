# Compiler and flags
CC	= gcc
CFLAGS	= -O3

# Targets
all: singleThread.run multiThread.run

# Single-threaded program
singleThread.run: singleThread.c
	$(CC) $(CFLAGS) singleThread.c -o singleThread.run

# Multi-threaded program
multiThread.run: multiThread.c
	$(CC) $(CFLAGS) -pthread multiThread.c -o multiThread.run

# Clean build artifacts
clean:
	rm -f singleThread.run multiThread.run

# Phony targets
.PHONY: all clean

