/*
 * SD_DMA.h
 *
 *  Created on: May 9, 2019
 *      Author: SD
 */
/*****************************************************************************************************
* Module definition against multiple inclusion
*****************************************************************************************************/

#ifndef DMA_H_
#define DMA_H_
/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "Projecttypes.h"
#include "MK60N512.h"
//#include "../NVIC/NVIC.h"
#include "SD_UART.h"
/*****************************************************************************************************
* Declaration of project wide TYPES
*****************************************************************************************************/
typedef struct
{
	u32 u32saddr;
	s16 s16soff;
	u16 u16tcdAttr;
	u32 u32nbytes;
	u32 u32slast;
	u32 u32daddr;
	s16 s16doff;
	u16 u16citer;
	u32 u32dlast_sga;
	u16 u16csr;
	u16 u16biter;
	u32 u32channelno;
	u32 u32loopcount;
    u32 u32link;
    u32 u32TriggerSource;
}stcd_DMA;

typedef enum
{
	DMA_TRIGGER_DISABLE = 0,
	DMA_TRIGGER_RESERVED,
	DMA_TRIGGER_UART0_RX,
	DMA_TRIGGER_UART0_TX,
	DMA_TRIGGER_UART1_RX,
	DMA_TRIGGER_UART1_TX,
	DMA_TRIGGER_UART2_RX,
	DMA_TRIGGER_UART2_TX,
	DMA_TRIGGER_UART3_RX,
	DMA_TRIGGER_UART3_TX,
	DMA_TRIGGER_UART4_RX,
	DMA_TRIGGER_UART4_TX,
	DMA_TRIGGER_UART5_RX,
	DMA_TRIGGER_UART5_TX,
	DMA_TRIGGER_I2S0_RX,
	DMA_TRIGGER_I2S0_TX,
	DMA_TRIGGER_SPI0_TX,
	DMA_TRIGGER_SPI0_RX,
	DMA_TRIGGER_SPI1_TX,
	DMA_TRIGGER_SPI1_RX,
	DMA_TRIGGER_SPI2_TX,
	DMA_TRIGGER_SPI2_RX,
	DMA_TRIGGER_I2C0,
	DMA_TRIGGER_I2C1,
	DMA_TRIGGER_FTM0_CHANNEL_0,
	DMA_TRIGGER_FTM0_CHANNEL_1,
	DMA_TRIGGER_FTM0_CHANNEL_2,
	DMA_TRIGGER_FTM0_CHANNEL_3,
	DMA_TRIGGER_FTM0_CHANNEL_4,
	DMA_TRIGGER_FTM0_CHANNEL_5,
	DMA_TRIGGER_FTM0_CHANNEL_6,
	DMA_TRIGGER_FTM0_CHANNEL_7,
	DMA_TRIGGER_FTM1_CHANNEL_0,
	DMA_TRIGGER_FTM1_CHANNEL_1,
	DMA_TRIGGER_FTM2_CHANNEL_0,
	DMA_TRIGGER_FTM2_CHANNEL_1,
	DMA_TRIGGER_EEE1588_TIMER_0,
	DMA_TRIGGER_EEE1588_TIMER_1,
	DMA_TRIGGER_EEE1588_TIMER_2,
	DMA_TRIGGER_EEE1588_TIMER_3,
	DMA_TRIGGER_ADC0,
	DMA_TRIGGER_ADC1,
	DMA_TRIGGER_CMP0,
	DMA_TRIGGER_CMP1,
	DMA_TRIGGER_CMP2,
	DMA_TRIGGER_DAC0,
	DMA_TRIGGER_DAC1,
	DMA_TRIGGER_CMT,
	DMA_TRIGGER_PDB,
	DMA_TRIGGER_PORT_A,
	DMA_TRIGGER_PORT_B,
	DMA_TRIGGER_PORT_C,
	DMA_TRIGGER_PORT_D,
	DMA_TRIGGER_PORT_E,
	DMA_TRIGGER_ALWAYS_EN_0,
	DMA_TRIGGER_ALWAYS_EN_1,
	DMA_TRIGGER_ALWAYS_EN_2,
	DMA_TRIGGER_ALWAYS_EN_3,
	DMA_TRIGGER_ALWAYS_EN_4,
	DMA_TRIGGER_ALWAYS_EN_5,
	DMA_TRIGGER_ALWAYS_EN_6,
	DMA_TRIGGER_ALWAYS_EN_7,
	DMA_TRIGGER_ALWAYS_EN_8,
	DMA_TRIGGER_ALWAYS_EN_9,
	DMA_TRIGGER_UNSUPPORT_TRIGGER
}eDMATriggerSource;

typedef enum
{
	DMA_CHANNEL_0 = 0,
	DMA_CHANNEL_1,
	DMA_CHANNEL_2,
	DMA_CHANNEL_3,
	DMA_CHANNEL_4,
	DMA_CHANNEL_5,
	DMA_CHANNEL_6,
	DMA_CHANNEL_7,
	DMA_CHANNEL_8,
	DMA_CHANNEL_9,
	DMA_CHANNEL_10,
	DMA_CHANNEL_11,
	DMA_CHANNEL_12,
	DMA_CHANNEL_13,
	DMA_CHANNEL_14,
	DMA_CHANNEL_15,
}eDMAChannels;
/*****************************************************************************************************
* Definition of project wide VARIABLES
*****************************************************************************************************/

/*****************************************************************************************************
* Definition of project wide MACROS / #DEFINE-CONSTANTS
*****************************************************************************************************/
#define DMA_ENABLE_REQ(dmach)	(DMA_ERQ |= (1<<dmach))

#define DMA_LINK_MINOR_TRUE			(DMA_CITER_ELINKYES_ELINK_MASK)
#define DMA_LINK_MINOR_CHANNEL(x)	(DMA_CITER_ELINKYES_LINKCH(x))
/*****************************************************************************************************
* Declaration of project wide FUNCTIONS
*****************************************************************************************************/

/*****************************************************************************************************
* Declaration of module wide FUNCTIONs - NOT for use in other modules
*****************************************************************************************************/

u32 u32fnDMA_ChannelInit(stcd_DMA * psDMAInit, void(* vfnDMAChCallback)(void));
/*extern void vfnDMAChannel0_ISR (void);
extern void vfnDMAChannel1_ISR (void);*/

#endif /*DMA_H_*/

