#include <Arduino.h>
#include <MainMCU.h>
#include <LiquidCrystal_I2C.h>

extern class ModuleMain MyModuleMain;
extern class LiquidCrystal_I2C lcd;

extern bool lcd_on;

void ModuleMain::receive_clear_signal(){
    if(digitalRead(_PIN_R_CLEAR_SIGNAL) == HIGH){
        digitalWrite(_PIN_T_CLEAR_SIGNAL,HIGH);
    }
}
void ModuleMain::receive_location_data(){

}
void ModuleMain::data_parsing(){
}


