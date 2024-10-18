#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/10.h"

int main() {
	int base;
	printf("Enter the base of the number system (2-36):\n");
	scanf("%d", &base);
	if (base < 2 || base > 36) {
		fprintf(stderr, "Incorrectly entered number system.\n");
		return 1;
	}

	char *input = malloc(100);
	if (input == NULL) {
		return 1;
	}

	size_t input_size = 1;
	size_t length = 0;

	char *maxNum = NULL;
	printf("Enter number (or 'Stop' for finish):\n");

	while (1) {
		int ch, flag = 0;
		length = 0;
		while ((ch = getchar()) != '\n' && ch != EOF) {
			if (length + 1 >= input_size) {
				input_size *= 2;
				char *temp = realloc(input, input_size);
				if (!temp) {
					fprintf(stderr, "Realloc error memory.\n");
					free(input);
					free(maxNum);
					return 1;
				}
				input = temp;
			}
			input[length++] = (char)ch;
		}
		input[length] = '\0';

		if (strcmp(input, "Stop") == 0) {
			if (maxNum[0] == '\0') {
				printf("Error: No valid numbers were entered.\n");
				free(input);
				free(maxNum);
				return 1;
			}
			break;
		}

		if (!IsValidNumber(input, base)) {
			printf("Invalid number format: it must consist of digits and uppercase letters within the base.\n");
			flag = 1;
		}

		if ((!maxNum || IsGreater(input, maxNum, base)) && (!flag)) {
			if (maxNum != NULL) {
				free(maxNum);
			}

			maxNum = malloc(100);
			if (!maxNum) {
				fprintf(stderr, "Error malloc memory");
				free(input);
				free(maxNum);
				return 1;
			}
			strcpy(maxNum, input);
		}
	}

	printf("The maximum number: %s\n", maxNum);

	for (int i = 9; i <= 36; i += 9) {
		int error = 0;
		char *converted = ConvertBase(maxNum, base, i, &error);
		switch (error) {
			case 1:
				printf("Invalid number format while converting to base %d.\n", i);
				break;
			case 2:
				printf("Overflow occurred while converting to base %d.\n", i);
				break;
			default:
				printf("Base %d: %s\n", i, converted);
				free(converted);
				break;
		}
	}
	free(input);
	free(maxNum);
	return 0;
}
