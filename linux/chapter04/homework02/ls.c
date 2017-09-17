#include "ls.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <langinfo.h>
#include <unistd.h>
#include <libgen.h>

void main(int argc, char **argv) {
    DIR *dp = NULL;
    struct dirent *dirp;
    struct stat fs;
    int lswitchPresent = 0, i;
    char path[MAX];
    int is_file = 0;

    if(argc > 3) {
        perror("too many arguments\n");
        exit(EXIT_FAILURE);
    }

    path[0] = '\0';

    for (i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            strcpy(path, argv[i]);
        } else if (!strcmp(argv[i], "-l")) {
            lswitchPresent = 1;
        }
    }

    if (path[0] == '\0') {
        if (getcwd(path, MAX) == NULL) {
            perror("getcwd() error");
            exit(EXIT_FAILURE);
        }
    }

    printf("%s\n", path);

    if((dp = opendir(path)) == NULL) {
        if (access(path, F_OK) == -1) {
            perror("opendir()");
            exit(-1);
        } else {
            is_file = 1;
        }
    }

    if (is_file) {
        char *name = basename(path);
        if (!lswitchPresent) {
            printDirentNormal(name);
        } else {
            lstat(path, &fs);
            printLongFormat(name, &fs);
        }
    } else {
        while((dirp = readdir(dp)) != NULL) {
            if (!lswitchPresent) {
                printDirentNormal(dirp->d_name);
            } else {
                lstat(dirp->d_name, &fs);
                printLongFormat(dirp->d_name, &fs);
            }
        }

        closedir(dp);
    }

    exit(EXIT_SUCCESS);
}

void printDirentNormal(char *name) {
    printf("%s\n", name);
}

void printLongFormat(char *name, struct stat *fs) {
    struct group    *g;
    struct passwd   *pwd;
    struct tm       *mod_time;
    char date_string[MAX];

    g = getgrgid(fs->st_gid);
    pwd = getpwuid(fs->st_uid);

    printDirentType(fs);
    printPerms(fs);
    printf(" %d ", fs->st_nlink);
    printf(" %s %s ", pwd->pw_name, g->gr_name);
    printf(" %10d ", (int)fs->st_size);
    
    #ifdef __APPLE__
    mod_time = localtime(&fs->st_mtimespec.tv_sec);
    #else
    mod_time = localtime(&fs->st_mtime);
    #endif
    strftime(date_string, sizeof(date_string), nl_langinfo(D_T_FMT), mod_time);
    printf(" %s ", date_string);
    printf("%s\n", name);
}

/**
 * Kind of like the linux sperm()
 */
void printPerms(struct stat *fs) {
    static int perms[] = {
            // user flags
            S_IRUSR, S_IWUSR, S_IXUSR,
            // group flags
            S_IRGRP, S_IWGRP, S_IXGRP,
            // owner flags
            S_IROTH, S_IWOTH, S_IXOTH,
    };

    int i;

    for (i = 0; i < PERMS_COUNT; i++) {
        char flag = '-';
        if (fs->st_mode & perms[i]) {
            if (i % 3 == 0) {
                flag = 'r';
            } else if (i % 2 == 0) {
                flag = 'x';
            } else {
                flag = 'w';
            }
        }

        putchar(flag);
    }
}

void printDirentType(struct stat *fs) {
    char type = '?';

    if (S_ISREG(fs->st_mode)) {
        type = '-';
    } else if (S_ISLNK(fs->st_mode)) {
        type = 'l';
    } else if (S_ISDIR(fs->st_mode)) {
        type = 'd';
    } else if (S_ISBLK(fs->st_mode)) {
        type = 'b';
    }  else if (S_ISCHR(fs->st_mode)) {
        type = 'c';
    }  else if (S_ISLNK(fs->st_mode)) {
        type = 'l';
    }  else if (S_ISSOCK(fs->st_mode)) {
        type = 's';
    }

    putchar(type);
}
