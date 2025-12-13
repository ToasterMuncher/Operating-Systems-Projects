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
	if(fd < 0) {
    printf("Error: Cannot open device file. Is the driver loaded?\n");
    return 1;
	}

	char cmd = '0';
	write(fd, &cmd, 1);

	int UserInput;

	printf("Please enter how many times to blink (Positive Integer Values ONLY):");
	scanf("%d", &UserInput);

	if(UserInput <=0){
		printf("Error: Value Input is Invalid\n");
		close(fd);
		return 1;
	}

	while(UserInput > 0){
		// Write to turn LED on
		cmd = '1';
		write(fd, &cmd, 1);
		printf("LED IS ON\n");

		sleep(2);

		// Write to turn LED off
		cmd = '0';
		write(fd, &cmd, 1);
		printf("LED IS OFF\n");

		sleep (2);

		UserInput--;

	}

	printf("Program Completed\n");

	close(fd);

	return 0;
}
