#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdlib.h>
#include <util/delay.h>


#define F_CPU 16000000
#define BAUD 9600
#define BRC ((F_CPU/16/BAUD) - 1)
#define RX_BUFFER_SIZE 128

char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxPos = 0;
int inteiro = 0;

int dutyCycle = 0;
int controlADC = 0;
int feedback = 0;
int posBefore = 0;
int pos = 0;

//Variaveis de enderecos e dados para EEPROM

unsigned int uiAddress1 = 0x02;
unsigned int uiAddress2 = 0x03;
unsigned int uiAddress3 = 0x04;
unsigned int uiAddress4 = 0x05;
char ucData1 = '1';
char ucData2 = '1';
char ucData3 = '0';
boolean estadoInicial = true;
int posInicial = 0;
int posBeforeInicial = 0;

int main(void){

  setupPWM10bit();
  setupADC();
  serialBegin();

  adc();
  
 // DDRD = _BV(PORTD2)|(0<<PORTD3)|(0<<PORTD4)|(0<<PORTD5);
  DDRD = 0b00000110;
  DDRC = (0<<PC4) | (0<<PC5) | (0<<PC2); //PC2 sinal;

  if(EEPROM_read(uiAddress4) == 'b'){
    char x = EEPROM_read(uiAddress1);
    char y = EEPROM_read(uiAddress2);
    char z = EEPROM_read(uiAddress3);
     transmitir(EEPROM_read(uiAddress1));
     transmitir(EEPROM_read(uiAddress2));
     transmitir(EEPROM_read(uiAddress3));
     transmitir(EEPROM_read(uiAddress4));

    posInicial = (x - '0') * 100;
    posInicial = posInicial + (y - '0')*10;
    posInicial = posInicial + (z - '0');
    
    while(estadoInicial){

      startConversion();
      feedback = ADC;

      posBeforeInicial = ((feedback/1000.0) * 220);
      for(int i = 0; i < 4; i++){
        transmitir(((String)feedback)[i]);
        }
         
      if(posBeforeInicial > posInicial){
          if(feedback >= ((posInicial/220.0)*1000)){
      
        dutyCycle = 1023; 
        PORTD &= ~(1<<PD2);
        }
       else if (feedback < ((posInicial/220.0)*1000)){
        
        dutyCycle = 0;
        PORTD &= ~(1<<PD2);
        estadoInicial = false;
        }
        //dutyCycle = 512;
        OCR1A = dutyCycle;
        }

      //Aumenta o angulo
       else if(posBeforeInicial <= posInicial){

      
      if(feedback >= ((posInicial/220.0)*1000)){
       
        dutyCycle = 0;
        PORTD &= ~(1<<PD2);
        estadoInicial = false;
        }
       else if (feedback < ((posInicial/220.0)*1000)){

        
        dutyCycle = 0;
        PORTD |= (1<<PD2);
        }
        //dutyCycle = 512;
        OCR1A = dutyCycle;
        }
      
      }
    
    }

//if(EEPROM_read(uiAddress4) != 'c')  {
  while(1)
  {

//LEDS

if(pos == 0){
  PORTB |= (1<<PB3);
  PORTB &= ~(1<<PB2);
}
else if(pos != 0){
  PORTB &= ~(1<<PB3);
  PORTB |= (1<<PB2); 
  }

//ESTADO
int estado = PINB & (1<<PB4);
if(estado){
     //AUTOMATICO - SERIAL
     
     if(pos == 0 && receber(estado) != '\0'){
     char c = receber(estado);
     EEPROM_write(uiAddress1,c);
     if(c != '-'){
     pos = c - '0';
     pos = pos * 100;
     
     c = receber(estado);
     EEPROM_write(uiAddress2,c);

     pos = pos + ((c - '0')*10);

     c = receber(estado);
     EEPROM_write(uiAddress3,c);
     pos = pos + (c - '0');}
     EEPROM_write(uiAddress4,'b');
     }
     
}
else if(!estado){
     //MANUAL

     
 

 if(pos == 0){

// int bit7 = PINC & (1<<PC2);
 int bit6 = PIND & (1<<PD3);
 int bit5 = PIND & (1<<PD4);
 int bit4 = PIND & (1<<PD5);
 int bit3 = PIND & (1<<PD6);
 int bit2 = PIND & (1<<PD7);
 int bit1 = PINC & (1<<PC5);
 int bit0 = PINC & (1<<PC4);

// if(bit7){bit7 = 128;}
 if(bit6){bit6 = 64;}
 if(bit5){bit5 = 32;}
 if(bit4){bit4 = 16;}
 if(bit3){bit3 = 8;}
 if(bit2){bit2 = 4;}
 if(bit1){bit1 = 2;}
 if(bit0){bit0 = 1;}
 pos = (bit6+bit5+bit4+bit3+bit2+bit1+bit0)+1;
 if(pos > 220){
  pos = 200;
  }
 if(pos < 10){
  pos = 10;
  }
}
}
     

      startConversion();
      feedback = ADC;
   //   char sFeed[] = "TEST";
      for(int i = 0; i < 4; i++){
        transmitir(((String)feedback)[i]);
        }
      

       
      if(posBefore > pos){
          if(feedback >= ((pos/220.0)*1000)){
      
        dutyCycle = 1023;
        PORTD &= ~(1<<PD2);
        }
       else if (feedback < ((pos/220.0)*1000)){
        
        dutyCycle = 0;
        PORTD &= ~(1<<PD2);
        posBefore = pos;
        pos = 0;
        }
        //dutyCycle = 512;
        OCR1A = dutyCycle;
        }

      //Aumenta o angulo
       else if(posBefore <= pos){

      
      if(feedback >= ((pos/220.0)*1000)){
       
        dutyCycle = 0;
        PORTD &= ~(1<<PD2);
        posBefore = pos;
        pos = 0;
        }
       else if (feedback < ((pos/220.0)*1000)){

        
        dutyCycle = 0;
        PORTD |= (1<<PD2);
        }
        //dutyCycle = 512;
        OCR1A = dutyCycle;
        }
  }   
      
  
}

void setupPWM10bit(){
  DDRB = _BV(PORTB1) | _BV(PORTB2) | _BV(PORTB3) | _BV(PORTB4);
  TCCR1A = _BV(COM1A1) | _BV(WGM10) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(CS11);
  TIMSK0 = _BV(TOIE0);

  }

void setupADC(){
  
  ADMUX = (0 << REFS0) | (0 << REFS1);
  ADCSRA = (1 << ADEN) | (1 << ADIE) | (1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);

  startConversion();
  }
void startConversion(){
  
  ADCSRA |= (1<<ADSC);
  }
void adc(){
  //if (controlADC == 1){
  ADMUX = (1<<MUX0) | (1<<MUX1) | (0<<MUX2);
 // controlADC--;

}

void transmitir(char data){
  while(!(UCSR0A &(1<<UDRE0)))
  ;
  UDR0 = data;
}

void serialBegin(){
    UBRR0H = (BRC >> 8);
  UBRR0L = BRC;

  UCSR0B = (1<< RXEN0) | (1<<TXEN0) | (1<<RXCIE0) ;//| (1<<TXCIE0); //|  (1<<RXCIE0);//(1 << TXEN0) | (1<<TXCIE0) ; //Habilita o TX
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); //valores de 8 bits
  }

ISR(USART_RX_vect){
 rxBuffer[rxPos] = UDR0;
 rxPos++;
  }

  unsigned char receber( int estado )
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) ){
  if(!estado){
    break;
    }
  }

/* Get and return received data from buffer */

return UDR0;
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


