#ifndef CONFIG_H
#define CONFIG_H

#include <termios.h>

// Buad rate
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

// Receiver device settings for open()
#define R_DEV_FLAGS  (O_RDWR | O_NOCTTY | O_NONBLOCK)

// Receiver control flags
#define R_CTRL_FLAGS (CS8 | PARENB | PARODD | CSTOPB | CREAD | CLOCAL)

// Sender device settings for open()
#define S_DEV_FLAGS  (O_RDWR | O_NOCTTY | O_NONBLOCK)

// Sender control flags
#define S_CTRL_FLAGS (CS8 | PARENB | PARODD | CSTOPB | CLOCAL)

#endif