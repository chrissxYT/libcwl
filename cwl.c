#include "cwl.h"
#include "unzip.h"

int cwl_load(char *file, wl *dest)
{
	unzFile uf = unzOpen(file);
	if(!uf) return 0;
	unzGoToFirstFile(uf);
	unz_file_info fi;
	unzGetCurrentFileInfo(uf, &fi,
		NULL, //TODO: check name
		0,
		NULL, 0, NULL, 0);
	unsigned len = fi.uncompressed_size;
	unzOpenCurrentFile(uf);
	char bfr[len];
	unzReadCurrentFile(uf, bfr, len);
	unzCloseCurrentFile(uf);
	unzClose(uf);
	return cwl_parse(bfr, len, dest);
}

int cwl_parse(char *bfr, unsigned len, wl *dest)
{
	char *limit = bfr + len;
	while(bfr < limit)
	{
		while(*++bfr != '<');
		if(*++bfr == 'i' &&
		   *++bfr == 't' &&
		   *++bfr == 'e' &&
		   *++bfr == 'm')
		{
			item i;
			while(*++bfr != '=');
			if(*++bfr != '"') return 0;
			char *namebfr = malloc(len);
			char *namelen = namebfr;
			while(*++bfr != '"') *namelen = *bfr, namelen++;
			*namelen = '\0';
			cstr2str(namebfr, &i.name);
			free(namebfr);
			while(*++bfr != '=');
			if(*++bfr != '"')
			{
				delstr(i.name);
				return 0;
			}
			char *urlbfr = malloc(len);
			char *urllen = urlbfr;
			while(*++bfr != '"') *urllen = *bfr, urllen++;
			*urllen = '\0';
			cstr2str(urlbfr, &i.url);
			free(urlbfr);
			wl_add(dest, i);
		}
	}
	return 1;
}
