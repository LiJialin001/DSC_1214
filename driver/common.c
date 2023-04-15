/*------------------------------------------*/
/*	file: 		common.c					*/
/*	revision:	0	Samuel Lee				*/
/*				1	Samuel Lee	2015-04-12	*/
/*				2	Samuel Lee	2015-04-13	*/
/*											*/
/*			(C)2012-2015 IES-Lab			*/
/*			All rights reserved.			*/
/*------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "common.h"

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (IMPLEMENTATIONS)										*/
/*------------------------------------------------------------------------------*/
unsigned char Reg_Field_Set(unsigned char Register, Bit_Mask_t Bit_Mask)
{
	switch(Bit_Mask)
	{
		case BIT0:
			return (Register |= 0x01);
			break;
		
		case BIT1:
			return (Register |= 0x02);
			break;
		
		case BIT2:
			return (Register |= 0x04);
			break;
		
		case BIT3:
			return (Register |= 0x08);
			break;
		
		case BIT4:
			return (Register |= 0x10);
			break;
		
		case BIT5:
			return (Register |= 0x20);
			break;
		
		case BIT6:
			return (Register |= 0x40);
			break;
		
		case BIT7:
			return (Register |= 0x80);
		break;		
		
		default:
			return (Register);
			break;
	}
}

unsigned char Reg_Field_Clr(unsigned char Register, Bit_Mask_t Bit_Mask)
{
	switch(Bit_Mask){

		case BIT0:
			return (Register &= 0xFE);
			break;
		
		case BIT1:
			return (Register &= 0xFD);
			break;
		
		case BIT2:
			return (Register &= 0xFB);
			break;
		
		case BIT3:
			return (Register &= 0xF7);
			break;
		
		case BIT4:
			return (Register &= 0xEF);
			break;
		
		case BIT5:
			return (Register &= 0xDF);
			break;
		
		case BIT6:
			return (Register &= 0xBF);
			break;
		
		case BIT7:
			return (Register &= 0x7F);
			break;		
		
		default:
			return (Register);
			break;
	}
}

void Loop_Delay(unsigned int loop)
{
	unsigned int i,j;

	for(i=0; i<loop; i++)
	{
		for(j=0;j<1000;j++)
		{

		}
	}
}

void Delay1ms(void) 
{
 	unsigned  int  i  ;
	/* 2500 for 22.1184MHz crystal */
	for(i=0;i<2500;i++)
	{ 
		
	}
}

/* end */