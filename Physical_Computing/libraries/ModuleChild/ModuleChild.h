#ifndef ModuleChild_h
#define ModuleChild_h

#include "Arduino.h"
#include "TinyGPS.h"

#define _SAFETY_LAT_MIN 10
#define _SAFETY_LAT_MAX 10

#define _SAFETY_LON_MIN 10
#define _SAFETY_LON_MAX 10

#define C_LED 3
#define C_Buzzer 4
#define C_Warning_Clear 5

class Module_Child{
public:
    enum{
        CHILD_IN_SAFETY_LOCATION,CHILD_IN_DANGEROUS_LOCATION
    };
    ModuleChild();  
    void check_gps_stat();
    void update_position();
    void is_dangerous_location();
    void led_process();
    void buzzer_process();
    void send_location_data();
    void clear_waring_process();
    bool _gps_available;
    bool _get_valid_data;

private:
    float _c_lat, _c_lon;       
    unsigned long _c_age;
    bool _led_status,_buzzer_status;
    int _location_status;

    unsigned long _c_chars;
    unsigned short _c_sentences;
    unsigned short _c_failed_cs;

    bool _clear_dangerous;
};

#endif