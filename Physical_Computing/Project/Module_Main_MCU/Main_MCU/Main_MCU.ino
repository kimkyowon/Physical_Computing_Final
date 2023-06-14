#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <MainMCU.h>
#include <Wire.h>

ModuleMain MyModuleMain;
LiquidCrystal_I2C lcd(LCD_I2C_ADDR,16,2);
String lat_str;
String lon_str;

// GetTick() for count time..
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long warning_time = 0;
// Flag for LCD
bool lcd_on = false;
enum {
  lcd_show_location_data,lcd_show_time
};
bool lcd_current_show = lcd_show_time;
int lcd_show_data = 0;

double lat1 = 37.200648;
double lat2 = 37.200664;

double lon1 = 127.071662;
double lon2 = 127.071830;

volatile char inChar = 0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(_PIN_R_CLEAR_SIGNAL,INPUT);
  pinMode(_PIN_R_WARNING_SIGNAL,INPUT);
  pinMode(_PIN_T_WARNING_SIGNAL,OUTPUT);
  pinMode(_PIN_T_CLEAR_SIGNAL,OUTPUT);
  
  
  Serial.println("Serial Init Complete!");
  lcd.init();
  lcd.backlight();
  delay(1000);
  lcd.clear();
}
bool a = 0;
void loop()
{
  if(millis()-time2 >= 1000){
    time2 = millis();
    if(lcd_on == true){
      lcd_on = false;
    _process_lcd();
    }
  } 
  MyModuleMain.receive_clear_signal();
  MyModuleMain.receive_location_data();
  //serialEvent();
  MyModuleMain.cal_warning_time();
  _switching_lcd();
  
}

void _process_lcd(){
  if(lcd_show_data == lcd_show_location_data){ 
    Serial.println("lcdDATA");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(lat1,7);
    lcd.setCursor(0,1);
    lcd.print(lon1,7);
  }
  else if(lcd_show_data == lcd_show_time){
    Serial.println("lcdTIME");
    lcd.clear();
    lcd.setCursor(0,0);
    String timestr = String(warning_time); 
    lcd.print("Time:"+ timestr);
    
  }
}
void _switching_lcd(){
  if(millis() - time1 >= 6000){
    Serial.print("lcd_current_show");
    Serial.println(lcd_show_data);
    switch(lcd_show_data){
      case lcd_show_location_data :
        lcd_show_data = lcd_show_time;
         break;
      case lcd_show_time :
        lcd_show_data = lcd_show_location_data;
        break;
    }
    time1 = millis();
  }
}
void serialEvent(){
  while(Serial1.available() >0){
    //byte len = Serial1.readBytes(londataformat.c,8);
    //Serial.println(len);
    /*
    Serial.println(londataformat.c[0],HEX);
    Serial.println(londataformat.c[1],HEX);
    Serial.println(londataformat.c[2],HEX);
    Serial.println(londataformat.c[3],HEX);
    */
    //Serial.println(londataformat.f,7);
    
    lcd_on = true;
  }
}
