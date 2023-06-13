#include "Arduino.h"
#include <SoftwareSerial.h>
#include "ModuleChild.h"
#include "TinyGPS.h"

uint8_t ETX;
char buffer[50];
int cnt = 0;
extern class TinyGPS gps;
extern class SoftwareSerial MySerial;

void Module_Child::check_gps_stat(){
    gps.stats(&this->_c_chars,&this->_c_sentences,&this->_c_failed_cs);
    if(this->_c_chars == 0) this->_gps_available = false;
    else this->_gps_available = true;
}

void Module_Child::update_position(){
    gps.f_get_position(&this->_c_lat,&this->_c_lon,&this->_c_age);
    this->latdataformat.f = this->_c_lat;
    this->londataformat.f = this->_c_lon;
}
void Module_Child::is_dangerous_location(){
    if(this->_c_lat < _SAFETY_LAT_MIN && this->_c_lat >  _SAFETY_LAT_MAX && this->_c_lon < _SAFETY_LON_MIN && this->_c_lat > _SAFETY_LON_MAX) this->_location_status = CHILD_IN_DANGEROUS_LOCATION;
    else this->_location_status = CHILD_IN_SAFETY_LOCATION;
}
void Module_Child::led_process(){
    if(this->_location_status == CHILD_IN_DANGEROUS_LOCATION && this->_clear_dangerous == false){
        if(digitalRead(_PIN_LED) == LOW) digitalWrite(_PIN_LED,HIGH); 
        Serial.println("LED_OFF");
    }
    else{
         if(digitalRead(_PIN_LED) == HIGH) digitalWrite(_PIN_LED,LOW); 
         Serial.println("LED_OFF");
    }
}
void Module_Child::buzzer_process(){
    if(this->_location_status == CHILD_IN_DANGEROUS_LOCATION && this->_clear_dangerous == false){
        digitalWrite(_PIN_Buzzer, HIGH);
        Serial.println("buzzer_process");
    }
}

void Module_Child::send_location_data(){
    if(this->_location_status == CHILD_IN_DANGEROUS_LOCATION && this->_clear_dangerous == false){
        char packet = 0;
        MySerial.write(this->_location_status);
    }
}

void Module_Child::clear_waring_process(){
    if(digitalRead(_PIN_Read_Signal) == LOW){
        this->_clear_dangerous = true;
        //Serial.println("this->_clear_dangerous = true"); 
    }
}

