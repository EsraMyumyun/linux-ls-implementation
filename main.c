#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "options.h"
#include "scanner.h"
#include "display.h"
#include "file_info.h"

int main(int argc, char *argv[]) {
    Options opt;
    char target_dir[1024] = "."; 
    struct stat st;

    parse_options(argc, argv, &opt);

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            strncpy(target_dir, argv[i], sizeof(target_dir) - 1);
            target_dir[sizeof(target_dir) - 1] = '\0';
            break; 
        }
    }

    if (stat(target_dir, &st) == 0) {
        if (S_ISDIR(st.st_mode)) {
           process_directory(target_dir, &opt);
        } else {
        FileInfo file;
            strncpy(file.name, target_dir, sizeof(file.name) - 1);
            strncpy(file.path, target_dir, sizeof(file.path) - 1);
            file.info = st;
            file.is_dir = 0;
            display_output(&file, 1, &opt);
        }
    } else {
        fprintf(stderr, "my_ls: грешка при достъп до '%s': ", target_dir);
        perror("");
        return EXIT_FAILURE;
    }

    return 0;
}
