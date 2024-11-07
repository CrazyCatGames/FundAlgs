#include "include/8.h"

int main(int argc, char **argv) {
	FILE *input;
	char command[5];
	char ch;
	int count;
	Polynom adder, polynom_1, polynom_2, res;
	kOpt status;
	if (argc != 2) {
		printf("Input error. Use: %s <input_file>\n", argv[0]);
		return OPT_INPUT_ERROR;
	}

	InitPolynom(&adder);
	input = fopen(argv[1], "r");
	if (!input) {
		printf("File open error\n");
		return OPT_FILE_OPEN_ERROR;
	}

	while ((ch = getc(input)) != EOF) {
		command[0] = '\0';
		if (isspace(ch) || ch == ';') continue;
		if (ch == '%') {
			while (ch != EOF && ch != '\n') ch = getc(input);
			continue;
		}
		if (ch == '[') {
			while (ch != EOF && ch != ']') ch = getc(input);
			if (ch == EOF) {
				fclose(input);
				DestroyPolynom(&adder);
				printf("Input error\n");
				return OPT_INPUT_ERROR;
			}
			continue;
		}
		if (ch == 'A' || ch == 'S' || ch == 'M' || ch == 'D' || ch == 'E' || ch == 'C') {
			command[0] = ch;
			count = 0;
			fscanf(input, "%3[^(]s", command + 1);
			if (strcmp(command, "Add") != 0 && strcmp(command, "Sub") != 0 &&
				strcmp(command, "Mult") != 0 && strcmp(command, "Div") != 0 &&
				strcmp(command, "Mod") != 0 && strcmp(command, "Eval") != 0 &&
				strcmp(command, "Diff") != 0 && strcmp(command, "Cmps") != 0) {
				printf("Input error\n");
				DestroyPolynom(&adder);
				fclose(input);
				return OPT_INPUT_ERROR;
			}
		}
		if (!strcmp(command, "Add")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Add(&adder, &polynom_1) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&polynom_1);
			}
			if (count == 2) {
				if (Add(&polynom_1, &polynom_2) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&adder);
				adder = polynom_1;
			}
			printf("Add result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Sub")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Sub(&adder, &polynom_1) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&polynom_1);
			}
			if (count == 2) {
				if (Sub(&polynom_1, &polynom_2) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&adder);
				adder = polynom_1;
			}
			printf("Sub result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Mult")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Multiply(&adder, &polynom_1, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			if (count == 2) {
				if (Multiply(&polynom_1, &polynom_2, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			DestroyPolynom(&polynom_1);
			DestroyPolynom(&adder);
			adder = res;
			printf("Mult result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Div")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Mod(&adder, &polynom_1, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			if (count == 2) {
				if (Mod(&polynom_1, &polynom_2, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			DestroyPolynom(&polynom_1);
			DestroyPolynom(&adder);
			adder = res;
			printf("Div result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Mod")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Mod(&adder, &polynom_1, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&polynom_1);
			}
			if (count == 2) {
				if (Mod(&polynom_1, &polynom_2, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				DestroyPolynom(&adder);
				adder = polynom_1;
			}
			DestroyPolynom(&res);
			printf("Mod result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Cmps")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			switch (status) {
				case OPT_MEMORY_ERROR:
					fprintf(stderr, "Error alloc memory.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_MEMORY_ERROR;
				case OPT_OVERFLOW_ERROR:
					fprintf(stderr, "Overflow.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_OVERFLOW_ERROR;
				case OPT_INPUT_ERROR:
				case OPT_ZERO_ARGS:
					fprintf(stderr, "Incorrect inputs.\n");
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					return OPT_INPUT_ERROR;
			}
			if (count == 1) {
				if (Cmps(&adder, &polynom_1, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			if (count == 2) {
				if (Cmps(&polynom_1, &polynom_2, &res) != OPT_SUCCESS) {
					DestroyPolynom(&polynom_1);
					DestroyPolynom(&polynom_2);
					DestroyPolynom(&res);
					DestroyPolynom(&adder);
					fclose(input);
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
			}
			DestroyPolynom(&polynom_1);
			DestroyPolynom(&adder);
			adder = res;
			printf("Cmps result: ");
			PrintPolynom(&adder);
		} else if (!strcmp(command, "Eval")) {
			double x, res_double;
			status = OPT_SUCCESS;
			if (getc(input) != '(')
				status = OPT_INPUT_ERROR;
			if (status || fscanf(input, "%lf", &x) != 1 || getc(input) != ')' || getc(input) != ';' || Eval(&adder, x, &res_double)) {
				DestroyPolynom(&adder);
				fclose(input);
				printf("Input error\n");
				return OPT_INPUT_ERROR;
			}
			printf("Eval result: %lf\n", res_double);
		} else if (!strcmp(command, "Diff")) {
			status = GetExpression(&polynom_1, &polynom_2, input, &count);
			if (status == OPT_INPUT_ERROR || status == OPT_MEMORY_ERROR || getc(input) != ';') {
				DestroyPolynom(&polynom_1);
				DestroyPolynom(&adder);
				fclose(input);
				if (status == OPT_MEMORY_ERROR) {
					printf("Memory error\n");
					return OPT_MEMORY_ERROR;
				}
				printf("Input error\n");
				return OPT_INPUT_ERROR;
			}
			if (status == OPT_ZERO_ARGS)
				status = Diff(&adder, &res);
			else
				status = Diff(&polynom_1, &res);
			if (status) {
				DestroyPolynom(&polynom_1);
				DestroyPolynom(&adder);
				DestroyPolynom(&res);
				fclose(input);
				printf("Memory error\n");
				return OPT_MEMORY_ERROR;
			}
			DestroyPolynom(&adder);
			DestroyPolynom(&polynom_1);
			adder = res;
			printf("Diff result: ");
			PrintPolynom(&adder);
		} else {
			DestroyPolynom(&adder);
			fclose(input);
			printf("Input error\n");
			return OPT_INPUT_ERROR;
		}
	}
	DestroyPolynom(&adder);
	DestroyPolynom(&polynom_1);
	fclose(input);
	return OPT_SUCCESS;
}