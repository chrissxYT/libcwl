#include <stdlib.h>
#include <string.h>
#include "string.h"

void cstr2str(char *cstr, string *dest)
{
	dest->len = strlen(cstr);
	dest->ptr = malloc(dest->len);
	memcpy(dest->ptr, cstr, dest->len);
}

void ncstr2str(char *ncstr, int len, string *dest)
{
	dest->len = len;
	dest->ptr = malloc(len);
	memcpy(dest->ptr, ncstr, len);
}

void delstr(string str)
{
	free(str.ptr);
}
