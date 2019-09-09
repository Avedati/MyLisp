#include "../include/symtable.h"
#include <stdlib.h>
#include <string.h>

struct symbol_table* sym_table_create(void) {
	struct symbol_table* s = malloc(sizeof(struct symbol_table*));
	s->len = 0;
	s->keys = malloc(0);
	s->values = malloc(0);
	return s;
}

void sym_table_set(struct symbol_table* s, char* key, void* value) {
	for(int i=0;i<s->len;i++) {
		if(strcmp(s->keys[i], key) == 0) {
			s->values[i] = value;
			return;
		}
	}
	s->keys = realloc(s->keys, (s->len + 1) * sizeof(char*));
	s->keys[s->len] = key;
	s->values = realloc(s->values, (s->len + 1) * sizeof(char*));
	s->values[(s->len)++] = value;
}

void* sym_table_lookup(struct symbol_table* s, char* key) {
	for(int i=0;i<s->len;i++) {
		if(strcmp(s->keys[i], key) == 0) { return s->values[i]; }
	}
	return NULL;
}

void sym_table_destroy(struct symbol_table* s) {
	free(s->keys);
	free(s->values);
	free(s);
}
