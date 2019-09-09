#ifndef __SYMTABLE_H
#define __SYMTABLE_H

struct symbol_table {
	int len;
	char** keys;
	void** values;
};

struct symbol_table* sym_table_create(void);
void sym_table_set(struct symbol_table*,char*,void*);
void* sym_table_lookup(struct symbol_table*,char*);
void sym_table_destroy(struct symbol_table*);

#endif // __SYMTABLE_H
