#ifndef _UART1_H_
#define _UART1_H_

// Rutina que configura la mini UART
void setup_uart1(void);

// Rutina que recibe datos por la UART1 (mini UART)
void irq_uart1(void);

// Rutina para escribir un caracter en uart1
unsigned int uart1_getc(void);

// Rutina para leer una línea terminada en \r
int uart1_readline(char *buf, int n);

// Rutina para escribir un caracter en uart1
void uart1_putc(unsigned int c);

// Envía una cadena terminada en \0 por la uart1
int uart1_putstr(char *str);

// Envía una cadena con formato por la uart1
int uart1_printf(char *fmt, ...);

#endif
