#pragma once
#include "types.h"
#include "std.h"

int cwlb_load(char *file, wl *dest);
int cwlb_parse(char *bfr, unsigned len, wl *dest);
