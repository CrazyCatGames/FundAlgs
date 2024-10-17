#include "include/5.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    FILE* textfile = fopen("C:\\Users\\user\\CLionProjects\\FUNDLABS\\2LAB\\5\\file\\test.txt", "w");
    if (textfile == NULL){
        fprintf(stderr, "Error of opening file.\n");
        return 0;
    }

    overfprintf(stdout, "Number is: %Ro %Ro\n", 5124, 1);
    overfprintf(stdout, "Number is: %Zr\n", (unsigned int)10);
    overfprintf(stdout, "Number is: %Cv\n", 1234, 16);
    overfprintf(stdout, "Numbers: %to %TO %to %TO\n", "abcdef", 16, "123", 12, "0001", 2, "-25", 17);
    overfprintf(stdout, "%mi\n%mu\n%md\n%mf\n", (int)10, (unsigned int)12, (double)2.2, (double)5.6);
    overfprintf(textfile, "Number is: %Ro\n", (unsigned int)111);
    overfprintf(stdout, "%Ro %CV %Ro %CV %CV\n", 15, 10, 16, 15, 22, 2, 17, 2);

    char* buf = (char*)malloc(sizeof(char) * 32);
    oversprintf(buf, "Number is: %Ro", 123);
    printf("%s\n", buf);
    oversprintf(buf, "Number is: %Cv, %CV", 0010, 5, 1234, 16);
    printf("%s\n", buf);
    oversprintf(buf, "Numbers: %to %TO %d%d", "abcdef", 16, "10", 10, 12, 12);
    printf("%s\n", buf);
    oversprintf(buf, "%mi\n%mu\n%md\n%mf\n", (int)10, (unsigned int)12, (double)2.2, (double)5.6);
    printf("%s\n", buf);
    oversprintf(buf, "Number is: %Zr\n", (unsigned int)10);
    printf("%s\n", buf);
    free(buf);
    fclose(textfile);
}