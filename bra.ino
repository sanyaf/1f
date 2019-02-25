#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
int TC_bragi = 10;
OneWire ds(10); 
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
unsigned long last_time;
  int a=0;
  float b=0;
  float c=0;
  float d=0;

void setup(void) {
   lcd.init();  // initialize the lcd
  lcd.backlight();
 Serial.begin(9600);
 }
 void loop(void) {
  
 
    
 byte i;
 byte present = 0; //переменные
 byte type_s;
 byte data[12];
 byte addr[8];
 float celsius, fahrenheit;
 
  if (millis() - last_time >= 10000) {
    last_time = millis();  d = b / a; d = round(d*10); c = d /10;
    
    Serial.print("C = "); 
    Serial.print(c);
    Serial.println();
    Serial.println(); 
    a = 0;  b = 0; 
    
    }  //
    
 if ( !ds.search(addr)) {
 ds.reset_search();
 delay(250);
 return;
 }
 Serial.print("ROM =");
 for( i = 0; i < 8; i++) {
 Serial.write(' ');
 Serial.print(addr[i], HEX);
 }
 Serial.println();
 switch (addr[0]) {
 case 0x10:
 Serial.println(" Chip = DS18S20"); // or old DS1820
 type_s = 1;
 break;
 case 0x28:
 Serial.println(" Chip = DS18B20");
 type_s = 0;
 break;
 case 0x22:
 Serial.println(" Chip = DS1822");
 type_s = 0;
 break;
 default:
 Serial.println("Не является устройством семейства DS18x20.");
 return;
 }
 ds.reset();         //обнуляем датчик
 ds.select(addr);    // выбираем датчик
 ds.write(0x44, 0); // посылаем команду датчику провести измерение температуры
                    // и записать данные в оперативную память старт преобразования с питанием от внешнего источника.
 delay(1000); // ждем конца преобразования.
 present = ds.reset();
 ds.select(addr);
 ds.write(0xBE); // Читаем память .
 Serial.print(" Data = ");
 Serial.print(present, BIN);
 Serial.print("                          ");
 for ( i = 0; i < 9; i++) { // нам нужно 9 байт
 data[i] = ds.read();
 Serial.print(data[i], BIN);
 Serial.print("__");
 }
 Serial.print("       CRC=");
 Serial.print(OneWire::crc8(data, 8), BIN);
 Serial.println();
 int16_t raw = (data[1] << 8) | data[0];  //надо разобраться со знаком "|" влияет на показания температуры
 if (type_s) {
 raw = raw << 3; // 9 бит разрешение по умолчанию у датчиков DS18S20 or old DS1820
 if (data[7] == 0x10) {
 // "количество остается" дает полное разрешение 12 бит
 raw = (raw & 0xFFF0) + 12 - data[6];
 }
 } else {
 byte cfg = (data[4] & 0x60);  //при удалении строки перем. "celsius" удаляется!
 // при более низком разрешении низкие биты не определены, поэтому давайте обнуляем их.
 //if (cfg == 0x00) raw = raw & ~7; // 9 bit resolution, 93.75 ms
// else if (cfg == 0x20) raw = raw & ~3; // 10 bit res, 187.5 ms
 //else if (cfg == 0x40) raw = raw & ~1; // 11 bit res, 375 ms
 // default is 12 bit resolution, 750 ms conversion time
 }
 celsius = (float)raw / 16.0;
 fahrenheit = celsius * 1.8 + 32.0;
 Serial.print(" Temperature = ");
 Serial.print(celsius);
 Serial.print(" Celsius, ");
 Serial.println();
 Serial.println();
 float TC_bragi = (celsius);
 
 Serial.print(" TC_bragi = ");
 Serial.print(TC_bragi);
 Serial.print(" ");
 Serial.println();
 Serial.println();
 Serial.println();
 
  lcd.setCursor(0, 0);
  lcd.print("TC_bragi = ");
  lcd.print(c);
  
  lcd.setCursor(0, 1);
  lcd.print("C = ");lcd.print(c);
  
  a++; b = b + TC_bragi;
 Serial.print(" a = ");
 Serial.print(a);
 Serial.print(" b = ");
 Serial.print(b);
   Serial.println();
   Serial.println();
 }
