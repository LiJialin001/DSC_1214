/*------------------------------------------*/
/*	file: 		osc.c						*/
/*	revision:	0	Samuel Lee				*/
/*				1	Samuel Lee	2015-04-12	*/
/*											*/
/*			(C)2012-2015 IES-Lab			*/
/*			All rights reserved.			*/
/*------------------------------------------*/
/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "common.h"
#include "osc.h"

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (IMPLEMENTATIONS)											*/
/*------------------------------------------------------------------------------*/

/* Osc_Init(): only EXTERNAL_OSC/CRYSTAL supported! */

void Osc_Init(Osc_Init_Parameter_t *initParameter)
{	
	switch(initParameter->Source_Select)
	{
		case EXTERNAL_OSC:

			switch(initParameter->External_Mode)
			{
				case CRYSTAL:

					if(initParameter->Frequency>6700000){
						OSCXCN = Reg_Field_Set(OSCXCN, BIT2);
						OSCXCN = Reg_Field_Set(OSCXCN, BIT1);
						OSCXCN = Reg_Field_Set(OSCXCN, BIT0);	
					}
					else{
						if(initParameter->Frequency>2200000){
							OSCXCN = Reg_Field_Set(OSCXCN, BIT2);
							OSCXCN = Reg_Field_Set(OSCXCN, BIT1);
							OSCXCN = Reg_Field_Clr(OSCXCN, BIT0);
						}
						else{
							if(initParameter->Frequency>720000){
								OSCXCN = Reg_Field_Set(OSCXCN, BIT2);
								OSCXCN = Reg_Field_Clr(OSCXCN, BIT1);
								OSCXCN = Reg_Field_Set(OSCXCN, BIT0);
							}
							else{
								if(initParameter->Frequency>270000){
									OSCXCN = Reg_Field_Set(OSCXCN, BIT2);
									OSCXCN = Reg_Field_Clr(OSCXCN, BIT1);
									OSCXCN = Reg_Field_Clr(OSCXCN, BIT0);
								}
								else{
									if(initParameter->Frequency>95000){
										OSCXCN = Reg_Field_Clr(OSCXCN, BIT2);
										OSCXCN = Reg_Field_Set(OSCXCN, BIT1);
										OSCXCN = Reg_Field_Set(OSCXCN, BIT0);
									}
									else{
										if(initParameter->Frequency>30000){
											OSCXCN = Reg_Field_Clr(OSCXCN, BIT2);
											OSCXCN = Reg_Field_Set(OSCXCN, BIT1);
											OSCXCN = Reg_Field_Clr(OSCXCN, BIT0);
										}
										else{
											if(initParameter->Frequency>12000){
												OSCXCN = Reg_Field_Clr(OSCXCN, BIT2);
												OSCXCN = Reg_Field_Clr(OSCXCN, BIT1);
												OSCXCN = Reg_Field_Set(OSCXCN, BIT0);
											}
											else{
												OSCXCN = Reg_Field_Clr(OSCXCN, BIT2);
												OSCXCN = Reg_Field_Clr(OSCXCN, BIT1);
												OSCXCN = Reg_Field_Clr(OSCXCN, BIT0);
											}
										}
									}
								}
							}
						}
					}
					OSCXCN = Reg_Field_Set(OSCXCN, BIT6);
					OSCXCN = Reg_Field_Set(OSCXCN, BIT5);
					OSCXCN = Reg_Field_Clr(OSCXCN, BIT4);
					break;

				case DISABLE:
				case COMS_CLK:
				case COMS_CLK_DIV2:
				case RC_OR_C_DIV2:
				case CRYSTAL_DIV2:
				default:
					break;

			}

			while (!(OSCXCN & 0x80));
			OSCICN = Reg_Field_Set(OSCICN, BIT3);
			OSCICN = Reg_Field_Set(OSCICN, BIT7);
			OSCICN = Reg_Field_Clr(OSCICN, BIT2);
			while (!(OSCXCN & 0x80));
			OSCICN = Reg_Field_Clr(OSCICN, BIT7);
			break;

		case INTERNAL_OSC:
			break;

		default:
			break;
	}
}

/* end */