#ifndef LAB1_H
#define LAB1_H

typedef enum kOpts { OPT_L, OPT_R, OPT_U, OPT_N, OPT_C, OPT_SUCCESS, OPT_ERROR_MEMORY } kOpts;

kOpts FlagL(const char *input, char **output);
kOpts FlagR(const char *input, char **output);
kOpts FlagU(const char *input, char **output);
kOpts FlagN(const char *input, char **output);
kOpts FlagC(char **output, int number, int argc, char** argv);
char *MyStrcat(char *dest, const char *src);
char *MyStrCpy(char *dest, const char *src);
int MyStrCmp(const char *s1, const char *s2);
int MyStrtoi(const char *str, char **end);
int CheckFlag(const char *kflag, char *valid_flag);
int GetOpts(int argc, char **argv, kOpts *option, int *number);

#endif