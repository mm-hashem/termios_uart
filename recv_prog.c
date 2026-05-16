#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <poll.h>
#include <string.h>
#include <err.h>
#include "uart_if.h"
#include "config.h"

int main(int argc, char *argv[]) {
    struct termios config;
    ssize_t rd_size;
    char buf[20];
    size_t buf_size = sizeof(buf);
    int fd, ready,
        open_devs = 0;

    // Return if there are no commandline arguments
    if (argc < 2)
        err(EXIT_FAILURE, "Usage: %s <device>\n", argv[0]);

    char *device = argv[1]; 
    
    // Open the 
    fd = open_dev(device, R_DEV_FLAGS);

    if (fd == -1)
        err(EXIT_FAILURE, "Failed to open device %s", device);
    else if (errno == ENOTTY)
        err(EXIT_FAILURE, "The file descriptor is not pointing to a TTY device\n");

    open_devs = 1;

    printf("Opened \"%s\" on fd %d\n", device, fd);

    if (get_config(fd, &config) == -1)
        err(EXIT_FAILURE, "Couldn't get the config");

    int cfg_ret = config_dev(fd, &config, R_CTRL_FLAGS, SPEED);

    if (cfg_ret == -1)
        err(EXIT_FAILURE, "Error in configuring the device");

    struct pollfd pfd = {
        .fd = fd,
        .events = POLLIN
    };

    while (open_devs > 0) {
        printf("Polling\n");
        ready = poll(&pfd, 1, 1000);

        if (errno == EAGAIN || errno == EWOULDBLOCK) {
            continue; 
        } else if (ready == -1)
            err(EXIT_FAILURE, "poll");

        printf("Ready: %d\n", ready);

        if (pfd.revents != 0) {
            printf("events: %s%s\n",
                    (pfd.revents & POLLHUP) ? "POLLHUP " : "",
                    (pfd.revents & POLLERR) ? "POLLERR " : "");

            if (pfd.revents & POLLIN) {
                printf("Event: POLLIN\n");

                rd_size = read_dev(fd, buf, buf_size); 
                
                if (rd_size == -1) {
                    close(fd);
                    err(EXIT_FAILURE, "read");
                }

                printf("read %zd bytes: %.*s\n", rd_size, (int) rd_size, buf);

            } else { /* POLLERR | POLLHUP */
                printf("Events: %s%s\n",
                    (pfd.revents & POLLHUP) ? "POLLHUP " : "",
                    (pfd.revents & POLLERR) ? "POLLERR " : "");

                printf("Closing fd %d\n", pfd.fd);

                if (close(pfd.fd) == -1)
                    err(EXIT_FAILURE, "close");

                open_devs = 0;
            }
        }
    }
    exit(EXIT_SUCCESS);
}