/*---------------------------------System Control Block--------------------------------------------------*/
#define CORE_SCB_ACTLR					(*((volatile uint32_t *)0xE000E008))
#define CORE_SCB_CPUID					(*((volatile uint32_t *)0xE000ED00))
#define CORE_SCB_ICSR					(*((volatile uint32_t *)0xE000ED04))
#define CORE_SCB_VTOR					(*((volatile uint32_t *)0xE000ED08))
#define CORE_SCB_AIRCR					(*((volatile uint32_t *)0xE000ED0C))
#define CORE_SCB_SCR					(*((volatile uint32_t *)0xE000ED10))
#define CORE_SCB_CCR					(*((volatile uint32_t *)0xE000ED14))
#define CORE_SCB_SHPR1					(*((volatile uint32_t *)0xE000ED18))
#define CORE_SCB_SHPR2					(*((volatile uint32_t *)0xE000ED1C))
#define CORE_SCB_SHPR3					(*((volatile uint32_t *)0xE000ED20))
#define CORE_SCB_SHCSR					(*((volatile uint32_t *)0xE000ED24))
#define CORE_SCB_CFSR 					(*((volatile uint32_t *)0xE000ED28))
#define CORE_SCB_MMSR 					(*((volatile uint32_t *)0xE000ED28))
#define CORE_SCB_BFSR 					(*((volatile uint32_t *)0xE000ED29))
#define CORE_SCB_UFSR 					(*((volatile uint32_t *)0xE000ED2A))
#define CORE_SCB_HFSR 					(*((volatile uint32_t *)0xE000ED2C))
#define CORE_SCB_MMAR 					(*((volatile uint32_t *)0xE000ED34))
#define CORE_SCB_BFAR 					(*((volatile uint32_t *)0xE000ED38))
#define CORE_SCB_AFSR 					(*((volatile uint32_t *)0xE000ED3C))

/*------------------------------------SysTick definations------------------------------------------------*/
#define CORE_SYS_TIM_CSR 				(*((volatile uint32_t *)0xE000E010))
#define CORE_SYS_TIM_RVR 				(*((volatile uint32_t *)0xE000E014))
#define CORE_SYS_TIM_CVR 				(*((volatile uint32_t *)0xE000E018))
#define CORE_SYS_TIM_CALR 				(*((volatile uint32_t *)0xE000E01C))

/*------------------------------------			NVIC		-------------------------------------------------*/

#define CORE_NVIC_ISER_BASE_ADD			((volatile uint32_t *)0xE000E100)
#define CORE_NVIC_ISER_BASE_PTR			(*(CORE_NVIC_ISER_BASE_ADD))
#define CORE_NVIC_ISER(n) 				(*((CORE_NVIC_ISER_BASE_ADD) + (n * 4))

#define CORE_NVIC_ICER_BASE_ADD			((volatile uint32_t *)0XE000E180)
#define CORE_NVIC_ICER_BASE_PTR			(*(CORE_NVIC_ICER_BASE_ADD))
#define CORE_NVIC_ICER(n) 				(*((CORE_NVIC_ICER_BASE_ADD) + (n * 4)))

#define CORE_NVIC_ISPR_BASE_ADD			((volatile uint32_t *)0XE000E200)
#define CORE_NVIC_ISPR_BASE_PTR			(*(CORE_NVIC_ISPR_BASE_ADD))
#define CORE_NVIC_ISPR(n) 				(*((CORE_NVIC_ISPR_BASE_ADD) + (n * 4)))

#define CORE_NVIC_ICPR_BASE_ADD			((volatile uint32_t *)0XE000E280)
#define CORE_NVIC_ICPR_BASE_PTR			(*(CORE_NVIC_ICPR_BASE_ADD))
#define CORE_NVIC_ICPR(n) 				(*((CORE_NVIC_ICPR_BASE_ADD) + (n * 4)))

#define CORE_NVIC_IABR_BASE_ADD			((volatile uint32_t *)0xE000E300)
#define CORE_NVIC_IABR_BASE_PTR			(*(CORE_NVIC_IABR_BASE_ADD))
#define CORE_NVIC_IABR(n) 				(*((CORE_NVIC_IABR_BASE_ADD) + (n * 4)))

#define CORE_NVIC_IPR_BASE_ADD			((volatile uint32_t *)0xE000E400)
#define CORE_NVIC_IPR_BASE_PTR			(*(CORE_NVIC_IPR_BASE_ADD))
#define CORE_NVIC_IPR(n) 				(*((CORE_NVIC_IPR_BASE_ADD) + (n * 4)))

#define CORE_NVIC_STIR					(*((volatile uint32_t *)0xE000EF00))
	
/*------------------------------------			MPU			----------------------------------------------------*/

#define CORE_MPU_TYPE					((volatile uint32_t *)0xE000ED90)
#define CORE_MPU_CTRL					((volatile uint32_t *)0xE000ED94)
#define CORE_MPU_RNR					((volatile uint32_t *)0xE000ED98)
#define CORE_MPU_RBAR					((volatile uint32_t *)0xE000ED9C)
#define CORE_MPU_RASR					((volatile uint32_t *)0xE000EDA0)
#define CORE_MPU_RBAR_A1				((volatile uint32_t *)0xE000EDA4)
#define CORE_MPU_RASR_A1				((volatile uint32_t *)0xE000EDA8)
#define CORE_MPU_RBAR_A2				((volatile uint32_t *)0xE000EDAC)
#define CORE_MPU_RASR_A2				((volatile uint32_t *)0xE000EDB0)
#define CORE_MPU_RBAR_A3				((volatile uint32_t *)0xE000EDB4)
#define CORE_MPU_RASR_A3				((volatile uint32_t *)0xE000EDB8)
	
/*-------------------------------------			FPU			-----------------------------------------------------

#define CORE_CPACR
#define CORE_FPCCR
#define CORE_FPCAR
#define CORE_FPSCR
#define CORE_FPDSCR




#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_
#define CORE_*/