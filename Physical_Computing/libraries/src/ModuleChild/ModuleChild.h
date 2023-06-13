#ifndef ModuleChild_h
#define ModuleChild_h

#include "Arduino.h"
#include "TinyGPS.h"


// Pin 
#define _PIN_GPS_Serial_TX 3
#define _PIN_GPS_Serial_RX 4
#define _PIN_LED 7          
#define _PIN_Buzzer 8 
#define _PIN_Read_Signal 9
#define _PIN_Send_Signal 10
#define _PIN_Serial_TX 11
#define _PIN_Serial_RX 12


// Range of warning zone
#define _SAFETY_LAT_MIN 10
#define _SAFETY_LAT_MAX -10

#define _SAFETY_LON_MIN 10
#define _SAFETY_LON_MAX -10


class Module_Child{
public:
    enum{
        CHILD_IN_SAFETY_LOCATION,CHILD_IN_DANGEROUS_LOCATION
    };
    //ModuleChild();  
    void check_gps_stat();
    void update_position();
    void is_dangerous_location();
    void led_process();
    void buzzer_process();
    void send_location_data();
    void clear_waring_process();
    void parsing_data();
    bool _gps_available;
    bool _get_valid_data;
    
    char ReadData;

private:
    float _c_lat, _c_lon;       
    unsigned long _c_age;
    bool _led_status,_buzzer_status;
    int _location_status;

    unsigned long _c_chars;
    unsigned short _c_sentences;
    unsigned short _c_failed_cs;
    
    bool _clear_dangerous;

    union{
        unsigned long l;
        byte c[4];
        float f;   
    }latdataformat;
    union{
        unsigned long l;
        byte c[4];
        float f;   
    }londataformat;
};

#endif