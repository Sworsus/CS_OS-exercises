.global complementarioRGB

.equ N, 128
.equ M, 128
.extern complementario

.text

complementarioRGB:
      push {r4-r11,lr}

      mov r6, r0     @me da  la primera posicion de la "matriz orig"
      mov r4, #0     @i=0
      mov r9, #M
      mov r10, #3

forFilas:
      cmp r4, #N
      bge termina

      mov r5, #0     @j=0

forColumnas:
      cmp r5, #M
      bge im1

      mla r0, r4, r9, r5
      mul r0, r0, r10
      ldrb r0, [r6, r0]      @guarda en r0 la informaci�n contenida en r0 (orig[i][j].R)

      bl complementario
      mov r8, r0
      mla r0, r4, r9, r5
      mul r0, r0, r10
      strb r8, [r6, r0]


      mla r0, r4, r9, r5
      mul r0, r0, r10
      add r0, r0, #1
      ldrb r0, [r6, r0]      @orig[i][j].G

      bl complementario
      mov r8, r0
      mla r1, r4, r9, r5
      mov r11, r1
      add r1, r1, r11
      add r1, r1, r11
      add r1, r1, #1
      strb r8, [r6, r0]

      mla r2, r4, r9, r5
      mov r11, r2
      add r2, r2, r11
      add r2, r2, r11
      add r2, r2, #2
      ldrb r2, [r6, r2]      @orig[i][j].B

      bl complementario
      mov r8, r0
      mla r2, r4, r9, r5
      mov r11, r2
      add r2, r2, r11
      add r2, r2, r11
      add r2, r2, #2
      mla r0, r4, r9, r5
      strb r8, [r7, r0]

      add r5, r5, #1
      b forColumnas

im1:
      add r4, r4, #1
      b forFilas

termina:
      pop {r4-r11,lr}
      mov pc, lr
      .end
