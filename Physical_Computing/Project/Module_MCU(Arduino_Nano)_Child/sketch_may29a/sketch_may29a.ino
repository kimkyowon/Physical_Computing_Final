#include <ModuleChild.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>

SoftwareSerial GPSSerial(11,12,false); 
SoftwareSerial MySerial(0,1,false); 

Module_Child MyChildModule;
TinyGPS gps;

unsigned long time = 0;

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  GPSSerial.begin(9600);
  MySerial.begin(9600);
  pinMode(C_LED,OUTPUT);
  pinMode(C_Buzzer,OUTPUT);
  MyChildModule._get_valid_data = true;
}

void loop() {
  // put your main code here, to run repeatedly:
  MyChildModule.check_gps_stat(); // check gps module state every loop..

  if(GPSSerial.available() && MyChildModule._gps_available == true){
    if(millis() - time >= 1000){  // every 1s
      time = millis();
      char c = GPSSerial.read();
      if(gps.encode(c)) MyChildModule._get_valid_data = true;
    } 
  }

  if(MyChildModule._get_valid_data){
    MyChildModule._get_valid_data = false;
    MyChildModule.update_position();
    MyChildModule.is_dangerous_location();
    MyChildModule.send_location_data();
    MyChildModule.buzzer_process();
    MyChildModule.led_process();
  }
}

void serialEvent(){
  while(MySerial.available()){
    char ReadData = (char)Serial.read();
    inputString += ReadData;
    if(ReadData == '\n') stringComplete = true;
  }
}
