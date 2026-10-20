
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/syslog.h>
#include <syslog.h>

#include <fcntl.h>
#include <unistd.h>


int main(int num, char** args) {
    openlog("Writer", LOG_PID, LOG_USER);

    if (num != 3) {
        syslog(LOG_ERR, "less than 2 arguments");
        return 1;
    }

    const char* file = args[1];
    const char* string = args[2];
    ssize_t strLen = strlen(string);

    int fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0644);
    
    if (fd < 0) {
        syslog(LOG_ERR, "Unable to open file, %s", strerror(errno));
        return 1;
    }

    ssize_t len = write(fd, string, strLen);
    if (len < 0) {
        syslog(LOG_ERR, "unable to write, %s", strerror(errno));
        close(fd);
        return -1;
    } else if (len != strLen) {
        syslog(LOG_WARNING, "Wrtie only part of data");
    }

    close(fd);

    syslog(LOG_DEBUG, "Writing %s to %s", string, file);

    return 0;
}