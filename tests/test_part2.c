#include <linux/unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>

#define __NR_virtualmemstatus 341


int main(int argc, char *argv[])
{
	int pid_input;
	printf("Enter a pid: ");
	scanf("%d", &pid_input);
	
	unsigned long mem;
	printf("Enter an address for the memory: ");
	scanf("%ld",&mem);

	syscall(__NR_virtualmemstatus, mem, pid_input);
	return 0;
}
