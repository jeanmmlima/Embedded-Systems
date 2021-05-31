//Jogo Genius

//variaveis necessarias a implementacao

#define NOTE_D4 294
#define NOTE_G4 392
#define NOTE_A4 440
#define NOTE_A5 880

int sequencia[100] = {};
int notas[4] = { NOTE_A4, NOTE_G4, NOTE_D4 ,NOTE_A5};
int rodada = 0;
int passo_sequencia = 0;
int botao = 0;
bool perdeu = false;

//Leds, Botoes e o pino do buzzer

int pinAudio = 7;
int pinLeds[4] = {8,9,10,11};
int pinButtons[4] = {3,4,5,6};

void setup() {
  // put your setup code here, to run once:
  
  for (int i = 0; i < 4; i++){
    pinMode(pinLeds[i], OUTPUT);
  }
  
    for (int i = 0; i < 4; i++){
    pinMode(pinButtons[i], INPUT);
  }
  
  pinMode(pinAudio, OUTPUT);
  
  randomSeed(analogRead(0));

}

void loop() {
  // put your main code here, to run repeatedly:
  //Caso o Jogador Tenha perdido, zero as variaveis pra que se possa comecar outro jogo
  if(perdeu){
  int sequencia[100] = {};
  rodada = 0;
  passo_sequencia = 0;
  perdeu = false;
  }
  
  if(rodada == 0){
    Inicio();
    delay(3000);
  }
  
  proximaRodada();
  tocaSequencia();
  jogador();
  
  delay(1000);

}

void proximaRodada(){
  int nota = random(0,4);
  sequencia[rodada++] = nota;
 
}

void tocaSequencia(){
  for (int i = 0; i < rodada; i++){
    tone(pinAudio, notas[sequencia[i]]);
    digitalWrite(pinLeds[sequencia[i]],HIGH);
    delay(500);
    noTone(pinAudio);
    digitalWrite(pinLeds[sequencia[i]],LOW);
    delay(100);
  }
  noTone(pinAudio);
}

void jogador(){
  for (int i = 0; i < rodada; i++){
    esperaJogada();
    checaJogada();
    
    if (perdeu){
      break;
    }
    passo_sequencia++;
  }
 passo_sequencia=0;
}

void esperaJogada(){
  boolean espera = false;
  while(!espera){
    for(int i = 0; i <= 3; i++){
      if(digitalRead(pinButtons[i]) == HIGH){
     //   delay(10000);
        botao = i;
        tone(pinAudio, notas[i]);
        digitalWrite(pinLeds[i], HIGH);
        delay(300);
        digitalWrite(pinLeds[i], LOW);
        noTone(pinAudio);
        espera = true;
      }
    }
    delay(10);
  }
}

void checaJogada(){
  if (sequencia[passo_sequencia] != botao){
   for (int i = 0; i <= 3; i++) {
     tone(pinAudio, notas[i]);
     digitalWrite(pinLeds[i], HIGH);
     delay(200);
     digitalWrite(pinLeds[i], LOW);
     noTone(pinAudio);
   }
   tone(pinAudio, notas[2]);
   for (int i = 0; i <= 3; i++) {
    digitalWrite(pinLeds[0], HIGH);
    digitalWrite(pinLeds[1], HIGH);
    digitalWrite(pinLeds[2], HIGH);
    digitalWrite(pinLeds[3], HIGH);
    delay(100);
    digitalWrite(pinLeds[0], LOW);
    digitalWrite(pinLeds[1], LOW);
    digitalWrite(pinLeds[2], LOW);
    digitalWrite(pinLeds[3], LOW);
    delay(100);
   }
   noTone(pinAudio);
   perdeu = true;
  }
}

void Inicio() {
tone(pinAudio, notas[0]);
digitalWrite(pinLeds[0], HIGH);
digitalWrite(pinLeds[1], HIGH);
digitalWrite(pinLeds[2], HIGH);
digitalWrite(pinLeds[3], HIGH);
delay(500);
digitalWrite(pinLeds[0], LOW);
digitalWrite(pinLeds[1], LOW);
digitalWrite(pinLeds[2], LOW);
digitalWrite(pinLeds[3], LOW);
delay(500);
noTone(pinAudio);
}


