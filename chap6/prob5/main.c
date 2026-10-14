
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>

char type(mode_t mode);
char *perm(mode_t mode);
void printStat(char *file, struct stat *st);

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *d;
    struct stat st;
    char path[BUFSIZ];
    char *dir;

    if (argc == 1) {
        dir = ".";
    } else {
        dir = argv[1];
    }

    dp = opendir(dir);

    if (dp == NULL) {
        perror(dir);
        return 1;
    }

    while ((d = readdir(dp)) != NULL) {
        if (snprintf(path, sizeof(path), "%s/%s",
                     dir, d->d_name) >= sizeof(path)) {
            fprintf(stderr, "Path too long\n");
            continue;
        }

        if (lstat(path, &st) == -1) {
            perror(path);
            continue;
        }

        printStat(d->d_name, &st);
    }

    closedir(dp);
    return 0;
}

void printStat(char *file, struct stat *st)
{
    struct passwd *pw = getpwuid(st->st_uid);
    struct group *gr = getgrgid(st->st_gid);

    printf("%5lld ", (long long)st->st_blocks);
    printf("%c%s ", type(st->st_mode), perm(st->st_mode));
    printf("%3lu ", (unsigned long)st->st_nlink);
    printf("%s %s ",
           pw ? pw->pw_name : "unknown",
           gr ? gr->gr_name : "unknown");
    printf("%9lld ", (long long)st->st_size);
    printf("%.12s ", ctime(&st->st_mtime) + 4);
    printf("%s\n", file);
}

char type(mode_t mode)
{
    if (S_ISREG(mode)) return '-';
    if (S_ISDIR(mode)) return 'd';
    if (S_ISCHR(mode)) return 'c';
    if (S_ISBLK(mode)) return 'b';
    if (S_ISLNK(mode)) return 'l';
    if (S_ISFIFO(mode)) return 'p';
    if (S_ISSOCK(mode)) return 's';

    return '?';
}

char *perm(mode_t mode)
{
    static char perms[10];
    strcpy(perms, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> (i * 3)))
            perms[i * 3] = 'r';

        if (mode & (S_IWUSR >> (i * 3)))
            perms[i * 3 + 1] = 'w';

        if (mode & (S_IXUSR >> (i * 3)))
            perms[i * 3 + 2] = 'x';
    }

    return perms;
}

