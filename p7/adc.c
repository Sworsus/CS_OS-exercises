#include "spi.h"
#include "adc.h"

#define ADC_START 0x40
#define ADC_SING  0x20
#define ADC_CHAN  0x10

int adc_read(unsigned int channel)
{
	int val;
	unsigned char frame[2];
	unsigned char dread[2];

	frame[0] = ADC_START | ADC_SING;

	if (channel > 1)
		return -1;

	if (channel)
		frame[0] |= ADC_CHAN;

	spi_send(frame, dread, 2);

	val = (((unsigned) dread[0] << 8) | ((unsigned) dread[1])) & 0x3FF;

	return val;
}

