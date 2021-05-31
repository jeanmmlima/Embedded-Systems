#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

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
    byte data[90];
    /* byte data[32]; // or int data[32];
     *  
     if(!Mirf.isSending() && Mirf.dataReady()){
          Serial.println("Got packet");
          Mirf.getData((byte *) &data);
          Serial.write(byte(data[0])); //h
          Serial.write(byte(data[1])); //e
          Serial.write(byte(data[2])); //l
          Serial.write(byte(data[3])); //l
          Serial.write(byte(data[4])); //o
          Serial.println("");
     }*/
     if(!Mirf.isSending() && Mirf.dataReady()){
      Serial.println("Got packet");
     Mirf.getData(data);
      int i;
      
      for (i = 0; i < sizeof(data); i++)
      {
      //Serial.println(data[i]); 
      if(data[i] == '/'){i = sizeof(data);}
      Serial.write((byte) data[i]);
    }
    Serial.println("");
}
  }

