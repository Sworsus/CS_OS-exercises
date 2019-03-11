## Configuraci—n del Makefile
.SUFFIXES:
.SUFFIXES: .c .s .o

## Variables del Makefile
CROSS_COMPILE = arm-none-eabi-

CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
LD = $(CROSS_COMPILE)ld

CFLAGS = -Wall -g -nostdlib -nostartfiles -ffreestanding 
ASFLAGS = -Wall -g

#-- Comienzo parte configurable
# 	programa que se desea generar
TARGET = main.elf
# 	ficheros objeto que requiere (separados por espacios si hay m‡s de uno)
OBJ = init.o main.o
#-- Fin parte configurable 

## Reglas del Makfile 
all : $(TARGET)

%.elf: $(OBJ) memmap
	$(LD) $(OBJ) -T memmap -o $@

clean:
	rm $(TARGET)

