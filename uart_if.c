#include <termios.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int open_dev(const char dev[], int flags) {
    int fd = open(dev, flags);

    if (fd == -1)
        return -1;

    if (!isatty(fd))
        return -1;
    
    return fd;
}

int get_config(int fd, struct termios *cfg) {
    return tcgetattr(fd, cfg);
}

int config_dev(int fd, struct termios *cfg, int CFLAGS, speed_t speed) {

    // Convert configuration to raw mode
    cfmakeraw(cfg);

    cfg->c_cflag &= ~CSIZE; // Mask the data size
    cfg->c_cflag |= CFLAGS;

    if(cfsetispeed(cfg, speed) == -1)
        return -1;

    if(cfsetospeed(cfg, speed) == -1)
        return -1;

    if(tcsetattr(fd, TCSANOW, cfg) == -1) 
        return -1;
    
    return 1;
}

ssize_t send_msg(int fd, const char msg[], size_t msg_size) {
    return write(fd, msg, msg_size);
}

ssize_t read_dev(int fd, char *buf, size_t buf_size) {
    return read(fd, buf, buf_size);
}