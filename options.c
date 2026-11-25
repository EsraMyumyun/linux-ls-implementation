#include "options.h"
#include <stdio.h>
#include <stdlib.h>

void parse_options(int argc, char *argv[], Options *opt) {
    opt->show_all = 0;
    opt->long_format = 0;
    opt->recursive = 0;
    opt->sort_by_size = 0;
    opt->sort_by_time = 0;
    opt->reverse_sort = 0;
    opt->human_readable = 0; 
//може и memset(opt, 0, sizeof(Options))
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            for (int j = 1; argv[i][j] != '\0'; j++) {
                switch (argv[i][j]) {
                    case 'a': opt->show_all = 1; break;
                    case 'l': opt->long_format = 1; break;
                    case 'R': opt->recursive = 1; break;
                    case 'S': opt->sort_by_size = 1; break;
                    case 't': opt->sort_by_time = 1; break;
                    case 'r': opt->reverse_sort = 1; break;
                    case 'h': opt->human_readable = 1; break;
                    default:
                        fprintf(stderr, "Неизвестна опция: -%c\n", argv[i][j]);
                        exit(EXIT_FAILURE);
                }
            }
        }
    }
}
