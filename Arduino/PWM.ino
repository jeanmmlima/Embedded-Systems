#include <avr/io.h>
#include <avr/interrupt.h>

int dutyCycle = 0;
int controlADC = 0;
int feedback = 0;

unsigned int Kp = 0;
unsigned int Output;
double error; 

int main(void){

  setupPWM10bit();
  setupADC();
  Serial.begin(9600);
  
adc();
  while(1)
  {
    startConversion();
    feedback = ADC;
    dutyCycle = 0;
    OCR1A = dutyCycle;
    Serial.println(feedback);

    }
      
  }

void setupPWM10bit(){
  DDRB = _BV(PORTB1);
  TCCR1A = _BV(COM1A1) | _BV(WGM10) | _BV(WGM11);
  TCCR1B = _BV(WGM12) | _BV(CS11);

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
