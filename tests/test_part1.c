#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_virtualmem 340

int main(int argc, char *argv[])
{
	int pid_input;
	printf("Enter a pid: ");
	scanf("%d", &pid_input);
	syscall(__NR_virtualmem, pid_input);
	return 0;
}
