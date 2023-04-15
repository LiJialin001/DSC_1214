/*------------------------------------------*/
/*	file: 		io_config.c					*/
/*	revision:	0	Samuel Lee				*/
/*				1	Samuel Lee	2015-04-12	*/
/*											*/
/*			(C)2012-2015 IES-Lab			*/
/*			All rights reserved.			*/
/*------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "io_config.h"

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (IMPLEMENTATIONS)											*/
/*------------------------------------------------------------------------------*/

void io_config(void)
{

	P3MDOUT=0x00;			// All: OD 

	P2MDOUT=0xFF;			///////////////////////////////////////// 
							// P2.7: 				PUSH-PULL
							// P2.6:				PUSH-PULL
							// P2.5:	TUBE6		PUSH-PULL
							// P2.4:	TUBE5		PUSH-PULL
							// P2.3:`	TUBE4		PUSH-PULL
							// P2.2:	TUBE3		PUSH-PULL
							// P2.1:	TUBE2		PUSH-PULL
							// P2.0:	TUBE1		PUSH-PULL
							
	P1MDOUT=0xFF;			///////////////// P-P ///////////////////
							// P1.7:	
							// P1.6:	
							// P1.5:	
							// P1.4:
							// P1.3:	
							// P1.2:	
							// P1.1:	
							// P1.0;	

	P0MDOUT=0xC0;			///////////////// P-P ///////////////////
							// P0.0: 	TX0, 	OUTPUT, 	OD
							// P0.1: 	RX0, 	INPUT,  	OD
							// P0.2: 						OD
							// P0.3:						OD
							// P0.4:						OD
							// P0.5:						OD
							// P0.6:	TP1,	OUTPUT,		PP
							// P0.7:	TP0,	OUTPUT,		PP
}

void io_init(void)
{
	P7=0xFF;
	P6=0xFF;
	P5=0xFF;
	P4=0xFF;
	P3=0xFF;
	P2=0xFF;
	P1=0xFF;
	P0=0xFF;	
}

/* end */

