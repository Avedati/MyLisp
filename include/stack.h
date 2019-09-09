#ifndef __STACK_H
#define __STACK_H

enum stack_item_type { SI_INT, SI_FLT, SI_STR, SI_VAR, SI_NIL, SI_LST };

struct stack_item {
	enum stack_item_type type;
	void* value;
};

struct stack {
	struct stack_item** items;
	int len;
	int size;
};

struct stack_item* si_create(enum stack_item_type,void*);
void si_print(struct stack_item*);
void si_destroy(struct stack_item*);
struct stack* stack_create(void);
void stack_destroy(struct stack*);
void stack_push(struct stack*,struct stack_item*);
struct stack_item* stack_get(struct stack*,int);
struct stack_item* stack_pop(struct stack*);

#endif // __STACK_H
