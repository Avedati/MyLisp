#include "../include/striter.h"
#include "../include/stack.h"
#include "../include/symtable.h"
#include "../include/lisp.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lisp__set__(struct lisp*);
void lisp__print__(struct lisp*);
void lisp__read__(struct lisp*);
void lisp__add__(struct lisp*);
void lisp__sub__(struct lisp*);
void lisp__mul__(struct lisp*);
void lisp__div__(struct lisp*);
void lisp__cons__(struct lisp*);
void lisp__car__(struct lisp*);
void lisp__cdr__(struct lisp*);

/*
 char* get_next_token(struct str_it* itr)
 
 This function will return the next token (a string, a number, an operator, etc.)
 
 @param itr A pointer to a str_it struct.
 @return The next token.
*/
char* get_next_token(struct str_it* itr) {
	if(str_it_c(itr) == -1) { return NULL; }
	while(isspace(str_it_c(itr))) { itr->it++; }
	if(str_it_c(itr) == -1) { return NULL; }
	else if(str_it_c(itr) == '(' || str_it_c(itr) == ')') {
		char* st = malloc(sizeof(char) * 2);
		st[0] = itr->str[(itr->it)++];
		st[1] = 0;
		return st;
	}
	else if(str_it_c(itr) == '\'' || str_it_c(itr) == '"') {
		char* st = malloc(sizeof(char));
		char end = st[0] = itr->str[(itr->it)++];
		int num_chars = 1;
		while(str_it_c(itr) != -1) {
			if(str_it_c(itr) == '\\') {
				st = realloc(st, sizeof(char) * (num_chars + 1));
				st[num_chars++] = itr->str[(itr->it)++];
			}
			st = realloc(st, sizeof(char) * (num_chars + 1));
			st[num_chars++] = itr->str[(itr->it)++];
			if(str_it_c(itr) == end) { break; }
		}
		(itr->it)++;
		st = realloc(st, sizeof(char) * (num_chars + 1));
		st[num_chars] = 0;
		return st;
	}
	char* st = malloc(sizeof(char));
	st[0] = itr->str[(itr->it)++];
	int num_chars = 1;
	while(str_it_c(itr) != -1 && !isspace(str_it_c(itr))) {
		st = realloc(st, sizeof(char) * (num_chars + 1));
		st[num_chars++] = itr->str[(itr->it)++];
	}
	st = realloc(st, sizeof(char) * (num_chars + 1));
	st[num_chars] = 0;
	return st;
}

/*
  char* expect_token(struct str_it* itr, char* value)
  
  This function will check if the next available token
  is equal to the provided value. If so, it will return
  the token. If not, it will print an error and exit
  the program with an error code of 1.
  
  @param itr A pointer to a str_it struct.
  @param value The expected token string.
  @return The next token, if it matches the expected token string.
*/
char* expect_token(struct str_it* itr, char* value) {
	char* tok = get_next_token(itr);
	if(tok == NULL || strcmp(tok, value) != 0) {
		fprintf(stderr, "Error: expected `%s`, got `%s`", value, tok);
		exit(1);
	}
	return tok;
}

/*
  int isint(char* tok)
  
  This function returns 1 if every character in
  the tok string is from 0-9. Otherwise, this
  function returns 0.
  
  @param tok The token to check.
  @return 1 if the token is an integer, 0 otherwise.
*/
int isint(char* tok) {
	for(int i=0;i<strlen(tok);i++) {
		if(!isdigit(tok[i])) { return 0; }
	}
	return 1;
}

/*
  int isint(char* tok)
  
  This function returns 1 if every character in
  the tok string is from 0-9 or is a '.' or
  an 'e' or an 'E'. Otherwise, this function
  returns 0.
  
  @param tok The token to check.
  @return 1 if the token is an float, 0 otherwise.
*/
int isflt(char* tok) {
	for(int i=0;i<strlen(tok);i++) {
		if(!isdigit(tok[i]) && tok[i] != '.' && tok[i] != 'e' && tok[i] != 'E') { return 0; }
	}
	return 1;
}

/*
  int isstr(char* tok)
  
  This function returns 1 if the first
  character of the tok string is a ' or
  a ". Otherwise, it returns 0.
  
  @param tok The token to check.
  @return 1 if the token is a string, 0 otherwise.
*/
int isstr(char* tok) {
	return tok[0] == '\'' || tok[0] == '"';
}

/*
  int pint(char* tok)
  
  This function converts the string to a int.
  
  @param tok The token to convert to an int.
  @return A pointer to the converted int.
*/
int* pint(char* tok) {
	int val = atoi(tok);
	int* ptr = malloc(sizeof(int*));
	*ptr = val;
	return ptr;
}

/*
  float* pflt(char* tok)
  
  This function converts the string to a float.
  
  @param tok The token to convert to an float.
  @return A pointer to the converted float.
*/
float* pflt(char* tok) {
	float val = atof(tok);
	float* ptr = malloc(sizeof(float*));
	*ptr = val;
	return ptr;
}

/*
  char* pstr(char* tok)
  
  This function creates a new string,
  which contains the value of the tok
  string with the quotes removed from
  the beginning and the end.
  
  @param tok The token to process.
  @return A pointer to the processed string.
*/
char* pstr(char* tok) {
	tok++;
	if(tok[strlen(tok) - 1] == '\'' || tok[strlen(tok) - 1] == '"') {
		tok[strlen(tok) - 1] = 0;
	}
	char* newtok = malloc(sizeof(char) * (strlen(tok) + 1));
	strcpy(newtok, tok);
	strcat(newtok, "\0");
	return newtok;
}

/*
  char* pvar(char* tok)
  
  This function copies the source string
  and returns the copied string.
  
  @param tok The token to copy.
  @return The copied string.
*/
char* pvar(char* tok) {
	char* var = malloc(sizeof(char) * (strlen(tok) + 1));
	strcpy(var, tok);
	strcat(var, "\0");
	return var;
}

/*
  int interpret_next_token(struct lisp* lisp)
  
  This function will interpret the next token.
  
  @param lisp A pointer to a lisp struct.
  @return 0 if something went wrong, 1 if nothing went wrong.
*/
int interpret_next_token(struct lisp* lisp);

/*
  struct stack_item* interpret_list(struct lisp* lisp)
  
  This function will interpret a lisp list.
  
  @param lisp A pointer to a lisp struct.
  @return A pointer to a new stack_item struct.
*/
struct stack_item* interpret_list(struct lisp* lisp) {
	while(interpret_next_token(lisp)) {}
	return si_create(SI_LST, lisp->stack);
}

/*
  int interpret_next_token(struct lisp* lisp)
  
  This function will interpret the next token.
  
  @param lisp A pointer to a lisp struct.
  @return 0 if something went wrong, 1 if nothing went wrong.
*/
int interpret_next_token(struct lisp* lisp) {
	char* tok = get_next_token(lisp->str_it);
	if     (tok == NULL) { return 0; }
	else if(isint(tok)) { stack_push(lisp->stack, si_create(SI_INT, (void*)pint(tok))); free(tok); }
	else if(isflt(tok)) { stack_push(lisp->stack, si_create(SI_FLT, (void*)pflt(tok))); free(tok); }
	else if(isstr(tok)) { stack_push(lisp->stack, si_create(SI_STR, (void*)pstr(tok))); free(tok); }
	else {
		if(strcmp(tok, "nil") == 0) {
			stack_push(lisp->stack, si_create(SI_NIL, tok));
			free(tok);
		}
		else if(strcmp(tok, "(") == 0) {
			stack_push(lisp->stack, interpret_list(lisp));
			free(tok);
		}
		else if(strcmp(tok, ")") == 0) {
			free(tok);
			return 0;
		}
		else {
			if(sym_table_lookup(lisp->symbol_table, tok) != NULL) {
				stack_push(lisp->stack, (struct stack_item*)sym_table_lookup(lisp->symbol_table, tok));
				free(tok);
				return 1;
			}
			else if(strcmp(tok, "set") == 0) { lisp__set__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "print") == 0) { lisp__print__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "read") == 0) { lisp__read__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "+") == 0) { lisp__add__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "-") == 0) { lisp__sub__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "*") == 0) { lisp__mul__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "/") == 0) { lisp__div__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "cons") == 0) { lisp__cons__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "car") == 0) { lisp__car__(lisp); free(tok); return 1; }
			else if(strcmp(tok, "cdr") == 0) { lisp__cdr__(lisp); free(tok); return 1; }
			else {
				stack_push(lisp->stack, si_create(SI_VAR, pvar(tok)));
			}
			free(tok);
		}
	}
	return 1;
}

/*
  void lisp__print__(struct lisp* lisp)

  This function is the lisp print function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__print__(struct lisp* lisp) {
	interpret_next_token(lisp);
	struct stack_item* si = stack_pop(lisp->stack);
	if(si->type == SI_INT) {
		int value = *((int*)(si->value));
		printf("%d\n", value);
	}
	else if(si->type == SI_FLT) {
		float value = *((float*)(si->value));
		printf("%f\n", value);
	}
	else if(si->type == SI_STR) {
		char* value = (char*)(si->value);
		printf("%s\n", value);
	}
	else if(si->type == SI_VAR) {
		char* value = (char*)(si->value);
		printf("%s\n", value);
	}
	else if(si->type == SI_NIL) {
		printf("nil\n");
	}
}

/*
  void lisp__add__(struct lisp* lisp)

  This function is the lisp addition function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__add__(struct lisp* lisp) {
	interpret_next_token(lisp);
	interpret_next_token(lisp);
	struct stack_item* snd = stack_pop(lisp->stack);
	struct stack_item* fst = stack_pop(lisp->stack);
	if(fst->type == snd->type) {
		if(fst->type == SI_INT) {
			int v1 = *((int*)(fst->value));
			int v2 = *((int*)(snd->value));
			int* result = malloc(sizeof(int*));
			*result = (v1 + v2);
			stack_push(lisp->stack, si_create(SI_INT, result));
			return;
		}
		else if(fst->type == SI_FLT) {
			float v1 = *((float*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 + v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	else {
		if(fst->type == SI_INT && snd->type == SI_FLT) {
			int v1 = *((int*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 + v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
		else if(fst->type == SI_FLT && snd->type == SI_INT) {
			float v1 = *((float*)(fst->value));
			int v2 = *((int*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 + v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	fprintf(stderr, "Error: can only add ints and floats.\n");
	exit(1);
}

/*
  void lisp__sub__(struct lisp* lisp)

  This function is the lisp subtraction function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__sub__(struct lisp* lisp) {
	interpret_next_token(lisp);
	interpret_next_token(lisp);
	struct stack_item* snd = stack_pop(lisp->stack);
	struct stack_item* fst = stack_pop(lisp->stack);
	if(fst->type == snd->type) {
		if(fst->type == SI_INT) {
			int v1 = *((int*)(fst->value));
			int v2 = *((int*)(snd->value));
			int* result = malloc(sizeof(int*));
			*result = (v1 - v2);
			stack_push(lisp->stack, si_create(SI_INT, result));
			return;
		}
		else if(fst->type == SI_FLT) {
			float v1 = *((float*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 - v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	else {
		if(fst->type == SI_INT && snd->type == SI_FLT) {
			int v1 = *((int*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 - v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
		else if(fst->type == SI_FLT && snd->type == SI_INT) {
			float v1 = *((float*)(fst->value));
			int v2 = *((int*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 - v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	fprintf(stderr, "Error: can only subtract ints and floats.\n");
	exit(1);
}

/*
  void lisp__mul__(struct lisp* lisp)

  This function is the lisp multiplication function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__mul__(struct lisp* lisp) {
	interpret_next_token(lisp);
	interpret_next_token(lisp);
	struct stack_item* snd = stack_pop(lisp->stack);
	struct stack_item* fst = stack_pop(lisp->stack);
	if(fst->type == snd->type) {
		if(fst->type == SI_INT) {
			int v1 = *((int*)(fst->value));
			int v2 = *((int*)(snd->value));
			int* result = malloc(sizeof(int*));
			*result = (v1 * v2);
			stack_push(lisp->stack, si_create(SI_INT, result));
			return;
		}
		else if(fst->type == SI_FLT) {
			float v1 = *((float*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 * v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	else {
		if(fst->type == SI_INT && snd->type == SI_FLT) {
			int v1 = *((int*)(fst->value));
			float v2 = *((float*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 * v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
		else if(fst->type == SI_FLT && snd->type == SI_INT) {
			float v1 = *((float*)(fst->value));
			int v2 = *((int*)(snd->value));
			float* result = malloc(sizeof(float*));
			*result = (v1 * v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	fprintf(stderr, "Error: can only multiply ints and floats.\n");
	exit(1);
}

/*
  void lisp__div__(struct lisp* lisp)

  This function is the lisp division function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__div__(struct lisp* lisp) {
	interpret_next_token(lisp);
	interpret_next_token(lisp);
	struct stack_item* snd = stack_pop(lisp->stack);
	struct stack_item* fst = stack_pop(lisp->stack);
	if(fst->type == snd->type) {
		if(fst->type == SI_INT) {
			int v1 = *((int*)(fst->value));
			int v2 = *((int*)(snd->value));
			if(v2 == 0) {
				fprintf(stderr, "Error: cannot divide by zero\n");
			}
			int* result = malloc(sizeof(int*));
			*result = (v1 / v2);
			stack_push(lisp->stack, si_create(SI_INT, result));
			return;
		}
		else if(fst->type == SI_FLT) {
			float v1 = *((float*)(fst->value));
			float v2 = *((float*)(snd->value));
			if(v2 == 0) {
				fprintf(stderr, "Error: cannot divide by zero\n");
			}
			float* result = malloc(sizeof(float*));
			*result = (v1 / v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	else {
		if(fst->type == SI_INT && snd->type == SI_FLT) {
			int v1 = *((int*)(fst->value));
			float v2 = *((float*)(snd->value));
			if(v2 == 0) {
				fprintf(stderr, "Error: cannot divide by zero\n");
			}
			float* result = malloc(sizeof(float*));
			*result = (v1 / v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
		else if(fst->type == SI_FLT && snd->type == SI_INT) {
			float v1 = *((float*)(fst->value));
			int v2 = *((int*)(snd->value));
			if(v2 == 0) {
				fprintf(stderr, "Error: cannot divide by zero\n");
			}
			float* result = malloc(sizeof(float*));
			*result = (v1 / v2);
			stack_push(lisp->stack, si_create(SI_FLT, result));
			return;
		}
	}
	fprintf(stderr, "Error: can only divide ints and floats.\n");
	exit(1);
}

/*
  void lisp__cons__(struct lisp* lisp)

  This function is the lisp cons function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__cons__(struct lisp* lisp) {
	interpret_next_token(lisp);
	interpret_next_token(lisp);
	struct stack_item* snd = stack_pop(lisp->stack);
	struct stack_item* fst = stack_pop(lisp->stack);
	struct stack* s = stack_create();
	stack_push(s, fst);
	stack_push(s, snd);
	stack_push(lisp->stack, si_create(SI_LST, (void*)s));
}

/*
  void lisp__car__(struct lisp* lisp)

  This function is the lisp car function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__car__(struct lisp* lisp) {
	interpret_next_token(lisp);
	struct stack_item* cell = stack_pop(lisp->stack);
	struct stack* cell_stack = (struct stack*)(cell->value);
	if(cell_stack->len < 2) {
		fprintf(stderr, "Error: cons cell has fewer than two elements\n");
		exit(1);
	}
	stack_push(lisp->stack, stack_get(cell_stack, 0));
}

/*
  void lisp__cdr__(struct lisp* lisp)

  This function is the lisp cdr function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__cdr__(struct lisp* lisp) {
	interpret_next_token(lisp);
	struct stack_item* cell = stack_pop(lisp->stack);
	struct stack* cell_stack = (struct stack*)(cell->value);
	if(cell_stack->len < 2) {
		fprintf(stderr, "Error: cons cell has fewer than two elements\n");
		exit(1);
	}
	stack_push(lisp->stack, stack_get(cell_stack, 0));
}

/*
  void lisp__set__(struct lisp* lisp)

  This function is the lisp set function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__set__(struct lisp* lisp) {
	char* tok = get_next_token(lisp->str_it);
	if(tok == NULL) {
		fprintf(stderr, "Error: expected variable, got EOF.");
		exit(1);
	}
	else if(isint(tok)) {
		fprintf(stderr, "Error: expected variable, got int.");
		exit(1);
	}
	else if(isflt(tok)) {
		fprintf(stderr, "Error: expected variable, got float.");
		exit(1);
	}
	else if(isstr(tok)) {
		fprintf(stderr, "Error: expected variable, got string.");
		exit(1);
	}
	interpret_next_token(lisp);
	struct stack_item* value = stack_pop(lisp->stack);
	sym_table_set(lisp->symbol_table, tok, value);
}

/*
  void lisp__read__(struct lisp* lisp)

  This function is the lisp read function.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp__read__(struct lisp* lisp) {
	char* result = malloc(0);
	int num_chars = 0;
	char c;
	while(1) {
		c = getchar();
		if(c == EOF || c == '\n') { break; }
		result = realloc(result, sizeof(char) * (num_chars + 1));
		result[num_chars++] = c;
	}
	result = realloc(result, sizeof(char) * (num_chars + 1));
	result[num_chars] = 0;
	stack_push(lisp->stack, si_create(SI_STR, result));
}

/*
  void interpret(char* str)
  
  This function interprets a source string.
  Before it interpretes the source string, it
  will define all global functions in the symbol table
  (add, sub, set, print, etc.)
  
  @param str The lisp source string.
*/
void interpret(char* str) {
	struct str_it* itr = str_it_create(str);
	struct lisp* lisp = lisp_create(itr);
	while(lisp->str_it->it < strlen(str)) {
		struct stack_item* s = interpret_list(lisp);
		struct stack* stk = (struct stack*)(s->value);
		for(int i=0;i<stk->len;i++) {
			si_destroy(stk->items[i]);
		}
	}
	lisp_destroy(lisp);
}

/*
  int main(int argc, char** argv)
  
  This function is called at the start
  of the program. We will try to use
  the users command line arguments to
  open a file, read lisp from it, and
  interpret that lisp. Otherwise, we
  will print an error message if we cannot
  open the file, and we will exit the
  program.
  
  @param argc The number of command line arguments ( >= 1 ).
  @param argv The command line arguments.
  @return The exit code of the program
          (0 if nothing went wrong, 1-255 if something went wrong).
*/
int main(int argc, char** argv) {
	if(argc > 1) {
		FILE* fp = fopen(argv[1], "r");
		if(!fp) {
			fprintf(stderr, "Error: could not open file `%s`", argv[1]);
			exit(1);
		}
		// https://stackoverflow.com/questions/174531/how-to-read-the-content-of-a-file-to-a-string-in-c
		fseek(fp, 0, SEEK_END);
		long length = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* buf = malloc(sizeof(char) * (length + 1));
		fread(buf, 1, length, fp);
		buf[length] = 0;
		fclose(fp);
		interpret(buf);
	}
	else {
		char* example_program = "( print + 1 2 )";
		interpret(example_program);
	}
	return 0;
}
