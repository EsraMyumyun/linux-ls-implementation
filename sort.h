#ifndef SORT_H
#define SORT_H

#include <stddef.h>
#include "file_info.h"
#include "options.h"

void sort_files(FileInfo *files, size_t count, Options *opt);

int compare_time(const void *a, const void *b);
int compare_size(const void *a, const void *b);
int compare_name(const void *a, const void *b);

#endif
