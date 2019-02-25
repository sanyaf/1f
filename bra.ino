#include <OneWire.h>

OneWire ds(8);                //class OneWire object ds

unsigned long last_time = 0;  //last read temperature
const int update_time= 1000;  //period update no delay
int t = 0;                    //global temperature

void setup() {
  Serial.begin(115200);
 }
 
 void loop() {
    readTemp();               //begin function every loop
    Serial.println(t);        //print console \n  
 }

//end loop/end file


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
    t = (data[1] << 8) + data[0]; 
    t = t >> 4;
  }
}
