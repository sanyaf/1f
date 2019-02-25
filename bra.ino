#include <OneWire.h>

OneWire ds(10);                //class OneWire object ds

unsigned long last_time = 0;  //last read temperature
const int update_time= 1000;  //period update no delay
float t = 0.0f;                    //global temperature

void setup() {
  Serial.begin(9600);
 }
 
 void loop() {
    readTemp();               //begin function every loop
    Serial.println(t,2);      //print console \n  
 }

//end loop


//Function read temperature
int readTemp(){ 
  byte data[2];   //place for temperature
  ds.reset();     //reset
  ds.write(0xCC); //no search address only one DS18b20
  ds.write(0x44); //begin measuring

  if (millis() - last_time >= update_time){   //1 sec
    last_time = millis();                     //remember the time for the next loop
    
    ds.reset();     //reset
    ds.write(0xCC); //no search address 
    ds.write(0xBE); //give me the value temperature
    
    data[0] = ds.read();  //read low byte
    data[1] = ds.read();  //read high byte
    
  // Convert the data to actual temperature
  // because the result is a 16 bit signed integer, it should
  // be stored to an "int16_t" type, which is always 16 bits
  // even when compiled on a 32 bit processor.
  
    int16_t raw = (data[1] << 8) | data[0]; 
    raw = raw << 3;       // 9 bit resolution default
    t = (float)raw/16.0;    //celsius
  }
}
