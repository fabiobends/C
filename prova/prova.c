#include <prova.h>
#include <lcd.c>
#include <stdio.h>
                   
int16 pulses;
int16 cnt=0;
float freq;

#INT_TIMER2
void timer2_isr()
{
   cnt=cnt+1;
   pulses=get_timer0();
   set_timer0(0);
}

void main()
{
  //float freq;
  setup_timer_0(RTCC_EXT_L_TO_H|RTCC_DIV_1);
  setup_timer_2(T2_DIV_BY_16,200, 15);
  lcd_init();
  enable_interrupts(INT_TIMER2);
  enable_interrupts(GLOBAL);                    
  while(TRUE)  
   {
   if(cnt==63)
      {
      if(pulses!=0)
         {  
      freq=(float)pulses/4;
      lcd_gotoxy(1,1);
	  printf("Frequencia:\n");                 
      lcd_gotoxy(5,2);                  
      printf("%.3f kHz", freq);
      cnt=0;
         }
      if(pulses==0)
         {
      lcd_gotoxy(1,1);                  
      printf("fora de escala!");
         }  
      }
   }
}

