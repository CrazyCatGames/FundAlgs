#include "../include/9.h"

char* combineDelimiters(int argc, char *argv[]) {
	size_t total_length = 0;
	for (int i = 2; i < argc; i++) {
		total_length += strlen(argv[i]);
	}

	char *delimiters = malloc(total_length + 1);
	delimiters[0] = '\0'; // Начинаем с пустой строки

	for (int i = 2; i < argc; i++) {
		strcat(delimiters, argv[i]);
	}

	return delimiters;
}


int processFile(const char *file_path, const char *delimiters, TreeNode **root) {
	FILE *file = fopen(file_path, "r");
	if (!file) {
		return -2;
	}

	int c;
	char *word = NULL;
	size_t length = 0, capacity = 0;

	while ((c = fgetc(file)) != EOF) {
		if (strchr(delimiters, c)) {
			if (length > 0) {
				word[length] = '\0';
				*root = insert(*root, word);
				if (!*root){
					if (word) free(word);
					return -2;
				}
				length = 0;
			}
		} else {
			if (length + 1 >= capacity) {
				capacity = capacity == 0 ? 16 : capacity * 2;
				char *tmp = realloc(word, capacity);
				if (!tmp){
					free(word);
					return -1;
				}
				word = tmp;
			}
			word[length++] = (char)c;
		}
	}

	if (length > 0) {
		word[length] = '\0';
		*root = insert(*root, word);
		if (!*root){
			free(word);
			return -2;
		}
	}

	free(word);
	fclose(file);
	return 0;
}

TreeNode* insert(TreeNode *node, const char *word) {
	if (node == NULL) return createNode(word);
	int cmp = strcmp(word, node->word);
	if (cmp == 0) {
		node->count++;
	} else if (cmp < 0) {
		node->left = insert(node->left, word);
	} else {
		node->right = insert(node->right, word);
	}
	return node;
}

TreeNode* createNode(const char *word) {
	TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
	if (!node){
		return NULL;
	}
	node->word = strdup(word);
	node->count = 1;
	node->left = node->right = NULL;
	return node;
}

void inorderPrint(TreeNode *root) {
	if (root) {
		inorderPrint(root->left);
		printf("%s: %d\n", root->word, root->count);
		inorderPrint(root->right);
	}
}

TreeNode* findWord(TreeNode *root, const char *word) {
	if (root == NULL || strcmp(root->word, word) == 0) return root;
	if (strcmp(word, root->word) < 0) return findWord(root->left, word);
	return findWord(root->right, word);
}

TreeNode* findLongest(TreeNode *root) {
	if (root == NULL) return NULL;
	TreeNode *longest = root, *left = findLongest(root->left), *right = findLongest(root->right);
	if (left && strlen(left->word) > strlen(longest->word)) longest = left;
	if (right && strlen(right->word) > strlen(longest->word)) longest = right;
	return longest;
}

TreeNode* findShortest(TreeNode *root) {
	if (root == NULL) return NULL;
	TreeNode *shortest = root, *left = findShortest(root->left), *right = findShortest(root->right);
	if (left && strlen(left->word) < strlen(shortest->word)) shortest = left;
	if (right && strlen(right->word) < strlen(shortest->word)) shortest = right;
	return shortest;
}

void printTopN(TreeNode *root, int *n) {
	if (root == NULL || *n <= 0) return;
	printTopN(root->right, n);
	if (*n > 0) {
		printf("%s: %d\n", root->word, root->count);
		(*n)--;
	}
	printTopN(root->left, n);
}

int treeDepth(TreeNode *root) {
	if (root == NULL) return 0;
	int left_depth = treeDepth(root->left);
	int right_depth = treeDepth(root->right);
	return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

void freeTree(TreeNode *root) {
	if (root) {
		freeTree(root->left);
		freeTree(root->right);
		free(root->word);
		free(root);
	}
}

void saveTree(TreeNode *root, FILE *file) {
	if (root == NULL) {
		fprintf(file, "(null)\n");
		return;
	}
	fprintf(file, "%s %d\n", root->word, root->count);
	saveTree(root->left, file);
	saveTree(root->right, file);
}

TreeNode* loadTree(FILE *file) {
	char buffer[1024];
	if (fscanf(file, "%1023s", buffer) != 1 || strcmp(buffer, "(null)") == 0) return NULL;

	int count;
	fscanf(file, "%d", &count);
	TreeNode *node = createNode(buffer);
	if (!node){
		return NULL;
	}
	node->count = count;
	node->left = loadTree(file);
	node->right = loadTree(file);
	return node;
}

void printTree(TreeNode *node, int depth) {
	if (node == NULL) {
		return;
	}

	printTree(node->right, depth + 1);
	for (int i = 0; i < depth; i++) {
		printf("    ");
	}
	printf("%s (%d)\n", node->word, node->count);
	printTree(node->left, depth + 1);
}