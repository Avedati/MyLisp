#include "../include/striter.h"
#include <stdlib.h>
#include <string.h>

struct str_it* str_it_create(char* str) {
	struct str_it* itr = (struct str_it*)malloc(sizeof(struct str_it*));
	itr->str = malloc(strlen(str) + 1);
	strcpy(itr->str, str);
	strcat(itr->str, "\0");
	itr->it = 0;
	return itr;
}

void str_it_destroy(struct str_it* itr) {
	free(itr->str);
	free(itr);
}

char str_it_c(struct str_it* itr) {
	return (itr->it < 0 || itr->it >= strlen(itr->str)) ? -1 : itr->str[itr->it];
}
