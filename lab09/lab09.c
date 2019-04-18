#include <lab09.h>
#include <math.h>

void main()
{
   int16 cnt, pwmS;                    // vari�veis
   setup_timer_2(T2_DIV_BY_1,127,1);   // tempo do timer2
   // T=1/12M*1*128=10,67 us;
   // f=1/T=93,5 KHz
   setup_port_a(NO_ANALOGS);
   setup_ccp1(CCP_PWM);
   // set_pwm_duty(1,1023);
   cnt=0;
   while(TRUE)
   {
   pwmS=((sin(((float)cnt/1000)*PI)+1)*512)+1; // calculo do per�odo de oscila��o
   set_pwm1_duty(pwmS);                        // implementa��o da oscila��o
   cnt=(cnt==2000) ? 0 : cnt+1;                // altera��o do pulso
   delay_ms(1);
   }
}
