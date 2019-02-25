#include <OneWire.h>

OneWire ds(10);               //class OneWire object ds

unsigned long last_time = 0;  //last read temperature
const int update_time= 1000;  //period update no delay

float t = 0.0f;               //global temperature
byte data[9];                 //place for temperature

void setup() {
  Serial.begin(9600);
 }
 
 void loop() {
    readTemp();               //begin function every loop
    Serial.println(t,2);      //print console \n  
 }

//Function read temperature
void readTemp(){ 
  ds.write(0xCC);                             //no search address 
  if (millis() - last_time >= update_time){   //1 sec
    last_time = millis();                     //remember the time for the next loop
    
    for ( byte i = 0; i < 9; i++){
      data[i] = ds.read();  //read byte
    }
    int16_t raw = (data[1] << 8) | data[0];
    t = (float)raw/16.0;    //celsius
    
    ds.reset();     //reset
    ds.write(0x44); //begin measuring
    ds.write(0xBE); //give me the value temperature
  }
}
