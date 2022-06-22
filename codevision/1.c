/*******************************************************
This program was created by the
CodeWizardAVR V3.12 Advanced
Automatic Program Generator
� Copyright 1998-2014 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project : 
Version : 
Date    : 6/23/2017
Author  : 
Company : 
Comments: 


Chip type               : ATmega32
Program type            : Application
AVR Core Clock frequency: 8.000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 512
*******************************************************/

#include <mega32.h>
#include <delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <alcd.h>
  char i,jump[6],j,k,t,time2,x,start=0,m=0,lcd[20],str[20];
  float w=0,time,t1;
  int  time1,loop,timing=0;
#define ADC_VREF_TYPE ((0<<REFS1) | (1<<REFS0) | (0<<ADLAR))


unsigned int read_adc(unsigned char adc_input)
{
ADMUX=adc_input | ADC_VREF_TYPE;
// Delay needed for the stabilization of the ADC input voltage
delay_us(10);
// Start the AD conversion
ADCSRA|=(1<<ADSC);
// Wait for the AD conversion to complete
while ((ADCSRA & (1<<ADIF))==0);
ADCSRA|=(1<<ADIF);
return ADCW;
}

 void gameover(void) 
 { 
   lcd_clear();
   printf("final score:");
   putchar(13);
   ftoa(w,1,str);
   sprintf(lcd,"%5s",str);
   puts(lcd);
   putchar(13);
     
   for(i=0;i<4;i++){
   lcd_clear();
   lcd_gotoxy(3,1);
   lcd_puts("GAME OVER");
   delay_ms(500);
   lcd_clear();
   delay_ms(500); 
   }  
         
   ftoa(w,1,str);
   sprintf(lcd,"YOUR SCORE IS:%5s",str);
   lcd_clear();
   lcd_gotoxy(0,1);
   lcd_puts(lcd);
   delay_ms(2000);
   while(1){start=0;}   
 } 
 
 float difficulty(void)
 {
   time1=read_adc(0);
   t1=(time1*1.2)/1023+.3;
   time2=(int)(t1*10);
   time=time2/10+(time2%10)*.1;
   return time;
 } 

 void chap(void)
{
       time=difficulty();                            
       t=m*3;
       for(j=0;j<=t;j=j+3)
       {
      for(i=0;i<4;i++)
      {
        if(i!=jump[j/3])
        { 
          lcd_gotoxy(j,i);
          lcd_puts("|"); 
          lcd_gotoxy(13,x);
          lcd_puts("*");
        }
       } 
       }      
}
 interrupt [EXT_INT0] void ext_int0_isr(void)
{
if(start!=0){
if(x!=3){
x=x+1;
lcd_clear();
chap();
}
}
}


interrupt [EXT_INT1] void ext_int1_isr(void)
{
if(start!=0){
if(x!=0){
x=x-1;
lcd_clear();
chap();
}
}
}

interrupt [EXT_INT2] void ext_int2_isr(void)
{
  start=1;  
}

void delay(void)
{
   loop=time*40;
   timing=0;
   while(timing<loop)
   {        
   } 
}

interrupt [TIM0_OVF] void timer0_ovf_isr(void)
{
TCNT0=0x3D;
timing++;
}
 

void main(void)
{
GICR|=(1<<INT1) | (1<<INT0) | (1<<INT2);
MCUCR=(1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
MCUCSR=(0<<ISC2);
GIFR=(1<<INTF1) | (1<<INTF0) | (1<<INTF2);
ADMUX=ADC_VREF_TYPE;
ADCSRA=(1<<ADEN) | (0<<ADSC) | (0<<ADATE) | (0<<ADIF) | (0<<ADIE) | (0<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
SFIOR=(0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0);
UCSRA=(0<<RXC) | (0<<TXC) | (0<<UDRE) | (0<<FE) | (0<<DOR) | (0<<UPE) | (0<<U2X) | (0<<MPCM);
UCSRB=(0<<RXCIE) | (0<<TXCIE) | (0<<UDRIE) | (0<<RXEN) | (1<<TXEN) | (0<<UCSZ2) | (0<<RXB8) | (0<<TXB8);
UCSRC=(1<<URSEL) | (0<<UMSEL) | (0<<UPM1) | (0<<UPM0) | (0<<USBS) | (1<<UCSZ1) | (1<<UCSZ0) | (0<<UCPOL);
UBRRH=0x00;
UBRRL=0x33;
TCCR0=(0<<WGM00) | (0<<COM01) | (0<<COM00) | (0<<WGM01) | (1<<CS02) | (0<<CS01) | (1<<CS00);
TCNT0=0x3D;
OCR0=0x00;
TIMSK=(0<<OCIE2) | (0<<TOIE2) | (0<<TICIE1) | (0<<OCIE1A) | (0<<OCIE1B) | (0<<TOIE1) | (0<<OCIE0) | (1<<TOIE0);
#asm("sei")
lcd_init(16);
DDRD=0X00;
PORTD=0XFF;
DDRB=0X00;
PORTB=0XFF; 
lcd_gotoxy(4,1);
lcd_puts("WELCOME!");
delay_ms(2000);
while (1)
      {  
        if(start!=0){ 
        lcd_clear();
         for(k=0;k<5;k=k+1){
        jump[5-k]=jump[4-k];
        } 
        jump[0]=(int)((rand()/(RAND_MAX/4)));                  
        chap();
       
         if(m==5){
         if(x!=jump[5])
         {
         gameover();
         }
          w=1+(1.5-time)/.6+w; 
         } 
         
         delay(); 
      
         //delay_ms(time*1000); 
          
        m++;
        if(m>5)
        {
         m=5;
        } 
      
         
         ftoa(w,1,str);
         sprintf(lcd,"%5s",str);
         puts(lcd);
         putchar(13);
       
        
       }
       
       if(start==0)
       { 
         time=difficulty(); 
         ftoa(time,1,str);
         sprintf(lcd,"HARDNESS:%4s",str);
         lcd_clear();
         lcd_gotoxy(2,1);
         lcd_puts(lcd);
         for(i=0;i<time2;i++)
      {
         lcd_gotoxy(i,3);
         lcd_putchar(0xff);
       } 
       delay_ms(200);  
       } 
       
}
}
