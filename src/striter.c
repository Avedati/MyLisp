#include "../include/striter.h"
#include <stdlib.h>
#include <string.h>

/*
  struct str_it* str_it_create(char* str)
  
  This function returns a new pointer to the str_it struct,
  with the str field being the argument provided.
  The str_it struct represents a string iterator, and
  has a string and an index as fields.
  
  @param str The string to iterate over.
  @return A new pointer to the str_it struct.
*/
struct str_it* str_it_create(char* str) {
	struct str_it* itr = (struct str_it*)malloc(sizeof(struct str_it*));
	itr->str = malloc(strlen(str) + 1);
	strcpy(itr->str, str);
	strcat(itr->str, "\0");
	itr->it = 0;
	return itr;
}

/*
  void str_it_destroy(struct str_it* itr)
  
  This function frees itr's string, and
  then frees itr itself.
  
  @param itr A pointer to the str_it struct.
*/
void str_it_destroy(struct str_it* itr) {
	free(itr->str);
	free(itr);
}

/*
  char str_it_c(struct str_it* itr)
  
  This function returns the string iterator's
  current character, if application. Otherwise,
  it returns -1.
  
  @param itr A pointer to the str_it struct.
  @return The current char, if applicable. Otherwise, -1.
*/
char str_it_c(struct str_it* itr) {
	return (itr->it < 0 || itr->it >= strlen(itr->str)) ? -1 : itr->str[itr->it];
}
