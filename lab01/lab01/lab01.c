#include <lab01.h>
#define LED_VERDE PIN_B0         //Defina três pinos
#define LED_AMARELO PIN_B1       //com suas respectivas   
#define LED_VERMELHO PIN_B2      //cores no semáforo

void main()
{
  set_tris_b(0x00); // define porta B como saída
  while(TRUE)
  {
  output_low(LED_VERMELHO); //led vermelho desligado
  output_low(LED_AMARELO);  //led amarelo desligado
  output_high(LED_VERDE);   //led verde ligado
  delay_ms(5000);           //por 5 segundos
  output_low(LED_VERDE);    //led verde desligado
  output_low(LED_VERMELHO); //led vermelho continua desligado
  output_high(LED_AMARELO); //led amarelo ligado
  delay_ms(2000);           //por 2 segundos
  output_low(LED_AMARELO);  //led amarelo desligado
  output_low(LED_VERDE);    //led verde desligado
  output_high(LED_VERMELHO);//led vermelho ligado
  delay_ms(4000);           //por 4 segundos
  }
}

