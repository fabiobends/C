#include <lab08.h>
#include <lcd.c>

// declara��o de variveis
int1 done=1; // tecla pressionada
int8 key=0;  // tecla inicial
int1 ok=0;   // reconhecimento do LCD
char character=0;

void get_line(int i)
{
   output_b((0x01<<i)); //de zero a 3
}

int8 calc(int8 line, int8 row)
{
   int j;               // valor para implementa��o da fun��o
   j = row + 4*line;
   return j;
}

void keypad_scan()
{
   int8 row, line;
   static int1 entry=0 ; // seguran�a
   static int position, old_position; //qual foi apertado
   static int8 cnt=0; // debounce
   entry=0;
   for(line=0;line<4;line++)
   {
      get_line(line);
      delay_us(10);
      for(row=0; row<4; row++)
      {
         if(input(row+PIN_B4))
            { 
            old_position=position;
            position=calc(line,row);
            entry=1;
            if(cnt>=TIME && entry && position==old_position && !done) // tempo requerido 
            {
               done=1;
               ok=0;
               key=position;
            }
            if(position!=old_position){
               cnt=0;
            }
         }  
      }
      }
      if(!entry){
      cnt=0;
      done=0;
      }
      if(position==old_position && cnt<TIME){// tecla continua pressionada
      cnt=cnt+1;
      }
   }
   


void input_code( )// decodifica as teclas
{
   // possibilidades
   if(done && !ok)
   {
      switch(key)
      {
         case 0:
            character='7';
            break;
         case 1:
            character='8';
            break;
         case 2:
            character='9';
            break;
         case 3:
            character='/';
            break;
         case 4:
            character='4';
            break;
         case 5:
            character='5';
            break;
         case 6:
            character='6';
            break;
         case 7:
            character='X';
            break;
         case 8:
            character='1';
            break;
         case 9:
            character='2';
            break;
         case 10:
            character='3';
            break;
         case 11:
            character='-';
            break;
         case 12:
            character='C';
            break;
         case 13:
            character='0';
            break;
         case 14:
            character='=';
            break;
         case 15:
            character='+';
            break;
         default:
            character='!';
            break;
      
      }
   }
}

void lcd_update()// atualiza o LCD
{

   if(!ok)
   {
      ok=1;
      printf(lcd_putc,"%c",character);
      character=0;
   }
}

void main()
{
   lcd_init();
   set_tris_b(0xf0);// bits 7-4 s�o colunas (row) e 3-0 s�o linhas (line)
   port_b_pullups(false);// define nivel alto
   while(true)
   {
      keypad_scan(); // leitura do teclado
      input_code();  // descodifica��o da tecla
      lcd_update();  // visualiza��o
   }
}
