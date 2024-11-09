#ifndef INC_1_1_H
#define INC_1_1_H

#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 128

typedef enum kOpt {
	OPT_SUCCESS,
	OPT_INPUT_ERROR,
	OPT_MEMORY_ERROR,
	OPT_HASH_SIZE,
	OPT_FILE_OPEN_ERROR,
	OPT_FAIL
} kOpt;

typedef struct Cell {
	char* define;
	char* value;
	unsigned long long key;
	struct Cell* next;
} Cell;

typedef struct HashTable {
	Cell** cells;
	int size;
} HashTable;

unsigned long long Hash(const char* key);
kOpt CreateTable(HashTable** _new, int _size);
bool IsPrime(int number);
int GetNextPrime(int number);
kOpt CreateCell(Cell** _new, const char* key, const char* value);
kOpt AddCell(Cell** head, Cell* item);
kOpt IsExist(bool* res, Cell* list, Cell* _new);
void FreeCell(Cell* del);
bool CheckTableRebuild(HashTable* table);
kOpt InsertTable(HashTable** table, char* key, char* value);
void FreeTable(HashTable* table);
kOpt ResizeTable(HashTable** old);
char* FindFromList(Cell* list, const char* key);
char* FindElement(HashTable* table, const char* key);
void PrintTable(HashTable* table);

#endif