#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <hermit/syscall.h>

static
uint64_t memparse(const char *ptr)
{
	// local pointer to end of parsed string
	char *endptr;

	// parse number
	uint64_t size = strtoull(ptr, &endptr, 0);

	// parse size extension, intentional fall-through
	switch (*endptr) {
	case 'E':
	case 'e':
		size <<= 10;
	case 'P':
	case 'p':
		size <<= 10;
	case 'T':
	case 't':
		size <<= 10;
	case 'G':
	case 'g':
		size <<= 10;
	case 'M':
	case 'm':
		size <<= 10;
	case 'K':
	case 'k':
		size <<= 10;
		endptr++;
	default:
		break;
	}

	return size;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "ERROR: You have to specify the size of the memory region to be allocated!\n");
		exit(-1);
	}

	uint64_t alloc_size = memparse(argv[1]);
	printf("Allocating %llu bytes ...\n", alloc_size);
	char *mem_reg = (char*)malloc(alloc_size);
	if (mem_reg == NULL) {
		fprintf(stderr, "ERROR: Could not allocate %llu bytes of memory!\n", alloc_size);
		exit(-1);
	}
	memset(mem_reg, 0x42, alloc_size);
	printf("Allocated and mapped!\n");

	uint32_t cnt = 0;
	while(1) {
		uint64_t i;
		for (i=0; i<alloc_size; ++i) {
			if (mem_reg[i] != 0x42) {
				fprintf(stderr, "ERROR: mem_reg[%llu] = 0x%x != 0x42!\n", i, mem_reg[i]);
			}
		}
		printf("Sleeping ...");
		fflush(stdout);
		sys_msleep(500);
		printf("%d!\n", cnt++);
	}
	return 0;
}
