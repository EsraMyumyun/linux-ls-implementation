#define _DEFAULT_SOURCE
#include "scanner.h"
#include "sort.h"
#include "display.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

FileInfo* scan_directory(const char *dirname, size_t *count, Options *opt) {
    DIR *dir = opendir(dirname);
    if (dir == NULL) {
        fprintf(stderr, "my_ls: cannot open directory '%s': ", dirname);
        perror("");
        return NULL;
    }

    size_t capacity = 10;
    *count = 0;
    FileInfo *files = calloc(capacity, sizeof(FileInfo));
    if (files == NULL) {
        closedir(dir);
        return NULL;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (!opt->show_all && entry->d_name[0] == '.') {
            continue;
        }

        if (*count >= capacity) {
            capacity *= 2;
            FileInfo *temp = realloc(files, capacity * sizeof(FileInfo));
            if (temp == NULL) {
                free(files);
                closedir(dir);
                return NULL;
            }
            files = temp;
        }

        strncpy(files[*count].name, entry->d_name, 255);
        files[*count].name[255] = '\0';

        snprintf(files[*count].path, sizeof(files[*count].path), "%s/%s", dirname, entry->d_name);

        if (lstat(files[*count].path, &files[*count].info) == -1) {
            continue; 
        }

        files[*count].is_dir = S_ISDIR(files[*count].info.st_mode);

        (*count)++;
    }

    closedir(dir);
    return files;
}

void process_directory(const char *dirname, Options *opt) {
    size_t count = 0;

    if (opt->recursive) {
        printf("\n%s:\n", dirname);
    }

    FileInfo *files = scan_directory(dirname, &count, opt);
    if (files == NULL) return;

    sort_files(files, count, opt);

    display_output(files, count, opt);

    if (opt->recursive) {
        for (size_t i = 0; i < count; i++) {
            if (files[i].is_dir) {
                if (strcmp(files[i].name, ".") == 0 || strcmp(files[i].name, "..") == 0) {
                    continue;
                }
                process_directory(files[i].path, opt);
            }
        }
    }

    free(files);
    files = NULL; 
}
