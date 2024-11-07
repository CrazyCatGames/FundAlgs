#ifndef INC_9_9_H
#define INC_9_9_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum kOpt {
	OPT_SUCCESS,
	OPT_ERROR_OPEN_FILE,
	OPT_ERROR_MEMORY,
	OPT_INVALID_INPUTS
} kOpt;

typedef struct TreeNode {
	char *word;
	int count;
	struct TreeNode *left, *right;
} TreeNode;

typedef struct  NodeArray {
	TreeNode **nodes;
	int size;
	int capacity;
} NodeArray;

char *combineDelimiters(int argc, char *argv[]);
kOpt processFile(const char *file_path, const char *delimiters, TreeNode **root);
TreeNode *insert(TreeNode *node, const char *word);
TreeNode *createNode(const char *word);
void inorderPrint(TreeNode *root);
TreeNode *findWord(TreeNode *root, const char *word);
TreeNode *findLongest(TreeNode *root);
TreeNode *findShortest(TreeNode *root);
TreeNode **FindTopN(TreeNode *root, long int n);
void freeTree(TreeNode *root);
int treeDepth(TreeNode *root);
int CountNodes(TreeNode *root);
void saveTree(TreeNode *root, FILE *file);
TreeNode *loadTree(FILE *file);
void printTree(TreeNode *node, int depth);

#endif
