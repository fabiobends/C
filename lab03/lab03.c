#include <lab03.h>

/* Função que decodificar o número decimal em representação 
             para o display de 7 segmentos                 */
byte dec2bcd(int num)
{
   byte bcd;
   switch(num)
   {
   case 0: bcd = 0b00111111; // algarismo 0
   break;
   case 1: bcd = 0b00000110; // algarismo 1
   break;
   case 2: bcd = 0b01011011; // algarismo 2
   break;
   case 3: bcd = 0b01001111; // algarismo 3
   break;
   case 4: bcd = 0b01100110; // algarismo 4
   break;
   case 5: bcd = 0b01101101; // algarismo 5
   break;
   case 6: bcd = 0b01111101; // algarismo 6
   break;
   case 7: bcd = 0b00000111; // algarismo 7
   break;
   case 8: bcd = 0b01111111; // algarismo 8
   break;
   case 9: bcd = 0b01101111; // algarismo 9
   break;
   default : bcd = 0b01000000; // exibir sinal de - (traço) quando houver erro 
   break;
   }
   return bcd;
}
void main()
{
   set_tris_d(0x00);   // definir porta D como saída
   set_tris_e(0xff);   // definir porta E como entrada
   int8 botao, i;      // declaração de variáveis
   while(TRUE)
   {
   output_d(0x00);     // bits da porta D valendo zero (segmentos apagados)
   botao=input(pin_e0);// variável 'botão' recebe valor de entrada do pino E0
      if(botao==0)     // se 'botão' igual a zero (nível baixo) então
      {                // entra no laço do contador
         for(i=0; i<=9; i++) // laço do contador de 0 a 9
         {
         output_d(dec2bcd(i)); // chamada da função que decodifica o algarismo
         delay_ms(1000);       // depois da conversão exibe por o valor por 1 seg
         }
         i=0;                  // zera contador depois de terminar,
      }                        // esperando novo acionamento
   }
}
