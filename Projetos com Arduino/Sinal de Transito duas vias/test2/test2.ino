const int ledCount = 6;
int ledPins[] = {2,3,4,5,6,7};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < ledCount; i++){
    pinMode(ledPins[i],OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPins[4], LOW);
  digitalWrite(ledPins[2], HIGH);
  digitalWrite(ledPins[5], HIGH);
  
  delay(1000);
  
  digitalWrite(ledPins[2], LOW);
  digitalWrite(ledPins[0], HIGH);
  
  delay (5000);
  
  digitalWrite(ledPins[1], HIGH);
  digitalWrite(ledPins[0], LOW);
  
  delay(1000);
  
  digitalWrite(ledPins[1], LOW);
  digitalWrite(ledPins[2], HIGH);
  
  delay (1000);
  
  digitalWrite(ledPins[5], LOW);
  digitalWrite(ledPins[3], HIGH);
  
  delay(5000);
  
  digitalWrite(ledPins[3], LOW);
  digitalWrite(ledPins[4], HIGH);
  
  delay(1000);
  
  
  

}
