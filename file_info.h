#ifndef FILE_INFO_H
#define FILE_INFO_H

#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

typedef struct {
    char name[256];
    char path[1024];
    struct stat info;
    int is_dir;
} FileInfo;

void get_permissions(mode_t mode, char *res);

void format_size(off_t size, char *res, int human_readable);

void format_time(time_t mod_time, char *res);

void get_owner_name(uid_t uid, char *res);

void get_group_name(gid_t gid, char *res);

#endif
