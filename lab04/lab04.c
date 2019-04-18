#include <lab04.h>
/* Declaração de pinos para displays e outras contantes 
                utilizadas no código                   */
#define D_UNI pin_a3          
#define D_DEC pin_e2
#define D_CENT pin_e1
#define D_MIL pin_e0
#define REFRESH_INTERNAL 10
#define CNT_MAX 99
#define SEG_MAX 9999

/* Função que decodificar o número decimal em representação 
             para o display de 7 segmentos                 */
byte bin2bcd(int8 num)
{
   byte bcd;
   switch(num)
   {
   case 0: bcd = 0b00111111; 
   break;
   case 1: bcd = 0b00000110; 
   break;
   case 2: bcd = 0b01011011; 
   break;
   case 3: bcd = 0b01001111; 
   break;
   case 4: bcd = 0b01100110; 
   break;
   case 5: bcd = 0b01101101; 
   break;
   case 6: bcd = 0b01111101; 
   break;
   case 7: bcd = 0b00000111; 
   break;
   case 8: bcd = 0b01111111; 
   break;
   case 9: bcd = 0b01101111; 
   break;
   default : bcd = 0b01000000; 
   break;
   }
   return bcd;
}

/* Função que opera com valor contado (segundo) */
void display_refresh(int16 val)
{
   int8 uni, dec, cent, mil;// declaração de variáveis
   static int8 digit=0;     // digito com em zero no início do programa (estática)
   int8 digit_bcd, bcd;     // valor do algarismo e representação no display
   
   uni=val%10;              // faz a divisão do valor 'val' em unidades,  
   dec=(val%100)/10;        // dezenas, centenas e unidades de milhar 
   cent=(val%1000)/100;     // usando a operação
   mil=(val%10000)/1000;    // resto (%)
   
   switch(digit)            // seleciona o display
   {
   case 0:                  // seleciona o bit de unidade
           {
      output_low(D_DEC);
      output_low(D_CENT);
      output_low(D_MIL);
      output_high(D_UNI);
      digit_bcd=uni;        // utiliza o valor operado em 'unidade'
      break;
           }
   case 1:                  // seleciona o bit de dezena
           {
      output_low(D_UNI);
      output_low(D_CENT);
      output_low(D_MIL);
      output_high(D_DEC);
      digit_bcd=dec;        // utiliza o valor operado em 'dezena'
      break;
           }        
   case 2:                  // seleciona o bit de centena
           {
      output_low(D_DEC);
      output_low(D_UNI);
      output_low(D_MIL);
      output_high(D_CENT);
      digit_bcd=cent;       // utiliza o valor operado em 'centena'
      break;
           }
   case 3:                  // seleciona o bit de milhar
           {
      output_low(D_DEC);
      output_low(D_CENT);
      output_low(D_UNI);
      output_high(D_MIL);
      digit_bcd=mil;        // utiliza o valor operado em 'milhar'
      break;
           }        
   }
   bcd=bin2bcd(digit_bcd);  // chama a função para decodificar e
   output_d(bcd);           // em seguida ocorre a representação
   digit =(digit==3) ? 0 : digit+1; // selecionador de display
   }


void main()
{
   int16 seg=0; // variáveis de inicialização
   int8 cnt=0;  
   
   while(TRUE)
   {
   display_refresh(seg);         // chama a função que opera com o valor contado 
   delay_ms(REFRESH_INTERNAL);   // refresh do display, técnica utilizada para representação nos displays 
                                 // ficarem ao "mesmo tempo"
   cnt=(cnt==CNT_MAX)? 0 : cnt+1;// um pequeno atraso para as transições
   seg=(cnt==0)? seg+1 : seg;    
   seg=(seg==SEG_MAX)? 0 : seg;  // contador de segundos
   }
}

