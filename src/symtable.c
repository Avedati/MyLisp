#include "../include/symtable.h"
#include <stdlib.h>
#include <string.h>

/*
  struct symbol_table* sym_table_create(void)
  
  This function returns a new pointer to the symbol_table struct.
  The len field will be set to 0, and the keys and values fields
  with both be set to NULL.
  
  @return A new pointer to the symbol_table struct.
*/
struct symbol_table* sym_table_create(void) {
	struct symbol_table* s = malloc(sizeof(struct symbol_table*));
	s->len = 0;
	s->keys = malloc(0);
	s->values = malloc(0);
	return s;
}

/*
  void sym_table_set(struct symbol_table* s, char* key, void* value)
  
  This function sets the value associated with the key in the symbol
  table to the value argument (represented as a pointer to any type).
  
  @param s A pointer to the symbol_table struct.
  @param key A string representing the key to set.
  @param value A pointer to any type representing the value to set the key to.
*/
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

/*
  void* sym_table_lookup(struct symbol_table* s, char* key)
  
  This function returns the value associated with the key in the
  symbol table, if applicable. Otherwise, it returns NULL.
  
  @param s A pointer to the symbol_table struct.
  @param key A string representing the key to check.
  @return The value associated with the key in the symbol_table, if applicable. Otherwise, NULL.
*/
void* sym_table_lookup(struct symbol_table* s, char* key) {
	for(int i=0;i<s->len;i++) {
		if(strcmp(s->keys[i], key) == 0) { return s->values[i]; }
	}
	return NULL;
}

/*
  void sym_table_destroy(struct symbol_table* s)
  
  This function frees the keys and values fields of
  the symbol table, and then frees the symbol table
  itself.
  
  @param s A pointer to the symbol_table struct.
*/
void sym_table_destroy(struct symbol_table* s) {
	free(s->keys);
	free(s->values);
	free(s);
}
