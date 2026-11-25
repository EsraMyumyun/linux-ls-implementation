#define _DEFAULT_SOURCE
#include "display.h"
#include "file_info.h"
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void get_owner_name(uid_t uid, char *res);
void get_group_name(gid_t gid, char *res);

void display_output(FileInfo *files, size_t count, Options *opt) {
    if (count == 0 || files == NULL) return;
    struct winsize w;
    int term_width = 80;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0 && w.ws_col > 0) {
        term_width = w.ws_col;
    }
    size_t max_name_len = 0;
    for (size_t i = 0; i < count; i++) {
        size_t len = strlen(files[i].name);
        if (len > max_name_len) max_name_len = len;
    }
    int col_width = (int)max_name_len + 2;
    int num_cols = term_width / col_width;
    if (num_cols <= 0) num_cols = 1;

    char perms[11], time_buf[20], size_buf[20], owner[64], group[64];

    if (opt->long_format) {

        long total_blocks = 0;
        for (size_t i = 0; i < count; i++) {
            total_blocks += (long)files[i].info.st_blocks;
        }
        if (opt->human_readable) {
           char total_buf[20];
           format_size(total_blocks*512, total_buf, 1);
           printf("total %g%c\n", (double)total_blocks / 2, total_buf[strlen(total_buf)-1]); 
        } else {
           printf("total %ld\n", total_blocks / 2);
        }

        for (size_t i = 0; i < count; i++) {
            get_permissions(files[i].info.st_mode, perms);
            format_size(files[i].info.st_size, size_buf, opt->human_readable);
            format_time(files[i].info.st_mtime, time_buf);
            get_owner_name(files[i].info.st_uid, owner);
            get_group_name(files[i].info.st_gid, group);

            const char* name_color = COLOR_RESET;
            if (S_ISDIR(files[i].info.st_mode)) name_color = COLOR_DIR;
            else if (S_ISLNK(files[i].info.st_mode)) name_color = COLOR_LNK;
            else if (S_ISFIFO(files[i].info.st_mode)) name_color = COLOR_FIFO;
            else if (files[i].info.st_mode & S_IXUSR) name_color = COLOR_EXEC;

            printf("%s%s%s ", COLOR_PERMS, perms, COLOR_RESET);                 
            printf("%s%2ld%s ", COLOR_LINKS, (long)files[i].info.st_nlink, COLOR_RESET);
            printf("%s%-8s%s ", COLOR_OWNER, owner, COLOR_RESET);                
            printf("%s%-8s%s ", COLOR_GROUP, group, COLOR_RESET);                
            printf("%s%8s%s ", COLOR_SIZE, size_buf, COLOR_RESET);               
            printf("%s%s%s ", COLOR_TIME, time_buf, COLOR_RESET);                
            printf("%s%s%s", name_color, files[i].name, COLOR_RESET);            

            if (S_ISLNK(files[i].info.st_mode)) {
                char link_target[1024];
                ssize_t len = readlink(files[i].path, link_target, sizeof(link_target)-1);
                if (len != -1) {
                    link_target[len] = '\0';
                    printf(" -> %s", link_target);
                }
            }
            printf("\n");
        }
    } 
    else {
        int num_rows = ((int)count + num_cols - 1) / num_cols;
        for (int r = 0; r < num_rows; r++) {
            for (int c = 0; c < num_cols; c++) {
                int idx = c * num_rows + r;
                if (idx < (int)count) {
                    const char* name_color = COLOR_RESET;
                    if (S_ISDIR(files[idx].info.st_mode)) name_color = COLOR_DIR;
                    else if (S_ISLNK(files[idx].info.st_mode)) name_color = COLOR_LNK;
                    else if (S_ISFIFO(files[idx].info.st_mode)) name_color = COLOR_FIFO;
                    else if (files[idx].info.st_mode & S_IXUSR) name_color = COLOR_EXEC;

                    printf("%s%-*s%s", name_color, col_width, files[idx].name, COLOR_RESET);
                }
            }
            printf("\n");
        }
    }
}
