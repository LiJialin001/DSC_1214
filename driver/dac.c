#include "dac.h"
#include "sin.h"
#include "common.h"


/*------------------------------------------------------------------------------*/
/*    MACROS																	*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*    GLOBAL VARS																*/
/*------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------*/
/*    GLOBAL FUNCTIONS (IMPLEMENTATIONS)									    */
/*------------------------------------------------------------------------------*/

/*!
* \brief Initialize the DAC0.
*/
void dac0_init(void)
{
    	//使能内部电压基准
	REF0CN=Reg_Field_Set(REF0CN,BIT1);
	REF0CN=Reg_Field_Set(REF0CN,BIT0);
	//使能DAC0，DAC0H: 8bit; DAC0L: 4bit
	DAC0CN=Reg_Field_Set(DAC0CN,BIT7);
	DAC0CN=Reg_Field_Set(DAC0CN,BIT2);

	DAC0L=0;
	DAC0H=0;
}

/*
* DAC输出电压
*/
void set_dac_voltage(unsigned int sinIndex)
{
    unsigned int dacValue;
    
    dacValue = sinTable[sinIndex];

 //   DAC0L = (dacValue % 16) * 16;
//    DAC0H = dacValue / 16;
    
    DAC0L = dacValue & 0x0F;
    DAC0H = (dacValue >> 4) & 0xFF;
  //  DAC0H += 32;
}

