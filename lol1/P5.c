#include "bcm2835.h"

int led1, led2, led2_mode;

void setup_gpio()
{
    // Configurar GPIO 17 como OUTPUT (001) --> L1
	
    // Configurar GPIO 18 como OUTPUT (001) --> L2
	
    // Configurar GPIO 22 como INPUT (000) --> P1
	
    // Configurar GPIO 23 como INPUT (000) --> P2
	

    // Activar el pull-up de los GPIO 22 y 23
} 

int main (void) 
{
    setup_gpio();

	//Inicializar L1 y L2 a apagado
	
	while (1) {
		// Esperar a que se pulse P1 o P2
		
		// Si se ha pulsado P1 cambiar el estado encendido/agapado de L1
		// Si se ha pulsado P2, conmutar el modo de L2 (igual o contrario de L1)
		// Actualizar el estado de encendido/apagado de L2
	}


    return 0;
}
