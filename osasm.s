;/*****************************************************************************/
; OSasm.s: low-level OS commands, written in assembly                       */
; // Runs on Freescale k60 microcontrollers
; // A very simple real time operating system with minimal features.
; // Shoubhik Das
; // Nov, 11, 2019
; 
; /*
;       Thanks to Mr. Valvano for the book "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
; */

        AREA |.text|, CODE, READONLY, ALIGN=2
        THUMB
        REQUIRE8
        PRESERVE8

        EXTERN  RunPt            ; currently running thread
        EXPORT  OS_DisableInterrupts
        EXPORT  OS_EnableInterrupts
        EXPORT  StartOS
        EXPORT  SysTick_Handler


OS_DisableInterrupts
        CPSID   I
        BX      LR


OS_EnableInterrupts
        CPSIE   I
        BX      LR


SysTick_Handler                ; 1) Saves R0-R3,R12,LR,PC,PSR
    CPSID   I                  ; 2) Prevent interrupt during switch
    PUSH    {R4-R11}           ; 3) Save remaining regs r4-11
    LDR     R0, =RunPt         ; 4) R0=pointer to RunPt, old thread
    LDR     R1, [R0]           ;    R1 = RunPt
    STR     SP, [R1]           ; 5) Save SP into TCB
    LDR     R1, [R1,#4]        ; 6) R1 = RunPt->next
    STR     R1, [R0]           ;    RunPt = R1
    LDR     SP, [R1]           ; 7) new thread SP; SP = RunPt->sp;
    POP     {R4-R11}           ; 8) restore regs r4-11
    CPSIE   I                  ; 9) tasks run with interrupts enabled
    BX      LR                 ; 10) restore R0-R3,R12,LR,PC,PSR

StartOS
    LDR     R0, =RunPt         ; currently running thread
    LDR     R2, [R0]           ; R2 = value of RunPt
    LDR     SP, [R2]           ; new thread SP; SP = RunPt->stackPointer;
    POP     {R4-R11}           ; restore regs r4-11
    POP     {R0-R3}            ; restore regs r0-3
    POP     {R12}
    POP     {LR}               ; discard LR from initial stack
    POP     {LR}               ; start location
    POP     {R1}               ; discard PSR
    CPSIE   I                  ; Enable interrupts at processor level
    BX      LR                 ; start first thread

    ALIGN
    END
