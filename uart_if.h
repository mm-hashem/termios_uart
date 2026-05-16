#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

#include <unistd.h>
#include <termios.h>

int open_dev(const char dev[], int flags);
int get_config(int fd, struct termios *cfg);
int config_dev(int fd, struct termios *cfg, int CFLAGS, speed_t speed);
ssize_t send_msg(int fd, const char msg[], size_t msg_size);
ssize_t read_dev(int fd, char *buf, size_t buf_size);

#endif