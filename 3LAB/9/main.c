#include <stdio.h>
#include "include/9.h"

int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("Usage: %s <file_path> <delimiters>\n", argv[0]);
		return 1;
	}

	char *delimiters = combineDelimiters(argc, argv);

	TreeNode *root = NULL;
	int tmp = processFile(argv[1], delimiters, &root);
	if (tmp == -1){
		fprintf(stderr, "Error alloc memory.\n");
		free(delimiters);
		return 2;
	} else if (tmp == -2){
		fprintf(stderr, "Error open file\n");
		free(delimiters);
		return 3;
	}

	char *choice = NULL;
	size_t choice_len = 0;
	do {
		printf("1. Print word frequencies\n");
		printf("2. Find word count\n");
		printf("3. Print top N frequent words\n");
		printf("4. Find longest and shortest words\n");
		printf("5. Calculate tree depth\n");
		printf("6. Save tree to file\n");
		printf("7. Load tree from file\n");
		printf("8. Print tree\n");
		printf("9. Exit\n\n");
		printf("Enter your choice: ");

		if (getline(&choice, &choice_len, stdin) == -1) {
			printf("Error reading input.\n");
			continue;
		}

		choice[strcspn(choice, "\n")] = 0;

		if (strlen(choice) > 1) {
			printf("Incorrect input.\n\n");
			continue;
		}

		switch (choice[0]) {
			case '1':
				inorderPrint(root);
				break;
			case '2':
				printf("Enter word: ");
				char *word = NULL;
				size_t len = 0;
				getline(&word, &len, stdin);
				word[strcspn(word, "\n")] = 0;
				TreeNode *found = findWord(root, word);
				printf("%s: %d\n", word, found ? found->count : 0);
				free(word);
				break;
			case '3':
				printf("Enter N: ");
				char *input = NULL;
				size_t leni = 0;

				if (getline(&input, &leni, stdin) != -1) {
					input[strcspn(input, "\n")] = 0;
					char *endptr;
					long n = strtol(input, &endptr, 10);
					if (*endptr == '\0' && n > 0) {
						printTopN(root, (int*)&n);
					} else {
						printf("Invalid input for N.\n");
					}
				} else {
					printf("Error reading input.\n");
				}

				free(input);
				break;
			case '4':
				printf("Longest word: %s\n", findLongest(root)->word);
				printf("Shortest word: %s\n", findShortest(root)->word);
				break;
			case '5':
				printf("Tree depth: %d\n", treeDepth(root));
				break;
			case '6': {
				FILE *file = fopen("tree.txt", "w");
				if (!file) {
					fprintf(stderr, "Error open file\n");
					break;
				}
				saveTree(root, file);
				fclose(file);
				printf("Tree saved to tree.txt\n");
				break;
			}
			case '7': {
				FILE *file = fopen("tree.txt", "r");
				if (!file) {
					fprintf(stderr, "Error open file\n");
					free(delimiters);
					free(choice);
					freeTree(root);
					return 3;
				}
				root = loadTree(file);
				if (!root){
					fprintf(stderr,"Error alloc memory\n");
					free(delimiters);
					free(choice);
					freeTree(root);
					fclose(file);
					return 2;
				}
				fclose(file);
				printf("Tree loaded from tree.txt\n");
				break;
			}
			case '8':
				printTree(root, 0);
				break;
			case '9':
				break;
			default:
				printf("Incorrect input\n");
				break;
		}
		printf("\n");
	} while (strcmp(choice, "9") != 0);

	free(delimiters);
	free(choice);
	freeTree(root);
	return 0;
}