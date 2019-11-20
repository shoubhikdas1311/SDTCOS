/*
 * SD_DMA.c
 *
 *  Created on: May 9, 2019
 *      Author: SD
 */
/*****************************************************************************************************
* Include files
*****************************************************************************************************/
#include "DMA.h"
/*****************************************************************************************************
* Declaration of module wide FUNCTIONs - NOT for use in other modules
*****************************************************************************************************/
void vfnDMAChannel0_ISR (void);
/*****************************************************************************************************
* Definition of module wide MACROs / #DEFINE-CONSTANTs - NOT for use in other modules
*****************************************************************************************************/
#define DMA_FIRST_IRQ	(INT_DMA0 - 16ul)
#define DMA_MAX_CHANNELS	(16)
/*****************************************************************************************************
* Declaration of module wide TYPEs - NOT for use in other modules
*****************************************************************************************************/
//void ( * const vfnDMACh0_Callback)(void);
/*****************************************************************************************************
* Definition of module wide VARIABLEs - NOT for use in other modules
*****************************************************************************************************/
void vfnDMAChannel0_ISR (void);
static u32 u32fnDMA_MUXInit(u32 u32Channel, u32 u32Source);
static void ( * vfnDMACh0_Callback[DMA_MAX_CHANNELS])(void);
extern uint8_t count;
uint8_t counter = 0;
/*****************************************************************************************************
* Definition of module wide (CONST-) CONSTANTs - NOT for use in other modules
*****************************************************************************************************/

/*****************************************************************************************************
* Code of project wide FUNCTIONS
*****************************************************************************************************/
u32 u32fnDMA_ChannelInit(stcd_DMA * psDMAInit, void(* vfnDMAChCallback)(void))
{
	u32 u32ErrorStatus = OK;
	u32 u32ChannelNumber = psDMAInit->u32channelno;
	u32 u32DMA_IRQ;

	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;

	if(DMA_MAX_CHANNELS > u32ChannelNumber)
	{
		DMA_SADDR_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u32saddr;

		DMA_ATTR_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u16tcdAttr;

		DMA_SOFF_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->s16soff;

		DMA_NBYTES_MLNO_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u32nbytes;

		DMA_SLAST_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u32slast;

		DMA_DADDR_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u32daddr;

		counter = psDMAInit->u32loopcount;
		
		if(psDMAInit->u32link & 0x80)
		{
			DMA_CITER_ELINKYES_REG(DMA_BASE_PTR,u32ChannelNumber) = /*DMA_CITER_ELINKYES_ELINK_MASK | psDMAInit->u32link | */DMA_CITER_ELINKYES_CITER(psDMAInit->u32loopcount);
			DMA_BITER_ELINKYES_REG(DMA_BASE_PTR,u32ChannelNumber) = /*DMA_CITER_ELINKYES_ELINK_MASK | psDMAInit->u32link | */DMA_BITER_ELINKYES_BITER(psDMAInit->u32loopcount);
		}
		else
		{
			DMA_CITER_ELINKNO_REG(DMA_BASE_PTR,u32ChannelNumber) = DMA_CITER_ELINKNO_CITER(psDMAInit->u32loopcount);
			DMA_BITER_ELINKNO_REG(DMA_BASE_PTR,u32ChannelNumber) = DMA_BITER_ELINKNO_BITER(psDMAInit->u32loopcount);
		}

		DMA_DOFF(u32ChannelNumber) = psDMAInit->s16doff;

		DMA_DLAST_SGA_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u32dlast_sga;



		DMA_CSR_REG(DMA_BASE_PTR,u32ChannelNumber) = psDMAInit->u16csr;

		u32ErrorStatus = u32fnDMA_MUXInit(u32ChannelNumber,psDMAInit->u32TriggerSource);

		if((psDMAInit->u16csr & DMA_CSR_INTHALF_MASK) || (psDMAInit->u16csr & DMA_CSR_INTMAJOR_MASK))
		{
			u32DMA_IRQ = DMA_FIRST_IRQ + u32ChannelNumber;
			u32ErrorStatus |= enable_irq(u32DMA_IRQ);
			if(vfnDMAChCallback != NULL)
			{
				vfnDMACh0_Callback[u32ChannelNumber] = vfnDMAChCallback;
			}
			else
			{
				u32ErrorStatus = ERROR;
			}


		}

	}
	else
	{
		u32ErrorStatus = ERROR;
	}

	return(u32ErrorStatus);
}

static u32 u32fnDMA_MUXInit(u32 u32Channel, u32 u32Source)
{
	u32 u32Status = ERROR;
	if(DMA_TRIGGER_UNSUPPORT_TRIGGER > u32Source)
	{
		DMAMUX_CHCFG_REG(DMAMUX_BASE_PTR,u32Channel) = DMAMUX_CHCFG_ENBL_MASK|DMAMUX_CHCFG_SOURCE(u32Source);
		u32Status = OK;
	}

	return(u32Status);
}


void vfnDMAChannel2_ISR (void)
{
	DMA_INT |= DMA_INT_INT2_MASK;
	vfnDMACh0_Callback[2]();
}

void vfnDMAChannel3_ISR (void)
{
	DMA_INT |= DMA_INT_INT3_MASK;
	vfnDMACh0_Callback[3]();
}

void vfnDMAChannel4_ISR (void)
{
	DMA_INT |= DMA_INT_INT4_MASK;
	vfnDMACh0_Callback[4]();
}

void vfnDMAChannel5_ISR (void)
{
	DMA_INT |= DMA_INT_INT5_MASK;
	vfnDMACh0_Callback[5]();
}

void vfnDMAChannel6_ISR (void)
{
	DMA_INT |= DMA_INT_INT6_MASK;
	vfnDMACh0_Callback[6]();
}
