#ifndef INC_9_9_H
#define INC_9_9_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode {
	char *word;
	int count;
	struct TreeNode *left, *right;
} TreeNode;

void processFile(const char *file_path, const char *delimiters, TreeNode **root);
TreeNode* insert(TreeNode *node, const char *word);
TreeNode* createNode(const char *word);
void inorderPrint(TreeNode *root);
TreeNode* findWord(TreeNode *root, const char *word);
TreeNode* findLongest(TreeNode *root);
TreeNode* findShortest(TreeNode *root);
void printTopN(TreeNode *root, int *n);
void freeTree(TreeNode *root);
int treeDepth(TreeNode *root);
void saveTree(TreeNode *root, FILE *file);
TreeNode* loadTree(FILE *file);
void printTree(TreeNode *node, int depth);

#endif
