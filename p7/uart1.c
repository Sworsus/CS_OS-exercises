#include "uart1.h"
#include "bcm2835.h"
#include "_aux.h"
#include <stdarg.h>
#include <stdio.h>


// Buffer de recepción
#define RXBUFMASK 0xFFF
static volatile unsigned int rxhead;
static volatile unsigned int rxtail;
static unsigned char rxbuffer[RXBUFMASK+1];
static int echo = 1;
static int ocrnl = 1;
static int onlcr = 1;

static void setup_uart_pins(void)
{
    // Configurar GPIO 14 como ALT5 (010) - TXD1

	// Configurar GPIO 15 como ALT5 (010) - RXD1

	// Desactivar resistencias pull-up/down para estos GPIOs
}

// Rutina que configura la mini UART
void setup_uart1(void)
{
	// Inicizalizar el buffer de recepción y el contador caracteres
	rxhead = rxtail = 0;
	//echo = ocrnl = icrnl = 1;

    // Habilitar mini UART

    // Antes de configurar:
    // Deshabilitar interrupciones rx y tx (atención: errara p12)
    // Deshabilitar emisor y receptor (atención: p17 del manual)
    // Borrar FIFOs

    setup_uart_pins();

    // Configurar: 115200, 8bits sin control de flujo (por defecto sin paridad)
    // Modo 8-bits (atención: errata p14 del manual)
    // Establecer velocidad (pp. 19 BCM2835 ARM Peripherals)

    // Activar mini UART:
    // Habilitar interrupciones rx (atención: errara p12)
    // Habilitar emisor y receptor (atención: p17 del manual)

	// Habilita las interrupciones AUX
}

void uart1_rxint()
{
    unsigned char c;
    while (AUX_MU_LSR_REG & 0x1) {
		// Mover dato de la FIFO al buffer

		//echo del caracter
		if (echo)
			uart1_putc(c);
    }
}

// Tratamiento de interrupciones de la mini uart
void irq_uart1()
{
    unsigned int r;
    unsigned char c;
    if (/* Es interrupción de recepción */) {
    	uart1_rxint();
    } else if (/* Es interrupción de envío */) {
    	// no hacemos nada
    }
}

//-------------------------------------------------------------------------
// Funciones lectura/escritura serie
//-------------------------------------------------------------------------

// Rutina para escribir un caracter en uart1
unsigned int uart1_getc()
{
	unsigned int c;

	// Esperar a que haya datos
	while (/* buffer vacío */);

	// Si los hay, leer caracter y avanzar una posición en el buffer

	return c;
}

int uart1_readline(char *buf, int n)
{
	char c;
	int num = 0;

	do {
		c = uart1_getc() & 0xFF;
		*buf++ = c;
		num++;
	} while ((c != '\r') && (num < (n-1)));
	*buf = '\0';
	return num;
}

void uart1_write(char c)
{
    // Esperar a que se pueda escribir en la FIFO de envio (transmitter empty)
	while(/* no quede hueco en la fifo de transmisión */ );

	// Escribir el caracter
}
// Rutina para escribir un caracter en uart1
void uart1_putc(unsigned int c)
{
	//conversión \n a \r\n de salida
	if (onlcr && c == '\n')
		uart1_write('\r');

	uart1_write(c);
	//conversión \r a \r\n de salida
	if (ocrnl && c == '\r')
		uart1_write('\n');
}

int uart1_putstr(char *str)
{
	int n = 0;

	while (*str) {
		uart1_putc(*str++);
		n++;
	}

	return n;
}

int uart1_printf(char *fmt, ...)
{
    va_list ap;
    char str[256];
    int n;

    va_start(ap, fmt);
    vsnprintf(str, 256, fmt, ap);
    n = uart1_putstr(str);
    va_end(ap);
    return n;
}
