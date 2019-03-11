#include "bcm2835.h"
#include "uart1.h"
#include "console.h"
#include "spi.h"
#include "_aux.h"

// Rutina de bajo nivel para habilitar la línea IRQ en el CPSR (init.s)
extern void enable_irq (void);

// Rutinas de gestión de interrupciones
void isr_irq(void) __attribute__ ((interrupt ("IRQ")));

// Rutina de tratamiento de la línea de interrupci￳n IRQ
void isr_irq(void)
{
    if (/* Hay interrupción pendiente del módulo AUX */){

    	// Mini UART irq?
    	if (/* Si es la mini UART */)
        	irq_uart1();
    }

}

//-------------------------------------------------------------------------
// Función main
//-------------------------------------------------------------------------
int main(void)
{
	// Configuración de la UART1 (mini UART)
	setup_uart1();

	// Configurar SPI con los parámetros adecuados (ver hoja de características
	// del MSP3002)
	//setup_spi(/* Elegir los parámetros */);

	//Habilitar IRQ (codigo ensamblador en init.s)
	enable_irq();

	console();

    return 0;
}
