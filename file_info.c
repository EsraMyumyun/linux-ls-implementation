#define _DEFAULT_SOURCE
#include "file_info.h"
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


void get_permissions(mode_t mode, char *res) {
    if (S_ISDIR(mode)) res[0] = 'd';
    else if (S_ISLNK(mode)) res[0] = 'l';
    else if (S_ISCHR(mode)) res[0] = 'c';
    else if (S_ISBLK(mode)) res[0] = 'b';
    else if (S_ISFIFO(mode)) res[0] = 'p';
    else if (S_ISSOCK(mode)) res[0] = 's';
    else res[0] = '-';

    res[1] = (mode & S_IRUSR) ? 'r' : '-';
    res[2] = (mode & S_IWUSR) ? 'w' : '-';
    res[3] = (mode & S_IXUSR) ? 'x' : '-';
    res[4] = (mode & S_IRGRP) ? 'r' : '-';
    res[5] = (mode & S_IWGRP) ? 'w' : '-';
    res[6] = (mode & S_IXGRP) ? 'x' : '-';
    res[7] = (mode & S_IROTH) ? 'r' : '-';
    res[8] = (mode & S_IWOTH) ? 'w' : '-';
    res[9] = (mode & S_IXOTH) ? 'x' : '-';
    res[10] = '\0';
}


void format_size(off_t size, char *res, int human_readable) {
    if (!human_readable) {
        sprintf(res, "%ld", (long)size);
        return;
    }

    const char *units[] = {"B", "K", "M", "G", "T"};
    int unit_idx = 0;
    double d_size = (double)size;

    while (d_size >= 1024 && unit_idx < 4) {
        d_size /= 1024;
        unit_idx++;
    }

    if (unit_idx == 0) sprintf(res, "%ld%s", (long)size, units[unit_idx]);
    else sprintf(res, "%.1f%s", d_size, units[unit_idx]);
}


void format_time(time_t mod_time, char *res) {
    struct tm *tm_info = localtime(&mod_time);
    strftime(res, 20, "%b %d %H:%M", tm_info);
}


void get_owner_name(uid_t uid, char *res) {
    struct passwd *pw = getpwuid(uid);
    if (pw) strcpy(res, pw->pw_name);
    else sprintf(res, "%d", uid);
}

void get_group_name(gid_t gid, char *res) {
    struct group *gr = getgrgid(gid);
    if (gr) strcpy(res, gr->gr_name);
    else sprintf(res, "%d", gid);
}
