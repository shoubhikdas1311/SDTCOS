/*
 * main implementation: use this 'C' sample to create your own application
 *
 */

#include "main.h" /* include peripheral declarations */

#define TIMESLICE               TIME_2MS    // thread switch time in system time units

uint32_t Count1;   // number of times thread1 loops
uint32_t Count2;   // number of times thread2 loops
uint32_t Count3;   // number of times thread3 loops
uint32_t Count4;   // number of times thread4 loops
uint32_t Count5;   // number of times thread4 loops
signed char resultx, resulty, resultz;

	/*******************************************************************/
	/*
	 * Convert 6-bit accelerometer result into an 8-bit signed char
	 */
signed char convert(signed char input)
{
		input &=~0x40; //Turn off alert bit
		if(input & 0x20)	// update 6-bit signed format to 8-bit signed format
		input |= 0xE0;
		return (signed char) input;
}

void Task1(void){
  Count1 = 0;
  for(;;)
	{
		LED_RED_ON;
		msDelay(100);
		LED_RED_OFF;
		printf("Task1 Count1 = %d\n\r",Count1++);
		printf("X = %3d\tY = %3d\tZ = %3d\n", resultx, resulty, resultz);
		msDelay(100);
	}
}
void Task2(void){
  Count2 = 0;
  for(;;)
	{
		LED_YELLOW_ON;
		msDelay(100);
		LED_YELLOW_OFF;
		printf("Task2 Count2 = %d\n\r",Count2++);
		printf("X = %3d\tY = %3d\tZ = %3d\n", resultx, resulty, resultz);
		msDelay(100);
	}
}
void Task3(void){
  Count3 = 0;
  for(;;)
	{
		LED_GREEN_ON;
		msDelay(100);
		LED_GREEN_OFF;
		printf("Task3 Count3 = %d\n\r",Count3++);
		printf("X = %3d\tY = %3d\tZ = %3d\n", resultx, resulty, resultz);
		msDelay(100);
	}
}
void Task4(void){
  Count4 = 0;
  for(;;)
	{
		LED_BLUE_ON;
		msDelay(100);
		LED_BLUE_OFF;
		printf("Task4 Count4 = %d\n\r",Count4++);
		printf("X = %3d\tY = %3d\tZ = %3d\n", resultx, resulty, resultz);		
		msDelay(100);
	}
}
void Task5(void)
{
	Count5 = 0;
	while(1)
	{
		//printf("  X     Y     Z\n");
		enable_irq(24);
		//Read x-axis register
		resultx = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x00);    
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resultx));
		//printf("%3d", convert(resultx));

		//Read y-axis register
		resulty = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x01);
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resulty));
		//printf("   %3d", convert(resulty));

		//Read z-axis register
		resultz = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x02); 
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resultz));
		//printf("   %3d\n", convert(resultz));
		disable_irq(24);
		printf("Task5 Count5 = %d\n\r",Count5++);
		msDelay(100);
		
	}
}
int main(void)
{
	uint8_t sys_freq;
	int8_t temp,i = 0, data_prnt, counter = 0;
	int8_t data_arr[8];
    int8_t in = 'A', out, decryptOut;
    int8_t key = 5;
	sys_freq = OS_Init();           // initialize, disable interrupts, 100 MHz
	TSI_Init();
	gpio_init();
	uart_port_init(UART5_BASE_PTR);
	uart5_init(UART5_BASE_PTR, sys_freq, 115200);
		SDprint("Hello World\n\r");
	  I2C_init(I2C0_BASE_PTR, 0x00);
	enable_irq(24);
	//Pause();
	  MMA7660WriteRegister(I2C0_BASE_PTR,0x09,0xE0); //Disable tap detection
	  disable_irq(24);
	//Pause();
	enable_irq(24);
	  MMA7660WriteRegister(I2C0_BASE_PTR,0x07,0x19); //Enable auto-sleep, auto-wake, and put in active mode
	  disable_irq(24);
  TSI_SelfCalibration();

  START_SCANNING;
  ENABLE_EOS_INT;
  ENABLE_TSI;
	for(;counter < 9;counter++) 
	{
		LED_RED_ON;
		msDelay(100);
		LED_YELLOW_ON;
		msDelay(100);
		LED_GREEN_ON;
		msDelay(100);
		LED_BLUE_ON;
		msDelay(100);
		LED_RED_OFF;
		msDelay(100);
		LED_YELLOW_OFF;
		msDelay(100);
		LED_GREEN_OFF;
		msDelay(100);
		LED_BLUE_OFF;
		msDelay(100);
	}
	  //MMA7660WriteRegister(I2C0_BASE_PTR,0x09,0xE0); //Disable tap detection	
	  //MMA7660WriteRegister(I2C0_BASE_PTR,0x07,0x19); //Enable auto-sleep, auto-wake, and put in active mode

	//Task5();
	//OS_AddThreads(5, Task1, Task2, Task3, Task4, Task5);
	//OS_Launch(TIMESLICE); // doesn't return, interrupts enabled in here according to the interrupt req
	//uart_init(UART5_BASE_PTR, phr_freq, 115200);
	  //rtc_data data; 
	//uart_port_init(UART0_BASE_PTR);
	//uart5_init(UART5_BASE_PTR, sys_freq, 115200);
	  //uart_port_init(UART0_BASE_PTR);
	//JTAG_UART_Init(phr_freq, 115200);
	//SDprint("HI WORLD\n\r");
    /*printf("Size of char : %d\n", sizeof(char));
    printf("Before encrypt : %c, %d, %x\n", in, in, in);
    out = (in << key) | (in >> ((sizeof(char)*8)-key));
    printf("After encrypt : %c, %d, %x\n", out, out, out);
    decryptOut = (out << ((sizeof(char) * 8)-key)) | (out >> key);
    printf("After decrypt : %c, %d, %x\n", decryptOut, decryptOut, decryptOut);
	for(;counter < 9;counter++) 
	{
		LED_RED_ON;
		msDelay(100);
		LED_YELLOW_ON;
		msDelay(100);
		LED_GREEN_ON;
		msDelay(100);
		LED_BLUE_ON;
		msDelay(100);
		LED_RED_OFF;
		msDelay(100);
		LED_YELLOW_OFF;
		msDelay(100);
		LED_GREEN_OFF;
		msDelay(100);
		LED_BLUE_OFF;
		msDelay(100);
	}
    PIT_init(0, 1000000);
    PIT_init(1, 2000000);
    while(1)
	{
    	printf("SD_PIT_Get_Current_value(int PIT%d) : %d\nSD_PIT_Get_Current_value(int PIT%d) : %d\n", 0, (uint32_t *)SD_PIT_Get_Current_value(0), 1, (uint32_t *)SD_PIT_Get_Current_value(1));
	}
		/*Read x-axis register
		resultx = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x00);
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resultx));
		printf("%3d", convert(resultx));

		//Read y-axis register
		resulty = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x01);
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resulty));
		printf("   %3d", convert(resulty));

		//Read z-axis register
		resultz = u8MMA7660ReadRegister(I2C0_BASE_PTR,0x02);
		//uart_putChar(UART5_BASE_PTR,(signed char)convert(resultz));
		printf("   %3d\n", convert(resultz));

		//Delay for 250ms
		myDelay(250);

	/*		//Read x-axis register
			resultx = u8MMA7660ReadRegister(0x00);
			printf("%3d", convert(resultx));

			//Read y-axis register
			resulty = u8MMA7660ReadRegister(0x01);
			printf("   %3d", convert(resulty));

			//Read z-axis register
			resultz = u8MMA7660ReadRegister(0x02);
			printf("   %3d\n", convert(resultz));

			//Delay for 250ms
			myDelay(250);
	  }*/
	  return 0;
}
