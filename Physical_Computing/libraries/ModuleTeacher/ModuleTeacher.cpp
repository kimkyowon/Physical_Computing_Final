#include "Arduino.h"
#include <SoftwareSerial.h>
#include "ModuleTeacher.h"
#include "TinyGPS.h"

extern class SoftwareSerial MySerial;
extern class Child_Status MyChild1Status;

void Module_Teacher::readprocess(){
    if(this->_ReadData == "warning") {
        this->_buzzer_step = b;
        this->_led_step = led_warning;
        if(this->clear_signal == true) this->clear_signal = false;
    }
    else if(this->_ReadData == "safe"){
        this->_buzzer_step = a;
        this->_led_step = led_idle;
        if(this->clear_signal == false) this->clear_signal = true;
    } 
}   
void Module_Teacher::sendproccess(){
    if(this->clear_signal == false) MySerial.write("clear");
}
void Module_Teacher::led_process(){
    switch(this->_led_step){
        case led_idle:
        digitalWrite(C_Buzzer, HIGH);
        case led_warning:
        digitalWrite(C_Buzzer, HIGH);
        case:
        case:
    }
}
void Module_Teacher::buzzer_process(){

}
