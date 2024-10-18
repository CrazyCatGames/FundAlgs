#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 2048

typedef enum kOpts { OPT_D, OPT_S, OPT_I, OPT_A} kOpts;

// Remove numbers.
void FlagD(FILE* input, FILE* output) {
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isdigit(buffer[i])) {
				fputc(buffer[i], output);
			}
		}
	}
}

// Count of letters.
void FlagI(FILE* input, FILE* output) {
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
		int count = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (isalpha(buffer[i])) {
				count++;
			}
		}
		fprintf(output, "%d\n", count);
	}
}

// Count of non letters and numbers.
void FlagS(FILE* input, FILE* output) {
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
		int count = 0;
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (!isalnum(buffer[i]) && !isspace(buffer[i])) {
				count++;
			}
		}
		fprintf(output, "%d\n", count);
	}
}

// Letters to ASCII
void FlagA(FILE* input, FILE* output) {
	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
		for (int i = 0; buffer[i] != '\0'; i++) {
			if (isdigit(buffer[i])) {
				fputc(buffer[i], output);
			} else {
				fprintf(output, "%x", buffer[i]);
			}
		}
	}
}

char* GenerateOutputFilename(const char* kinput_filename) {
	size_t len = strlen(kinput_filename);
	char* output_filename = (char*)malloc(len + 5); // "out_" + '\0'
	if (output_filename == NULL) {
		fprintf(stderr, "Memory allocation error");
		free(output_filename);
        return NULL;
	}
	strcpy(output_filename, "out_");
	strcat(output_filename, kinput_filename);
	return output_filename;
}

int CheckFlag(const char* kflag, const char* valid_flag) {
    if (kflag[0] == '-' || kflag[0] == '/') {
        for (int i = 1; kflag[i] != '\0'; i++) {
            if (kflag[i] == valid_flag[0] && valid_flag[1] == '\0') {
                return 1;
            }
        }
    }
    return 0;
}

int GetOpts(int argc, char** argv, kOpts* option, int* n_flag) {
	if (argc < 3) {
		fprintf(stderr, "Usage: %s [flag] [input_file] [output_file (optional)]\n", argv[0]);
		return 1;
	}

	*n_flag = (argv[1][1] == 'n');

	char* flags[4] = {"d", "i", "s", "a"};

	for (int i = 0; i < 4; i++) {
		if (CheckFlag(argv[1], flags[i])) {
			*option = i;
			return 0;
		}
	}

	return 3;
}

int main(int argc, char* argv[]) {
	kOpts opt = 0;
	const char *kflag = argv[1];
	const char *kinput_filename = argv[2];
	char *output_filename = NULL;
	FILE *input_file, *output_file;
	int n_flag;

	void (*func[4])(FILE*, FILE*) = {FlagD, FlagI, FlagS, FlagA};
	int result = GetOpts(argc, argv, &opt, &n_flag);
	
	if (n_flag) {
		if (argc < 4) {
			fprintf(stderr, "Output file required when using '-n' flag\n");
			return 1;
		}
        if (strlen(kflag) > 3){
            fprintf(stderr, "Unknown flag %s.\n", kflag);
			return 1;
        }
		output_filename = argv[3];
	} else {
		output_filename = GenerateOutputFilename(kinput_filename);
        if (output_filename == NULL){
            free(output_filename);
            return 1;
        }
	}

	input_file = fopen(kinput_filename, "r");
	if (input_file == NULL) {
		fprintf(stderr, "Failed to open input file.\n");
		fclose(input_file);
		return 1;
	}

	output_file = fopen(output_filename, "w");
	if (output_file == NULL) {
		fprintf(stderr, "Failed to open output file.\n");
		free(output_filename);
		fclose(input_file);
		return 1;
	}

    switch (result)
    {   
        case 0:
            break;
        case 1:
            printf("Incorrect number of arguments.\n");
		    return 1;
        case 2:
            printf("Error: %s isn't a natural number.\n", argv[2]);
		    return 1;
        case 3:
            printf("Unknown flag: %s\n", argv[1]);
		    return 1;
        default:
            printf("Unknown error.\n");
            return 1;
    }

	func[opt](input_file, output_file);
	fclose(input_file);
	fclose(output_file);

	if (!n_flag) {
		free(output_filename);
	}

	return 0;
}
