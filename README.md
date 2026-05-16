# Linux UART Interface using `termios`
A C program that initializes and configures a UART interface on Linux using the termios

## Configuration
You can configure the UART interface in `config.h`

## Build

```bash
$ gcc recv_prog.c uart_if.c -o recv_prog
$ gcc send_prog.c uart_if.c -o send_prog
```

## Run

```bash
./recv_prog "/dev/tty0"
./send_prog "Hello, World!" "/dev/tty0"
```
