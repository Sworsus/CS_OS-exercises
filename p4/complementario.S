      .global complementario
      .text
complementario:
      push {r4-r11,lr}
      mov r4, r0
      mov r5, 0xFF

      EOR r0, r4, r5
      AND r0, r0, r5

      pop {r4-r11,lr}
      mov pc, lr

      .end
