// os.c
// Runs on Freescale k60 microcontrollers
// A very simple real time operating system with minimal features.
// Shoubhik Das
// Nov, 11, 2019

/* Thanks to Mr. Valvano for the book "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
 */

#include <stdint.h>
#include <stdarg.h>
#include "os.h"
#include "Drivers/SD_Clk.h"
/*
#define NVIC_ST_CTRL_R          (*((volatile uint32_t *)SysTick_BASE_PTR))
#define NVIC_ST_CTRL_CLK_SRC    SysTick_CSR_CLKSOURCE_MASK  										// Clock Source
#define NVIC_ST_CTRL_INTEN      SysTick_CSR_TICKINT_MASK  										// Interrupt enable
#define NVIC_ST_CTRL_ENABLE     SysTick_CSR_ENABLE_MASK  										// Counter mode
#define NVIC_ST_RELOAD_R        (*((volatile uint32_t *)SYST_RVR))
#define NVIC_ST_CURRENT_R       (*((volatile uint32_t *)SYST_CVR))
#define NVIC_INT_CTRL_R         (*((volatile uint32_t *)SCB_ICSR))
#define NVIC_INT_CTRL_PENDSTSET SCB_ICSR_PENDSTSET_MASK  										// Set pending SysTick interrupt
#define NVIC_SYS_PRI3_R         (*((volatile uint32_t *)SCB_SHPR3))  				// Sys. Handlers 12 to 15 Priority
*/

#define NVIC_ST_CTRL_R          CORE_SYS_TIM_CSR
#define NVIC_ST_CTRL_CLK_SRC    0x00000004  // Clock Source
#define NVIC_ST_CTRL_INTEN      0x00000002  // Interrupt enable
#define NVIC_ST_CTRL_ENABLE     0x00000001  // Counter mode
#define NVIC_ST_RELOAD_R        CORE_SYS_TIM_RVR
#define NVIC_ST_CURRENT_R       CORE_SYS_TIM_CVR
#define NVIC_INT_CTRL_R         CORE_SCB_ICSR
#define NVIC_INT_CTRL_PENDSTSET 0x04000000  // Set pending SysTick interrupt
#define NVIC_SYS_PRI3_R         CORE_SCB_SHPR3  // Sys. Handlers 12 to 15 Priority
#define CPU_MK60N512VMD100		1

// function definitions in osasm.s
void OS_DisableInterrupts(void); 													// Disable interrupts
void OS_EnableInterrupts(void);  													// Enable interrupts
int32_t StartCritical(void);
void EndCritical(int32_t primask);
void StartOS(void);

#define NUMTHREADS  5        // maximum number of threads
#define STACKSIZE   100      // number of 32-bit words in stack
struct tcb{
  int32_t *sp;       // pointer to stack (valid for threads not running
  struct tcb *next;  // linked-list pointer
};
typedef struct tcb tcbType;
tcbType tcbs[NUMTHREADS];
tcbType *RunPt;
int32_t Stacks[NUMTHREADS][STACKSIZE];

// ******** OS_Init ************
// initialize operating system, disable interrupts until OS_Launch
// initialize OS controlled I/O: systick, 50 MHz PLL
// input:  none
// output: none
uint8_t OS_Init(void){
uint8_t sys_freq;
  OS_DisableInterrupts();
   sys_freq = sys_clk_init(1);                 		// set processor clock to 100 MHz
  NVIC_ST_CTRL_R = 0;        					 	// disable SysTick during setup
  NVIC_ST_CURRENT_R = 0;      						// any write to current clears it
  NVIC_SYS_PRI3_R =(NVIC_SYS_PRI3_R & 0x00FFFFFF)|0xE0000000; // priority 7
	return sys_freq;
}

void SetInitialStack(int i){
  tcbs[i].sp = &Stacks[i][STACKSIZE-16]; // thread stack pointer
  Stacks[i][STACKSIZE-1] = 0x01000000;   // thumb bit
  Stacks[i][STACKSIZE-3] = 0x14141414;   // R14
  Stacks[i][STACKSIZE-4] = 0x12121212;   // R12
  Stacks[i][STACKSIZE-5] = 0x03030303;   // R3
  Stacks[i][STACKSIZE-6] = 0x02020202;   // R2
  Stacks[i][STACKSIZE-7] = 0x01010101;   // R1
  Stacks[i][STACKSIZE-8] = 0x00000000;   // R0
  Stacks[i][STACKSIZE-9] = 0x11111111;   // R11
  Stacks[i][STACKSIZE-10] = 0x10101010;  // R10
  Stacks[i][STACKSIZE-11] = 0x09090909;  // R9
  Stacks[i][STACKSIZE-12] = 0x08080808;  // R8
  Stacks[i][STACKSIZE-13] = 0x07070707;  // R7
  Stacks[i][STACKSIZE-14] = 0x06060606;  // R6
  Stacks[i][STACKSIZE-15] = 0x05050505;  // R5
  Stacks[i][STACKSIZE-16] = 0x04040404;  // R4
}

//******** OS_AddThread ***************
// add three foregound threads to the scheduler
// Inputs: three pointers to a void/void foreground tasks
// Outputs: 1 if successful, 0 if this thread can not be added
int OS_AddThreads(int num, .../*void(*task0)(void),
                 void(*task1)(void),
                 void(*task2)(void)*/)
{ 
	//void (*func_ptr[MAX_FUNC])();
	va_list valist;
	int32_t status;
	void (*func)();	
	uint8_t i;
	status = StartCritical();
	/* initialize valist for num number of arguments */
	va_start(valist, num);
	
	/* access all the arguments assigned to valist */
	for (i = 0; i < num; i++) 
	{
		if(i == (num -1))
			tcbs[i].next = &tcbs[0]; // 2 points to 0
		else
			tcbs[i].next = &tcbs[i+1]; // 0 points to 1
		func = va_arg(valist, void *);
		SetInitialStack(i); Stacks[i][STACKSIZE-2] = (int32_t)(func); // PC
		//sum += va_arg(valist, int);
	}
	
	/* clean memory reserved for valist 
	va_end(valist);
	for(i = 0; i < num; i++)
	{
		SetInitialStack(i); Stacks[i][STACKSIZE-2] = (int32_t)(func_ptr[i]); // PC
	}
		
	/*
	tcbs[0].next = &tcbs[1]; // 0 points to 1
	tcbs[1].next = &tcbs[2]; // 1 points to 2
	tcbs[2].next = &tcbs[0]; // 2 points to 0
	SetInitialStack(0); Stacks[0][STACKSIZE-2] = (int32_t)(task0); // PC
	SetInitialStack(1); Stacks[1][STACKSIZE-2] = (int32_t)(task1); // PC
	SetInitialStack(2); Stacks[2][STACKSIZE-2] = (int32_t)(task2); // PC*/
	RunPt = &tcbs[0];       // thread 0 will run first
	EndCritical(status);
	return 1;               // successful
}

///******** OS_Launch ***************
// start the scheduler, enable interrupts
// Inputs: number of 20ns clock cycles for each time slice
//         (maximum of 24 bits)
// Outputs: none (does not return)
void OS_Launch(uint32_t theTimeSlice){
  NVIC_ST_RELOAD_R = theTimeSlice - 1; // reload value
  NVIC_ST_CTRL_R |= (
						NVIC_ST_CTRL_CLK_SRC	|												//SysTick EXCEPTION
						NVIC_ST_CTRL_INTEN		|												//pROCESSOR CLK
						NVIC_ST_CTRL_ENABLE														//Enable counter
					); // enable, core clock and interrupt arm
  StartOS();                   // start on the first task
}
