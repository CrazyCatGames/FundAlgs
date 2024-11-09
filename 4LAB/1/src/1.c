#include "../include/1.h"

unsigned long long Hash(const char* key) {
	if (!key) return 0;
	unsigned long long  size = strlen(key);
	unsigned long long result = 0;
	int pow = 1;
	for (int i = 0; i < size; i++) {
		if (key[i] == '\0') continue;
		result += pow * ((isdigit(key[i])) ? key[i] - '0' : ('A' <= key[i] && key[i] <= 'Z') ? key[i] - 'A' + 10
																							 : key[i] - 'a' + 36);
		pow *= 62;
	}
	return result;
}

void PrintList(Cell* list) {
	if (!list) return;

	Cell* cur = list;
	while (cur != NULL) {
		printf("\tdefine: %s, value: %s\n", cur->define, cur->value);
		cur = cur->next;
	}
}


kOpt CreateTable(HashTable** new, int _size) {
	(*new) = (HashTable*) malloc(sizeof(HashTable));
	if (!(*new)) return OPT_MEMORY_ERROR;

	(*new)->size = _size;
	(*new)->cells = (Cell**) malloc(sizeof(Cell*) * _size);
	if (!(*new)->cells) {
		free(*new);
		return OPT_MEMORY_ERROR;
	}
	for (int i = 0; i < _size; i++) {
		(*new)->cells[i] = NULL;
	}
	return OPT_SUCCESS;
}

bool IsPrime(const int num) {
	if (!num || num == 1) return false;
	if (num == 2) return true;
	if (!(num & 1)) return false;
	for (int i = 3; i * i <= num; i += 2) {
		if (!(num % i)) return false;
	}
	return true;
}

int GetNextPrime(int num) {
	if (!num || num == 1) return 2;

	if (!(num & 1)) return ++num;
	do {
		num += 2;
	} while (!IsPrime(num));

	return num;
}

int SizeList(Cell* list) {
	if (!list) return 0;

	Cell* cur = list;
	int size = 0;
	while (cur != NULL) {
		size++;
		cur = cur->next;
	}

	return size;
}

kOpt CreateCell(Cell** new, const char* key, const char* value) {
	if (!key || !value) return OPT_INPUT_ERROR;

	(*new) = (Cell*) malloc(sizeof(Cell));
	if (!(*new)) return OPT_MEMORY_ERROR;

	(*new)->define = strdup(key);
	if (!(*new)->define) return OPT_MEMORY_ERROR;

	(*new)->value = strdup(value);
	if (!(*new)->value) return OPT_MEMORY_ERROR;

	(*new)->next = NULL;
	return OPT_SUCCESS;
}

kOpt AddCell(Cell** head, Cell* item) {
	Cell* tmp = (Cell*) malloc(sizeof(Cell));
	if (!tmp) return OPT_MEMORY_ERROR;

	tmp->define = strdup(item->define);
	tmp->value = strdup(item->value);
	tmp->next = NULL;

	if (!tmp->value) {
		free(tmp->value);
		free(tmp->define);
		free(tmp);
		return OPT_MEMORY_ERROR;
	}

	if (!(*head)) {
		*head = tmp;
	} else {
		Cell* cur = *head;
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = tmp;
	}
	return OPT_SUCCESS;
}

kOpt IsExist(bool* res, Cell* list, Cell* new) {
	if (!new) return OPT_INPUT_ERROR;
	if (!list) {
		*res = false;
		return OPT_SUCCESS;
	}
	Cell* cur = list;
	char* cur_key = cur->define;
	char* cur_value = cur->value;

	while (cur != NULL) {
		cur_key = cur->define;
		if (!strcmp(cur_key, new->define)) {
			free(cur->value);
			cur->value = NULL;
			cur->value = strdup(new->value);
			if (!cur->value) return OPT_MEMORY_ERROR;

			*res = true;
			return OPT_SUCCESS;
		}
		cur = cur->next;
	}
	*res = false;
	return OPT_SUCCESS;
}


void FreeCell(Cell* del) {
	if (!del) return;

	while (del) {
		Cell* to_del = del;
		del = del->next;
		free(to_del->value);
		free(to_del->define);
		free(to_del);
	}
}

bool CheckTableRebuild(HashTable* table) {
	int min = -1;
	int max = -1;
	int tmp_size = 0;
	for (int i = 0; i < table->size; i++) {
		if (table->cells[i] != NULL) {
			tmp_size = SizeList(table->cells[i]);
			if (tmp_size > max) {
				max = tmp_size;
			}
			if (tmp_size < min || min == -1) {
				min = tmp_size;
			}
		}
	}
	if (min == 0) return false;

	if (max / min >= 2) return true;

	return false;
}


kOpt InsertTable(HashTable** table, char* key, char* value) {
	Cell* to_add = NULL;
	kOpt status = CreateCell(&to_add, key, value);
	if (status != OPT_SUCCESS) {
		free(to_add);
		return status;
	}

	unsigned long long index = Hash(key) % (*table)->size;
	bool exist;
	status = IsExist(&exist, (*table)->cells[index], to_add);
	if (status != OPT_SUCCESS) {
		FreeCell(to_add);
		return status;
	}

	to_add->key = index;
	if (!exist) {
		status = AddCell(&(*table)->cells[index], to_add);
		if (status != OPT_SUCCESS) {
			FreeCell(to_add);
			return status;
		}

		free(key);
		free(value);
		FreeCell(to_add);
		if (CheckTableRebuild(*table)) {
			status = ResizeTable(table);
			if (status != OPT_SUCCESS) {
				return status;
			}
		}
	}
	return OPT_SUCCESS;
}

void FreeTable(HashTable* table) {
	if (!table) return;

	for (int i = 0; i < table->size; i++) {
		FreeCell(table->cells[i]);
	}
	free(table->cells);
	free(table);
}

void PrintTable(HashTable* table) {
	for (int i = 0; i < table->size; i++) {
		Cell* cur = table->cells[i];
		if (table->cells[i]) {
			printf("Hash: %d\n", i);
			printf("%d--\n", SizeList(table->cells[i]));
			PrintList(table->cells[i]);
		}
	}
}

kOpt ResizeTable(HashTable** old) {
	HashTable* new = NULL;
	int new_size = GetNextPrime((*old)->size);
	kOpt status = CreateTable(&new, new_size);
	if (status != OPT_SUCCESS) return status;

	for (int i = 0; i < (*old)->size; i++) {
		while ((*old)->cells[i]) {
			Cell* cur = (*old)->cells[i];
			(*old)->cells[i] = cur->next;
			status = InsertTable(&new, cur->define, cur->value);
			if (status != OPT_SUCCESS) FreeTable(new);
			free(cur);
		}
	}
	FreeTable(*old);
	*old = new;
	return OPT_SUCCESS;
}

char* FindFromList(Cell* list, const char* key) {
	if (!list || !key) return NULL;

	Cell* cur = list;
	while (cur != NULL) {
		if (!strcmp(cur->define, key)) {
			return cur->value;
		}
		cur = cur->next;
	}
	return NULL;
}

char* FindElement(HashTable* table, const char* key) {
	if (!key || !table) return NULL;

	int index = Hash(key) % table->size;
	return FindFromList(table->cells[index], key);
}