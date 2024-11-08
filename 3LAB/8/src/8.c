#include "../include/8.h"

kOpt InitPolynom(Polynom *polynom) {
	if (!polynom) return OPT_MEMORY_ERROR;

	polynom->head = NULL;
	polynom->size = 0;
	return OPT_SUCCESS;
}

kOpt DestroyPolynom(Polynom *polynom) {
	Term *cur, *next;
	if (!polynom) return OPT_ZERO_ARGS;

	cur = polynom->head;
	while (cur) {
		next = cur->next;
		free(cur);
		cur = next;
	}

	polynom->head = NULL;
	polynom->size = 0;
	return OPT_SUCCESS;
}

kOpt InsertTerm(Polynom *polynom, int degree, int coef) {
	if (!coef) return OPT_SUCCESS;

	Term *temp;
	if (!polynom) return OPT_ZERO_ARGS;

	if (polynom->size == 0) {
		polynom->head = (Term *) malloc(sizeof(Term));
		if (!polynom->head) return OPT_MEMORY_ERROR;

		polynom->size++;
		polynom->head->coef = coef;
		polynom->head->degree = degree;
		polynom->head->next = NULL;
		return OPT_SUCCESS;
	}
	if (polynom->head->degree < degree) {
		temp = (Term *) malloc(sizeof(Term));
		if (!temp) return OPT_MEMORY_ERROR;

		temp->coef = coef;
		temp->degree = degree;
		temp->next = polynom->head;
		polynom->head = temp;
		polynom->size++;
		return OPT_SUCCESS;
	}
	if (polynom->head->degree == degree) {
		if (coef > 0 && INT_MAX - coef < polynom->head->coef) {
			return OPT_OVERFLOW_ERROR;
		} else if (coef < 0 && INT_MIN - coef > polynom->head->coef) {
			return OPT_OVERFLOW_ERROR;
		}

		polynom->head->coef += coef;
		if (polynom->head->coef == 0) {
			temp = polynom->head;
			polynom->head = temp->next;
			free(temp);
			polynom->size--;
		}
		return OPT_SUCCESS;
	}
	temp = polynom->head;
	while (temp != NULL) {
		if (temp->next == NULL || temp->next->degree < degree) {
			Term *new = (Term *) malloc(sizeof(Term));
			if (!new) return OPT_MEMORY_ERROR;

			new->coef = coef;
			new->degree = degree;
			new->next = temp->next;
			temp->next = new;
			polynom->size++;
			return OPT_SUCCESS;
		}
		if (temp->next->degree == degree) {
			if (coef > 0 && INT_MAX - coef < temp->next->coef) {
				return OPT_MEMORY_ERROR;
			} else if (coef < 0 && INT_MIN - coef > temp->next->coef) {
				return OPT_MEMORY_ERROR;
			}

			temp->next->coef += coef;
			if (temp->next->coef == 0) {
				Term *to_delete = temp->next;
				temp->next = to_delete->next;
				free(to_delete);
				polynom->size--;
			}
			return OPT_SUCCESS;
		}
		temp = temp->next;
	}
	return OPT_SUCCESS;
}

kOpt CreatePolynom(Polynom *polynom, const char *expression) {
	int coef, sign = 1, degree;
	const char *symbol = expression;
	if (!polynom || !expression) return OPT_ZERO_ARGS;

	InitPolynom(polynom);
	while (*symbol != '\0') {
		if (*symbol == '-' || *symbol == '+') {
			sign = (*symbol == '+') ? 1 : -1;
			coef = 0;
			symbol++;
			if (!isdigit(*symbol) && *symbol != 'x') return OPT_INPUT_ERROR;

			if (*symbol == 'x') {
				coef = 1;
				continue;
			}
			while (*symbol != 0 && isdigit(*symbol)) {
				if (INT_MAX / 10 < coef) return OPT_MEMORY_ERROR;

				coef *= 10;
				if (INT_MAX - (*symbol - '0') < coef) return OPT_MEMORY_ERROR;

				coef += *symbol - '0';
				symbol++;
			}

			if (*symbol != 'x') {
				if (InsertTerm(polynom, 0, coef * sign) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
				coef = 0;
			}
		} else if (*symbol == 'x') {
			if (symbol == expression) coef = 1;
			degree = 0;
			symbol++;
			if (*symbol != '\0') {
				if (*symbol == '^') {
					if (!isdigit(*(++symbol))) return OPT_INPUT_ERROR;

					while (*symbol != 0 && isdigit(*symbol)) {
						if (INT_MAX / 10 < degree) return OPT_MEMORY_ERROR;

						degree *= 10;
						if (INT_MAX - (*symbol - '0') < degree) return OPT_MEMORY_ERROR;

						degree += *symbol - '0';
						symbol++;
					}
					if (*symbol == 'x') return OPT_INPUT_ERROR;
				} else {
					degree = 1;
				}
			} else {
				degree = 1;
			}
			if (InsertTerm(polynom, degree, coef * sign) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
		} else if (isdigit(*symbol)) {
			coef = 0;
			sign = 1;
			while (*symbol != 0 && isdigit(*symbol)) {
				if (INT_MAX / 10 < coef) return OPT_MEMORY_ERROR;
				coef *= 10;
				if (INT_MAX - (*symbol - '0') < coef) return OPT_MEMORY_ERROR;
				coef += *symbol - '0';
				symbol++;
			}
			if (*symbol != 'x') {
				if (InsertTerm(polynom, 0, coef) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
			}
		} else {
			return OPT_INPUT_ERROR;
		}
	}
	return OPT_SUCCESS;
}

kOpt Add(Polynom *polynom_1, Polynom *polynom_2) {
	Term *temp;
	if (!polynom_1 || !polynom_2) return OPT_ZERO_ARGS;

	temp = polynom_2->head;
	while (temp) {
		if (InsertTerm(polynom_1, temp->degree, temp->coef) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
		temp = temp->next;
	}
	return OPT_SUCCESS;
}

kOpt Sub(Polynom *polynom_1, Polynom *polynom_2) {
	Term *temp;
	if (!polynom_1 || !polynom_2) return OPT_ZERO_ARGS;

	temp = polynom_2->head;
	while (temp) {
		if (InsertTerm(polynom_1, temp->degree, -temp->coef) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
		temp = temp->next;
	}
	return OPT_SUCCESS;
}

kOpt Multiply(Polynom *polynom_1, Polynom *polynom_2, Polynom *res) {
	Term *temp_1, *temp_2;
	if (!polynom_1 || !polynom_2 || !res) return OPT_MEMORY_ERROR;

	InitPolynom(res);
	temp_1 = polynom_1->head;
	while (temp_1) {
		temp_2 = polynom_2->head;
		while (temp_2) {
			int check_overflov = temp_1->coef * temp_2->coef;
			if (INT_MAX - temp_1->degree < temp_2->degree || (temp_1->coef && check_overflov / temp_1->coef != temp_2->coef)) return OPT_OVERFLOW_ERROR;
			if (InsertTerm(res, temp_1->degree + temp_2->degree, temp_1->coef * temp_2->coef) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;
			temp_2 = temp_2->next;
		}
		temp_1 = temp_1->next;
	}
	return OPT_SUCCESS;
}

kOpt Eval(Polynom *polynom, double x, double *result) {
	Term *temp;
	int i, last_degree = 0;
	if (!polynom || !result) return OPT_ZERO_ARGS;

	temp = polynom->head;
	*result = 0;
	if (x == 0) {
		if (!temp) return OPT_SUCCESS;
		while (temp->next) {
			temp = temp->next;
		}

		if (temp->degree == 0) *result = temp->coef;

		return OPT_SUCCESS;
	}
	while (temp) {
		for (i = 0; i < last_degree - temp->degree; ++i) {
			*result *= x;

			if (*result == INFINITY || *result == -INFINITY) {
				*result = (x < 0 && ((last_degree - temp->degree) & 2)) ? (-INFINITY) : (INFINITY);
				return OPT_SUCCESS;
			}
		}
		*result += temp->coef;
		last_degree = temp->degree;
		temp = temp->next;
	}

	for (i = 0; i < last_degree; ++i) {
		*result *= x;
	}
	return OPT_SUCCESS;
}

kOpt Diff(Polynom *polynom, Polynom *res) {
	Term *temp, *temp_res;
	if (!polynom || !res) return OPT_ZERO_ARGS;

	InitPolynom(res);
	temp = polynom->head;
	while (temp && temp->degree > 0) {
		if (res->size == 0) {
			res->head = (Term *) malloc(sizeof(Term));

			if (!res->head) return OPT_MEMORY_ERROR;

			res->head->next = NULL;
			res->head->coef = temp->coef * temp->degree;
			res->head->degree = temp->degree - 1;
			temp_res = res->head;
			res->size++;
		} else {
			temp_res->next = (Term *) malloc(sizeof(Term));

			if (!temp_res->next) return OPT_MEMORY_ERROR;

			temp_res = temp_res->next;
			temp_res->next = NULL;
			temp_res->coef = temp->coef * temp->degree;
			temp_res->degree = temp->degree - 1;
			res->size++;
		}

		temp = temp->next;
	}
	return OPT_SUCCESS;
}

kOpt Cmps(Polynom *polynom_1, Polynom *polynom_2, Polynom *result) {
	Term *temp;
	Polynom res;
	int i, last_degree = 0;
	if (!polynom_1 || !polynom_2 || !result) return OPT_ZERO_ARGS;

	InitPolynom(result);
	temp = polynom_1->head;
	while (temp) {
		for (i = 0; i < last_degree - temp->degree; ++i) {
			Multiply(result, polynom_2, &res);
			DestroyPolynom(result);
			*result = res;
			InitPolynom(&res);
		}
		InsertTerm(result, 0, temp->coef);
		last_degree = temp->degree;
		temp = temp->next;
	}
	for (i = 0; i < last_degree; ++i) {
		Multiply(result, polynom_2, &res);
		DestroyPolynom(result);
		*result = res;
		InitPolynom(&res);
	}
	return OPT_SUCCESS;
}

kOpt MultHelper(Polynom *polynom_1, int degree, int coef, Polynom *res) {
	Term *temp_1;
	if (!polynom_1 || !res) return OPT_ZERO_ARGS;

	InitPolynom(res);
	temp_1 = polynom_1->head;
	while (temp_1) {
		int check_overflov = temp_1->coef * coef;

		if (INT_MAX - temp_1->degree < degree || (temp_1->coef && check_overflov / temp_1->coef != coef)) return OPT_OVERFLOW_ERROR;

		if (InsertTerm(res, temp_1->degree + degree, temp_1->coef * coef) == OPT_MEMORY_ERROR) return OPT_MEMORY_ERROR;

		temp_1 = temp_1->next;
	}
	return OPT_SUCCESS;
}

kOpt Mod(Polynom *dividend, Polynom *divider, Polynom *res) {
	if (!dividend || !divider || !res || !divider->size) return OPT_ZERO_ARGS;

	InitPolynom(res);
	while (dividend->size && (dividend->head->degree >= divider->head->degree)) {
		Polynom new_polynom;
		int coef = dividend->head->coef / divider->head->coef;
		int degree = dividend->head->degree - divider->head->degree;

		if (dividend->head->coef % divider->head->coef) return OPT_INPUT_ERROR;

		if (InsertTerm(res, degree, coef) != OPT_SUCCESS) return OPT_MEMORY_ERROR;

		InitPolynom(&new_polynom);

		if (MultHelper(divider, degree, coef, &new_polynom) != OPT_SUCCESS) {
			DestroyPolynom(&new_polynom);
			return OPT_MEMORY_ERROR;
		}

		Sub(dividend, &new_polynom);
		DestroyPolynom(&new_polynom);
	}
	return OPT_SUCCESS;
}

kOpt GetExpression(Polynom *polynom_1, Polynom *polynom_2, FILE *input, int *count) {
	char ch, created = 0;
	String expr;
	kOpt status;

	if (!polynom_1 || !polynom_2 || !input || !count) return OPT_ZERO_ARGS;

	*count = 0;
	ch = getc(input);

	if (ch != '(') return OPT_INPUT_ERROR;

	if (InitString(&expr)) return OPT_MEMORY_ERROR;

	while (!feof(input)) {
		ch = getc(input);
		if (ch == ',') {
			if (expr.len == 0 || created) {
				DeleteString(&expr);
				return OPT_INPUT_ERROR;
			}

			if ((status = CreatePolynom(polynom_1, expr.arr)) == OPT_MEMORY_ERROR) {
				DeleteString(&expr);
				return OPT_MEMORY_ERROR;
			}

			DeleteString(&expr);

			if (status == OPT_INPUT_ERROR) return OPT_INPUT_ERROR;

			created = 1;
			*count = 1;
		} else if (isdigit(ch) || ch == '+' || ch == '-' || ch == '^' || ch == 'x') {
			if (AddCharToString(&expr, ch)) {
				DeleteString(&expr);
				return OPT_MEMORY_ERROR;
			}
		} else if (ch == ')') {
			if (expr.len == 0 && *count == 0) {
				DeleteString(&expr);
				return OPT_ZERO_ARGS;
			}
			if (expr.len == 0) {
				DeleteString(&expr);
				return OPT_INPUT_ERROR;
			}

			status = CreatePolynom((created ? polynom_2 : polynom_1), expr.arr);
			DeleteString(&expr);

			if (status != OPT_SUCCESS) return status;

			*count += 1;
			break;
		} else {
			DeleteString(&expr);
			return OPT_INPUT_ERROR;
		}
	}

	DeleteString(&expr);
	return OPT_SUCCESS;
}

kOpt PrintPolynom(Polynom *polynom) {
	Term *temp;
	if (!polynom) return OPT_ZERO_ARGS;

	if (!polynom->size) printf("0");

	temp = polynom->head;
	while (temp) {
		if (temp != polynom->head) {
			if (temp->coef > 0) printf(" + ");
			else
				printf(" - ");
		} else if (temp->coef < 0) {
			printf("-");
		}
		if (!temp->degree) {
			printf("%d", abs(temp->coef));
		} else {
			if (abs(temp->coef) != 1) printf("%d", abs(temp->coef));
			printf("x");
			if (temp->degree > 1) printf("^%d", temp->degree);
		}
		temp = temp->next;
	}

	putchar('\n');
	return OPT_SUCCESS;
}

kOpt InitString(String *string) {
	if (!string) return OPT_ZERO_ARGS;
	string->capacity = 1;
	string->len = 0;

	if (!(string->arr = (char *) malloc(sizeof(char)))) return OPT_MEMORY_ERROR;

	string->arr[0] = '\0';
	return OPT_SUCCESS;
}

kOpt DeleteString(String *string) {
	if (!string) return OPT_ZERO_ARGS;

	free(string->arr);
	string->arr = NULL;
	string->len = 0;
	string->capacity = 0;
	return OPT_SUCCESS;
}

kOpt AddCharToString(String *str, char ch) {
	if (!str) return OPT_ZERO_ARGS;
	if (str->capacity == 0) {
		if (InitString(str)) return OPT_MEMORY_ERROR;
	}
	if (str->capacity == str->len + 1) {
		char *for_realloc;
		str->capacity *= 2;
		for_realloc = (char *) realloc(str->arr, str->capacity * sizeof(char));
		if (!for_realloc) {
			DeleteString(str);
			return OPT_MEMORY_ERROR;
		}
		str->arr = for_realloc;
	}
	str->arr[str->len++] = ch;
	str->arr[str->len] = '\0';
	return OPT_SUCCESS;
}
