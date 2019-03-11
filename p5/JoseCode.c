CÓDIGO PRIMERA PARTE
#include "bcm2835.h"

int led1, led2, led2_mode;

#define LED_OFF 0
#define LED_ON 1
#define BUTTON_PUSHED 0
#define BUTTON_RELEASED 1


void led1_on(void){


	GPSET0 = 0x1 << 17;
	led1 = LED_ON;

}
void led1_off(void){

	GPCLR0 = 0x1 << 17;

	led1 = LED_OFF;
}
void led2_on(void){


	GPSET0 = 0x1 << 18;
	led2 = LED_ON;

}

void led2_off(void){

	GPCLR0 = 0x1 << 18;

	led2 = LED_OFF;
}

void ledP1_switch(void){ // Esto es presionar P1, porque va a cambiar el estado si o si cuando presiones,
	//aunque esten en distinto estado

if (led1 == LED_OFF)
	led1_on();
else
	led1_off();

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}
void ledP2_switch(void){ // Esto es presionar P2, porque va a cambiar L2 únicamente

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}

int button1_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 15)) == 0)
	button = BUTTON_PUSHED;
return button;
}

int button2_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 23)) == 0)
	button = BUTTON_PUSHED;
return button;
}

void short_wait(void){

	int w;

	for (w=0; w<150; w++) { //EN LAS TRANSPARENCIAS PONÍA QUE SE DEBE ESPERAR 150 CICLOS PERO SOLO ESPERAMOS 100
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

    // Activar el pull-up de los GPIO 15 y 23
		GPPUD = 0x2;
		short_wait();
		GPPUDCLK0 = (0x1 << 15);
		GPPUDCLK0 = (0x1 << 23);
		short_wait();
		GPPUD = 0;
		GPPUDCLK0 = 0;
}

int main (void) {
    setup_gpio();
    int but1_state=1;
    int but2_state=1;
	//Inicializar L1 y L2 a apagado
	led1_off();
	led2_off();

	while (1) {
		do{

			but1_state=button1_read();
			but2_state=button2_read();
		}while((but1_state==BUTTON_RELEASED) && (but2_state==BUTTON_RELEASED)); // Esperar a que se pulse P1 o P2


		if(but1_state !=BUTTON_RELEASED)
			ledP1_switch(); // Si se ha pulsado P1 cambiar el estado encendido/agapado de L1

	if(but2_state != BUTTON_RELEASED)
ledP2_switch();// Si se ha pulsado P2, conmutar el modo de L2 (igual o contrario de L1)
		// Actualizar el estado de encendido/apagado de L2
	}


    return 0;
}


CÓDIGO SEGUNDA PARTE
#include "bcm2835.h"

int led1, led2, led2_mode;

#define LED_OFF 0
#define LED_ON 1
#define BUTTON_PUSHED 0
#define BUTTON_RELEASED 1


void led1_on(void){


	GPSET0 = 0x1 << 17;
	led1 = LED_ON;

}
void led1_off(void){

	GPCLR0 = 0x1 << 17;

	led1 = LED_OFF;
}
void led2_on(void){


	GPSET0 = 0x1 << 18;
	led2 = LED_ON;

}

void led2_off(void){

	GPCLR0 = 0x1 << 18;

	led2 = LED_OFF;
}

void ledP1_switch(void){ // Esto es presionar P1, porque va a cambiar el estado si o si cuando presiones,
	//aunque esten en distinto estado

if (led1 == LED_OFF)
	led1_on();
else
	led1_off();

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}
void ledP2_switch(void){ // Esto es presionar P2, porque va a cambiar L2 únicamente

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}

int button1_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 15)) == 0)
	button = BUTTON_PUSHED;
return button;
}

int button2_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 23)) == 0)
	button = BUTTON_PUSHED;
return button;
}

int button3_read(int button){

	if ((GPLEV0 & (0x1 << 14)) == 0){
		if(button==BUTTON_PUSHED){
			button=BUTTON_RELEASED;
	}
		else{
			button = BUTTON_PUSHED;
		}
if(button==BUTTON_PUSHED){
	button=0;
}
	}
return button;
}
void short_wait(void){

	int w;

	for (w=0; w<150; w++) { //EN LAS TRANSPARENCIAS PONÍA QUE SE DEBE ESPERAR 150 CICLOS PERO SOLO ESPERAMOS 100
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
	// Configurar GPIO 14 como INPUT (000) --> P2
		GPFSEL1 = GPFSEL1 & ~(0x7 << 4*3);

    // Activar el pull-up de los GPIO 15, 23 y 14
		GPPUD = 0x2;
		short_wait();
		GPPUDCLK0 = (0x1 << 15);
		GPPUDCLK0 = (0x1 << 23);
		GPPUDCLK0 = (0x1 << 14);
		short_wait();
		GPPUD = 0;
		GPPUDCLK0 = 0;
}

int main (void) {
    setup_gpio();
    int but1_state=1;
    int but2_state=1;
    int but3_state=1;
	//Inicializar L1 y L2 a apagado
	led1_off();
	led2_off();

	while (1) {
		do{

			but1_state=button1_read();
			but2_state=button2_read();
			but3_state=button3_read(but3_state);

		}while((but1_state==BUTTON_RELEASED) && (but2_state==BUTTON_RELEASED) && (but3_state==BUTTON_RELEASED)); // Esperar a que se pulse P1 o P2


		if(but1_state !=BUTTON_RELEASED)
			ledP1_switch(); // Si se ha pulsado P1 cambiar el estado encendido/agapado de L1
		if(but2_state != BUTTON_RELEASED){
			if(but3_state == BUTTON_RELEASED)
				ledP2_switch();		// Si se ha pulsado P2, conmutar el modo de L2 (igual o contrario de L1)
		}
		// Actualizar el estado de encendido/apagado de L2
	}
	shorwait();

    return 0;
}

CÓDIGO TERCERA PARTE
#include "bcm2835.h"

int led1, led2, led2_mode, estadoled1, estadoled2;

#define LED_OFF 0
#define LED_ON 1
#define BUTTON_PUSHED 0
#define BUTTON_RELEASED 1


void led1_on(void){


	GPSET0 = 0x1 << 17;
	led1 = LED_ON;

}
void led1_off(void){

	GPCLR0 = 0x1 << 17;

	led1 = LED_OFF;
}
void led2_on(void){


	GPSET0 = 0x1 << 18;
	led2 = LED_ON;

}

void led2_off(void){

	GPCLR0 = 0x1 << 18;

	led2 = LED_OFF;
}

void ledP1_switch(void){ // Esto es presionar P1, porque va a cambiar el estado si o si cuando presiones,
	//aunque esten en distinto estado

if (led1 == LED_OFF)
	led1_on();
else
	led1_off();

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}
void ledP2_switch(void){ // Esto es presionar P2, porque va a cambiar L2 únicamente

if (led2 == LED_OFF)
	led2_on();
else
	led2_off();
}
int ledP31_switch(int estado1){ // Esto es presionar P1, porque va a cambiar el estado si o si cuando presiones,
	//aunque esten en distinto estado

if (estado1 == LED_OFF)
	estado1=LED_OFF;
else
	estado1=LED_ON;

	return estado1;
}
int ledP32_switch(int estado2){ // Esto es presionar P1, porque va a cambiar el estado si o si cuando presiones,
	//aunque esten en distinto estado

if (estado2 == LED_OFF)
	estado2=LED_OFF;
else
	estado2=LED_ON;

	return estado2;
}

int button1_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 15)) == 0)
	button = BUTTON_PUSHED;
return button;
}

int button2_read(void){

int button = BUTTON_RELEASED;
if ((GPLEV0 & (0x1 << 23)) == 0)
	button = BUTTON_PUSHED;
return button;
}

int button3_read(int button){
	if ((GPLEV0 & (0x1 << 14)) == 0){
		if(button==BUTTON_PUSHED){
			button=BUTTON_RELEASED;

			if(estadoled1==LED_ON)
				led1_on();
			else
				led1_off();

			if(estadoled2==LED_ON)
				led2_on();
			else
				led2_off();
			//AQUI DEBE DEVOLVER LOS ESTADOS
	}
		else{
			button = BUTTON_PUSHED;
			estadoled1=ledP31_switch(led1);
			estadoled2=ledP32_switch(led2);
			led1_on();
			led2_on();
		}
if(button==BUTTON_PUSHED){
	button=0;
}
	}
return button;
}
void short_wait(void){

	int w;

	for (w=0; w<150; w++) { //EN LAS TRANSPARENCIAS PONÍA QUE SE DEBE ESPERAR 150 CICLOS PERO SOLO ESPERAMOS 100
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
	// Configurar GPIO 14 como INPUT (000) --> P2
		GPFSEL1 = GPFSEL1 & ~(0x7 << 4*3);

    // Activar el pull-up de los GPIO 15, 23 y 14
		GPPUD = 0x2;
		short_wait();
		GPPUDCLK0 = (0x1 << 15);
		GPPUDCLK0 = (0x1 << 23);
		GPPUDCLK0 = (0x1 << 14);
		short_wait();
		GPPUD = 0;
		GPPUDCLK0 = 0;
}

int main (void) {
    setup_gpio();
    int but1_state=1;
    int but2_state=1;
    int but3_state=1;
	//Inicializar L1 y L2 a apagado
	led1_off();
	led2_off();

	while (1) {
		do{

			but1_state=button1_read();
			but2_state=button2_read();
			but3_state=button3_read(but3_state);



		}while((but1_state==BUTTON_RELEASED) && (but2_state==BUTTON_RELEASED) && (but3_state==BUTTON_RELEASED)); // Esperar a que se pulse P1 o P2


		if(but1_state !=BUTTON_RELEASED){
			if(but3_state == BUTTON_RELEASED)
				ledP1_switch();
			}// Si se ha pulsado P1 cambiar el estado encendido/agapado de L1
		if(but2_state != BUTTON_RELEASED){
			if(but3_state == BUTTON_RELEASED)
				ledP2_switch();		// Si se ha pulsado P2, conmutar el modo de L2 (igual o contrario de L1)
		}
		// LED_OFF 0
		// LED_ON 1
		// Actualizar el estado de encendido/apagado de L2
		short_wait();
	}


    return 0;
}
