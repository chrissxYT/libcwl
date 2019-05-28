#pragma once
#include "types.h"
#include "std.h"

int cwlu_load(char *file, wl *dest);
int cwlu_parse(char *bfr, unsigned len, wl *dest);
