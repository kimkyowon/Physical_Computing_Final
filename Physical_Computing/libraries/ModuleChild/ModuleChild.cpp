#include "Arduino.h"
#include <SoftwareSerial.h>
#include "ModuleChild.h"
#include "TinyGPS.h"


extern class TinyGPS gps;
extern class SoftwareSerial MySerial;

void Module_Child::check_gps_stat(){
    gps.stats(&this->_c_chars,&this->_c_sentences,&this->_c_failed_cs);
    if(this->_c_chars == 0) this->_gps_available = false;
    else this->_gps_available = true;
}

void Module_Child::update_position(){
    gps.f_get_position(&this->_c_lat,&this->_c_lon,&this->_c_age);
    MySerial.write("warning");
}
void Module_Child::is_dangerous_location(){
    if(this->_c_lat < _SAFETY_LAT_MIN && this->_c_lat >  _SAFETY_LAT_MAX && this->_c_lon < _SAFETY_LON_MIN && this->_c_lat > _SAFETY_LON_MAX) this->_location_status = CHILD_IN_DANGEROUS_LOCATION;
    else this->_location_status = CHILD_IN_SAFETY_LOCATION;
}
void Module_Child::led_process(){
    if(this->_location_status == CHILD_IN_DANGEROUS_LOCATION && this->_clear_dangerous == false){
        if(digitalRead(C_LED) == LOW) digitalWrite(C_LED,HIGH); 
    }
    else{
         if(digitalRead(C_LED) == HIGH) digitalWrite(C_LED,LOW); 
    }
}
void Module_Child::buzzer_process(){
    if(this->_location_status == CHILD_IN_DANGEROUS_LOCATION && this->_clear_dangerous == false)digitalWrite(C_Buzzer, HIGH);
}

void Module_Child::send_location_data(){
    MySerial.write(this->_location_status);
    MySerial.write("do complete!!");
}

void Module_Child::clear_waring_process(){
    if(this->ReadData == "Clear") this->_clear_dangerous = true;
}
