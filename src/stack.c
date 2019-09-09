#include "../include/stack.h"
#include <stdio.h>
#include <stdlib.h>

struct stack_item* si_create(enum stack_item_type type, void* value) {
	struct stack_item* si = (struct stack_item*)malloc(sizeof(struct stack_item*));
	si->type = type;
	si->value = value;
	return si;
}

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

void si_destroy(struct stack_item* s) {
	free(s->value);
	free(s);
}

struct stack* stack_create(void) {
	struct stack* s = (struct stack*)malloc(sizeof(struct stack*));
	s->items = malloc(0);
	s->len = 0;
	s->size = 0;
	return s;
}

void stack_destroy(struct stack* s) {
	free(s->items);
	free(s);
}

void stack_push(struct stack* s, struct stack_item* si) {
	if(s->size == s->len) {
		s->items = realloc(s->items, sizeof(struct stack_item*) * (s->size + 1));
		s->size++;
	}
	s->items[(s->len)++] = si;
}

struct stack_item* stack_get(struct stack* s, int i) {
	return (0 <= i && i < s->len) ? s->items[i] : NULL;
}

struct stack_item* stack_pop(struct stack* s) {
	return s->items[--(s->len)];
}

