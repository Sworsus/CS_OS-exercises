#include "bcm2835.h"

#define LED_OFF 0
#define LED_ON 1

int led1, led2, led3, N, D;

void enable_irq(void);

void led1_on(void){
    GPSET0 = (0x1 << 17);
    led1 = LED_ON;
}

void led2_on(void){
    GPSET0 = 0x1 << 18;
    led2 = LED_ON;
}

void led3_on(void){
    GPSET0 = 0x1 << 14;
    led3 = LED_ON;
}

void led1_off(void){
    GPCLR0 = 0x1 << 17;
    led1 = LED_OFF;
}

void led2_off(void){
    GPCLR0 = 0x1 << 18;
    led2 = LED_OFF;
}

void led3_off(void){
    GPCLR0 = 0x1 << 14;
    led3 = LED_OFF;
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

void led3_switch(void){
    if (led3 == LED_OFF)
        led3_on();
    else
        led3_off();
}

void T_2s(void){
    N=500000;
    D=999;
}

void T_1s(void){
    N=250000;
    D=999;
}

void T_05s(void){
    N=125000;
    D=999;
}

void T_025s(void){
    N=125000;
    D=499;
}

void setup_timer(void){
    ARM_TIMER_LOD = N; //N
    ARM_TIMER_DIV = D; //D
    ARM_TIMER_CLI = 0;
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

    // Configuramos el GPIO 14 como OUTPUT (001) --> L3
    GPFSEL1 = (GPFSEL1 & ~(0x7 << 4*3)) | (0x1 << 4*3);

    // Configurar GPIO 15 como INPUT (000) --> P1
    GPFSEL1 = GPFSEL1 & ~(0x7 << 5*3);

    // Configurar GPIO 23 como INPUT (000) --> P2
    GPFSEL2 = GPFSEL2 & ~(0x7 << 3*3);

    // Configuraramos GPIO 11 como INPUT (000) --> P3
    GPFSEL1 = GPFSEL1 & ~(0x7 << 1*3);

    // Activar detección de flanco de bajada para los GPIO 15 y 23
    GPFEN0 = ((0x1 << 15) | (0x1 << 23) | (0x1 << 11));

    // Activar el pull-up de los GPIO 15 y 23
    GPPUD = 0x2;
    short_wait();
    GPPUDCLK0 = ((0x1 << 15) | (0x1 << 23) | (0x1 << 11));
    short_wait();
    GPPUD = 0;
    GPPUDCLK0 = 0;

    //SetupTimer
    setup_timer();

    //Pre-escalado=1, contador de 23 bits, habilitamos timer e interrupciones
    ARM_TIMER_CTL = ARM_TIMER_ENABLE | ARM_TIMER_IRQ_ENABLE | ARM_TIMER_23b;
    //Habilitamos interrupciones del timer
    IRQ_ENABLE_BASIC = 0x1;

    // Habilitar las interrupciones gpio_int[0-3]
    IRQ_ENABLE_IRQS_2 = (0x8 << 17);

    // Habilitar las irq en el cpsr (codigo ensamblador)
    enable_irq();
}

// Declaración de la ISR de la línea I (IRQ)
void isr_irq(void) __attribute__ ((interrupt ("IRQ")));

// Implementación de la ISR de la línea I
void isr_irq (void)
{
	if(IRQ_BASIC & 0x1){
		//interrupcion del timer
		led3_switch();
		//reconocemos la interrupcion
		ARM_TIMER_CLI = 0x1;
	}
	// Si es interrupción de GPIO gpio_int[3]
	else if (IRQ_PEND2 & (0x8 << 17)) {
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
        // Si es interrupción por GPIO13
        if (GPEDS0 & (0x1 << 11)) {
			// Cambiamos el valor de N y/o D
            switch (N) {
                case 500000:
                    T_1s(); //T=1s
                    break;
      		    case 250000:
                    T_05s(); //T=0.5s
                    break;
      			case 125000:
                    if(D==999)
                        T_025s(); //T=0.25s
                    else if(D==499)
                        T_2s(); //T=2s
                    break;
            }
            setup_timer();
            //Reconocemos la interrupción
            GPEDS0 = 0x1 << 11;
        }
        // espera para eliminar rebotes
        short_wait();
    }

}


int main (void)
{
	//Inicializo las componentes N y D para T=2s
	T_2s();

    setup_gpio();

	//Inicializar L1 y L2 a apagado
    led1_off();
    led2_off();
    led3_off();

	while (1);

    return 0;
}
