@-----------------------------------------------
@ init.s
@
@ 	Esquema inicial para uso de C
@
@-----------------------------------------------

			.global start
			
			.equ STACK, 0x8000 @ valor inicial del puntero de pila
			.extern main	   @ declaraci�n de s�mbolo externo
			
			.text 
start:		ldr sp,	=STACK  @ inicializaci�n de la pila
			mov fp, #0		@ inicializaci�n del frame pointer (opcional)
			bl main			@ salto a la funci�n principal
fin: 		b . 			@ bucle infinito

			.end


