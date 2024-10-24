#include <stdio.h>
#include "include/1.h"
#include <stdlib.h>

int main(void) {
	size_t size_res = 10;
	char *result = (char *)malloc(sizeof(char) * size_res);
	if (!result){
		fprintf(stderr, "Error malloc memory.\n");
		return 1;
	}
	int size, power = 2, number = -52;
	kOpt status = Convert(&result, &size, number, power, &size_res);
	switch (status) {
		case OPT_ERROR:
			fprintf(stderr, "Error. Incorrect inputs.\n");
			break;
		case OPT_SUCCESS:
			PrintResult(result, size);
			break;
		case OPT_MEMORY:
			fprintf(stderr, "Error alloc memory.\n");
			break;
	}
	free(result);
	return 0;
}
