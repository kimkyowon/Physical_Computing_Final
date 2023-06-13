#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MainMCU.h>
#include <Wire.h>

ModuleMain MyModuleMain;
LiquidCrystal_I2C lcd(LCD_I2C_ADDR,16,2);

String lat_str;
String lon_str;

// GetTick() for count time..
uint32_t time1 = 0;
uint32_t warning_time = 0;
// Flag for LCD
bool lcd_on = false;
bool lcd_current_show = false;
int lcd_show_data = 0;
enum {
  lcd_show_location_data,lcd_show_time
};

bool parsingdone = 0;
union{
  unsigned long l;
  byte c[4];
  float f;   
}londataformat;
volatile char inChar = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  while(!Serial){
    ;
  }
  Serial.println("Serial Init Complete!");
  lcd.init();
  lcd.backlight();
  delay(1000);
  lcd.clear();
}
bool a = 0;
void loop()
{
  if(lcd_on == true){
    lcd_on = false;
    _process_lcd();
  }
  serialEvent();
}

void _process_lcd(){
  if(lcd_show_data == lcd_show_location_data && lcd_current_show != lcd_show_location_data){ 
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("LAT:"+lat_str);
    lcd.setCursor(1,0);
    lcd.print("LON:"+lon_str);
    lcd_current_show = lcd_show_location_data;
  }
  else if(lcd_show_data == lcd_show_time && lcd_current_show != lcd_show_time){
    lcd.clear();
    lcd.setCursor(0,0);
    String timestr = String(warning_time); 
    lcd.print("Time:"+ timestr);
    lcd_current_show = lcd_show_time;
  }
}
void _getTime(){
  if(millis() - time1 >= 10000){
    switch(lcd_show_data){
      case lcd_show_location_data :
        lcd_show_data = lcd_show_time;
      case lcd_show_time :
        lcd_show_data = lcd_show_location_data;
    }
    time1 = millis();
  }
}
void serialEvent(){
  while(Serial1.available() >0){
    byte len = Serial1.readBytes(londataformat.c,4);
    Serial.println(len);
    Serial.println(londataformat.c[0],HEX);
    Serial.println(londataformat.c[1],HEX);
    Serial.println(londataformat.c[2],HEX);
    Serial.println(londataformat.c[3],HEX);
    Serial.println(londataformat.f,7);
    lcd_on = true;
  }
}
