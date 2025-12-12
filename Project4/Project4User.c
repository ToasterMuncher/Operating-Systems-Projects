/*
 * Julio Anacleto & Abdullah Almaroof
 * TCES 420 - Principles of Operating Systems
 * December 12th, 2025
 */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main(int argc, char* argv[]) {
	int fd = open("/dev/etx_device", O_RDWR);

	// Write to turn LED on
	char cmd = '1';
	write(fd, &cmd, 1);

	// Read LED state
	char state[3];
	int n = read(fd, state, 2);
	state[n] = '\0';
	printf("LED is: %s", state);

	// Write to turn LED off
	cmd = '0';
	write(fd, &cmd, 1);

	// Read LED state
	n = read(fd, state, 2);
	state[n] = '\0';
	printf("LED is: %s", state);

	close(fd);
}
