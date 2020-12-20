#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

/*
  struct stack_item* si_create(enum stack_item_type type, void* value)
  
  This function creates a new pointer to the stack_item struct, and it will
  set the type and value fields of the stack_item struct accordingly.
  
  @param type The type of the stack item.
  @param value The value of the stack item (represented as a pointer to any type).
  @return A new pointer to the stack_item struct.
*/
struct stack_item* si_create(enum stack_item_type type, void* value) {
	struct stack_item* si = (struct stack_item*)malloc(sizeof(struct stack_item));
	si->type = type;
	si->value = value;
	return si;
}

/*
  void si_print(struct stack_item* s)
  
  This function prints the given stack item (using
  it's type field to determine what to cast
  it's value field to).
  
  @param s A pointer to the stack_item struct.
*/
void si_print(struct stack_item* s) {
	if(s->type == SI_INT) {
		printf("SI_INT, %d\n", *((int*)(s->value)));
	}
	else if(s->type == SI_FLT) {
		printf("SI_FLT, %f\n", *((float*)(s->value)));
	}
	else if(s->type == SI_STR) {
		printf("SI_STR, %s\n", ((char*)(s->value)));
	}
	else if(s->type == SI_VAR) {
		printf("SI_VAR, %s\n", ((char*)(s->value)));
	}
	else if(s->type == SI_NIL) {
		printf("SI_NIL, nil\n");
	}
}

/*
  void si_destroy(struct stack_item* s)
  
  This function frees the stack item's value
  and the stack item itself.
  
  @param s A pointer to the stack_item struct.
*/
void si_destroy(struct stack_item* s) {
	free(s);
}

/*
  struct stack* stack_create(void)
  
  This function creates a new pointer to the stack struct, and it will set
  the items field to NULL, and the len and size fields to 0. The stack struct
  is a structure which stack items can be pushed onto, accessed in, and poped
  from.
  
  @return A new pointer to the stack struct.
*/
struct stack* stack_create(void) {
	struct stack* s = (struct stack*)malloc(sizeof(struct stack));
	s->items = malloc(0);
	s->len = 0;
	s->size = 0;
	return s;
}

/*
  void stack_destroy(struct stack* s)
  
  This function frees the stack's items
  and then free the stack itself.
  
  @param s A pointer to the stack struct.
*/
void stack_destroy(struct stack* s) {
	free(s->items);
	free(s);
}

/*
  void stack_push(struct stack* s, struct stack_item* si)
  
  This function adds the stack item to the items field
  of the stack.
  
  @param s A pointer to the stack struct.
  @param si A pointer to the stack_item struct.
*/
void stack_push(struct stack* s, struct stack_item* si) {
	if(s->size == s->len) {
		s->items = realloc(s->items, sizeof(struct stack_item*) * (s->size + 1));
		s->size++;
	}
	s->items[(s->len)++] = si;
}

/*
  struct stack_item* stack_get(struct stack* s, int i)
  
  This function returns the stack item at the given index (i)
  if that index is in [0, s->len). Otherwise, this function
  returns NULL.
  
  @param s A pointer to the stack struct.
  @param i The index to get the stack item from.
  @return The stack item at the index, if applicable. Otherwise, NULL.
*/
struct stack_item* stack_get(struct stack* s, int i) {
	return (0 <= i && i < s->len) ? s->items[i] : NULL;
}

/*
  struct stack_item* stack_pop(struct stack* s)
  
  This function removes and returns the top item
  of the stack.
  
  @param s A pointer to the stack struct.
  @return The stack item at the top of the stack.
*/
struct stack_item* stack_pop(struct stack* s) {
	if(s->len >= 0) {
		return s->items[--(s->len)];
	}
	return NULL;
}

