/*------------------------------------------*/
/*	file: 		common.h					*/
/*	revision:	0	Samuel Lee				*/
/*				1	Samuel Lee	2015-04-12	*/
/*											*/
/*			(C)2012-2015 IES-Lab			*/
/*			All rights reserved.			*/
/*------------------------------------------*/

#ifndef __COMMON_H
#define __COMMON_H

/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "compiler_defs.h"
#include "C8051F020_defs.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*------------------------------------------------------------------------------*/
/*    MACROS																    */
/*------------------------------------------------------------------------------*/
#define SCON SCON0
#define SBUF SBUF0

#define TI TI0
#define RI RI0

#define BIT0_MASK 0x01
#define BIT1_MASK 0x02
#define BIT2_MASK 0x04
#define BIT3_MASK 0x08
#define BIT4_MASK 0x10
#define BIT5_MASK 0x20
#define BIT6_MASK 0x40
#define BIT7_MASK 0x80

/*------------------------------------------------------------------------------*/
/*    GLOBAL TYPES                                                              */
/*------------------------------------------------------------------------------*/
/** \brief Enumeration of mask for each bit of byte */
typedef enum{
	BIT0 = 0,
	BIT1,
	BIT2,
	BIT3,
	BIT4,
	BIT5,
	BIT6,
	BIT7
}Bit_Mask_t;

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (DECLARATIONS)											*/
/*------------------------------------------------------------------------------*/
unsigned char Reg_Field_Set(unsigned char Register, Bit_Mask_t Bit_Mask);
unsigned char Reg_Field_Clr(unsigned char Register, Bit_Mask_t Bit_Mask);
void Loop_Delay(unsigned int loop);	// delay about (loop * 1ms)
void Delay1ms(void) ;

#endif	/* __COMMON_H */

/* end */
 