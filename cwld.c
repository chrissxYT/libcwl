#include "cwld.h"
#include <zlib.h>

int cwld_load(FILE *stream, wl *dest)
{
	int i;
	z_stream s;
	s.zalloc = Z_NULL;
	s.zfree = Z_NULL;
	s.opaque = Z_NULL;
	s.avail_in = 0;
	s.next_in = Z_NULL;
	i = inflateInit(&s);
	if (i != Z_OK) return 0;
	while(!s.avail_out)
	{
		s.avail_in = fread(in, 1, CWLD_BLOCK_SIZE, stream);
	}
}

int cwld_parse(char *bfr, int len, wl *dest)
{
}
