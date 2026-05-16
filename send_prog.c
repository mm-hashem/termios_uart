#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <err.h>
#include "uart_if.h"
#include "config.h"

int main(int argc, char *argv[]) {
    struct termios config;
    int fd;
    
    if (argc < 3)
        err(EXIT_FAILURE, "Usage: %s <message> <device>", argv[0]);

    char *msg = argv[1];
    size_t msg_size = strlen(msg);
    char *device = argv[2]; 
    
    fd = open_dev(device, S_DEV_FLAGS);

    if (fd == -1)
        err(EXIT_FAILURE, "Failed to open device %s", device);
    else if (errno == ENOTTY)
        err(EXIT_FAILURE, "The file descriptor is not pointing to a TTY device\n");

    printf("Opened \"%s\" on fd %d\n", device, fd);

    if (get_config(fd, &config) < 0)
        err(EXIT_FAILURE, "Error getting the config");

    int cfg_ret = config_dev(fd, &config, S_CTRL_FLAGS, SPEED);

    if (cfg_ret == -1)
        err(EXIT_FAILURE, "Error in configuring the device");

    if (send_msg(fd, msg, msg_size) == -1)
        err(EXIT_FAILURE, "Couldn't send the message");

    exit(EXIT_SUCCESS);
}