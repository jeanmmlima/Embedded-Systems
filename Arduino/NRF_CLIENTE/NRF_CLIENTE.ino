#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>
#include <string.h>
String s = "Cliente: Jean, Consumo: ";
float litros = 400;
int tamanho;
void setup(){
   Serial.begin(9600);
    Mirf.spi = &MirfHardwareSpi;
    Mirf.csnPin = 10; //(This is optional to change the chip select pin)
    Mirf.cePin = 9; //(This is optional to change the enable pin)
    Mirf.init(); 
    Mirf.setTADDR((byte *)"serv1");
    Mirf.payload = 32;
    Mirf.config();
    Serial.println("Beginning ... "); // "Beginning ..." on sender, or "Listening ..." on sever (Receiver)
    
  }
 
  void loop(){
    s = s + (String)litros+"L/";
    tamanho = s.length();
    char a[tamanho];
    for(int i = 0; i < tamanho; i++){
      a[i] = s[i];
      }
    Mirf.send((byte *) a);
    delay(500);
}
