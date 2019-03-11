#include "bcm2835.h"

#define LED_OFF 0
#define LED_ON 1
#define BUTTON_PUSHED 0
#define BUTTON_RELEASED 1
int led1, led2, led2_mode;

void led1_on(void){
    GPSET0 = 0x1 << 17;
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

int button_read1(void){
    int button1 = BUTTON_RELEASED;
    if ((GPLEV0 & (0x1 << 15)) == 0)
        button1 = BUTTON_PUSHED;
    return button1;
}

int button_read2(void){
    int button2 = BUTTON_RELEASED;
    if ((GPLEV0 & (0x1 << 23)) == 0)
        button2 = BUTTON_PUSHED;
    return button2;
}

void wait_150(void){
    int w;
    for (w=0; w<300; w++) {
        w++;
        w--;
    }
}

void setup_gpio(){
    // Configurar GPIO 17 como OUTPUT (001) --> L1
    GPFSEL1 = (GPFSEL1 & ~(0x7 << 7*3)) | (0x1 << 7*3);

    // Configurar GPIO 18 como OUTPUT (001) --> L2
    GPFSEL1 = (GPFSEL1 & ~(0x7 << 8*3)) | (0x1 << 8*3);

    // Configurar GPIO 15 como INPUT (000) --> P1
    GPFSEL1 = GPFSEL1 & ~(0x7 << 5*3);

    // Configurar GPIO 23 como INPUT (000) --> P2
    GPFSEL2 = GPFSEL2 & ~(0x7 << 3*3);

    // Activar el pull-up de los GPIO 22 y 23
    GPPUD = 0x2;
    wait_150();
    GPPUDCLK0 = ((0x1 << 15) | (0x1 << 23))
    wait_150();
    GPPUD = 0;
    GPPUDCLK0 = 0;
}

int main (void){
    setup_gpio();
	//Inicializar L1 y L2 a apagado
    led1_off();
    led2_off();

	while (1) {
		// Esperar a que se pulse P1 o P2
        while ((button_read1() == BUTTON_RELEASED) && (button_read2() == BUTTON_RELEASED));

		// Si se ha pulsado P1 cambiar el estado encendido/agapado de L1
        if(!button_read1()){
            led1_switch();
            led2_switch();
        }

		// Si se ha pulsado P2, conmutar el modo de L2 (igual o contrario de L1)

        // Actualizar el estado de encendido/apagado de L2
        if (!button_read2()){
            led2_switch();
        }
    }
    return 0;
}
