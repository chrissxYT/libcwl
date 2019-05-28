#include "cwlu.h"
#include "unzip.h"

int cwlu_load(char *file, wl *dest)
{
	unzFile uf = unzOpen(file);
        if(!uf) return 0;
        unzGoToFirstFile(uf);
        unz_file_info fi;
        char c;
        unzGetCurrentFileInfo(uf, &fi,
                &c, 1,
                NULL, 0, NULL, 0);
        while(c != 'W') unzGoToNextFile(uf),
                     unzGetCurrentFileInfo(uf, &fi,
                                     &c, 1,
                                     NULL, 0, NULL, 0);
        unsigned len = fi.uncompressed_size;
        unzOpenCurrentFile(uf);
        char bfr[len];
        unzReadCurrentFile(uf, bfr, len);
        unzCloseCurrentFile(uf);
        unzClose(uf);
	return cwlu_parse(bfr, len, dest);
}

int cwlu_parse(char *bfr, unsigned len, wl *dest)
{
	char *limit = bfr + len;
	bfr++;
	while(bfr < limit)
	{
		while(*(bfr+=2) != '<');
		if(*(bfr+=2) == 'i')
		{
			item i;
			while(*(bfr+=2) != 'n');
			if(*(bfr+=2) != '=' || *(bfr+=2) != '"')
				return 0;
			char *namebfr = malloc(len);
			char *namelen = namebfr;
			while(*(++bfr+1) != '"' || *bfr != '\0')
				*namelen++ = *bfr;
			ncstr2str(namebfr, namelen-namebfr, &i.name);
			free(namebfr);
			while(*(bfr+=2) != 'u');
			if(*(bfr+=2) != '=' || *(bfr+=2) != '"')
			{
				delstr(i.name);
                                return 0;
			}
			char *urlbfr = malloc(len);
			char *urllen = urlbfr;
			while(*(++bfr+1) != '"' || *bfr != '\0')
				*urllen++ = *bfr;
			ncstr2str(urlbfr, urllen-urlbfr, &i.url);
			free(urlbfr);
			wl_add(dest, i);
		}
	}
	return 1;
}
