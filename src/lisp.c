#include "../include/lisp.h"
#include "../include/striter.h"
#include "../include/stack.h"
#include "../include/symtable.h"
#include <stdlib.h>

/*
  struct lisp* lisp_create(struct str_it* str_it)
  
  This function returns a pointer to a new lisp struct.
  The lisp struct is passed to every function in the parser.
  It will allocate the necessary memory and set the
  lisp's string iterator to the string iterator provided,
  and will create a new stack and symbol table.
  
  @param str_it A pointer to a str_it struct.
  @return A pointer to a new lisp struct.
*/
struct lisp* lisp_create(struct str_it* str_it) {
	struct lisp* lisp = malloc(sizeof(struct lisp*));
	lisp->str_it = str_it;
	lisp->stack = stack_create();
	lisp->symbol_table = sym_table_create();
	return lisp;
}

/*
  void lisp_destroy(struct lisp* lisp)
  
  This function frees all data in the pointer
  to a lisp struct provided. It will free
  the string iteratr, the stack, and the
  symbol table, as well as the lisp struct
  itself.
  
  @param lisp A pointer to a lisp struct.
*/
void lisp_destroy(struct lisp* lisp) {
	str_it_destroy(lisp->str_it);
	stack_destroy(lisp->stack);
	sym_table_destroy(lisp->symbol_table);
	free(lisp);
}
