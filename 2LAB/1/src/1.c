#include "../include/1.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int MyStrLen(const char *input) {
    int len = 0;
    while (input[len] != '\0') {
        len++;
    }
    return len;
}

kOpts FlagL(const char *input, char **output) {
    char *tmp = realloc(*output, 50);
    if (!tmp){
        return OPT_ERROR_MEMORY;
    }
    (*output) = tmp;

    sprintf(*output, "Length: %d", MyStrLen(input));
    return OPT_SUCCESS;
}

kOpts FlagR(const char *input, char **output) {
    int len = MyStrLen(input);
    char *tmp = realloc(*output, len + 1);
    if (!tmp) {
        return OPT_ERROR_MEMORY;
    }
    *output = tmp;

    for (int i = 0; i < len; i++) {
        (*output)[i] = input[len - i - 1];
    }

    (*output)[len] = '\0';
    return OPT_SUCCESS;
}

kOpts FlagU(const char *input, char **output) {
    int i = 0;
    int len = MyStrLen(input);
    char *tmp = realloc(*output, len + 1);
    if (!tmp) {
        return OPT_ERROR_MEMORY;
    }

    *output = tmp;

    while (input[i] != '\0') {
        if (i % 2 == 0) {
            (*output)[i] = toupper(input[i]);
        } else {
            (*output)[i] = input[i];
        }
        i++;
    }

    *output[i] = '\0';
    return OPT_SUCCESS;
}

kOpts FlagN(const char *input, char **output) {
    int len = MyStrLen(input);
    int ind = 0;

    char *tmp = realloc(*output, len);
    if (!tmp) {
        return OPT_ERROR_MEMORY;
    }

    (*output) = tmp;

	char* others = (char*)malloc((len + 1) * sizeof(char));
	if (!others){
		return OPT_ERROR_MEMORY;
	}

    char* letters = (char*)malloc((len + 1) * sizeof(char));
	if (!letters){
		free(others);
		return OPT_ERROR_MEMORY;
	}
    int other_count = 0, letter_count = 0;

    for (int j = 0; j < len; j++) {
        char obj = input[j];
        if (isdigit(obj)) {
            (*output)[ind++] = obj;
        } else if (isalpha(obj)) {
            letters[letter_count++] = obj;
        } else {
            others[other_count++] = obj;
        }
    }

    for (int i = 0; i < letter_count; i++) {
        (*output)[ind++] = letters[i];
    }

    for (int i = 0; i < other_count; i++) {
        (*output)[ind++] = others[i];
    }

    (*output)[ind] = '\0';
	free(others);
	free(letters);
    return OPT_SUCCESS;
}

kOpts FlagC(char **output, int seed, int argc, char **argv) {
    srand(seed);
    size_t total_len = MyStrLen(argv[2]);

    for (int i = 4; i < argc; i++) {
        total_len += MyStrLen(argv[i]);
    }

    char *result = (char *) malloc(total_len + 1);
    if (result == NULL) {
        return OPT_ERROR_MEMORY;
    }

    result[0] = '\0';

    int *index_array = (int *) malloc((argc - 3) * sizeof(int));
    if (index_array == NULL) {
        free(result);
        return OPT_ERROR_MEMORY;
    }

    index_array[0] = 2;
    for (int i = 4; i < argc; i++) {
        index_array[i - 3] = i;
    }

    for (int i = argc - 4; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = index_array[i];
        index_array[i] = index_array[j];
        index_array[j] = temp;
    }

    for (int i = 0; i < argc - 3; i++) {
        MyStrcat(result, argv[index_array[i]]);
    }

    char *tmp = realloc(*output, total_len + 1);
    if (!tmp) {
        free(result);
        free(index_array);
        return OPT_ERROR_MEMORY;
    }
    (*output) = tmp;

    MyStrCpy(*output, result);
    free(result);
    free(index_array);

    return OPT_SUCCESS;
}

char *MyStrcat(char *dest, const char *src) {
    char *ptr = dest;

    while (*ptr) {
        ptr++;
    }

    while (*src) {
        *ptr++ = *src++;
    }

    *ptr = '\0';
    return dest;
}

char *MyStrCpy(char *dest, const char *src) {
    char *ptr = dest;
    while (*src) {
        *ptr++ = *src++;
    }
    *ptr = '\0';
    return dest;
}

int MyStrtoi(const char *str, char **end) {
    while (isspace((unsigned char) *str)) {
        str++;
    }

    int sign = 1;
    if (*str == '-') {
        sign = -1;
        str++;
    } else if (*str == '+') {
        str++;
    }

    int result = 0;
    while (isdigit((unsigned char) *str)) {
        result = result * 10 + (*str - '0');
        str++;
    }

    if (end) {
        *end = (char *) str;
    }

    return sign * result;
}

int MyStrCmp(const char *s1, const char *s2) {
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(const unsigned char *) s1 - *(const unsigned char *) s2;
}

int CheckFlag(const char *kflag, char *valid_flag) {
    return (kflag[0] == '-' || kflag[0] == '/') && MyStrCmp(&kflag[1], valid_flag) == 0;
}

int GetOpts(int argc, char **argv, kOpts *option, int *number) {
    if (argc < 3 || (argv[1][1] == 'c' && argc < 4)) {
        return 1;
    }

    if (argv[1][1] == 'c') {
        char *end;
        *number = MyStrtoi(argv[3], &end);
        if (*end != '\0') {
            return 2;
        }
        if (*number < 1){
            return 4;
        }
    }

    char *flags[5] = {"l", "r", "u", "n", "c"};

    for (int i = 0; i < 5; i++) {
        if (CheckFlag(argv[1], flags[i])) {
            *option = i;
            return 0;
        }
    }

    return 3;
}