
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

char fileType(mode_t mode)
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

const char *permissions(mode_t mode)
{
    static char result[10];
    strcpy(result, "---------");

    for (int i = 0; i < 3; i++) {
        if (mode & (S_IRUSR >> (i * 3)))
            result[i * 3] = 'r';

        if (mode & (S_IWUSR >> (i * 3)))
            result[i * 3 + 1] = 'w';

        if (mode & (S_IXUSR >> (i * 3)))
            result[i * 3 + 2] = 'x';
    }

    return result;
}

void printFileInfo(const char *name, const struct stat *st,
                   int show_inode, int mark_dirs, int quote_names)
{
    struct passwd *owner = getpwuid(st->st_uid);
    struct group *group = getgrgid(st->st_gid);
    const char *modified = ctime(&st->st_mtime);

    if (show_inode) {
        printf("%llu ", (unsigned long long)st->st_ino);
    }

    printf("%5lld ", (long long)st->st_blocks);
    printf("%c%s ", fileType(st->st_mode), permissions(st->st_mode));
    printf("%3lu ", (unsigned long)st->st_nlink);
    printf("%s %s ",
           owner ? owner->pw_name : "unknown",
           group ? group->gr_name : "unknown");
    printf("%9lld ", (long long)st->st_size);
    printf("%.12s ", modified ? modified + 4 : "unknown");

    if (quote_names)
        putchar('"');

    printf("%s", name);

    if (mark_dirs && S_ISDIR(st->st_mode))
        putchar('/');

    if (quote_names)
        putchar('"');

    putchar('\n');
}

int main(int argc, char *argv[])
{
    int show_inode = 0;
    int mark_dirs = 0;
    int quote_names = 0;
    int option;

    while ((option = getopt(argc, argv, "ipQ")) != -1) {
        switch (option) {
            case 'i':
                show_inode = 1;
                break;
            case 'p':
                mark_dirs = 1;
                break;
            case 'Q':
                quote_names = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [directory]\n", argv[0]);
                return 1;
        }
    }

    if (optind + 1 < argc) {
        fprintf(stderr, "Usage: %s [-i] [-p] [-Q] [directory]\n", argv[0]);
        return 1;
    }

    const char *directory = (optind < argc) ? argv[optind] : ".";
    DIR *dp = opendir(directory);

    if (dp == NULL) {
        perror(directory);
        return 1;
    }

    struct dirent *entry;
    struct stat st;
    char path[BUFSIZ];

    while ((entry = readdir(dp)) != NULL) {
        int length = snprintf(path, sizeof(path), "%s/%s",
                              directory, entry->d_name);

        if (length < 0 || (size_t)length >= sizeof(path)) {
            fprintf(stderr, "Path too long: %s\n", entry->d_name);
            continue;
        }

        if (lstat(path, &st) == -1) {
            perror(path);
            continue;
        }

        printFileInfo(entry->d_name, &st,
                      show_inode, mark_dirs, quote_names);
    }

    if (closedir(dp) == -1) {
        perror("closedir");
        return 1;
    }

    return 0;
}

