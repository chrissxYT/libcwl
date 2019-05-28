#pragma once
typedef struct _string
{
	char *ptr;
	int   len;
} string;
void cstr2str(char *cstr, string *dest);
void ncstr2str(char *ncstr, int len, string *dest);
void delstr(string str);
