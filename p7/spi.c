#include "bcm2835.h"
#include "spi.h"
#include "_aux.h"
#include "uart1.h"

int setup_spi(int cpol, int cpha, int cs, int div)
{
	unsigned int spi_cs = 0x0;

	if (cs > 2)
		return -1;

	//Configurar los pines GPIO 7,8,9,10,11 (función ALT0)

	// Desactivar resistencias pull-up/down para estos GPIOs


	// Escribimos la configuración del registro SPI_CS en la variable spi_cs en
	// función de los parámetros de entrada
	if (cpol)
		// activar bit SPI_CS_POL

	if (cpha)
		// activar bit SPI_CS_CPHA

	if (cs == 1)
		// activar bit SPI_CS_CS0

	if (cs == 2)
		// activar bit SPI_CS_CS1

	// Escribir la configuración de spi_cs en el SPI_CS

	// Configuramos el divisor de reloj a partir de div

	return 0;
}

void spi_send(unsigned char *ds, unsigned char *dr, int n)
{
   int bsent = 0, brcvd = 0;
   // Borrar fifos: poner a 1 simultaneamente los bits
   //    CLEAR_TX CLEAR_RX y TA en CS
    while (bsent != n) {
        // 1. Esperar a que haya un hueco en la FIFO de TX
        // 2. Escribir el siguiente byte de ds en TX FIFO
        while (haya bytes en la RX FIFO) {
            // Leer un byte de RX FIFO y añadirlo a dr
        }
    }
    while (bsent < brcvd) {
        // 1. Esperar a que haya un byte en la RX FIFO
        // 2. Leer un byte de RX FIFO y añadirlo a dr
    }
    // Esperar a que finalice la operación (bit DONE en CS)
    // Marcar la operación como finalizada (bit TA en CS)
}
