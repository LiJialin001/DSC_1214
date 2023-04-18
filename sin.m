/*====================================================
             
                     电子系统设计平台实验板演示程序
                            作者：梁，黄，姬
                                   Release 2016
 
=====================================================*/
 
#include "compiler_defs.h"
 
#include "C8051F020_defs.h"
 
#include "driver\common.h"
 
#include "driver\io_config.h"
 
#include "driver\osc.h"
 
#include "driver\uart.h"
 
 
 
SBIT (TP0, SFR_P0, 7);
 
SBIT (TP1, SFR_P0, 6);
 
 
 
static unsigned char LED_BUF[6]={0xc0,0xf9,0xc0,0xc0,0xa4,0x40}; // LED数码管显示缓冲区，共6字节
 
static double DACAM=0.0;
 
static unsigned int DACFM=0;
 
static unsigned int tun=0;          //将频率以100HZ为中心，分为两部分
 
static unsigned int Mu_cnt=0;                                                                                                      //sin函数数据表
 
static unsigned char SinData[256]={         53,54,55,57,58,60,61,62,63,65,66,67,68,70,71,72,73,75,75,77,78,79,80,81,
 
                                                                      83,83,85,85,87,88,89,90,90,91,92,93,94,95,95,96,97,98,98,99,100,100,101,
 
                                                                      101,102,103,103,103,104,104,104,105,105,105,105,105,105,106,106,106,106,
 
                                                                      106,106,106,105,105,105,105,105,105,104,104,103,103,103,102,102,101,100,
 
                                                                      100,100,99,98,98,97,96,95,94,93,93,92,91,90,89,88,87,86,85,84,83,82,81,80,
 
                                                                      78,78,76,75,74,73,71,70,69,68,66,65,64,63,61,60,59,58,56,55,54,52,51,50,48,
 
                                                                      47,46,45,43,42,41,40,38,37,36,35,33,32,31,30,28,28,26,25,24,23,22,21,20,19,
 
                                                                      18,17,16,15,14,13,13,12,11,10,9,8,8,7,6,6,5,5,4,4,3,3,3,2,2,1,1,1,1,0,0,0,0,
 
                                                                      0,0,0,0,0,0,0,0,1,1,1,2,2,2,3,3,3,4,5,5,5,6,7,8,8,9,10,10,11,12,13,14,15,15,
 
                                                               16,17,18,19,20,21,23,23,25,25,27,28,29,30,31,33,34,35,36,38,39,40,41,43,44,45,46,48,49,50,52,53};
 
 
 
 
 
static unsigned char AmData[256]={ 127,148,168,186,201,212,218,218,213,202,187,167,145,121,97,74,55,39,28,23,25,32,46,65,88,
 
                                                        114,141,167,191,212,228,238,242,238,228,211,189,163,134,105,77,51,30,15,6,5,11,24,44,68,97,
 
                                                        127,158,186,212,232,246,253,252,244,228,207,180,150,119,89,60,36,17,5,1,4,14,31,54,82,112,142,
 
                                                        172,199,221,237,247,249,244,232,214,190,163,134,105,78,54,34,20,13,13,20,33,52,74,100,127,154,178,
 
                                                        199,215,226,231,229,221,208,190,169,145,121,98,77,59,46,38,36,39,47,60,77,96,117,137,157,174,189,199,
 
                                                        204,205,201,193,181,166,149,131,114,98,84,73,65,62,62,66,74,85,98,112,127,141,154,166,174,180,182,181,
 
                                                        176,169,160,149,136,124,112,101,92,85,81,80,82,86,92,101,111,122,132,143,152,160,166,169,170,168,164,157,
 
                                                        149,140,130,119,109,100,93,88,85,84,86,91,98,106,116,127,138,148,158,165,171,174,174,171,166,158,148,136,124,
 
                                                        111,100,89,81,75,72,73,77,84,94,106,120,134,149,163,175,184,190,193,191,185,176,164,148,131,114,96,80,67,57,51,49,52,60,72,88,107,127};
 
 
 
/* 用户代码（定时器0中断服务,100us周期） */
 
void t0_isr_callback(void)
 
{
 
              static unsigned int cnt=0;
 
              static unsigned int tun_cnt=0;
 
              static unsigned char led_cnt=0;
 
              static unsigned int Sincut=0;            
 
       TP0=!TP0;     // TP0 翻转，用来指示中断触发频率或周期 
 
       TP1=1;          // TP1 置高，TP1的高电平持续时间代表中断服务程序执行时间
 
      
 
       if(tun_cnt>10)       //确保能进入波形输出程序
 
              {
 
                     tun_cnt=0;
 
              }
 
       tun_cnt++;
 
      
 
       if(tun_cnt==tun)
 
              {
 
                     tun_cnt=0;
 
                     if(Mu_cnt==0)
 
                     {
 
                            DAC0H=SinData[Sincut]*DACAM;
 
                     }
 
              else
 
              {
 
                     DAC0H=AmData[Sincut]*DACAM;
 
              }
 
                     Sincut+=DACFM;                                                  //抽样，实现频率的变化
 
              }
 
       if(Sincut>255)                                                               //周期
 
              {
 
                     Sincut=0;
 
              }
 
 
 
       DAC1H+=1;  // DAC1 输出锯齿波，递减
 
      
 
       // 每十次中断执行一次以下代码，扫描一位LED
 
       if(cnt==10)
 
       {
 
 
 
              cnt=0;
 
             
 
              switch(led_cnt)
 
              {
 
                     case 0:
 
                            P2=0x01;
 
                            P1=LED_BUF[0];
 
                            led_cnt=1;
 
                            break;
 
                     case 1:
 
                            P2=0x02;
 
                            P1=LED_BUF[1];
 
                            led_cnt=2;
 
                            break;
 
                     case 2:
 
                            P2=0x04;
 
                            P1=LED_BUF[2];
 
                            led_cnt=3;
 
                            break;
 
                     case 3:
 
                            P2=0x08;
 
                            P1=LED_BUF[3];
 
                            led_cnt=4;
 
                            break;
 
                     case 4:
 
                            P2=0x10;
 
                            P1=LED_BUF[4];
 
                            led_cnt=5;
 
                            break;
 
                     case 5:
 
                            P2=0x20;
 
                            P1=LED_BUF[5];
 
                            led_cnt=0;
 
                            break;
 
                     default:
 
                            break;
 
              }
 
 
 
              cnt++;
 
 
 
       }
 
       else
 
       {
 
              cnt++;
 
       }
 
      
 
       TP1=0;   // TP1 置低，TP1的高电平持续时间代表中断服务程序执行时间
 
}
 
 
 
/* 用户代码（主循环）*/
 
int main(void)
 
{
 
       unsigned int i,j;
 
/
 
       unsigned int key=0;
 
       unsigned int TranAFM=0;
 
       int Integer=0;
 
      int DeNum=0;
 
       double AM_Value=0.2;
 
       double   Test_AM=0.2;
 
       int cut_FM=0;
 
       unsigned int FM_Value=10;
 
       unsigned int Test_FM=0;
 
       unsigned int FM_Bit[6]={0,0,0,0,0,0};
 
       unsigned char LED_FM[6]={0xc0,0xf9,0xc0,0xc0,0xff,0xff};                    //频率显示缓存,初始显示10
 
       unsigned int Values_FM[7]={10,20,50,100,200,500,1000};                           //频率的可能取值
 
       unsigned char LED_AM[6]={0xff,0xff,0xff,0xff,0xa4,0x40};              //幅度显示缓存,初始显示0.2
 
       unsigned int  Samp=0;                                                                                                                                            //Samp为采样间隔
 
       unsigned int  Fun=0;
 
       unsigned int  Mu=0;
 
/       
 
       Osc_Init_Parameter_t Osc_Init_Parameter; // 振荡器初始化参数
 
      
 
      
 
       // 用于键盘线扫描：         D7=0,    D6=0,    D5=0,    D4=0    
 
       unsigned char LINE[4]={      0x7F,      0xBF,      0xDF,     0xEF};
 
 
 
       // 字符对应的段数值：      "0"  "1"  "2"  "3"  "4"  "5"  "6"  "7"  "8"  "9"  "."  "8." " " 
 
       unsigned char DIGI[13]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x7f,0x00,0xff};
 
       unsigned char TEXT[6]={0xc0,0xc0,0xc0,0xc0,0xc0,0xc0};
 
 
 
       // 键值             D0=0,    D1=0,    D2=0,    D3=0
 
       unsigned char KEY[4]={       0x0e,      0x0d,      0x0b,      0x07};
 
 
 
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
 
       //使能DAC1，DAC1H: 8bit; DAC1L: 4bit
 
       DAC1CN=Reg_Field_Set(DAC1CN,BIT7);
 
       DAC1CN=Reg_Field_Set(DAC1CN,BIT2);
 
 
 
       DAC0L=0;
 
       DAC0H=0;
 
       DAC1L=0;
 
       DAC1H=0;
 
 
 
       /*启动信息*/
 
       printf("\n");
 
       printf("Tianjin University\n");
 
       printf("Electronic System Design Kit\n");
 
       printf("Version 1.0 [C]2012-2016\n");
 
       printf("----------------------------\n");
 
       printf("MCU: C8051F020/24MHz\n");
 
       printf("PWR: 3.3V/100mA\n");
 
       printf("\n");
 
      
 
 
 
       //
 
       //
 
       // Timer 0/1 initialization
 
       //
 
       //
 
      
 
       //                  BIT7 BIT6 BIT5 BIT4 BIT3 BIT2 BIT1 BIT0
 
       //    ---------------------------------------------------------------------
 
       //    TCON:    TF1        TR1        TF0        TR0        IE1         IT1         IE0         IT0
 
       //                  0            0            0            1            0            0            0            0
 
       //                 
 
       //    TMOD:   GATE1    C/T1       T1M1     T1M0     GATE0    C/T0       T0M1     T0M0
 
       //                  0            0            0            0            0            0            1            0
 
       //
 
       //    IE:           EA          IEGF0     ET2        ES0        ET1        EX1        ET0        EX0
 
       //                  1            0            0            0            0            0            1            0
 
      
 
       TL0=(256-78);      // when 24MHz & SYSCLK/12, 10kHz timeout
 
       TH0=(256-78);     // reload
 
      
 
       EA=1;
 
       ET0=1;
 
 
 
       TMOD=0x02;
 
 
 
       TR0=1;
 
 
 
//
 
 
 
 
 
 
 
#if 1
 
       while(1)
 
       {
 
                           
 
                            P3=LINE[0];                        //扫描第一行键盘
 
                            Delay10ms;
 
                            if((P3&0x0f)==KEY[0])         //第一个按键是否按下,AMFM转换
 
                            {
 
                                   Delay10ms;                        //去抖动
 
                                   if((P3&0x0f)==KEY[0]) 
 
                                          {
 
                                                 key++;
 
                                                 TranAFM=key%2; 
 
                                                 while((P3&0x0f)==KEY[0]);                //直到按键松开
 
                                          }     
 
                            }
 
                                   Delay10ms;
 
                                   if((P3&0x0f)==KEY[1])         //更新DAC显示
 
                            {
 
                                   Delay10ms;                        //去抖动
 
                                   if((P3&0x0f)==KEY[1]) 
 
                                          {
 
                                                 DACAM=AM_Value;
 
                                                 DACFM=Samp;   
 
                                                 tun=Fun;
 
                                                
 
                                                 for(i=0;i<3;i++)           //更新提示
 
                                                                      {
 
                                                                             P4=0xF3;
 
                                                                          Loop_Delay(20);
 
                                                                             P4=0xF0;
 
                                                                             Loop_Delay(20);
 
                                                                      }
 
                                                 while((P3&0x0f)==KEY[1]);                //直到按键松开
 
                                          }     
 
                            }
 
 
 
                            if(TranAFM==0)                 //显示幅度
 
                                   {
 
                                                        //立即显示幅度的值
 
                         
 
                                       LED_BUF[5]=LED_AM[5];                   //LED_AM为幅度显示缓存
 
                                        LED_BUF[4]=LED_AM[4];
 
                                        P4=0xF7;
 
                                          Test_AM=AM_Value;                        //Test_AM保存AM_Value的初值
 
                                          if((P3&0x0f)==KEY[2])         //检测KEY13是否按下，KEY13为加按键
 
                                                 {
 
                                                        Delay10ms;
 
                                                        if((P3&0x0f)==KEY[2])
 
                                                        {
 
                                                               AM_Value=AM_Value+0.2;        //AM_Value为幅度值，double型数
 
                                                               while((P3&0x0f)==KEY[2]);
 
                                                        }
 
                                                
 
                                                               if(AM_Value>2.2)                              //容错处理，保持显示值不变，闪灯提示
 
                                                               {
 
                                                                      AM_Value=AM_Value-0.2;
 
                                                                      for(i=0;i<4;i++)
 
                                                                      {
 
                                                                             P4=0xFF;
 
                                                                        Loop_Delay(100);
 
                                                                             P4=0xF0;
 
                                                                             Loop_Delay(100);
 
                                                                      }
 
                                                               }
 
                                                       
 
                                                 }     
 
                                                 Delay10ms;
 
                                          if((P3&0x0f)==KEY[3])         //检测KEY14是否按下，KEY14为减按键
 
                                                 {
 
                                                        Delay10ms;
 
                                                        if((P3&0x0f)==KEY[3])
 
                                                        {
 
                                                                      AM_Value=AM_Value-0.2;         //AM_Value为幅度值，double型数
 
                                                                      while((P3&0x0f)==KEY[3]);
 
                                                        }
 
                                                
 
                                                        if(AM_Value<0.2)                              //容错处理，保持显示值不变，闪灯提示
 
                                                               {
 
                                                                      AM_Value=AM_Value+0.2;
 
                                                                      for(i=0;i<4;i++)
 
                                                                      {
 
                                                                             P4=0xFF;
 
                                                                        Loop_Delay(100);
 
                                                                             P4=0xF0;
 
                                                                             Loop_Delay(100);
 
                                                                      }
 
                                                               }
 
                                                 }     
 
                                          if(Test_AM!=AM_Value)             //如果有按键按下则刷新LED的值
 
                                                        {
 
                                                          Integer=AM_Value;
 
                                                               DeNum=(AM_Value-Integer)*10;
 
                                                               LED_AM[5]=DIGI[Integer]&DIGI[10];
 
                                                               LED_AM[4]=DIGI[DeNum];
 
                                                              
 
                                                        }
 
                                                                                                 
 
                              }                      
 
                            else                                                  //显示频率
 
                                   {
 
                                          for(i=0;i<4;i++)           //立即显示频率的值
 
                                          {
 
                                                 LED_BUF[i]=LED_FM[i];               //LED_FM为频率显示缓存
 
                                          }
 
 
 
                                          P4=0xFE;
 
                                          if((P3&0x0f)==KEY[2])                //检测KEY13是否按下
 
                                          {
 
                                                 Delay10ms;
 
                                                 if((P3&0x0f)==KEY[2])
 
                                                 {
 
                                                        cut_FM++;
 
                                                        while((P3&0x0f)==KEY[2]);
 
                                                 }
 
 
 
                                                 if(cut_FM>6)                              //容错处理，保持显示值不变，闪灯提示
 
                                                               {
 
                                                                      cut_FM--;
 
                                                                      for(i=0;i<4;i++)
 
                                                                      {
 
                                                                             P4=0xFF;
 
                                                                        Loop_Delay(100);
 
                                                                             P4=0xF0;
 
                                                                             Loop_Delay(100);
 
                                                                             }
 
                                                                      }
 
                                   }
 
                                   if((P3&0x0f)==KEY[3])                //检测KEY14是否按下
 
                                   {
 
                                                 Delay10ms;
 
                                                 if((P3&0x0f)==KEY[3])
 
                                                 {
 
                                                        cut_FM--;
 
                                                        while((P3&0x0f)==KEY[3]);
 
                                                 }
 
 
 
                                  
 
                                          if(cut_FM<0)                              //容错处理，保持显示值不变，闪灯提示
 
                                                               {
 
                                                                      cut_FM++;
 
                                         
 
                                                                      for(i=0;i<4;i++)
 
                                                                      {
 
                                                                             P4=0xFF;
 
                                                                        Loop_Delay(100);
 
                                                                             P4=0xF0;
 
                                                                             Loop_Delay(100);
 
                                                                             }
 
                                                                      }
 
                                   }
 
                               Test_FM=FM_Value;                    //Test_FM保存FM_Value的初值
 
                                    FM_Value=Values_FM[cut_FM];
 
                                    if(Test_FM!=FM_Value)                                         //如果有按键按下，则刷新LED的值
 
                                          {
 
                                         
 
                                           FM_Bit[3]=FM_Value/1000;
 
                                           FM_Bit[2]=(FM_Value%1000)/100;
 
                                           FM_Bit[1]=(FM_Value%100)/10;
 
                                           FM_Bit[0]=FM_Value%10;
 
                                           for(i=0;i<4;i++)
 
                                           {
 
                                                j=FM_Bit[i];
 
                                                LED_FM[i]=DIGI[j];
 
                                           }
 
                                               
 
                                          }
 
                                   }
 
                            if(FM_Value<100)               //将频率以100HZ为中心分成两部分
 
                                   {
 
                                          Fun=10;
 
                                          Samp=FM_Value/10;
 
                                   }
 
                            else
 
                            {
 
                                   Fun=1;
 
                                   Samp=FM_Value/100;
 
                            }
 
 
 
                            P3=LINE[1];                        //扫描第一行键盘
 
                            Delay10ms;
 
                            if((P3&0x0f)==KEY[0])         //第一个按键是否按下,AMFM转换
 
                            {
 
                                   Delay10ms;                        //去抖动
 
                                   if((P3&0x0f)==KEY[0]) 
 
                                          {
 
                                                 Mu++;
 
                                                 while((P3&0x0f)==KEY[0]);                //直到按键松开
 
                                          }
 
                                   Mu_cnt=Mu%2;    
 
                            }     
 
       }
 
#endif
 
 
       // 前台程序完成，进入中断事件驱动状态
 
       while(1);
 
 
 
}
 
 
 
 
 
/* system call: */
 
void putchar (char c)
 
{
 
       while (!TI); /* assumes UART is initialized */
 
       TI = 0;
 
       SBUF = c;
 
}
 
 
 
 
 
/* interrupt entrances */
 
void t0_isr(void) __interrupt (1)   // 定时器0中断服务程序
 
{
 
       t0_isr_callback();
 
 
 
}
 
 
 
/* end */
 
 
 
 
 
void Delay10ms (void)
 
{
 
       unsigned int a;
 
       for(a=0;a<10;a++)
 
       {
 
              Delay1ms;
 
       }
 
}