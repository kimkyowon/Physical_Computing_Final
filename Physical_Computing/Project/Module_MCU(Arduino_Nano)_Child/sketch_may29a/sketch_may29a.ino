#include <ModuleChild.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial GPSSerial(_PIN_GPS_Serial_TX,_PIN_GPS_Serial_RX); 
SoftwareSerial MySerial(_PIN_Serial_TX,_PIN_Serial_RX);
Module_Child MyChildModule;
TinyGPS gps;
ezOutput led1(_PIN_LED);

unsigned long time1 = 0;
unsigned long time = 0;
bool test_flag = 0;
String inputString = "";
bool stringComplete = false;

void setup() {
  // put your setup code here, to run once:
  MySerial.begin(9600);
  Serial.begin(9600);
  GPSSerial.begin(9600);
  pinMode(_PIN_LED,OUTPUT);
  pinMode(_PIN_Buzzer,OUTPUT);
  pinMode(_PIN_Read_Signal,INPUT);
  pinMode(_PIN_Send_Signal,OUTPUT);
  MyChildModule._get_valid_data = true;
}

void loop() {
  
  // put your main code here, to run repeatedly:
  MyChildModule.check_gps_stat(); // check gps module state every loop..

  // every 1s get gps data
  
  if(GPSSerial.available() && MyChildModule._gps_available == true){  
    if(millis() - time >= 1000){  
      time = millis();
      char c = GPSSerial.read();
      if(gps.encode(c)) MyChildModule._get_valid_data = true;
      if( MyChildModule._get_valid_data == true) Serial.println(" MyChildModule._get_valid_data true");
      else Serial.println(" MyChildModule._get_valid_data false");
    } 
  }
  //test code
  else{
    MyChildModule._get_valid_data = true;
  }

  if(MyChildModule._get_valid_data == true){
    MyChildModule._get_valid_data = false;
    //MyChildModule.update_position();
    MyChildModule.is_dangerous_location();
    MyChildModule.send_location_data();
    MyChildModule.buzzer_process();
    MyChildModule.led_process();
    MyChildModule.test();
  }
  MyChildModule.clear_waring_process();
  
}
