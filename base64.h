#pragma once
#include <stdio.h>
char *base64_encode(char *src, size_t len, size_t *out_len);
char *base64_decode(char *src, size_t len, size_t *out_len);
