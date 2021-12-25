/*
 * Attiny1416_USART.h
 *
 * Created: 2021-11-27 18:34:28
 *  Author: Nasreddine Salem
 */ 

/*
 Pre Processor COnfigurable Driver
 Linking Configurable Driver
 PostBuild Configurable Driver "During Runtime"
*/
#ifndef ATTINY1416_USART_H_
#define ATTINY1416_USART_H_

typedef enum 
{
	USART_SingleProcessor,
	USART_MultiProcessor,
	
}USART_CommunicationTerminal;

typedef enum
{
	USART_Async_NormalSpeed,
	USART_Async_DoubleSpeed,
	
}USART_CommunicationAsynMode;

typedef enum
{
	USART_Disable,
	USART_Tx_Only,
	USART_Rx_Only,
	USART_Tx_Rx,
	
}USART_Enable;

typedef enum
{
	USART_InterruptDisable,
	USART_RxCompl_Enable,
	USART_TxCompl_Enable,
	USART_DataRegisterEmpty_Enable,
	USART_RxCompl_TxCompl_Enable,
	USART_RxCompl_DataRegisterEmpty_Enable,
	USART_TxCompl_DataRegisterEmpty_Enable,
	USART_RxCompl_TxCompl_Enable_DataRegisterEmpty_Enable,
	
}USART_InterruptSource;

typedef enum
{
	USART_5bitData,
	USART_6bitData,
	USART_7bitData,
	USART_8bitData,
	USART_9bitDataH,
	USART_9bitDataL,
		
}USART_DataFrame;

typedef enum
{
	USART_ParityDisabel_1STop,
	USART_ParityDisabel_2STop,
	USART_ParityEven_1STop,
	USART_ParityEven_2STop,
    USART_ParityOdd_1STop,
	USART_ParityOdd_2STop,
}USART_ControlFrame;

typedef enum
{
	USART_NoError,
	USART_ParityError,
	USART_OverRunError,
	USART_FramError,
	
}USART_ErrorType;
/* Please Refer to upper Enum for more details*/
typedef struct
{
	USART_Enable  EnableMode;
	USART_CommunicationAsynMode CommunicationAsynMode;
	USART_CommunicationTerminal CommmunicationTerminal;
	USART_InterruptSource InterruptSource;
	USART_DataFrame DataFrame;
	USART_ControlFrame ControlFrame;
	
	unsigned long BaudRate;
	USART_ErrorType   ReadMsg_Error;
	/*call back members*/
	/* Make the pointer to a function you wish to be  called by RXC Interrupt*/
	void (*RXC_InterruptCall)(void);
	void (*TXC_InterruptCall)(void);
	void (*DataRegister_InterruptCall)(void);
		
}USART_ConfigurationStruct;

extern USART_ConfigurationStruct UART0;

void USART_Init(void);
void USART_SendByte_Blocking(unsigned short data);
void USART_SendByte_NonBlocking(unsigned short data);
unsigned short USART_ReadByte_Blocking(void);
unsigned short USART_ReadByte_NonBlocking(void);
#endif /* ATTINY1416_USART_H_ */