#include <lab05.h>
/* Declara��o de pinos para displays e outras contantes
                utilizadas no c�digo                   */
#define D_UNI pin_a3          
#define D_DEC pin_e2
#define D_CENT pin_e1
#define D_MIL pin_e0
#define PONTO pin_d7
#define REFRESH_INTERNAL 10
#define CNT_MAX 99
#define SEG_MAX 9999

/* Fun��o que decodificar o n�mero decimal em representa��o 
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

/* Fun��o que opera com valor contado (segundo) */
void display_refresh(int16 val)
{
   int8 uni, dec, cent, mil;// declara��o de vari�veis
   static int8 digit=0;     // digito com em zero no in�cio do programa (est�tica)
   int8 digit_bcd, bcd;     // valor do algarismo e representa��o no display
   
   uni=val%10;              // faz a divis�o do valor 'val' em unidades,  
   dec=(val%100)/10;        // dezenas, centenas e unidades de milhar 
   cent=(val%1000)/100;     // usando a opera��o
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
   bcd=bin2bcd(digit_bcd);  // chama a fun��o para decodificar e
   output_d(bcd);           // em seguida ocorre a representa��o
   if (digit==3) output_high(PONTO);// uso do ponto no �ltimo display
   digit =(digit==3) ? 0 : digit+1; // selecionador de display
}

void main()
{
   setup_adc_ports(AN0|VSS_VDD); // seleciona canal de para leitura ADC
   set_adc_channel(0);           // e referencia para leitura VSS_VDD
   setup_adc(ADC_CLOCK_INTERNAL);// opera��o com clock interno
   
   int32 tensao, val;            // declara��o das vari�veis
   int8 cnt=CNT_MAX;             // inicializa��o para come�ar a contar do zero
   
   while(TRUE)
   {
   delay_ms(REFRESH_INTERNAL);   // refresh do display
   cnt=(cnt==CNT_MAX)? 0 : cnt+1;// demora para realizar amostras
   if(cnt==0)
   {
      tensao=read_adc();         // fun��o que extrai o valor anal�gico
      val=(tensao*5000)/1023;    // valor digital a ser tratado
                                 // precis�o feita com 10 bits (4,88 miliVolts)
   }
   display_refresh(val);         // representa��o do valor atrav�s da multiplexa��o
   }
}

