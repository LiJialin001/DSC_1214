/*====================================================
		
			       数字合成信号发生器
				
						R2023

			作者：1214
			基于 李燕青老师（samlee@tju.edu.cn）	电子系统设计平台实验板演示程序

=====================================================*/
#include "compiler_defs.h"
#include "C8051F020_defs.h"

#include "driver\common.h"
#include "driver\io_config.h"
#include "driver\osc.h"
#include "driver\uart.h"

SBIT (TP0, SFR_P0, 7);
SBIT (TP1, SFR_P0, 6);


// LED数码管显示缓冲区，共6字节
static unsigned char LED_BUF[6]={0xff,0xff,0xff,0xff,0xff,0xff};

// 用于键盘线扫描：		D7=0,	D6=0,	D5=0,	D4=0	
unsigned char LINE[4]={	0x7F,	0xBF,	0xDF,	0xEF};

// 字符对应的段数值：	"0"  "1"  "2"  "3"  "4"  "5"  "6"  "7"  "8"  "9"  "."  "8." " "  	
unsigned char DIGI[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0x00,0xff};

// 键值             	D0=0,	D1=0,	D2=0,	D3=0
unsigned char KEY[4]={	0x0e,	0x0d,	0x0b,	0x07};



/* 用户代码（定时器0中断服务,100us周期） */
void t0_isr_callback(void)
{

}


/* 用户代码（主循环）*/
int main(void)
{

	Osc_Init_Parameter_t Osc_Init_Parameter;	// 振荡器初始化参数


	// 中断全局关闭
	EA=0;	

	//关闭开门狗定时器
	WDTCN = 0xDE;
	WDTCN = 0xAD;

	//初始化振荡器
	Osc_Init_Parameter.Source_Select = EXTERNAL_OSC;
	Osc_Init_Parameter.External_Mode = CRYSTAL;
	Osc_Init_Parameter.Frequency = 24000000;	
	Osc_Init(&Osc_Init_Parameter);
	Loop_Delay(100);

	io_config();
	io_init();
	uart0_init();


	//设置串口0所占用的IO口：P0.0和P0.1
	XBR0=Reg_Field_Set(XBR0,BIT2);
	//使能交叉开关
	XBR2=Reg_Field_Set(XBR2,BIT6);
	//使能内部电压基准
	REF0CN=Reg_Field_Set(REF0CN,BIT1);
	REF0CN=Reg_Field_Set(REF0CN,BIT0);
	//使能DAC0，DAC0H: 8bit; DAC0L: 4bit
	DAC0CN=Reg_Field_Set(DAC0CN,BIT7);
	DAC0CN=Reg_Field_Set(DAC0CN,BIT2);

	DAC0L=0;
	DAC0H=0;

	TL0=(256-200);	// when 24MHz & SYSCLK/12, 10kHz timeout 
	TH0=(256-200);	// reload


	EA=1;
	ET0=1;


	TMOD=0x02;

	TR0=1;


	return 0;

}



/* system call: */
void putchar (char c) 
{
	while (!TI); /* assumes UART is initialized */
	TI = 0;
	SBUF = c;
}


/* interrupt entrances */
void t0_isr(void) __interrupt (1)	// 定时器0中断服务程序
{
	t0_isr_callback();

}

