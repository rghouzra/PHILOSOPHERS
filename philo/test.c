#include <libc.h>
#include <dirent.h>


int main()
{
    DIR *dir;
    char *dir_name = "/";
    dir = opendir(dir_name);
    struct dirent *d;
    d = readdir(dir);
    while(d != NULL)
    {
        printf("%s\n", d->d_name);
        char *dir_name = d->d_name;
        DIR *dir2 = opendir(dir_name);
        struct dirent *d2;
        d2 = readdir(dir2);
        while(d2 != NULL)
        {
            printf("%s\n", d2->d_name);
            d2 = readdir(dir2);
        }
        d = readdir(dir);
    }
}