#include <lab07_.h>
#include <lcd.c>
                   // Interrup��o com o timer0
int8 cnt, seg, min;// defini��o de vari�veis globais
#INT_TIMER0        // c�digo da interrup��o do timer0
void timer0_isr(){
  cnt=(cnt==184)?0:cnt+1;
  seg=(cnt==0)?((seg==59)?0:seg+1):seg;          // fun��o que conta os segundos e
  min=(cnt==0 && seg==0)?((min==59)?0:min+1):min;// minutos atrav�s da interrup��o
  }
  
void main()
  {
  int8 seg_old=99;
  // configura o timer0 para estourar em 5,4ms
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
  // outras rotinas de configura��o 
  seg=0; min=0; cnt=0;           // inicializa��o de vari�veis
  enable_interrupts(INT_TIMER0); // habilita interrup��o timer0
  enable_interrupts(GLOBAL);     // habilita interrup��o global
  lcd_init();                    // inicializa o LCD
  while(TRUE){
  if(seg!=seg_old){              // 
  lcd_gotoxy(1,1);               // posicionamento do texto
  printf(lcd_putc,"Tempo:\n");   // texto
  lcd_gotoxy(6,2);               // posicionamento do contador
  printf(lcd_putc,"%02u:%02u",min,seg);// contador
  seg_old=seg;                   // novo valor para compara��o
      }   
   }
}
