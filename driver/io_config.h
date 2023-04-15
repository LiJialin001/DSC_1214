/*------------------------------------------*/
/*	file: 		io_config.h					*/
/*	revision:	0	Samuel Lee				*/
/*				1	Samuel Lee	2015-04-12	*/
/*											*/
/*			(C)2012-2015 IES-Lab			*/
/*			All rights reserved.			*/
/*------------------------------------------*/

#ifndef __IO_CONFIG_H
#define __IO_CONFIG_H

/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "common.h"

/*------------------------------------------------------------------------------*/
/*    GLOBAL VARS																*/
/*------------------------------------------------------------------------------*/

/*
sbit TUBE1=P2^0;	// push-pull
sbit TUBE2=P2^1;	// push-pull
sbit TUBE3=P2^2;	// push-pull
sbit TUBE4=P2^3;	// push-pull
sbit TUBE5=P2^4;	// push-pull
sbit TUBE6=P2^5;	// push-pull
*/
SBIT (TUBE1, SFR_P2, 0);
SBIT (TUBE2, SFR_P2, 1);
SBIT (TUBE3, SFR_P2, 2);
SBIT (TUBE4, SFR_P2, 3);
SBIT (TUBE5, SFR_P2, 4);
SBIT (TUBE6, SFR_P2, 5);

/*
sbit SA=P1^0;	// push-pull or OD
sbit SB=P1^1;	// push-pull or OD
sbit SC=P1^2;	// push-pull or OD
sbit SD=P1^3;	// push-pull or OD
sbit SE=P1^4;	// push-pull or OD
sbit SF=P1^5;	// push-pull or OD
sbit SG=P1^6;	// push-pull or OD
sbit DOT=P1^7;	// push-pull or OD
*/

SBIT (SA, SFR_P1, 0);
SBIT (SB, SFR_P1, 1);
SBIT (SC, SFR_P1, 2);
SBIT (SD, SFR_P1, 3);
SBIT (SE, SFR_P1, 4);
SBIT (SF, SFR_P1, 5);
SBIT (SG, SFR_P1, 6);
SBIT (DOT, SFR_P1, 7);

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (DECLARATIONS)											*/
/*------------------------------------------------------------------------------*/
void io_config(void);
void io_init(void);

#endif /* __IO_CONFIG_H	*/

/* end */