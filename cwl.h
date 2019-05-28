#pragma once
#include "types.h"
#include "std.h"

int cwl_load(char *file, wl *dest);
int cwl_parse(char *bfr, unsigned len, wl *dest);
