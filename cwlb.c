#include "cwlb.h"
#include "unzip.h"
#include "base64.h"

int cwlb_load(char *file, wl *dest)
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
	return cwlb_parse(bfr, len, dest);
}

int cwlb_parse(char *bfr, unsigned len, wl *dest)
{
	char *limit = bfr + len;
	while(bfr < limit)
	{
		while(*++bfr != '<');
		if(*++bfr == 'i')
		{
			item i;
			while(*++bfr != 'n');
			if(*++bfr != '=' || *++bfr != '"') return 0;
			char *namebfr = malloc(len);
			char *namelen = namebfr;
			while(*++bfr != '"') *namelen++ = *bfr;
			size_t name_len;
			char *name = base64_decode(namebfr,
						   namelen - namebfr,
						   &name_len);
			if(!name)
			{
				free(namebfr);
				return 0;
			}
			ncstr2str(name, name_len, &i.name);
			free(namebfr);
			free(name);
			while(*++bfr != 'u');
			if(*++bfr != '=' || *++bfr != '"')
			{
				delstr(i.name);
				return 0;
			}
			char *urlbfr = malloc(len);
			char *urllen = urlbfr;
			while(*++bfr != '"') *urllen++ = *bfr;
			size_t url_len;
			char *url = base64_decode(urlbfr,
						   urllen - urlbfr,
						   &url_len);
			if(!url)
			{
				free(urlbfr);
				return 0;
			}
			ncstr2str(url, url_len, &i.url);
			free(urlbfr);
			free(url);
			wl_add(dest, i);
		}
	}
	return 1;
}
