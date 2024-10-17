#include "../include/5.h"
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

optRealloc MyRealloc(void **var, int size) {
    void *new_ptr = realloc(*var, size);
    if (new_ptr != NULL) {
        *var = new_ptr;
        return OPT_REALLOC_SUCCESS;
    } else {
        return OPT_REALLOC_FAIL;
    }
}

kOpt ToRoman(int number, char **roman_value) {
    const int numbers[13] = {1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000};
    const char letters[13][2] = {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
    int roman_size = 0;
    int roman_capacity = 2;
    (*roman_value) = (char *) malloc(sizeof(char) * roman_capacity);
    if (*roman_value == NULL) {
        return OPT_ERROR_ALLOC;
    }

    if (number < 0) {
        (*roman_value)[0] = '-';
        roman_size++;
        number = abs(number);
    }

    while (number) {
        int index = 13;
        while (numbers[--index] > number)
            ;

        for (int i = 0; i < 2; i++) {
            if (letters[index][i] == 'I' || letters[index][i] == 'V' || letters[index][i] == 'X' ||
                letters[index][i] == 'L' || letters[index][i] == 'C' || letters[index][i] == 'D' || letters[index][i] == 'M') {
                (*roman_value)[roman_size] = letters[index][i];
                roman_size++;
                if (roman_size == roman_capacity - 1) {
                    roman_capacity *= 2;
                    optRealloc st_realloc = MyRealloc((void **)roman_value, roman_capacity);
                    if (st_realloc == OPT_REALLOC_FAIL) {
                        return OPT_ERROR_ALLOC;
                    }
                }
            }
        }
        number -= numbers[index];
    }
    (*roman_value)[roman_size] = '\0';
    return OPT_SUCCESS;
}

void Fibonacci(unsigned int result[2], unsigned int number) {
    unsigned int count = 0;
    unsigned int tmp1 = 0, tmp2 = 1;
    unsigned int next = tmp1 + tmp2;
    while (next <= number) {
        tmp1 = tmp2;
        tmp2 = next;
        next = tmp1 + tmp2;
        count++;
    }
    result[0] = count;
    result[1] = tmp2;
}

void Zeckendorf(int *result_size, unsigned int number, unsigned int result[number][2]) {
    (*result_size) = 0;
    while (number) {
        Fibonacci(result[*result_size], number);
        (*result_size)++;
        number -= result[(*result_size) - 1][1];
    }
}

kOpt FromDecimal(long long decimal_number, int base, int flag, char **result) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    int index = 0;
    bool is_minus = false;
    (*result) = (char *) malloc((32 + 1) * sizeof(char));
    if (*result == NULL) {
        return OPT_ERROR_ALLOC;
    }
    int size = 0;
    if (decimal_number == 0) {
        (*result)[index] = '0';
        (*result)[index + 1] = '\0';
        return OPT_SUCCESS;
    }

    if (decimal_number < 0) {
        is_minus = true;
        (*result)[index++] = '-';
        size++;
    }

    decimal_number = abs(decimal_number);
    while (decimal_number) {
        long long remainder = decimal_number % base;
        if (remainder < 10) {
            (*result)[index++] = remainder + '0';
        } else {
            if (flag) {
                (*result)[index++] = remainder - 10 + 'A';
            } else {
                (*result)[index++] = remainder - 10 + 'a';
            }
        }
        size++;
        if (size > sizeof(*result) - 1) {
            optRealloc st_realloc = MyRealloc((void **)result, size * 2);
            if (st_realloc == OPT_REALLOC_FAIL) {
                return OPT_ERROR_ALLOC;
            }
        }
        decimal_number /= base;
    }
    (*result)[size] = '\0';
    int len = strlen(*result);
    for (int i = 0, j = 0; len - 1 - j > i; i++, j++) {
        if (is_minus) {
            i++;
            is_minus = false;
        }
        char tmp = (*result)[i];
        (*result)[i] = (*result)[len - 1 - j];
        (*result)[len - 1 - j] = tmp;
    }
    return OPT_SUCCESS;
}

kOpt ToDecimal(char *number_str, int base, long long *dec_number, int flag) {
    if (base < 2 || base > 36) {
        base = 10;
    }

    unsigned long long decimal_number = 0;
    int power = strlen(number_str) - 1;
    bool start = true;
    bool minus = false;
    for (int i = 0; i < strlen(number_str); i++) {
        char digit = number_str[i];
        if (digit == '-' && start) {
            power--;
            start = false;
            minus = true;
            continue;
        }
        int digit_value;
        if (isdigit(digit)) {
            digit_value = digit - '0';
        } else if (isalpha(digit)) {
            if (flag) {
                digit_value = digit - 'A' + 10;
            } else {
                digit_value = digit - 'a' + 10;
            }
        } else {
            return OPT_INVALID_PARAMETER;
        }

        decimal_number += digit_value * pow(base, power);
        power--;
        start = false;
    }
    if (decimal_number > INT_MAX) {
        return OPT_INVALID_PARAMETER;
    }
    *dec_number = minus ? -1 * decimal_number : decimal_number;
    return OPT_SUCCESS;
}

bool is_lower(char *str, int size) {
    for (int i = 0; i < size; i++) {
        if ((str[i] >= 'A') && (str[i] <= 'Z')) {
            return false;
        }
    }
    return true;
}

bool is_upper(char *str, int size) {
    for (int i = 0; i < size; i++) {
        if ((str[i] >= 'a') && (str[i] <= 'z')) {
            return false;
        }
    }
    return true;
}

int overfprintf(FILE *stream, char *format, ...) {
    if (!stream) {
        return -1;
    }

    int size_format = strlen(format);
    if (!size_format) {
        return -1;
    }

    int argc = 0;
    for (int i = 0; i < size_format; i++) {
        if (format[i] == '%') {
            if (format[i + 1] != '%') {
                argc++;
            }
        }
    }

    va_list ptr;
    va_start(ptr, format);
    int index = 0;
    char *flag = NULL;
    int ret_value = 0;
    for (int i = 0; i < argc; i++) {
        int size_flag = 1;
        int capacity_flag = 2;
        while (format[index] != '%' && index < size_format) {
            ret_value += fprintf(stream, "%c", format[index]);
            index++;
        }
        flag = (char *) malloc(sizeof(char) * (capacity_flag + 2));
        if (flag == NULL) {
            fprintf(stderr, "Error malloc memory.\n");
            return OPT_ERROR_ALLOC;
        }

        flag[0] = '%';
        index++;
        while ((isalpha(format[index]) || isdigit(format[index]) || (format[index] == '%' && format[index - 1] == '%') ||
                (format[index] == '.' && (isalpha(format[index + 1]) || isdigit(format[index + 1]) || format[index + 1] == '*')) || (format[index] == '#') || (format[index] == '+') || (format[index] == '-') || (format[index] == '0')) &&
               (index < size_format)) {
            char symbol = format[index];
            flag[size_flag] = symbol;
            size_flag++;
            if (size_flag == capacity_flag - 1) {
                capacity_flag *= 2;
                optRealloc st_realloc = MyRealloc((void **)flag, capacity_flag);
                if (st_realloc == OPT_REALLOC_FAIL) {
                    free(flag);
                    fprintf(stderr, "Error realloc memory.\n");
                    return -1;
                }
            }
            index++;
        }
        flag[size_flag] = '\0';
        if (!strcmp(flag, "%Ro\0")) {
            char *roman_value = NULL;
            kOpt st_roman = ToRoman(va_arg(ptr, int), &roman_value);
            if (st_roman == OPT_ERROR_ALLOC) {
                printf("Error malloc memory\n");
                free(roman_value);
                return -2;
            }
            ret_value += fprintf(stream, "%s", roman_value);
            free(roman_value);
        } else if (!strcmp(flag, "%Zr\0")) {
            unsigned int number = va_arg(ptr, unsigned int);
            int res_size;
            unsigned int res[number][2];
            Zeckendorf(&res_size, number, res);
            int count = 1;
            int j = res_size - 1;
            while (j >= 0) {

                if (count == res[j][0]) {
                    ret_value += fprintf(stream, "1");
                    j--;
                } else {
                    ret_value += fprintf(stream, "0");
                }

                count++;
            }
            ret_value += fprintf(stream, "1");
        } else if (!strcmp(flag, "%Cv\0")) {
            long long number_to_convert = va_arg(ptr, long long);
            argc++;
            int base = va_arg(ptr, int);
            char *result = NULL;
            kOpt st_convert = FromDecimal(number_to_convert, base, 0, &result);
            if (st_convert == OPT_ERROR_ALLOC) {
                free(result);
                printf("Error malloc memory.\n");
                break;
            }
            ret_value += fprintf(stream, "%s", result);
            free(result);
        } else if (!strcmp(flag, "%CV\0")) {
            long long number_to_convert = va_arg(ptr, long long);
            argc++;
            int base = va_arg(ptr, int);
            char *result = NULL;
            kOpt st_convert = FromDecimal(number_to_convert, base, 1, &result);
            if (st_convert == OPT_ERROR_ALLOC) {
                free(result);
                printf("Error malloc memory\n");
                break;
            }
            ret_value += fprintf(stream, "%s", result);
            free(result);
        } else if (!strcmp(flag, "%to\0")) {
            char *num_to_convert = va_arg(ptr, char *);
            int size = strlen(num_to_convert);
            argc++;
            int base = va_arg(ptr, int);
            long long result;

            if (!is_lower(num_to_convert, size)) {
                printf("Letters are in upper case\n");
                break;
            }

            kOpt st_convert = ToDecimal(num_to_convert, base, &result, 0);
            if (st_convert == OPT_INVALID_PARAMETER) {
                printf("Invalid parameter.\n");
                break;
            }
            ret_value += fprintf(stream, "%lld", result);
        } else if (!strcmp(flag, "%TO\0")) {
            char *num_to_convert = va_arg(ptr, char *);
            int size = strlen(num_to_convert);
            argc++;
            int base = va_arg(ptr, int);
            long long int result;

            if (!is_upper(num_to_convert, size)) {
                printf("Letters are in lower case\n");
                break;
            }

            kOpt st_convert = ToDecimal(num_to_convert, base, &result, 1);
            if (st_convert == OPT_INVALID_PARAMETER) {
                printf("Invalid parameter.\n");
                break;
            }

            ret_value += fprintf(stream, "%lld", result);
        } else if (!strcmp(flag, "%mi\0")) {
            int val = va_arg(ptr, int);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            ret_value = 0;

            for (int j = 0; j < sizeof(int); j++) {
                unsigned char byte = *tmp_ptr;
                for (int bit = 7; bit >= 0; bit--) {
                    ret_value += fprintf(stream, "%u", (byte >> bit) & 1);
                }
                if (j < sizeof(int) - 1) {
                    fprintf(stream, " ");
                }
                tmp_ptr++;
            }
        } else if (!strcmp(flag, "%mu\0")) {
            unsigned int val = va_arg(ptr, unsigned int);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            ret_value = 0;

            for (int j = 0; j < sizeof(unsigned int); j++) {
                unsigned char byte = *tmp_ptr;
                for (int bit = 7; bit >= 0; bit--) {
                    ret_value += fprintf(stream, "%u", (byte >> bit) & 1);
                }
                if (j < sizeof(unsigned int) - 1) {
                    fprintf(stream, " ");
                }
                tmp_ptr++;
            }
        } else if (!strcmp(flag, "%md\0")) {
            double val = va_arg(ptr, double);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            ret_value = 0;

            for (int j = 0; j < sizeof(double); j++) {
                unsigned char byte = *tmp_ptr;
                for (int bit = 7; bit >= 0; bit--) {
                    ret_value += fprintf(stream, "%u", (byte >> bit) & 1);
                }
                if (j < sizeof(double) - 1) {
                    fprintf(stream, " ");
                }
                tmp_ptr++;
            }
        } else if (!strcmp(flag, "%mf\0")) {
            float val = (float) va_arg(ptr, double);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            ret_value = 0;

            for (int j = 0; j < sizeof(float); j++) {
                unsigned char byte = *tmp_ptr;
                for (int bit = 7; bit >= 0; bit--) {
                    ret_value += fprintf(stream, "%u", (byte >> bit) & 1);
                }
                if (j < sizeof(float) - 1) {
                    fprintf(stream, " ");
                }
                tmp_ptr++;
            }
        } else {
            ret_value += vfprintf(stream, flag, ptr);
        }


        free(flag);
        flag = NULL;
    }

    if (strchr(format, '\n')) {
        ret_value += fprintf(stream, "\n");
    }

    if (flag) {
        free(flag);
    }

    va_end(ptr);
    return ret_value;
}

int oversprintf(char *buf, char *format, ...) {
    int size_format = strlen(format);
    if (!size_format) {
        return -1;
    }

    int argc = 0;
    for (int i = 0; i < size_format; i++) {
        if (format[i] == '%') {
            if (format[i + 1] != '%') {
                argc++;
            }
        }
    }
    va_list ptr;
    va_start(ptr, format);
    int index = 0;
    char *flag = NULL;
    int ret_value = 0;
    for (int i = 0; i < argc; i++) {
        int size_flag = 1;
        int capacity_flag = 2;
        while (format[index] != '%' && index < size_format) {
            ret_value += sprintf(buf + ret_value, "%c", format[index]);
            index++;
        }
        flag = (char *) malloc(sizeof(char) * (capacity_flag + 2));
        if (!flag) {
            return -1;
        }
        flag[0] = '%';
        index++;
        while ((isalpha(format[index]) || isdigit(format[index]) || (format[index] == '%' && format[index - 1] == '%') ||
                (format[index] == '.' && (isalpha(format[index + 1]) || isdigit(format[index + 1]) || format[index + 1] == '*')) || (format[index] == '#') || (format[index] == '+') || (format[index] == '-') || (format[index] == '0')) &&
               (index < size_format)) {
            char symbol = format[index];
            flag[size_flag] = symbol;
            size_flag++;
            if (size_flag == capacity_flag - 1) {
                capacity_flag *= 2;
                optRealloc st_realloc = MyRealloc((void **)flag, capacity_flag);
                if (st_realloc == OPT_REALLOC_FAIL) {
                    free(flag);
                    printf("Error realloc memory.\n");
                    return -1;
                }
            }
            index++;
        }
        flag[size_flag] = '\0';

        if (!strcmp(flag, "%Ro\0")) {
            char *roman_value = NULL;
            kOpt st_roman = ToRoman(va_arg(ptr, int), &roman_value);
            if (st_roman == OPT_ERROR_ALLOC) {
                printf("Error alloc memory.\n");
                free(roman_value);
                return -2;
            }
            ret_value += sprintf(buf + ret_value, "%s", roman_value);
            free(roman_value);
        } else if (!strcmp(flag, "%Zr\0")) {
            unsigned int number = va_arg(ptr, unsigned int);
            //printf("%d---\n", number);
            int res_size;
            unsigned int res[number][2];
            Zeckendorf(&res_size, number, res);
            int count = 1;
            int j = res_size - 1;
            while (j >= 0) {
                if (count == res[j][0]) {
                    ret_value += sprintf(buf + ret_value, "1");
                    j--;
                } else {
                    ret_value += sprintf(buf + ret_value, "0");
                }

                count++;
            }

            ret_value += sprintf(buf + ret_value, "1");
        } else if (!strcmp(flag, "%Cv\0")) {
            long long number_to_convert = va_arg(ptr, long long);
            argc++;
            int base = va_arg(ptr, int);
            char *result = NULL;
            kOpt st_convert = FromDecimal(number_to_convert, base, 0, &result);
            if (st_convert == OPT_ERROR_ALLOC) {
                free(result);
                printf("Error malloc memory.\n");
                break;
            }
            ret_value += sprintf(buf + ret_value, "%s", result);
            free(result);
        } else if (!strcmp(flag, "%CV\0")) {
            long long number_to_convert = va_arg(ptr, long long);
            int base = va_arg(ptr, int);
            char *result = NULL;
            argc++;
            kOpt st_convert = FromDecimal(number_to_convert, base, 1, &result);
            if (st_convert == OPT_ERROR_ALLOC) {
                free(result);
                printf("Error alloc!!!\n");
                break;
            }
            ret_value += sprintf(buf + ret_value, "%s", result);
            free(result);
        } else if (!strcmp(flag, "%to\0")) {
            char *num_to_convert = va_arg(ptr, char *);
            int size = strlen(num_to_convert);
            argc++;
            int base = va_arg(ptr, int);
            long long result;

            if (!is_lower(num_to_convert, size)) {
                printf("Letters are in upper case\n");
                break;
            }

            //printf("%s -- %d\n", num_to_convert, base);
            kOpt st_convert = ToDecimal(num_to_convert, base, &result, 0);
            if (st_convert == OPT_INVALID_PARAMETER) {
                printf("Invalid parameter detected!!!\n");
                break;
            }
            ret_value += sprintf(buf + ret_value, "%lld", result);
        } else if (!strcmp(flag, "%TO\0")) {
            char *num_to_convert = va_arg(ptr, char *);
            int size = strlen(num_to_convert);
            argc++;
            int base = va_arg(ptr, int);
            long long int result;

            if (!is_upper(num_to_convert, size)) {
                printf("Letters are in lower case\n");
                break;
            }

            kOpt st_convert = ToDecimal(num_to_convert, base, &result, 1);
            if (st_convert == OPT_INVALID_PARAMETER) {
                printf("Invalid parameter detected!!!\n");
                break;
            }
            ret_value += sprintf(buf + ret_value, "%lld", result);
        } else if (!strcmp(flag, "%mi\0")) {
            int val = va_arg(ptr, int);
            unsigned char *tmp_ptr = (unsigned char *)&val;
            size_t num_bytes = sizeof(int);
            int ret_value = 0;

            for (size_t j = 0; j < num_bytes; j++) {
                for (int bit = 7; bit >= 0; bit--) {
                    ret_value += sprintf(buf + ret_value, "%u", (*tmp_ptr >> bit) & 1);
                }
                if (j < num_bytes - 1) {
                    buf[ret_value++] = ' ';
                }
                tmp_ptr++;
            }
            buf[ret_value] = '\0';
        } else if (!strcmp(flag, "%mu\0")) {
            unsigned int val = va_arg(ptr, unsigned int);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            for (int j = 0; j < sizeof(unsigned int); j++) {
                ret_value += sprintf(buf + ret_value, "%u", *tmp_ptr % 2);
                tmp_ptr++;
            }
        } else if (!strcmp(flag, "%md\0")) {
            double val = va_arg(ptr, double);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            for (int j = 0; j < sizeof(double); j++) {
                ret_value += sprintf(buf + ret_value, "%u", *tmp_ptr % 2);
                tmp_ptr++;
            }
        } else if (!strcmp(flag, "%mf\0")) {
            float val = va_arg(ptr, double);
            unsigned char *tmp_ptr = (unsigned char *) &val;
            for (int j = 0; j < sizeof(float); j++) {
                ret_value += sprintf(buf + ret_value, "%u", *tmp_ptr % 2);
                tmp_ptr++;
            }
        } else {
            ret_value += vsprintf(buf + ret_value, flag, ptr);
        }
        free(flag);
        flag = NULL;
    }

    if (flag) {
        free(flag);
    }

    va_end(ptr);
    return ret_value;
}