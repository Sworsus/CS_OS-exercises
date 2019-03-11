#ifndef SPI_H_
#define SPI_H_

int setup_spi(int cpol, int cpha, int cs, int div);

void spi_send(unsigned char *ds, unsigned char *dr, int n);

#endif /* SPI_H_ */
