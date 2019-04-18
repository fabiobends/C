#include <lab07_.h>
#include <lcd.c>
                   // Interrupção com o timer0
int8 cnt, seg, min;// definição de variáveis globais
#INT_TIMER0        // código da interrupção do timer0
void timer0_isr(){
  cnt=(cnt==184)?0:cnt+1;
  seg=(cnt==0)?((seg==59)?0:seg+1):seg;          // função que conta os segundos e
  min=(cnt==0 && seg==0)?((min==59)?0:min+1):min;// minutos através da interrupção
  }
  
void main()
  {
  int8 seg_old=99;
  // configura o timer0 para estourar em 5,4ms
  setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
  // outras rotinas de configuração 
  seg=0; min=0; cnt=0;           // inicialização de variáveis
  enable_interrupts(INT_TIMER0); // habilita interrupção timer0
  enable_interrupts(GLOBAL);     // habilita interrupção global
  lcd_init();                    // inicializa o LCD
  while(TRUE){
  if(seg!=seg_old){              // 
  lcd_gotoxy(1,1);               // posicionamento do texto
  printf(lcd_putc,"Tempo:\n");   // texto
  lcd_gotoxy(6,2);               // posicionamento do contador
  printf(lcd_putc,"%02u:%02u",min,seg);// contador
  seg_old=seg;                   // novo valor para comparação
      }   
   }
}
