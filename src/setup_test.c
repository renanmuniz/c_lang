#include <stdio.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <time.h>

int main() {
    struct sysinfo info;
    struct statvfs stat;
    struct utsname osinfo;

    // Get current date/time
    time_t now = time(NULL);
    struct tm *local = localtime(&now);
    char datetime_str[100];
    strftime(datetime_str, sizeof(datetime_str), "%Y-%m-%d %H:%M:%S", local);

    printf("*************************\n");
    printf("*  W  E  L  C  O  M  E  *\n");
    printf("*  %s  *\n", datetime_str);
    printf("*************************\n\n");

    
    

    printf("=========================\n");
    printf("= S Y S T E M   I N F O =\n");
    printf("=========================\n");

    if (uname(&osinfo) == 0) {
        printf("System Name: %s\n", osinfo.sysname);
        printf("Node Name: %s\n", osinfo.nodename);
        printf("Release: %s\n", osinfo.release);
        printf("Version: %s\n", osinfo.version);
        printf("Machine: %s\n", osinfo.machine);
    } else {
        perror("uname");
        return 1;
    }

    long nprocs = sysconf(_SC_NPROCESSORS_ONLN);
    if (nprocs < 1) {
        perror("sysconf");
        return 1;
    }
    printf("Number of available processors: %ld\n", nprocs);

    if (sysinfo(&info) == 0) {
        printf("Total RAM: %lu MB\n", info.totalram / 1024 / 1024);
        printf("Free RAM: %lu MB\n", info.freeram / 1024 / 1024);
        printf("Available RAM: %lu MB\n", info.freeram / 1024 / 1024);
    } else {
        perror("sysinfo");
        return 1;
    }

    if (statvfs("/", &stat) == 0) {
        unsigned long total = stat.f_blocks * stat.f_frsize;
        unsigned long free = stat.f_bfree * stat.f_frsize;
        unsigned long available = stat.f_bavail * stat.f_frsize;
        printf("Total disk space: %lu MB\n", total / 1024 / 1024);
        printf("Free disk space: %lu MB\n", free / 1024 / 1024);
        printf("Available disk space: %lu MB\n", available / 1024 / 1024);
    } else {
        perror("statvfs");
        return 1;
    }
    printf("=========================\n");
    return 0;
}