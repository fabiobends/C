#include <lab06.h>
#include <LCD.C>

void main()
{
   int16 cnt;  // variáveis para contador
   lcd_init(); // inicialização do LCD
   cnt=CNT_MAX;// inicialização para começar do zero
   
   while(TRUE)
   {
      cnt=(cnt==CNT_MAX)? 0 : cnt+1;// contador
      lcd_gotoxy(1,1);              // posicionamento da frase da linha 15
      lcd_putc("Tempo:\n");         // texto exibido em (1,1)
      lcd_gotoxy(8,2);              // posicionamento de centralizado dos números a ser exibidos
      printf(lcd_putc, "%ld",cnt);  // número exibido
      delay_ms(REFRESH_INTERNAL);   // delay das transições
   }
}
