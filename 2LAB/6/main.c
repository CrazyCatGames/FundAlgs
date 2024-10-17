#include <stdio.h>
#include "include/6.h"

int main(int argc, char* argv[]) {
	FILE* file = fopen("C:\\Users\\user\\CLionProjects\\FUNDLABS\\2LAB\\6\\file\\test.txt", "r");
	if (file == NULL){
		fprintf(stderr, "Error of opening file.\n");
		return 1;
	}

	char s[STR_SIZE];
	int num1, num2, num3;
	unsigned int num4;
    overfscanf(file, "%CV %Zr %s %Cv %Ro", &num1, 16, &num4, s, &num2, 16, &num3);
    printf("Results: %d %d %s %d %d\n", num1, num4, s, num2, num3);

    oversscanf("012DEF 010011 ABOBA abc MCXXVIII", "%CV %Zr %s %Cv %Ro", &num1, 16, &num4, s, &num2, 36, &num3);
    printf("Results: %d %d %s %d %d\n", num1, num4, s, num2, num3);

	oversscanf("XV XVX 1010", "%Ro %Ro %CV", &num1, &num2, &num3, 2);
	printf("Results: %d %d %d\n", num1, num2, num3);
	fclose(file);
}