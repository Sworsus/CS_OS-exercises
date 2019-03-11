	.global rgb2gray

	.equ COEF1, 3483
	.equ COEF2, 11718
	.equ COEF3, 1183

	.text

rgb2gray:
  		ldr r3, =COEF1
  		mul r0, r3, r0
  		ldr r3, =COEF2
  		mla r0, r3, r1, r0
  		ldr r3, =COEF3
  		mla r0, r3, r2, r0
  		mov r0, r0, lsr #14

  		mov pc, lr

  		.end
