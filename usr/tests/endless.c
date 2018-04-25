#include <time.h>
#include <stdio.h>
#include <hermit/syscall.h>


int main(int argc, char **argv) {
	int cnt = 0;
#pragma omp parallel
	while(1) {
#pragma omp critical
{
		printf("Counter %d\n", ++cnt);
}
		sys_msleep(500);
	}

	return 0;
}
