#include "include/3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
	int size = 0;
	if (ValidateInput(argc, argv)){
		fprintf(stderr, "Error. Incorrect arguments. Correct: <file_in> <flag(-a /a -d /d)> <file_out>\n");
		return -1;
	}

	char flag = 0;
	if (argv[2][1] == 'd'){
		flag = 1;
	}

	Employee *data = NULL;

	FILE *input = fopen(argv[1], "r");
	if (!input){
		printf("Error open input file.\n");
		fclose(input);
		return -2;
	}

	FILE *output = fopen(argv[3], "w");
	if (!output){
		printf("Error open output file.\n");
		fclose(input);
		fclose(output);
		return -2;
	}

	kOpt status = GetEmployee(input, &data, &size);
	switch (status) {
		case OPT_SUCCESS:
			break;
		case OPT_ERROR_INPUT:
			fprintf(stderr, "Incorrect values.\n");
			fclose(input);
			fclose(output);
			return -3;
		case OPT_ERROR_MEMORY:
			fprintf(stderr, "Error alloc memory.\n");
			fclose(input);
			fclose(output);
			return -4;
	}

	if (flag){
		qsort(data, size, sizeof(Employee), CompareB);
	}else{
		qsort(data, size, sizeof(Employee), CompareA);
	}

	for (int i = 0; i < size; i++){
		fprintf(output, "%u %s %s %lf\n", data[i].id, data[i].name, data[i].surname, data[i].salary);
	}

	free(data);
	fclose(input);
	fclose(output);
	return 0;
}
