//ideia:
//criar uma matriz de fios e botoes e ler alteracao de estado. o ser lido, aceitar e retornar o valor escolhido
//versao 1: ler do teclado

//obs importante: quando se le a porta de setagem mista  le-se tambem os valores que voce setou


#include "teclado.h"
#include <LCD.C>


/////////////minhas variaveis/////////////
int8 tecla=0;//para saber o valor da tecla a ser pressionada
int1 acertei=0;//para "habilitar leitura do teclado". impede repetição infinita
char caractere=0; //para input_code
int1 digitalizado=1; //se o lcd ja conheceu a criança


void escolhe_linha(int k)
{
   output_b((0x01<<k)); //de zero a 3
}

int8 calculo(int8 linha, int8 coluna)//implementada por motivo de maleabilidade e possibilidade de alteracao
{
   int temp;//para que nao comece com zero
   temp = 4*linha + coluna;
   return temp;
}

void keypad_scan()//le teclas
{
/*
situações possiveis:
botao apertado
nada pressionado
mais botoes pressionados
*/
   int8 linha, coluna;
   static int1 entrada=0 ; //se foi apertado e se aceito. tambem impede a repetição de caracterer
   static int position, old_position; //qual foi apertado
   static int8 contador=0; //para debounce
   
   entrada=0;//começa sempre como 0. se alguma tecla for apertada ele ai a 1
   for(linha=0;linha<4;linha++)
   {
      escolhe_linha(linha);
      delay_us(10);
      for(coluna=0;coluna<4;coluna++)
      {
         if(input(coluna+PIN_B4))//lendo no 18f4550.h vemos que os pinos b4-b7 sao 31756-31759
            { 
            old_position=position;
            position=calculo(linha,coluna);
            entrada=1;
            if(contador>=TIME && entrada && position==old_position && !acertei) //se passou tempo suficieete para aceitar a tecla e ainda nao foi lida
            {
               acertei=1;
               digitalizado=0;//diz que esse digito ainda nao veio ao mundo
               //usado na lcd_update;
               tecla=position;
            }
            if(position!=old_position){//no caso de apertar um botao e depois apertar outro sem soltar o primeiro;
               contador=0;
            }
         }  
      }
      }
      if(!entrada){
      contador=0;
      acertei=0;
      }
      if(position==old_position && contador<TIME){//se a mesma tecla continua pressionada
      contador=contador+1;
      }
   }
   


void input_code( )//reponsavel por dar significado as teclas
{
   //um monte de switches
   if(acertei && !digitalizado)//se ainda nao fez a atribuicao
   {
      switch(tecla)
      {
         case 0:
            caractere='7';
            break;
         case 1:
            caractere='8';
            break;
         case 2:
            caractere='9';
            break;
         case 3:
            caractere='/';
            break;
         case 4:
            caractere='4';
            break;
         case 5:
            caractere='5';
            break;
         case 6:
            caractere='6';
            break;
         case 7:
            caractere='X';
            break;
         case 8:
            caractere='1';
            break;
         case 9:
            caractere='2';
            break;
         case 10:
            caractere='3';
            break;
         case 11:
            caractere='-';
            break;
         case 12:
            caractere='C';
            break;
         case 13:
            caractere='0';
            break;
         case 14:
            caractere='=';
            break;
         case 15:
            caractere='+';
            break;
         default:
            caractere='!';
            break;
      
      }
   }
}

void lcd_update()// somente ela fala com o lcd
{
   if(!digitalizado)
   {
      digitalizado=1;
      printf(lcd_putc,"%c",caractere);
      caractere=0;
   }
}

void setup()
{
   lcd_init();
   set_tris_b(0xf0);// bits 7-4 sao colunas e 3-0 sao linhas
   port_b_pullups(false);//n fac ideia do pq
}

void main()
{

   setup();
   printf(lcd_putc,"ola mundo\n");
   while(true)
   {
      keypad_scan();//le o teclado e devolve posicao
      input_code();//atribui significado ao botao
      lcd_update();//manda pro lcd
   }
}

