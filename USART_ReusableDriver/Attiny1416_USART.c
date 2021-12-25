/*
 * Attiny1416_USART.c
 *
 * Created: 2021-11-27 18:33:41
 *  Author: Hi
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "Attiny1416_USART.h"
#include "uc_Configuration.h"

#define NULL_PTR  ((void *)0x00)

USART_ConfigurationStruct UART0 = {0,
									.RXC_InterruptCall = NULL_PTR,
									.TXC_InterruptCall = NULL_PTR,
									.DataRegister_InterruptCall = NULL_PTR };

ISR(USART0_RXC_vect)
{
	if(UART0.RXC_InterruptCall != NULL_PTR)
	{
		UART0.RXC_InterruptCall();
	}
	else{
		//Handle Error Using Error Function
	}
}

ISR(USART0_TXC_vect)
{
	if(UART0.TXC_InterruptCall != NULL_PTR)
	{
		UART0.TXC_InterruptCall();
	}
	else{
		//Handle Error Using Error Function
	}
}	

ISR(USART0_DRE_vect)
{
	if(UART0.DataRegister_InterruptCall != NULL_PTR)
	{
		UART0.DataRegister_InterruptCall();
	}
	else{
		//Handle Error Using Error Function
	}
}
void USART_Init(void)
{
	unsigned char USART0_Status_Temp=0;
	unsigned char USART0_CTRLA_Temp=0;
	unsigned char USART0_CTRLB_Temp=0;
	unsigned char USART0_CTRLC_Temp=0;
	float Baud_Temp=0;
	
	switch (UART0.EnableMode)
	{
	    case USART_Disable:
		
		break;
		case USART_Rx_Only:
			USART0_CTRLB_Temp = (1<< USART_RXEN_bp);
		break;
		case USART_Tx_Only:
			USART0_CTRLB_Temp = (1<< USART_TXEN_bp);
		break;
		case USART_Tx_Rx:
			USART0_CTRLB_Temp = (1<< USART_RXEN_bp) | (1<< USART_TXEN_bp);
		break;
		default:
		break;
	}
	
	
	switch (UART0.CommunicationAsynMode)
	{
		case USART_Async_DoubleSpeed:
			USART0_CTRLB_Temp |= USART_RXMODE_CLK2X_gc;
			Baud_Temp = ((float)(F_CPU)* 64 / (8 *(float)(UART0.BaudRate)) + 0.5);
		break;
		case USART_Async_NormalSpeed:
			USART0_CTRLB_Temp |= USART_RXMODE_NORMAL_gc;	
			Baud_Temp = ((float)(F_CPU)* 64 / (16 *(float)(UART0.BaudRate)) + 0.5); 
		break;
		default:
		break;
		
	}
	switch (UART0.CommmunicationTerminal)
	{
		case USART_SingleProcessor:
		break;
		case USART_MultiProcessor:
		break;
			USART0_CTRLB_Temp |= (1<< USART_MPCM_bp);
		default:
		break;
	}
	switch(UART0.InterruptSource) 
	{
			case USART_InterruptDisable:
			break;
			case USART_RxCompl_Enable:
				USART0_CTRLA_Temp |= (1<< USART_RXCIE_bp);
			break;
			case USART_TxCompl_Enable:
				USART0_CTRLA_Temp |= (1<< USART_TXCIE_bp);
			break;
			case USART_DataRegisterEmpty_Enable:
				USART0_CTRLA_Temp |= (1<< USART_DREIE_bp);
			break;
			case USART_RxCompl_TxCompl_Enable:
				USART0_CTRLA_Temp |= (1<< USART_RXCIE_bp) | (1<< USART_TXCIE_bp);
			break;
			case USART_RxCompl_DataRegisterEmpty_Enable:
				USART0_CTRLA_Temp |= (1<< USART_RXCIE_bp) | (1<< USART_DREIE_bp);
			break;
			case USART_TxCompl_DataRegisterEmpty_Enable:
				USART0_CTRLA_Temp |= (1<< USART_TXCIE_bp) | (1<< USART_DREIE_bp);
			break;
			case USART_RxCompl_TxCompl_Enable_DataRegisterEmpty_Enable:
				USART0_CTRLA_Temp |= (1<< USART_RXCIE_bp) | (1<< USART_TXCIE_bp) | (1<< USART_DREIE_bp);
			break;
			default:
			break;
	}
	
	switch (UART0.DataFrame)
	{
			case USART_5bitData:
				USART0_CTRLC_Temp |= USART_CHSIZE_5BIT_gc;	
			break;
			case USART_6bitData:
				USART0_CTRLC_Temp |= USART_CHSIZE_6BIT_gc;
			break;
			case USART_7bitData:
				USART0_CTRLC_Temp |= USART_CHSIZE_7BIT_gc;
			break;
			case USART_8bitData:
				USART0_CTRLC_Temp |= USART_CHSIZE_8BIT_gc;
			break;
			case USART_9bitDataH:
				USART0_CTRLC_Temp |= USART_CHSIZE_9BITH_gc >> 8;
			break;
			case USART_9bitDataL:
			USART0_CTRLC_Temp |= USART_CHSIZE_9BITL_gc;
			break;
			default:
			break;
	}
	
	switch (UART0.ControlFrame)
	{
			case USART_ParityDisabel_1STop:
			break;
			case USART_ParityDisabel_2STop:
				USART0_CTRLC_Temp |= USART_SBMODE_bm;
			break;
			case USART_ParityEven_1STop:
				USART0_CTRLC_Temp |= USART_PMODE_EVEN_gc;
			break;
			case USART_ParityEven_2STop:
				USART0_CTRLC_Temp |= USART_PMODE_EVEN_gc | USART_SBMODE_bm;
			break;
			case USART_ParityOdd_1STop:
				USART0_CTRLC_Temp |= USART_PMODE_ODD_gc;
			break;
			case USART_ParityOdd_2STop:
				USART0_CTRLC_Temp |= USART_PMODE_ODD_gc | USART_SBMODE_bm;
			break;
			default:
			break;
	}
	
	USART0_BAUDH = ((unsigned short)Baud_Temp) >> 8;
	USART0_BAUDL = ((unsigned short)Baud_Temp);
	USART0_STATUS = USART0_Status_Temp;
	USART0_CTRLA = USART0_CTRLA_Temp;
	USART0_CTRLB = USART0_CTRLA_Temp;
	USART0_CTRLC = USART0_CTRLA_Temp;

}

void USART_SendByte_Blocking(unsigned short data)
{
	while (!(USART0.STATUS & USART_DREIF_bm))
	{
	}
	if(UART0.DataFrame == USART_9bitDataH)
	{
		USART0.TXDATAH = (USART0_TXDATAH & 0xFE) | ((data & (1<<8)) >>8);
	}
	USART0.TXDATAL = (unsigned char)data;
}

void USART_SendByte_NonBlocking(unsigned short data)
{
	if ((USART0.STATUS & USART_DREIF_bm)!=0)
	{
		if(UART0.DataFrame == USART_9bitDataH)
		{
			USART0.TXDATAH = (USART0_TXDATAH & 0xFE) | ((data & (1<<8)) >>8);
		}
		USART0.TXDATAL = (unsigned char)data;
	}
}

unsigned short USART_ReadByte_Blocking(void)
{
	unsigned short rxData = 0;
	while (!(USART0.STATUS & USART_RXCIF_bm))
	{
		;
	}
	if(USART0.STATUS & ((USART_BUFOVF_bm)| (USART_FERR_bm) | (USART_PERR_bm) ))
	{
		// You should handle it as you witch
		if(USART0.STATUS & (USART_BUFOVF_bm))
		{
			UART0.ReadMsg_Error = USART_OverRunError;
		}else if(USART0.STATUS & (USART_FERR_bm))
		{
			UART0.ReadMsg_Error = USART_FramError;
		}else
		{
			UART0.ReadMsg_Error = USART_ParityError;
		}
	}
	if(UART0.DataFrame == USART_9bitDataH)
	{
		rxData = USART0_RXDATAH & (1<<USART_DATA8_bm) <<7 ;
	}
	rxData |= USART0.RXDATAL;
	return rxData;
}

unsigned short USART_ReadByte_NonBlocking(void)
{
	unsigned short rxData = 0;
	if ((USART0.STATUS & USART_RXCIF_bm) !=0)
	{

	if(USART0.STATUS & ((USART_BUFOVF_bm)| (USART_FERR_bm) | (USART_PERR_bm) ))
	{
			// You should handle it as you witch
			if(USART0.STATUS & (USART_BUFOVF_bm))
			{
				UART0.ReadMsg_Error = USART_OverRunError;
			}else if(USART0.STATUS & (USART_FERR_bm))
			{
				UART0.ReadMsg_Error = USART_FramError;
			}else
			{
				UART0.ReadMsg_Error = USART_ParityError;
			}
	}
		if(UART0.DataFrame == USART_9bitDataH)
		{
			rxData = USART0_RXDATAH & (1<<USART_DATA8_bm) <<7 ;
		}
		rxData |= USART0.RXDATAL;
	}
	return rxData;
}