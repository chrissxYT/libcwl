#pragma once
#include "item.h"
typedef struct _wl
{
	item *items;
	int   count;
} wl;
wl   wl_new();
void wl_delete(wl wl);
void wl_add(wl *wl, item itm);
void wl_remove(wl *wl, int idx);
