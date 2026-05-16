#ifndef CONFIG_H
#define CONFIG_H

#include <termios.h>

#define SPEED B19200

// O_RDWR    : Open port for reading/writing
// O_NOCTTY  : Block port from controlling the process
// O_NONBLOCK: Non-blocking I/O
// CS8   : 8 data bits
// PARENB: enable parity checking
// PARODD: enable odd parity
// CREAD : Enable receiver
// CSTOPB: use 2 stop bits
// CLOCAL: Ignore modem control lines

#define R_DEV_FLAGS  (O_RDWR | O_NOCTTY | O_NONBLOCK)
#define R_CTRL_FLAGS (CS8 | PARENB | PARODD | CSTOPB | CREAD | CLOCAL)
#define S_DEV_FLAGS  (O_RDWR | O_NOCTTY | O_NONBLOCK)
#define S_CTRL_FLAGS (CS8 | PARENB | PARODD | CSTOPB | CLOCAL)

#endif