#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>

int main() {
    struct sysinfo info;
    struct statvfs stat;

    printf("Welcome!\n");
    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs < 1) {
        perror("sysconf");
        return 1;
    }
    printf("\n---\n");
    printf("Number of available processors: %ld\n", nprocs);
    
    if (sysinfo(&info) == 0) {
        printf("\n---\n");
        printf("Total RAM: %lu MB\n", info.totalram / 1024 / 1024);
        printf("Free RAM: %lu MB\n", info.freeram / 1024 / 1024);
        printf("Available RAM: %lu MB\n", info.freeram / 1024 / 1024); // approx
    } else {
        perror("sysinfo");
        return 1;
    }

    if (statvfs("/", &stat) == 0) {
        unsigned long total = stat.f_blocks * stat.f_frsize;
        unsigned long free = stat.f_bfree * stat.f_frsize;
        unsigned long available = stat.f_bavail * stat.f_frsize;
        printf("\n---\n");
        printf("Total disk space: %lu MB\n", total / 1024 / 1024);
        printf("Free disk space: %lu MB\n", free / 1024 / 1024);
        printf("Available disk space: %lu MB\n", available / 1024 / 1024);
    } else {
        perror("statvfs");
        return 1;
    }
    printf("\n---\n");
    return 0;
}