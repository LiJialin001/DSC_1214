#ifndef __OSC_H
#define __OSC_H

/*------------------------------------------------------------------------------*/
/*    GLOBAL TYPES                                                              							*/
/*------------------------------------------------------------------------------*/
typedef enum {
	INTERNAL_OSC,
	EXTERNAL_OSC
}Osc_Source_Select_t;

typedef enum {
	DISABLE,
	COMS_CLK,
	COMS_CLK_DIV2,
	RC_OR_C_DIV2,
	CRYSTAL,
	CRYSTAL_DIV2	
}Osc_External_Mode_t;

typedef struct Osc_Init_Parameter_s{
	Osc_Source_Select_t		Source_Select; 
	Osc_External_Mode_t		External_Mode;
	unsigned long			Frequency;
}Osc_Init_Parameter_t;

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (DECLARATIONS)											*/
/*------------------------------------------------------------------------------*/

void Osc_Init(Osc_Init_Parameter_t *initParameter);

#endif	/* __OSC_H */

/* end */