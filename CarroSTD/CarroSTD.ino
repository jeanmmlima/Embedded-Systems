//#include <Ultrasonic.h>
#include <Servo.h>
#include <SoftwareSerial.h>

//#define TRIGGER_PIN  12
//#define ECHO_PIN     13
#define Input1 4
#define Input2 12
#define chipEnable 3
#define led 13

//Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);
Servo senseServo;
//SoftwareSerial modBlue(0,1);

//float safetyDistance = 5;
//int key = 1234;
//int _key;
//int direcao;
//int aceleracao;
char comando;

void setup(){
  Serial.begin(9600);
  pinMode(Input1, OUTPUT);
  pinMode(Input2, OUTPUT);
  pinMode(chipEnable, OUTPUT);
  pinMode(led, OUTPUT);
  senseServo.attach(9);
  //modBlue.begin(9600);
}

void loop(){
  //goUp();
  //delay(1000);
  //goDown();
  //delay(1000);
  //stopCar();
  //  delay(1000);
  if(Serial.available()){
    digitalWrite(led, LOW);
    comando = (char) Serial.read();
    if(comando == 'f'){
      goHead();
      goUp();
    }
    else if(comando == 'a'){
      goHead();
      goDown();
    }
    else if(comando == 'd'){
      turnRight();
    }
    else if(comando == 'e'){
      turnLeft();
    }
    else if(comando == 'p'){
      stopCar();
      goHead();  
    }
  }
  else{
    digitalWrite(led, HIGH);  
  }
}

/*
int testaDistancia(){
  float cmMsec;
  long microsec = ultrasonic.timing();
  
  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  if(cmMsec >= safetyDistance)
    return 1;
  else
    return 0;
}
*/

void goUp(){
  analogWrite(chipEnable, 255);
  digitalWrite(Input1, LOW);
  digitalWrite(Input2, HIGH);
  //digitalWrite(chipEnable, HIGH);  
}

void goDown(){
  analogWrite(chipEnable, 255);
  digitalWrite(Input1, HIGH);
  digitalWrite(Input2, LOW);
  //analogWrite(chipEnable, HIGH);
}

void stopCar(){
  analogWrite(chipEnable, 0);
}

void goHead(){
  senseServo.write(120);
}

void turnLeft(){
  senseServo.write(105);  
}

void turnRight(){
  senseServo.write(135);  
}

/*
int testKey(int _key){
  if(_key = key)
    return 1;
  else
    return 0;
}
*/

