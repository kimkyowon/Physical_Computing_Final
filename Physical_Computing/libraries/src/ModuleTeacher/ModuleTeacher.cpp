#include "ModuleTeacher.h"
extern class ezOutput led1;
void Module_Teacher::check_warning_signal(){
    if(digitalRead(_PIN_WARNING_R) == HIGH){
        this->_warning_state = this->Warning;
        if(this->_catch_time == false){
            _first_warning_time = millis();
            this->_catch_time = true;
        }
    }
    else{
        if(this->_warning_state = this->Warning){
            /*
            Serial.println("Catch Clear signal.. Reset..");
            this->_warning_state = this->Safety;
            this->_first_warning_time = 0;
            this->_warning_time = 0;
            this->_switch_pushed_time = 0;
            this->_catch_time = 0;
            this->_warning_step = 0;
            this->_switch_step = 0;
            */
        }
    }  
}

void Module_Teacher::check_warning_time(){
    if(this->_warning_state == this->Warning){
        this->_warning_time = millis() - this->_first_warning_time;
        if(this->_warning_time >= 300000){
            this->_warning_step += 1;
            this->_first_warning_time = this->_warning_time;
        }
    }
}

void Module_Teacher::process_led(){
    switch(this->_warning_step){
        case 0:
            led1.blink(1000,1000);
            //Serial.println(digitalRead(_PIN_LED));  
            break;
        case 1:
            led1.blink(500,500);     
            break;
        default:
            led1.blink(200,200);
            break;
    }

}
void Module_Teacher::process_buzzer(){
    if(this->buzzer_off == false){
        switch(this->_warning_step){
            case 0:
                tone(_PIN_BUZZER,131);
                //Serial.print("Buzzer State : ");
                //Serial.println(digitalRead(_PIN_BUZZER));
                break;
            case 1:
                tone(_PIN_BUZZER,200);
                break;
            default:
                break;
        }
    }
}
void Module_Teacher::process_switch1(){
    switch(this->_switch1_step){
        case 0:
            if(digitalRead(_PIN_WARNING_CLEAR_SW) == LOW){
                //Serial.println("Catch SW PUSHED!");
                this->_switch1_pushed_time++;
                if(this->_switch1_pushed_time >= 15000){
                    this->_switch1_step = 1;
                }   
            }
            else if(this->_switch1_pushed_time >= 200 && this->_switch1_pushed_time < 15000){
                Serial.print("PushSW1 Time is not enough :");
                Serial.println(this->_switch1_pushed_time);
                this->_switch1_pushed_time = 0;
            }
            else{
                this->_switch1_pushed_time = 0;
            }
            break;
        case 1:
            if(digitalRead(_PIN_WARNING_CLEAR_SW) == HIGH){
                Serial.println("Check SW1 Clear SW !!");
                digitalWrite(_PIN_WARNING_W,HIGH);
                this->_switch1_pushed_time = 0;
                this->_switch1_step = 0;
            }
            break;
    }
}

void Module_Teacher::process_switch2(){
    switch(this->_switch2_step){
        case 0:
            if(digitalRead(_PIN_BUZZER_ON_OFF_SW) == LOW){
                this->_switch2_pushed_time++;
                if(this->_switch2_pushed_time >= 15000){
                    this->_switch2_step = 1;
                }  
            }
            else if(this->_switch2_pushed_time >= 200 && this->_switch2_pushed_time < 15000){
                Serial.print("PushSW2 Time is not enough :");
                Serial.println(this->_switch2_pushed_time);
                this->_switch2_pushed_time = 0;
            }
            else{
                this->_switch2_pushed_time = 0;
            }
            break;
        case 1:
            if(digitalRead(_PIN_BUZZER_ON_OFF_SW) == HIGH){
                Serial.println("Check SW2 Clear SW !!");
                if(this->buzzer_off == false) {
                    this->buzzer_off = true;
                    noTone(_PIN_BUZZER);
                }
                else this->buzzer_off = false;
                this->_switch2_pushed_time = 0;
                this->_switch2_step = 0;
            }
            break;
    }
}



