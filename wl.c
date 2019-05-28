#include "wl.h"
#include <stdlib.h>

wl wl_new()
{
	wl wl;
	wl.items = malloc(0);
	wl.count = 0;
	return wl;
}

void wl_delete(wl wl)
{
	for(int i = 0; i < wl.count; i++)
		delstr(wl.items[i].name), delstr(wl.items[i].url);
	free(wl.items);
}

void wl_add(wl *wl, item itm)
{
	item *i = wl->items;
	wl->items = malloc((wl->count + 1) * sizeof(item));
	for(int j = 0; j < wl->count; j++) wl->items[j] = i[j];
	free(i);
	wl->count++;
}

void wl_remove(wl *wl, int idx)
{
	item *i = wl->items;
	wl->count--;
	wl->items = malloc((wl->count) * sizeof(item));
	for(int j = 0;     j < idx;       j++) wl->items[j]   = i[j];
	for(int j = idx+1; j < wl->count; j++) wl->items[j-1] = i[j];
	free(i);
}
