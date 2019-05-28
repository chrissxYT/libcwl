#pragma once
#include "types.h"
#include "std.h"

#define CWLD_BLOCK_SIZE 1024 * 256

int cwld_load(FILE *stream, wl *dest);
int cwld_parse(char *bfr, int len, wl *dest);
