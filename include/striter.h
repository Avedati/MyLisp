#ifndef __STRITER_H
#define __STRITER_H

struct str_it {
	char* str;
	int it;
};

struct str_it* str_it_create(char*);
void str_it_destroy(struct str_it*);
char str_it_c(struct str_it*);

#endif // __STRITER_H
