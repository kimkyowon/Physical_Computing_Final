#ifndef ModuleTeacher_h
#define ModuleTeacher_h

#include "Arduino.h"
#include <SoftwareSerial.h>
#include <ezOutput.h>

#define _PIN_WARNING_R 3    
#define _PIN_WARNING_W 4
#define _PIN_LED 5
#define _PIN_BUZZER_ON_OFF_SW 6
#define _PIN_WARNING_CLEAR_SW 7 //SWITCH
#define _PIN_BUZZER 8




class Module_Teacher{
    enum{
        Safety,Warning
    };
    public:
        void check_warning_signal();
        void check_warning_time();
        void process_led();
        void process_buzzer();
        void process_switch1();
        void process_switch2();
        
    private:
        bool _warning_state = 0;
        unsigned long _first_warning_time = 0;
        unsigned long _warning_time = 0;
        unsigned long _switch1_pushed_time = 0;
        unsigned long _switch2_pushed_time = 0;
        unsigned long _buzzer_tone_time = 0;
        
        bool _catch_time = 0;
        int _warning_step = 0;
        int _switch1_step = 0;
        int _switch2_step = 0;
        bool buzzer_off = 0;
        bool system_reset = 0;
};
   

#endif 