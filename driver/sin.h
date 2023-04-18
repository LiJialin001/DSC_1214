#ifndef __SIN_H
#define __SIN_H

/*------------------------------------------------------------------------------*/
/*    INCLUDES																	*/
/*------------------------------------------------------------------------------*/
#include "common.h"

/*------------------------------------------------------------------------------*/
/*    DEFINE                                                                    */
/*------------------------------------------------------------------------------*/
#define SIN_TABLE_SIZE 512


/*------------------------------------------------------------------------------*/
/*    GLOBAL TYPES                                                              */
/*------------------------------------------------------------------------------*/

extern unsigned int sinTable[512];

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (DECLARATIONS)											*/
/*------------------------------------------------------------------------------*/
void generate_sine_wave(unsigned int sinIndex,unsigned int frequency, unsigned int amplitude);


#endif	/* __SIN_H */

/* end */