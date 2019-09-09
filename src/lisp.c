#include "../include/lisp.h"
#include "../include/striter.h"
#include "../include/stack.h"
#include "../include/symtable.h"
#include <stdlib.h>

struct lisp* lisp_create(struct str_it* str_it) {
	struct lisp* lisp = malloc(sizeof(struct lisp*));
	lisp->str_it = str_it;
	lisp->stack = stack_create();
	lisp->symbol_table = sym_table_create();
	return lisp;
}

void lisp_destroy(struct lisp* lisp) {
	str_it_destroy(lisp->str_it);
	stack_destroy(lisp->stack);
	sym_table_destroy(lisp->symbol_table);
	free(lisp);
}
