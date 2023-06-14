Segue abaixo o código e a explicação barrada (em verde) ao lado das linhas.
/* Layout de pinos usados:
 * --------------------------------------
 *             MFRC522      Arduino       
 *             Leitor/PCD    Uno       
 * Sinal       Pinos        Pinos           
 * --------------------------------------
 * RST/Reset   RST          9             
 * SPI SS      SDA(SS)      10            
 * SPI MOSI    MOSI         11 / ICSP-4   
 * SPI MISO    MISO         12 / ICSP-1   
 * SPI SCK     SCK          13 / ICSP-3 
 
  SPI - (Biblioteca) Comunicação SPI (Serial Peripheral Interface) com Arduino.
  A Serial Peripheral Interface é um protocolo de dados seriais 
  síncronos utilizado em microcontroladores para comunicação 
  entre o microcontrolador e um ou mais periféricos.
  MFRC522 - (Biblioteca) módulo RFID usa o chip MFRC522 da empresa NXP, 
  que por sua vez, pode ser usado em comunicações a uma frequência
  de 13,56MHz, permitindo, por exemplo, sem contato, a leitura e 
  escrita em cartões que seguem o padrão Mifare
  TimeLib - A biblioteca Time adiciona funcionalidade de cronometragem ao
  Arduino com ou sem hardware externo de cronometragem. Permite
  um esboço para obter a hora e a data como: segundo, minuto, 
  hora, dia, mês e ano. Ele também fornece o tempo como um time_t C 
  padrão para que os tempos decorridos possam ser facilmente calculados 
  e os valores de tempo compartilhados entre diferentes plataformas.
  PICC - Proximity Integrated Circuit Chip (cartão ou chaveiro)
  
*/
#include <SPI.h>        // Inclui a Biblioteca SPI (Serial Peripheral Interface)- resposavel pela comunicação
#include <MFRC522.h>    //Inclui a Biblioteca MFRC522
#include <TimeLib.h>    //Inclui a Biblioteca TimeLib

#define SS_PIN 10       //Define que o Pino Slave Select (SDA-SS) do Modulo RFID esta conectado ao pino 10 do Arduino
#define RST_PIN 9       //Define que o Pino RST (RESET) do Modulo RFID esta conectado ao pino 9 do Arduino
#define som 8           //Define que o Pino 8 do Arduino tera o parâmetro som

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Definição do objeto mfrc522 da qual se passa os parâmetros SS_PIN e RST_PIN
String card_ID="";                  //Informa que a variavel card_ID é uma string (cadeia de caracteres)e atribui o valor vazio

//Adicionar os cartoes abaixo 
String Aluno1="891052195";          // Tipo da varivel do Aluno1 é uma string (cadeia de caracteres)
String Aluno2="198136543";          // Tipo da varivel do Aluno2 é uma string (cadeia de caracteres)
/*String Aluno3="15353114169";
String Aluno4="13937143185";
String Aluno5="79 DD 81 2F";
String Aluno6="89 48 C9 2F";*/

int NumbCard[2];
int j=0;  
int statu[2];
int s=0;  

int const LedVermelho=6;
int const LedVerde=5;
int const LedAzul=7;

String Aluno;
long Numero;
int ID=1;

void setup() {
  setTime(20,00,00,1,31,2020);       // ajusta a data e hora para 20:00:00, 31 de janeiro de 2020
  Serial.begin(9600);                // Inicia a porta serial com velocidade de 9600 bounds
  SPI.begin();                       // Inicia as vias de comunicação com o protocolo SPI
  mfrc522.PCD_Init();                // Inicia o Modulo leitor PCD (Proximity Coupling Device)
  
  Serial.println("CLEARSHEET");      //Limpa a página do Excel             
  Serial.println("LABEL,ID,Date,Aluno,Numero,Card ID,Time IN,Time OUT");      //Cria as colunas no Excel
  pinMode(LedVermelho,OUTPUT);       // Declara que o LedVermelho esta ligado numa porta Saída do Arduino
  pinMode(LedVerde,OUTPUT);          // Declara que o LedVerde esta ligado numa porta Saída do Arduino
  pinMode(LedAzul,OUTPUT);           // Declara que o LedAzul esta ligado numa porta Saída do Arduino
  pinMode (som, OUTPUT);             // Declara que o som esta ligado numa porta Saída do Arduino
  setTime(20,00,00,1,31,2020);       // ajusta a data e hora para 20:00:00, 31 de janeiro de 2020
  
  delay(200);                        //Espera 200 milisegundos
 }
   
void loop() {

 if ( ! mfrc522.PICC_IsNewCardPresent()) {          // Se um novo cartão foi apresentado ao leitor RFID, laia e continue
  return;
 }
 
 if ( ! mfrc522.PICC_ReadCardSerial()) {            // Uma vez que um PICC colocado, obtenha o Serial e continue
  return;
 }

 for (byte i = 0; i < mfrc522.uid.size; i++) {      // Byte = 0 a 255 - Loop 4 vezes para obter os 4 bytes (size do cartão)
                                                    // incremento de 1  (i++)
     card_ID += mfrc522.uid.uidByte[i];             // Soma o valor da variavel card_ID com o valor de i

 }

 Serial.println(card_ID);                           //imprime na porta serial as informações contidas no cartão "card_ID" 
 
       if(card_ID==Aluno1){                         //Se a variavel card_ID é igual ao Aluno1, então o Aluno1 é o 
                                                    //Bruno Fatte e o numero dele é 891052195
       Aluno="Bruno Fatte";
       Numero="891052195";
       j=0;                                         //Atribui para a variavel j o valor zero
       s=0;                                         //Atribui para a variavel s o valor zero
      }
      else if(card_ID==Aluno2){                     //Se a variavel card_ID é igual ao Aluno2, então o Aluno2 é a 
                                                    //Bruna Fraga e o numero dela é 198136543
       Aluno="Bruna Fraga";
       Numero="198136543";
       j=1;                                         //Atribui para a variavel j o valor um
       s=1;                                         //Atribui para a variavel s o valor um
      }
      /*else if(card_ID==Aluno3){
       Aluno="Third employee";
       Numero=789101;
       j=2;
       s=2;
      }
      else if(card_ID==Aluno4){
       Aluno="Fourth employee";
       Numero=789101;
       j=3;
       s=3;
      }
      else if(card_ID==Aluno5){
       Aluno="Fiveth employee";
       Numero=789101;
       j=4;
       s=4;
      }
      else if(card_ID==Aluno6){
       Aluno="Sixth employee";
       Numero=789101;
       j=5;
       s=5;
      }*/
      else{                         
          digitalWrite(LedAzul,LOW);                   //LedAzul desligado
          digitalWrite(LedVerde,LOW);                  //LedVerde desligado
          digitalWrite(LedVermelho,HIGH);              //LedVermelho ligado
          tone (som,600,100);                          // ALERTA ID do cartao DESCONHECIDO -  600hz é a frequencia de saída do som
                                                       // 100 milisegundos é o tempo de duração do som
             delay(100);
          tone (som,300,100);
             delay(100);
          tone (som,600,100);
             delay(100);
          tone (som,300,100);
             delay(100);
          tone (som,600,300); 
             delay(30);
          
          goto cont;                                   // Pula o  algoritimo para a parte que esta escrito cont
     }

      if(NumbCard[j] == 1 && statu[s] == 0){           //Faz a comparação se j é igual a 1 e s = 0
      statu[s]=1;                                      // atribui o valor 1 para a variavel(s) --> vai imprimir no excel a saída
    
      Serial.print("DATA,");                           // printa na serial/Excel os dados ID, DATA, Aluno, Numero, card_ID e Horas (saída)
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Aluno);
      Serial.print(",");
      Serial.print(Numero); 
      Serial.print(",");
      Serial.print(card_ID); 
      Serial.print(",");
      Serial.print("");
      Serial.print(",");
      Serial.println("TIME");
      ID=ID+1;                                         //Incrementa o valor do ID com mais 1 --> índice que aparece na coluna ID do excel
      digitalWrite(LedVerde,HIGH);                     //LedVerde ligado
      digitalWrite(LedVermelho,LOW);                   //LedVermelho desligado
      digitalWrite(LedAzul,HIGH);                      //LedAzul acompanha o Alerta 
   
      tone (som,1200,100);                             // ALERTA SAÍDA -  1200hz é a frequencia de saída do som
                                                       // 100 é o tempo de duração do som
         delay(100);
      tone (som,900,100);
         delay(100);
      tone (som,700,100);
         delay(100);
      tone (som,500,100);
         delay(100);
      tone (som,300,300);
         delay(500); 
      digitalWrite(LedAzul,LOW);                       //LedAzul acompanha o Alerta, desligado
         delay(30);
        }
   
     if(NumbCard[j] == 0){                             //Quando NumbCard[j] = 0 --> Foi lido o cartão mas não printa, 
                                                       //quando ele vai pra 1 printa entrada
     NumbCard[j] = 1;                                  //Informa a entrada do cartão --> NumbCard[j] = 1 
                                                       //(printa o horário da entrada no excel)
      
          
      Serial.print("DATA,");                           // printa na serial/Excel os dados ID, DATA, Aluno, Numero, card_ID e Horas (entrada)
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Aluno);
      Serial.print(",");
      Serial.print(Numero); 
      Serial.print(",");
      Serial.print(card_ID); 
      Serial.print(",");
      Serial.print("TIME");
      Serial.print(",");
      Serial.println("");
      digitalWrite(LedVerde,HIGH);                     //LedVerde ligado
      digitalWrite(LedVermelho,LOW);                   //LedVermelho desligado
      digitalWrite(LedAzul,HIGH);                      //LedAzul acompanha o Alerta 
      tone (som,300,100);                              // ALERTA ENTRADA -  300hz é a frequencia de saída do som
                                                       // 100 é o tempo de duração do som
         delay(100);
      tone (som,500,100);
         delay(100);
      tone (som,700,100);
         delay(100);
      tone (som,800,100);
         delay(100);
      tone (som,1200,300); 
         delay(500);
      digitalWrite(LedAzul,LOW);
         delay(30);
         
      ID=ID+1;                                         // Incrementa o valor do ID com mais 1 --> índice que aparece na coluna ID do excel
      }
      
      else if((statu[s] == 1)&&(NumbCard[j] == 1)){    //Se ja foi verificado que o cartão ja entrou = NumbCard[j] = 1
                                                       //e o cartão ja saiu = statu[s] = 1
                                                       //então zera a entrada = NumbCard[j]=0
                                                       //então zera a saída = statu[s]=0
      statu[s]=0;                                            
      NumbCard[j]=0;
      
      }
      delay(1000);                                     //espera 1000 milisegundos
   
     
cont:                                                  //o algotitimo de cima pula pra cá, que é o cont
delay(2000);                                           //espera 2000 milisegundos
digitalWrite(LedVerde,LOW);                            //LedVerde desligado
digitalWrite(LedVermelho,LOW);                         //LedVermelho desligado

card_ID="";                                            //Atribui o valor da variavel card_ID para vazio

}
  void printTime() {                                   //chama a função printTime
  Serial.print(hour());                                //imprime as horas, minutos e segundos no excel
  Serial.print(":");
  Serial.print(minute());
  Serial.print(":");
  Serial.print(second());
  Serial.print(","); 
}
