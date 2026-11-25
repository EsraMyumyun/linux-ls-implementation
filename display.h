#ifndef DISPLAY_H
#define DISPLAY_H

#include <sys/types.h>
#include <stddef.h>
#include "file_info.h"
#include "options.h"

#define COLOR_RESET   "\x1b[0m"
#define COLOR_PERMS   "\x1b[33m"
#define COLOR_LINKS   "\x1b[90m"
#define COLOR_OWNER   "\x1b[1;37m"
#define COLOR_GROUP   "\x1b[37m"
#define COLOR_SIZE    "\x1b[36m"
#define COLOR_TIME    "\x1b[35m"
#define COLOR_DIR     "\x1b[1;34m"
#define COLOR_LNK     "\x1b[1;36m"
#define COLOR_EXEC    "\x1b[1;32m"
#define COLOR_FIFO    "\x1b[33m"

void display_output(FileInfo *files, size_t count, Options *opt);

void get_permissions(mode_t mode, char *res);
void format_size(off_t size, char *res, int human_readable);
void format_time(time_t mod_time, char *res);

#endif

