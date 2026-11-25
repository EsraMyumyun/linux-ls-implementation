#define _DEFAULT_SOURCE
#include "sort.h"
#include <string.h>
#include <stdlib.h>

int compare_name(const void *a, const void *b) {
    const FileInfo *file_a = (const FileInfo *)a;
    const FileInfo *file_b = (const FileInfo *)b;
    return strcmp(file_a->name, file_b->name);
}

int compare_size(const void *a, const void *b) {
    const FileInfo *file_a = (const FileInfo *)a;
    const FileInfo *file_b = (const FileInfo *)b;
    
    if (file_b->info.st_size > file_a->info.st_size) return 1;
    if (file_b->info.st_size < file_a->info.st_size) return -1;
    return 0;
}

int compare_time(const void *a, const void *b) {
    const FileInfo *file_a = (const FileInfo *)a;
    const FileInfo *file_b = (const FileInfo *)b;
    
    if (file_b->info.st_mtime > file_a->info.st_mtime) return 1;
    if (file_b->info.st_mtime < file_a->info.st_mtime) return -1;
    return 0;
}

static void reverse_array(FileInfo *files, size_t count) {
    FileInfo temp;
    for (size_t i = 0; i < count / 2; i++) {
        temp = files[i];
        files[i] = files[count - 1 - i];
        files[count - 1 - i] = temp;
    }
}

void sort_files(FileInfo *files, size_t count, Options *opt) {
    if (count <= 1) return;

    if (opt->sort_by_size) {
        qsort(files, count, sizeof(FileInfo), compare_size);
    } else if (opt->sort_by_time) {
        qsort(files, count, sizeof(FileInfo), compare_time);
    } else {
        qsort(files, count, sizeof(FileInfo), compare_name);
    }

    if (opt->reverse_sort) {
        reverse_array(files, count);
    }
}
