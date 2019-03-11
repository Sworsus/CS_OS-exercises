/*
#include "bcm2835.h"

#define LED_OFF 0
#define LED_ON 1

int led1, led2;

void led1_on(void){
    GPSET0 = (0x1 << 17);
    led1 = LED_ON;
}

void led2_on(void){
    GPSET0 = 0x1 << 18;
    led2 = LED_ON;
}

void led1_off(void){
    GPCLR0 = 0x1 << 17;
    led1 = LED_OFF;
}

void led2_off(void){
    GPCLR0 = 0x1 << 18;
    led2 = LED_OFF;
}

void led1_switch(void){
    if (led1 == LED_OFF)
        led1_on();
    else
        led1_off();
}

void led2_switch(void){
    if (led2 == LED_OFF)
        led2_on();
    else
        led2_off();
}

void short_wait(void){
	int w;
	for (w=0; w<100; w++) {
		w++;
		w--;
	}
}


void setup_gpio()
{
    // Configurar GPIO 17 como OUTPUT (001) --> L1
    GPFSEL1 = (GPFSEL1 & ~(0x7 << 7*3)) | (0x1 << 7*3);

    // Configurar GPIO 18 como OUTPUT (001) --> L2
    GPFSEL1 = (GPFSEL1 & ~(0x7 << 8*3)) | (0x1 << 8*3);

    // Configurar GPIO 15 como INPUT (000) --> P1
    GPFSEL1 = GPFSEL1 & ~(0x7 << 5*3);

    // Configurar GPIO 23 como INPUT (000) --> P2
    GPFSEL2 = GPFSEL2 & ~(0x7 << 3*3);

    // Activar detección de flanco de bajada para los GPIO 15 y 23
    GPFEN0 = ((0x1 << 15) | (0x1 << 23));

    // Activar el pull-up de los GPIO 15 y 23
    GPPUD = 0x2;
    short_wait();
    GPPUDCLK0 = ((0x1 << 15) | (0x1 << 23));
    short_wait();
    GPPUD = 0;
    GPPUDCLK0 = 0;

    // Habilitar las interrupciones gpio_int[0-3]
    IRQ_ENABLE_IRQS_2 = (0xF << 17);

    // Habilitar las irq en el cpsr (codigo ensamblador)
    enable_irq();
}

// Declaración de la ISR de la línea I (IRQ)
void isr_irq(void) __attribute__ ((interrupt ("IRQ")));

// Implementación de la ISR de la línea I
void isr_irq (void)
{
	// Si es interrupción de GPIO gpio_int[3]
    if (IRQ_PEND2 & (0x8 << 17)) {
		// Si es interrupción por GPIO15
        if (GPEDS0 & (0x1 << 15)) {
			// Conmutar los dos leds
            led1_switch();
            led2_switch();
            // Reconocemos la interrupción
            GPEDS0 = 0x1 << 15;
        }
		// Si es interrupción por GPIO23
        if (GPEDS0 & (0x1 << 23)) {
			// Conmutamos el led 2
            led2_switch();
            //Reconocemos la interrupción
            GPEDS0 = 0x1 << 23;
        }
    }
        // espera para eliminar rebotes
        short_wait();
}


int main (void)
{
    setup_gpio();

	//Inicializar L1 y L2 a apagado
    led1_off();
    led2_off();

	while (1);

    return 0;
}*/
