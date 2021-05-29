#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <String.h>
#include <string.h>
#include <avr/io.h>

//Variaveis para transmissao:
String s = "Cliente: Jean, Consumo: ";
String data = "";
//float litros = 400;
int tamanho;

volatile int  flow_frequency;  // Pulsos do medidor de vazao
unsigned int  l_hour;          // Calculated litres/hour                      
unsigned char flowmeter = 2;  // pino do sensor medidor de vazao
unsigned long currentTime;
unsigned long cloopTime;
unsigned long consumoTime;
unsigned long dayTime;
String litrosString;
float litros = 0; 
int periodo = 5000;
char valoresDeLitros[10];
char valorLitrosEEPROM[10];
unsigned int vetorDeEnderecos[11];


void flow ()                  // funcao de interrupcao
{ 
   flow_frequency++;
} 

void setup()
{ 

   iniciandoVetorDeValores();
   if(EEPROM_read(vetorDeEnderecos[10]) == 'k'){
   //   String aux = "";
      for(int i = 0; i < 10; i++){
          if(EEPROM_read(vetorDeEnderecos[i] != 'b')){
            valorLitrosEEPROM[i] = EEPROM_read(vetorDeEnderecos[i]);
           }
           else{
            i = 10;
            }
        }
        litros = atoi(valorLitrosEEPROM); 
    }
  
   pinMode(flowmeter, INPUT);
   Serial.begin(9600); 
   attachInterrupt(0, flow, RISING); 
                                     
   sei();     //habilita interrupcao                    
   currentTime = millis();
   cloopTime = currentTime;
   consumoTime = currentTime;
   dayTime = currentTime;

   //Configuracoes do Mirf:

    Mirf.spi = &MirfHardwareSpi;
    Mirf.csnPin = 10; //(This is optional to change the chip select pin)
    Mirf.cePin = 9; //(This is optional to change the enable pin)
    Mirf.init(); 
    Mirf.setTADDR((byte *)"serv1");
    Mirf.payload = 32;
    Mirf.config();
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
   
} 

void loop ()    
{
   currentTime = millis();
   // A cada segundo calcula a vazao em litros e escreve na tela
   if(currentTime >= (cloopTime + 1000))
   {     
      cloopTime = currentTime;              //Atualiza o tempo de cloop (1 segundo)
      // Frenquencia de pulso do sensor (Hz) = 7.5Q, Q e a vazao em L / min. (3% range)
      l_hour = (flow_frequency / 7.5); 
      flow_frequency = 0;                 
      Serial.print(l_hour);         
      Serial.println(" L/min");
      litros = litros + (l_hour/60.0);
      litrosString = (String) litros;
      Serial.println(litrosString);
      EEPROM_write(vetorDeEnderecos[10],'k');
    
      
   }
   if(currentTime >= (consumoTime + periodo)){
    consumoTime = currentTime; 
    Serial.print("Consumo de: ");  
    Serial.print(litros);
    Serial.println(" litros.");
    lendoString(litrosString);
    gravandoNaEEPROM();

    data = s + (String)litros+"L/";
    tamanho = data.length();
    char a[tamanho];
    for(int i = 0; i < tamanho; i++){
      a[i] = data[i];
      }
    Mirf.send((byte *) a);
    delay(200);
    
  }
  
     
}


void EEPROM_write(int uiAddress, char ucData)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEPE))
;
/* Set up address and Data Registers */
EEAR = uiAddress;
EEDR = ucData;
/* Write logical one to EEMPE */
EECR |= (1<<EEMPE);
/* Start eeprom write by setting EEPE */
EECR |= (1<<EEPE);
}

char EEPROM_read(int uiAddress)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEPE))
;
/* Set up address register */
EEAR = uiAddress;
/* Start eeprom read by writing EERE */
EECR |= (1<<EERE);
/* Return data from Data Register */
return EEDR;
}

void lendoString(String s){
    for(int i = 0;  i < s.length(); i++){
      if(s[i] == '.'){
          i = s.length();
        }
      else if(i > 9){
        i = s.length();
        }
      else{
        valoresDeLitros[i] = s[i];
        }
      }
  }

void gravandoNaEEPROM(){
  for(int i = 0; i < 10; i++){
      if(valoresDeLitros[i] != 'b'){
          EEPROM_write(vetorDeEnderecos[i],valoresDeLitros[i]);
        }
       else{
           EEPROM_write(vetorDeEnderecos[i],'b');
        }
    }
  }

void iniciandoVetorDeValores(){
  for(int i = 0; i < 10; i++){
      valoresDeLitros[i] = 'b';
    }
      for(int i = 0; i < 10; i++){
      valorLitrosEEPROM[i] = 0;
    }
    vetorDeEnderecos[0] = 0x02;
    vetorDeEnderecos[1] = 0x03;
    vetorDeEnderecos[2] = 0x04;
    vetorDeEnderecos[3] = 0x05;
    vetorDeEnderecos[4] = 0x06;
    vetorDeEnderecos[5] = 0x07;
    vetorDeEnderecos[6] = 0x08;
    vetorDeEnderecos[7] = 0x09;
    vetorDeEnderecos[8] = 0x010;
    vetorDeEnderecos[9] = 0x011;
    //checa Epprom pela primeira vez
    vetorDeEnderecos[10] = 0x012;
  }

