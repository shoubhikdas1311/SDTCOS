// os.h
// Runs on Freescale k60 microcontrollers
// A very simple real time operating system with minimal features.
// Shoubhik Das
// Nov, 11, 2019

/* Thanks to Mr. Valvano for the book "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
 */

#ifndef __OS_H
#define __OS_H  1


#include "Core/coreHAL.h"
// fill these depending on your clock
#define TIME_1MS  500
#define TIME_2MS  2*TIME_1MS

//#define MAX_FUNC										10

// ******** OS_Init ************
// initialize operating system, disable interrupts until OS_Launch
// initialize OS controlled I/O: systick, 50 MHz PLL
// input:  none
// output: none
uint8_t OS_Init(void);

//******** OS_AddThread ***************
// add three foregound threads to the scheduler
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(int tasks, ...);



//******** OS_Launch ***************
// start the scheduler, enable interrupts
// Inputs: number of 20ns clock cycles for each time slice
//         (maximum of 24 bits)
// Outputs: none (does not return)
void OS_Launch(uint32_t theTimeSlice);

#endif
