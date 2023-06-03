#ifndef ModuleTeacher_h
#define ModuleTeacher_h

#include "Arduino.h"
#include "TinyGPS.h"

#define C_LED 3
#define C_Buzzer 4

class Module_Teacher{
    public:
    enum{
        CHILD_IN_SAFETY_LOCATION,CHILD_IN_DANGEROUS_LOCATION
    };
    Module_Teacher();
    void readprocess();
    void sendproccess();
    void led_process();
    void buzzer_process();

    private:
    bool clear_signal;
    int led_step;
    int buzzer_step;  
    
};

class Child_Status{
    public:
    enum{
        SAFETY,WARNING
    };
    Child_Status();
    
    private:
    char _location_status;
};

#endif 