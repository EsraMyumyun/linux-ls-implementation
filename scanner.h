#ifndef SCANNER_H
#define SCANNER_H

#include <stddef.h>
#include "file_info.h"
#include "options.h"

FileInfo* scan_directory(const char *dirname, size_t *count, Options *opt);

void process_directory(const char *dirname, Options *opt);

#endif
