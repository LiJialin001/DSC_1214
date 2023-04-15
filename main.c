/*====================================================
		
			       ���ֺϳ��źŷ�����
				
						R2023

			���ߣ�1214
			���� ��������ʦ��samlee@tju.edu.cn��	����ϵͳ���ƽ̨ʵ�����ʾ����

=====================================================*/
#include "compiler_defs.h"
#include "C8051F020_defs.h"

#include "driver\common.h"
#include "driver\io_config.h"
#include "driver\osc.h"
#include "driver\uart.h"
#include "driver\dac.h"
#include "driver\sin.h"

SBIT (TP0, SFR_P0, 7);
SBIT (TP1, SFR_P0, 6);


// LED�������ʾ����������6�ֽ�
static unsigned char LED_BUF[6]={0xff,0xff,0xff,0xff,0xff,0xff};

// ���ڼ�����ɨ�裺		D7=0,	D6=0,	D5=0,	D4=0	
unsigned char LINE[4]={	0x7F,	0xBF,	0xDF,	0xEF};

// �ַ���Ӧ�Ķ���ֵ��	"0"  "1"  "2"  "3"  "4"  "5"  "6"  "7"  "8"  "9"  "."  "8." " "  	
unsigned char DIGI[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0x00,0xff};

// ��ֵ             	D0=0,	D1=0,	D2=0,	D3=0
unsigned char KEY[4]={	0x0e,	0x0d,	0x0b,	0x07};



/* �û����루��ʱ��0�жϷ���,100us���ڣ� */
void t0_isr_callback(void)
{
	static unsigned int cnt=0;		//cnt��counter ����˼����������ע���� static ��! ... ...
	TP0=!TP0; 						// TP0 ��ת������ָʾ�жϴ���Ƶ�ʻ�����
	TP1=1; 							// TP1 �øߣ�TP1 �ĸߵ�ƽ����ʱ������жϷ������ִ��ʱ��
	cnt++; 							// ��������1
	if (cnt>=512) cnt=0; 			// ��������������¼���
	generate_sine_wave(cnt,100,1);  // �������Ҳ�
	TP1=0; 							// TP1 �õͣ�TP1 �ĸߵ�ƽ����ʱ������жϷ������ִ��ʱ��
}


/* �û����루��ѭ����*/
int main(void)
{
	Osc_Init_Parameter_t Osc_Init_Parameter;	// ������ʼ������

	// �ж�ȫ�ֹر�
	EA=0;	

	//�رտ��Ź���ʱ��
	WDTCN = 0xDE;
	WDTCN = 0xAD;

	//��ʼ������
	Osc_Init_Parameter.Source_Select = EXTERNAL_OSC;
	Osc_Init_Parameter.External_Mode = CRYSTAL;
	Osc_Init_Parameter.Frequency = 24000000;	
	Osc_Init(&Osc_Init_Parameter);
	Loop_Delay(100);

	io_config();
	io_init();
	uart0_init();
	dac0_init();


	//���ô���0��ռ�õ�IO�ڣ�P0.0��P0.1
	XBR0=Reg_Field_Set(XBR0,BIT2);
	//ʹ�ܽ��濪��
	XBR2=Reg_Field_Set(XBR2,BIT6);


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
void t0_isr(void) __interrupt (1)	// ��ʱ��0�жϷ������
{
	t0_isr_callback();

}

