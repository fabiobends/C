#include <projeto.h>
#include <glcd.c>
#define CNT_MAX 24
#define POINT_MAX 102
#define INICIO_X 0
#define FIM_X 102
#define INICIO_Y 0
#define FIM_Y 62
#define MEIO_X (INICIO_X+FIM_X)/2
#define MEIO_Y (INICIO_Y+FIM_Y)/2
signed int32 tensao, val;
int8 cnt=0;
int8 ponto=POINT_MAX;
#INT_TIMER2
void timer2_isr()
{
   cnt=(cnt==1) ? 0 : cnt+1;
   tensao=read_adc();
   tensao=tensao-512;
   val=(tensao*20000)/1023;
   /*if(tensao>512)
   tensao=tensao-512;
   val=(tensao*20000)/1023;*/
}

void representacao(signed int32 value, int8 point)
{   
    if(value<0)
    {
    value=(value%10000)/1000;
    glcd_pixel(INICIO_X+point,MEIO_Y+value,off);
    }
    if(value>=0)
    {
    value=(value%10000)/1000;
    glcd_pixel(INICIO_X+point,MEIO_Y-value,off);
    }
}

void faz_indicador(int8 x0, int8 y0)
{
   int8 a,b,c;
   c=0;
   for(a=y0;a<=y0+2;a--)
   {
      for(b=x0;b<=x0+4-2*c;b++)
      {
      glcd_pixel(b,a,ON);
      }
      c++;
      x0++;
   }
}

void desfaz_indicador(int8 x0, int8 y0)
{
   int8 a,b,c;
   c=0;
   for(a=y0;a<=y0+2;a--)
   {
      for(b=x0;b<=x0+4-2*c;b++)
      {
      glcd_pixel(b,a,OFF);
      }
      c++;
      x0++;
   }
}

void quadro_osc(int8 state, int8 distance)
{
   int8 i;
   glcd_fillscreen(off);
   glcd_rect(INICIO_X,INICIO_Y,FIM_X,FIM_Y,state,state); // faz retangulo delimitador
   glcd_line(MEIO_X,INICIO_Y,MEIO_X,FIM_Y,~state); // faz linha vertical principal
   for(i=MEIO_X;i<=FIM_X;i=i+distance){
   glcd_pixel(i,MEIO_Y-1,~state); // faz linha horizontal secundária inferior direita
   glcd_pixel(i,MEIO_Y+1,~state); // faz linha horizontal secundária superior direita
   }
   for(i=MEIO_X;i<=FIM_X;i=i-distance){
   glcd_pixel(i,MEIO_Y-1,~state); // faz linha horizontal secundária inferior esquerda
   glcd_pixel(i,MEIO_Y+1,~state); // faz linha horizontal secundária superior esquerda
   }
   for(i=MEIO_Y;i<=FIM_Y;i=i+(distance+2)){
   glcd_pixel(MEIO_X-1,i,~state); // faz linha vertical secundária esquerda inferior
   glcd_pixel(MEIO_X+1,i,~state); // faz linha vertical secundária direita inferior
   }
   for(i=MEIO_Y;i<=FIM_Y;i=i-(distance+2)){
   glcd_pixel(MEIO_X-1,i,~state); // faz linha vertical secundária esquerda superior
   glcd_pixel(MEIO_X+1,i,~state); // faz linha vertical secundária direita superior
   }
   glcd_line(INICIO_X,MEIO_Y,FIM_X,MEIO_Y,~state); // faz linha horizontal principal
}
   
void main()
{
   set_tris_a(0xff);
   setup_timer_2(T2_DIV_BY_16,75,10);//(.,75,10)
   setup_adc_ports(AN0|VREF_VREF); // seleciona canal de para leitura ADC
   set_adc_channel(0);           // e referencia para leitura VSS_VDD
   delay_us(10);
   setup_adc(ADC_CLOCK_INTERNAL);// operação com clock interno
   glcd_init(on);
   quadro_osc(on,5);
   enable_interrupts(INT_TIMER2);
   enable_interrupts(GLOBAL);                    
         
   while(TRUE)
   {

      if(cnt==0)
      { 
         if(ponto==POINT_MAX)
         {
         representacao(val,ponto);
         quadro_osc(on,5);
         ponto=0;
         }
         if(ponto!=POINT_MAX)
         {
         representacao(val,ponto);
         ponto=ponto+1;
         }
      }
   }
}
