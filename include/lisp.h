#ifndef __LISP_H
#define __LISP_H

#include "striter.h"
#include "stack.h"
#include "symtable.h"

struct lisp {
	struct str_it* str_it;
	struct stack* stack;
	struct symbol_table* symbol_table;
};

struct lisp* lisp_create(struct str_it*);
void lisp_destroy(struct lisp*);

#endif // __LISP_H
