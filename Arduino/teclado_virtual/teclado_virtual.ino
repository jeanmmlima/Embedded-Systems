//Teclado Virtual

//Difinindo as notos
//#define atribuiu a uma "string" um valor inteiro

#define NOTA_DO 262
#define NOTA_RE 294
#define NOTA_MI 330
#define NOTA_FA 349
#define NOTA_SOL 392
#define NOTA_LA 440
#define NOTA_SI 494

int pinAudio = 10; //pino que vai para o buzzer (330 ohms resistor)
int nota;

void setup() {
  // put your setup code here, to run once:
  //Taxa de transfericia de dados na comunicacao serial
  
  Serial.begin(9600);
  
  //esvaziar serial
  
  Serial.flush();
  
  pinMode(pinAudio, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    nota = Serial.read();
    Serial.println(nota);
    
    if(nota == 49){
      tone(pinAudio, NOTA_DO);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 50){
      tone(pinAudio, NOTA_RE);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 51){
      tone(pinAudio, NOTA_MI);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 52){
      tone(pinAudio, NOTA_FA);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 53){
      tone(pinAudio, NOTA_SOL);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 54){
      tone(pinAudio, NOTA_LA);
      delay(500);
      noTone(pinAudio);
    }
    
    if(nota == 55){
      tone(pinAudio, NOTA_SI);
      delay(500);
      noTone(pinAudio);
    }
    
    Serial.flush();
  }

}
